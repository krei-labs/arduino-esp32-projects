#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <ArduinoJson.h>

// PINS
#define DHT_PIN 4
#define MQ135_PIN 33
#define LDR_PIN 34
#define SOIL_PIN 35
#define RELAY_PUMP 25
#define RELAY_FAN 26
#define LED_PIN 27

const char* ssid = "ENV_HUB";
const char* password = "CHANGE_ME_123";
float SOIL_DRY = 20.0;
float SOIL_WET = 70.0;
int AIR_QUALITY_HIGH = 1000;
int LIGHT_DARK = 2500;
int LIGHT_BRIGHT = 2500;
unsigned long WET_PUMP_OFF_DELAY = 2500;  // EDITABLE: 2.5s delay when wet

bool autoMode = false;
bool pumpManual = false, fanManual = false, ledManual = false;
bool pumpState = false, fanState = false, ledState = false;
unsigned long lastPumpTime = 0, lastRead = 0;
unsigned long pumpStartTime = 0;
unsigned long lastPumpCheck = 0;
unsigned long wetPumpOffTime = 0;
unsigned long startTime = 0;

struct LogEntry {
  float soil, temp, aq;
  int light;
  unsigned long uptime;
};
LogEntry logs[50];
int logCount = 0;
unsigned long lastLogTime = 0;

DHT dht(DHT_PIN, DHT11);
LiquidCrystal_I2C lcd(0x27, 16, 4);
WebServer server(80);

struct Data { float t,h,s,aq; int l; bool m,p,f,e; } sensors;

void setup() {
  Serial.begin(115200);
  startTime = millis();

  pinMode(RELAY_PUMP, OUTPUT); digitalWrite(RELAY_PUMP, 1);
  pinMode(RELAY_FAN, OUTPUT); digitalWrite(RELAY_FAN, 1);
  pinMode(LED_PIN, OUTPUT); digitalWrite(LED_PIN, 0);

  lcd.init(); lcd.backlight();
  dht.begin();
  EEPROM.begin(512);
  autoMode = EEPROM.read(0);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/data", HTTP_GET, handleData);
  server.on("/logs", HTTP_GET, handleLogs);
  server.on("/control", HTTP_GET, handleControl);
  server.on("/auto", HTTP_GET, handleAuto);
  server.begin();

  Serial.println("ENV Hub - 192.168.4.1 - PERFECT!");
  Serial.println("Wet pump off delay: " + String(WET_PUMP_OFF_DELAY) + "ms");
}

void loop() {
  server.handleClient();
  unsigned long now = millis();

  if (now - lastRead > 800) {
    readSensors();
    updateDevices(now);
    updateLCD();
    logData(now);
    lastRead = now;
  }
  yield();
}

void readSensors() {
  sensors.t = dht.readTemperature();
  sensors.h = dht.readHumidity();
  if (isnan(sensors.t)) sensors.t = 0.0;
  if (isnan(sensors.h)) sensors.h = 0.0;

  sensors.aq = analogRead(MQ135_PIN) / 4.0;
  int soilRaw = analogRead(SOIL_PIN);
  sensors.s = constrain(100.0 - (soilRaw / 40.95), 0.0, 100.0);
  sensors.l = analogRead(LDR_PIN);

  sensors.p = pumpState;
  sensors.f = fanState;
  sensors.e = ledState;
  sensors.m = autoMode;
}

