#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Servo.h>

#define IR_PIN 2            // IR Sensor for Entry
#define TRIG_PIN 4          // Ultrasonic Trigger
#define ECHO_PIN 5          // Ultrasonic Echo
#define DHT_PIN 6           // DHT11 Data Pin
#define BUTTON_PIN 7        // Button to Mute/Stop Alarm (PULLUP used)
#define SERVO_PIN 9         // Servo Motor for Door
#define BUZZER_PIN 10       // Passive/Active Buzzer  
#define LED_GREEN 11        // Green LED
#define LED_RED 12          // Red LED

// --- HARDWARE CONFIGURATION ---
#define DHT_TYPE DHT11
#define I2C_ADDRESS 0x27
#define LCD_COLS 16
#define LCD_ROWS 4

// --- TIMING & LOGIC CONSTANTS ---
const int MAX_PEOPLE = 5;
// Door open time (3 seconds)
const unsigned long DOOR_HOLD_MS = 3000; 
// Debounce/Sensing delay for IR and Ultrasonic
const unsigned long SENSOR_DELAY_MS = 1000; 
// Wait time after an entry before ultrasonic exit checks resume
const unsigned long ULTRASONIC_QUIET_MS = 2000; 
const unsigned long FULL_WARNING_BLINK_MS = 300;
// Interval to update Temp/Hum on LCD
const unsigned long LCD_REFRESH_MS = 2000; 
// Distance threshold for exit
const unsigned long DISTANCE_LIMIT_CM = 20;

// --- OBJECT INSTANTIATION ---
LiquidCrystal_I2C lcd(I2C_ADDRESS, LCD_COLS, LCD_ROWS);
DHT dht(DHT_PIN, DHT_TYPE);
Servo door;

// --- DOOR STATE MANAGEMENT ---
// Enum to clearly define the door's operation state
enum DoorState { CLOSED, ENTRY_OPENING, EXIT_OPENING, OPEN, CLOSING };
DoorState currentDoorState = CLOSED;

// --- STATE VARIABLES AND TIMERS (Non-Blocking) ---
int peopleCount = 0;
bool alarmActive = false;
bool alarmMuted = false;
bool blinkState = false; // Tracks the ON/OFF state for the blinking alarm

// Timers for non-blocking control
unsigned long sensorDebounceTimer = 0; // Tracks last sensor trigger (IR/Ultrasonic)
unsigned long doorActionTimer = 0;     // Tracks when the door should close
unsigned long blinkTimer = 0;          // Tracks LED/Buzzer blink interval
unsigned long lcdUpdateTimer = 0;      // Tracks LCD update interval
unsigned long ultrasonicQuietTimer = 0; // Tracks time since last door action

float currentTemp = 0;
float currentHum = 0;

// --- FUNCTION PROTOTYPES ---
void handleDoorState();
void triggerDoor(DoorState action);
void checkIRSensor();
void checkUltrasonicSensor();
float measureDistance();
void triggerFullAlarm();
void stopAlarm();
void handleAlarmBlink();
void updateLCD();
void readDHTSensor();

void setup() {
  Serial.begin(9600);


q  pinMode(IR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); 
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // Initialize Servo (Closed position)
  door.attach(SERVO_PIN);
  door.write(0); // Ensure door is closed immediately

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  // Initial display setup for clarity
  lcd.print(" SMART ROOM SYSTEM"); 
  lcd.setCursor(0,1);
  lcd.print(" T:--C H:--% ");
  lcd.setCursor(0,2);
  lcd.print(" Ppl: -/5       ");
  lcd.setCursor(0,3);
  lcd.print(" STATUS: INIT... ");
  delay(1000); 
  
  // Initial DHT read to populate display
  readDHTSensor();
  updateLCD();
}

void loop() {
  unsigned long currentTime = millis();

  // 1. Check Button for Alarm Mute/Stop (Always responsive)
  if (digitalRead(BUTTON_PIN) == LOW && alarmActive) {
    stopAlarm();
    // Simple debounce check, but mainly handles the button press logic
    while(digitalRead(BUTTON_PIN) == LOW); 
  }

  // 2. Continuous Sensor Checks (Only check if door is closed)
  if (currentDoorState == CLOSED) {
    checkIRSensor();
    checkUltrasonicSensor();
  }

  // 3. Handle Door Movement and Timing
  handleDoorState();

  // 4. Handle Alarm Visuals and Sound
  handleAlarmBlink();

  // 5. Update Ambient Data (Temp/Hum) Periodically
  if (currentTime - lcdUpdateTimer >= LCD_REFRESH_MS) {
    readDHTSensor();
    updateLCD();
  }
}

// ------------------- Sensor Reading Functions -------------------

// Reads the DHT sensor data
void readDHTSensor() {
  currentTemp = dht.readTemperature();
  currentHum = dht.readHumidity();
  // Simple error handling
  if (isnan(currentTemp)) currentTemp = 0;
  if (isnan(currentHum)) currentHum = 0;
}

// Checks IR Sensor (Entry)
void checkIRSensor() {
  if (digitalRead(IR_PIN) == LOW && millis() - sensorDebounceTimer > SENSOR_DELAY_MS) {
    sensorDebounceTimer = millis();
    
    if (peopleCount < MAX_PEOPLE) {
      peopleCount++;
      triggerDoor(ENTRY_OPENING);
      // If we grant entry, stop any residual alarm
      if (alarmActive) stopAlarm(); 
    } else {
      // Room is full, attempted entry
      triggerFullAlarm();
    }
  }
}

