#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int GREEN_LED = 4;   
LiquidCrystal_I2C lcd(0x27, 16, 2);
int cars = 0;

Servo gateServo;

const int ir = 3;   
const int servoPin = 2;      
int sensorValue = 0;
int lastIrState = HIGH;   
bool carAtUltrasonic = false; 

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  Serial.begin(115200);
  pinMode(ir, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  gateServo.attach(servoPin);
  gateServo.write(0);
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void loop() {
  long distance = getDistance();
  sensorValue = digitalRead(ir);

  if (sensorValue == LOW && lastIrState == HIGH) {
    cars++;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Gate Open");
    gateServo.write(90);
    delay(1000);
    gateServo.write(0);
    digitalWrite(GREEN_LED, HIGH);
  }else{
    digitalWrite(GREEN_LED, LOW);
  }
  lastIrState = sensorValue;

  
  if (distance < 20) {
    carAtUltrasonic = true;  
  } 
  else if (distance > 20 && carAtUltrasonic) {
    cars--;
    if (cars < 0) cars = 0; 
    carAtUltrasonic = false;
    lcd.setCursor(0,0);
    lcd.print("Gate Close");
    gateServo.write(90);
    delay(1000);
    gateServo.write(0);

  }


  lcd.setCursor(0,1);
  lcd.print("Cars: ");
  lcd.print(cars);
  lcd.print("   "); 

  delay(200);
}