void updateDevices(unsigned long now) {
  // *** FIXED INSTANT PUMP LOGIC ***
  if (pumpManual) {
    digitalWrite(RELAY_PUMP, pumpState ? 0 : 1);
  } else if (autoMode) {
    // INSTANT DRY DETECTION → PUMP ON (no delay)
    if (sensors.s < SOIL_DRY && !pumpState && (now - lastPumpTime > 60000)) {
      pumpState = true;
      pumpStartTime = now;
      digitalWrite(RELAY_PUMP, 0);
      wetPumpOffTime = 0;
      Serial.println("*** PUMP ON INSTANT - Dry: " + String(sensors.s,1) + "% ***");
    }
    
    // WET DETECTION → 2.5s DELAY → OFF
    if (sensors.s > SOIL_WET && pumpState) {
      if (wetPumpOffTime == 0) {
        wetPumpOffTime = now;
        Serial.println("PUMP - Wet soil " + String(sensors.s,1) + "% - " + String(WET_PUMP_OFF_DELAY) + "ms delay START");
      } else if (now - wetPumpOffTime >= WET_PUMP_OFF_DELAY) {
        pumpState = false;
        digitalWrite(RELAY_PUMP, 1);
        lastPumpTime = now;
        Serial.println("*** PUMP OFF - Wet after delay: " + String(sensors.s,1) + "% ***");
        wetPumpOffTime = 0;
      }
    } else if (sensors.s <= SOIL_WET) {
      wetPumpOffTime = 0; // Reset delay timer
    }
    
    // 3s MAX RUNTIME
    if (pumpState && (now - pumpStartTime > 3000)) {
      pumpState = false;
      digitalWrite(RELAY_PUMP, 1);
      lastPumpTime = now;
      wetPumpOffTime = 0;
      Serial.println("*** PUMP OFF - 3s max runtime ***");
    }
  } else {
    if (!pumpManual && pumpState) {
      pumpState = false;
      digitalWrite(RELAY_PUMP, 1);
      wetPumpOffTime = 0;
    }
  }

  // FAN
  if (!fanManual && autoMode) {
    fanState = (sensors.aq > AIR_QUALITY_HIGH);
  }
  digitalWrite(RELAY_FAN, fanState ? 0 : 1);

  // LED
  if (!ledManual && autoMode) {
    if (sensors.l > LIGHT_DARK && !ledState) {
      ledState = true;
      digitalWrite(LED_PIN, 1);
      Serial.println("*** LED ON - DARK: " + String(sensors.l));
    } else if (sensors.l < LIGHT_BRIGHT && ledState) {
      ledState = false;
      digitalWrite(LED_PIN, 0);
      Serial.println("*** LED OFF - BRIGHT: " + String(sensors.l));
    }
  }
}

void logData(unsigned long now) {
  if (now - lastLogTime > 30000) {
    unsigned long uptime = (now - startTime) / 1000;
    int writeIndex = logCount % 50;
    logs[writeIndex] = {sensors.s, sensors.t, sensors.aq, sensors.l, uptime};
    logCount++;
    lastLogTime = now;
    Serial.println("LOG #" + String(logCount) + " Uptime:" + String(uptime) + "s S:" + 
                   String(sensors.s,1) + " T:" + String(sensors.t,1) + " AQ:" + String(sensors.aq,0));
  }
}

void updateLCD() {
  static unsigned long lcdTime = 0;
  if (millis() - lcdTime < 1500) return;

  lcd.clear();
  lcd.setCursor(0,0); lcd.print("T:"); lcd.print(sensors.t,0); lcd.print("C H:"); lcd.print(sensors.h,0);
  lcd.setCursor(0,1); lcd.print("S:"); lcd.print(sensors.s,0); lcd.print(" AQ:"); lcd.print(sensors.aq,0);
  lcd.setCursor(0,2); lcd.print("L:"); lcd.print(sensors.l/10,0); lcd.print(autoMode?"AUTO":"MAN");
  lcd.setCursor(0,3); lcd.print(pumpState?"P1 ":"P0 "); lcd.print(fanState?"F1 ":"F0 "); lcd.print(ledState?"E1":"E0");
  lcdTime = millis();
}

String getJSON() {
  DynamicJsonDocument doc(300);
  doc["t"] = sensors.t;
  doc["h"] = sensors.h;
  doc["s"] = sensors.s;
  doc["aq"] = sensors.aq;
  doc["l"] = sensors.l;
  doc["m"] = autoMode;
  doc["p"] = pumpState;
  doc["f"] = fanState;
  doc["e"] = ledState;
  String json; serializeJson(doc, json); return json;
}