// Checks Ultrasonic Sensor (Exit)
void checkUltrasonicSensor() {
  // Only check if enough time has passed since any door action
  if (millis() - ultrasonicQuietTimer < ULTRASONIC_QUIET_MS) {
    return;
  }
  
  float distance = measureDistance();
  
  // Valid distance and person is close
  if (distance > 0 && distance < DISTANCE_LIMIT_CM && millis() - sensorDebounceTimer > SENSOR_DELAY_MS) {
    sensorDebounceTimer = millis();

    if (peopleCount > 0) {
      peopleCount--;
      triggerDoor(EXIT_OPENING);
    }
  }
}

// Measures distance using the ultrasonic sensor
float measureDistance() {
  // Send pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Read echo
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); 
  float distance = duration * 0.034 / 2;
  
  // Return -1 for invalid readings
  if (duration == 0 || distance > 400) return -1;
  return distance;
}

// ------------------- Door and State Functions -------------------

// Initiates a door action and resets timers
void triggerDoor(DoorState action) {
  if (currentDoorState == CLOSED) {
    currentDoorState = action;
    door.write(0); // Open the door
    doorActionTimer = millis(); // Start the 3-second hold timer
    ultrasonicQuietTimer = millis(); // Start the quiet period timer

    // Only update door LEDs and the LCD status line (via updateLCD)
    if (action == ENTRY_OPENING) {
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_RED, LOW);
    } else { // EXIT_OPENING
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_RED, HIGH);
    }
    // Force a display refresh to show the new door state immediately
    updateLCD(); 
  }
}

// Non-blocking handler for door state transitions
void handleDoorState() {
  unsigned long currentTime = millis();

  switch (currentDoorState) {
    case ENTRY_OPENING:
    case EXIT_OPENING:
      // Door is physically open
      if (currentTime - doorActionTimer >= 500) { // Give it a short time to open
        currentDoorState = OPEN;
        updateLCD(); // Update LCD to show OPEN
      }
      break;
      
    case OPEN:
      // Hold door open for 3 seconds (DOOR_HOLD_MS)
      if (currentTime - doorActionTimer >= DOOR_HOLD_MS) {
        currentDoorState = CLOSING;
        door.write(90); // Close the door
        updateLCD(); // Update LCD to show CLOSING
      }
      break;
      
    case CLOSING:
      // Give the servo time to close (e.g., 500ms)
      if (currentTime - doorActionTimer >= DOOR_HOLD_MS + 500) {
        currentDoorState = CLOSED;
        // Turn off door LEDs
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_RED, LOW);
        // Update LCD immediately to show final count and status
        updateLCD(); 
      }
      break;
      
    case CLOSED:
      // Do nothing, wait for sensor input
      break;
  }
}

// ------------------- Alarm Functions -------------------

// Initiates the room full alarm sequence
void triggerFullAlarm() {
  if (!alarmActive) {
    alarmActive = true;
    alarmMuted = false;
    // Update LCD immediately to show the ALERT status
    updateLCD(); 
    // Ensure the alarm starts blinking immediately
    blinkTimer = 0; 
  }
}

// Stops the alarm and clears the warning state
void stopAlarm() {
  if (alarmActive) {
    alarmActive = false;
    alarmMuted = true;
    noTone(BUZZER_PIN);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    
    // Force immediate LCD update to clear notification and revert to normal status
    updateLCD(); 
  }
}

// Non-blocking handler for blinking LEDs and pulsed buzzer
void handleAlarmBlink() {
  if (alarmActive && !alarmMuted) {
    if (millis() - blinkTimer >= FULL_WARNING_BLINK_MS) {
      blinkTimer = millis();
      // This line now correctly toggles the globally declared blinkState
      blinkState = !blinkState; 
      
      // Flash R/G LEDs and Buzzer pulse
      if (blinkState) {
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_RED, LOW);
        tone(BUZZER_PIN, 1000); 
      } else {
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_RED, HIGH);
        noTone(BUZZER_PIN);
      }
    }
  } else {
    // Ensure buzzer is off if alarm is not active or muted
    noTone(BUZZER_PIN);
  }
}

// ------------------- Display Functions -------------------

// Updates the 4-line LCD display with current system stats
void updateLCD() {
  // Reset timer for next periodic update
  lcdUpdateTimer = millis();
  
  // Line 0: Title and Header (Fixed)
  lcd.setCursor(0,0);
  lcd.print("SMART ROOM SYSTEM");

  // Line 1: Temp and Humidity (Data)
  lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.print(currentTemp, 1); // 1 decimal place for Temp
  lcd.print("C H:");
  lcd.print(currentHum, 0); // 0 decimal place for Hum
  lcd.print("%          "); // Pad to clear the line

  // Line 2: People Count (Data)
  lcd.setCursor(0,2);
  lcd.print("Ppl:");
  lcd.print(peopleCount);
  lcd.print("/");
  lcd.print(MAX_PEOPLE);
  lcd.print(" Max         "); // Pad to clear the line

  // Line 3: Dynamic Status (State Machine/Alarm)
  lcd.setCursor(0,3);
  
  if (alarmActive) {
    lcd.print("STATUS: **ALERT!**"); // 16 chars
  } else {
    switch(currentDoorState) {
      case CLOSED:
        if (peopleCount >= MAX_PEOPLE) {
          lcd.print("STATUS: ROOM FULL "); // 16 chars
        } else {
          lcd.print("STATUS: OK/READY  "); // 16 chars
        }
        break;
      case ENTRY_OPENING:
        lcd.print("DOOR: ENTRY OPEN  "); // 16 chars
        break;
      case EXIT_OPENING:
        lcd.print("DOOR: EXIT OPEN   "); // 16 chars
        break;
      case OPEN:
        lcd.print("DOOR: HELD OPEN   "); // 16 chars
        break;
      case CLOSING:
        lcd.print("DOOR: CLOSING...  "); // 16 chars
        break;
    }
  }
}