void handleData() {
  server.send(200, "application/json", getJSON());
}

void handleLogs() {
  DynamicJsonDocument doc(2048);
  JsonArray logArray = doc.createNestedArray("logs");
  
  int recentCount = min(20, logCount);
  for (int i = 0; i < recentCount; i++) {
    int idx = ((logCount - 1 - i) % 50 + 50) % 50;
    JsonObject entry = logArray.createNestedObject();
    entry["s"] = logs[idx].soil;
    entry["t"] = logs[idx].temp;
    entry["aq"] = logs[idx].aq;
    entry["l"] = logs[idx].light;
    entry["uptime"] = logs[idx].uptime;
  }
  String json; serializeJson(doc, json);
  server.send(200, "application/json", json);
}

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>Environmental Hub</title>
<meta name=viewport content="width=device-width, initial-scale=1">
<meta charset="UTF-8">
<style>
*{margin:0;padding:0;box-sizing:border-box}
body{font-family:-apple-system,BlinkMacSystemFont,'Segoe UI',Arial,sans-serif;background:#000;color:#0f0;padding:12px;font-size:14px;line-height:1.4}
.container{max-width:500px;margin:0 auto}
.sensors{background:#111;border:1px solid #0f0;border-radius:12px;padding:20px;margin:12px 0}
.sensor{font-size:16px;margin:12px 0;display:flex;align-items:baseline;gap:12px}
.label{flex:1;font-weight:500}
.value{font-size:22px;font-weight:900;color:#0f0;text-align:right;flex-shrink:0;width:90px}
.controls{background:#111;border:1px solid #0f0;border-radius:12px;padding:20px;margin:12px 0}
.btn{width:100%;background:#0066cc;color:#fff;border:none;padding:16px;border-radius:10px;cursor:pointer;font-size:16px;font-weight:900;margin:8px 0;transition:all 0.2s}
.btn.on{background:#0f0;box-shadow:0 0 20px #0f0}
.btn.off{background:#c00;box-shadow:0 0 10px #c00}
.btn:hover{transform:scale(1.02)}
.status{padding:16px;background:#0f0;color:#000;border-radius:12px;margin:12px 0;font-weight:900;text-align:center;font-size:16px}
.logs{background:#111;border:1px solid #0f0;border-radius:12px;padding:16px;margin:12px 0;max-height:240px;overflow:auto}
.log-entry{font-size:12px;margin:5px 0;color:#ccc;font-family:monospace;border-bottom:1px solid #333;padding:6px 0}
h1{text-align:center;color:#0f0;font-size:24px;margin:20px 0;font-weight:900;text-shadow:0 0 10px #0f0}
h2{color:#0f0;margin:0 0 16px 0;font-size:16px}
@media(max-width:500px){.value{font-size:20px;width:85px}}
</style>
</head>
<body>
<div class=container>
<h1>Environmental Hub</h1>
<div class=sensors>
<h2>Sensors (Live)</h2>
<div class=sensor><span class=label>Temperature</span><span class=value id=t>0.0</span></div>
<div class=sensor><span class=label>Humidity</span><span class=value id=h>0.0</span></div>
<div class=sensor><span class=label>Air Quality</span><span class=value id=aq>0.0</span></div>
<div class=sensor><span class=label>Soil Moisture</span><span class=value id=s>0.0</span></div>
<div class=sensor><span class=label>Light (LDR)</span><span class=value id=l>0</span></div>
</div>
<div class=status id=mode>LOADING...</div>
<div class=controls>
<h2>Controls</h2>
<button class=btn id=autoBtn onclick=toggleAuto()>AUTO MODE</button>
<button class="btn off" id=pumpBtn onclick=togglePump()>WATER PUMP</button>
<button class="btn off" id=fanBtn onclick=toggleFan()>FAN</button>
<button class="btn off" id=ledBtn onclick=toggleLed()>LED LIGHT</button>
</div>
<div class=logs>
<h2>Recent Logs (Uptime + Sensors)</h2>
<div id=logList>Loading...</div>
</div>
</div>
<script>
function updateAll(){
fetch('/data').then(r=>r.json()).then(d=>{
document.getElementById('t').textContent=d.t.toFixed(1)+'°C';
document.getElementById('h').textContent=d.h.toFixed(1)+'%';
document.getElementById('aq').textContent=d.aq.toFixed(1)+'PPM';
document.getElementById('s').textContent=d.s.toFixed(1)+'%';
document.getElementById('l').textContent=d.l;
let mode=document.getElementById('mode');
mode.textContent=d.m?'AUTO ACTIVE':'MANUAL MODE';
mode.style.background=d.m?'#0f0':'#c00';
updateBtn('autoBtn',d.m);updateBtn('pumpBtn',d.p);updateBtn('fanBtn',d.f);updateBtn('ledBtn',d.e);
});
fetch('/logs').then(r=>r.json()).then(d=>{
let html='';
d.logs.slice().reverse().forEach(entry=>{
let uptimeMin = Math.floor(entry.uptime / 60);
let uptimeSec = entry.uptime % 60;
let timeStr = uptimeMin + 'm' + uptimeSec.toString().padStart(2,'0') + 's';
html+=`<div class=log-entry>${timeStr} S:${entry.s.toFixed(1)}% T:${entry.t.toFixed(1)}°C AQ:${entry.aq.toFixed(0)} L:${entry.l}</div>`;
});
document.getElementById('logList').innerHTML=html||'No logs yet';
});
}
function updateBtn(id,isOn){let btn=document.getElementById(id);btn.classList.toggle('on',isOn);btn.classList.toggle('off',!isOn);}
function toggleAuto(){fetch('/auto?mode='+(document.getElementById('autoBtn').classList.contains('on')?'off':'on')).then(()=>updateAll());}
function togglePump(){fetch('/control?pump='+(document.getElementById('pumpBtn').classList.contains('on')?'off':'on')).then(()=>updateAll());}
function toggleFan(){fetch('/control?fan='+(document.getElementById('fanBtn').classList.contains('on')?'off':'on')).then(()=>updateAll());}
function toggleLed(){fetch('/control?led='+(document.getElementById('ledBtn').classList.contains('on')?'off':'on')).then(()=>updateAll());}
setInterval(updateAll,2000);updateAll();
</script>
</body>
</html>
)rawliteral";
  server.send(200, "text/html", html);
}

void handleControl() {
  unsigned long now = millis();
  if (server.hasArg("pump")) {
    pumpManual = true;
    pumpState = !pumpState;
    digitalWrite(RELAY_PUMP, pumpState ? 0 : 1);
    if (pumpState) {
      pumpStartTime = now;
      wetPumpOffTime = 0;
    }
    Serial.println("PUMP MANUAL: " + String(pumpState ? "ON" : "OFF"));
  }
  if (server.hasArg("fan")) {
    fanManual = true;
    fanState = !fanState;
    digitalWrite(RELAY_FAN, fanState ? 0 : 1);
    Serial.println("FAN MANUAL: " + String(fanState ? "ON" : "OFF"));
  }
  if (server.hasArg("led")) {
    ledManual = true;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? 1 : 0);
    Serial.println("LED MANUAL: " + String(ledState ? "ON" : "OFF"));
  }
  server.send(200, "text/plain", "OK");
}

void handleAuto() {
  autoMode = server.arg("mode") == "on";
  if (autoMode) {
    pumpManual = fanManual = ledManual = false;
  }
  EEPROM.write(0, autoMode);
  EEPROM.commit();
  Serial.println("AUTO MODE: " + String(autoMode ? "ON" : "OFF"));
  server.send(200, "text/plain", "OK");
}