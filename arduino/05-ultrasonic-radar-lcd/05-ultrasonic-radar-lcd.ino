#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Servo
Servo radarServo;
const int servoPin = 11;

// Ultrasonic
const int trigPin = 9;
const int echoPin = 8;

// LCD (I2C address 0x27, 16x2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

long duration;
int distance;

void setup() {
  // Servo
  radarServo.attach(servoPin);

  // Ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Radar System ");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Sweep servo from 0° to 180° and back
  for (int pos = 0; pos <= 180; pos += 10) {
    radarServo.write(pos);
    delay(150);

    distance = getDistance();
    displayData(pos, distance);
  }

  for (int pos = 180; pos >= 0; pos -= 10) {
    radarServo.write(pos);
    delay(150);

    distance = getDistance();
    displayData(pos, distance);
  }
}

// Function to measure distance
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 40000); // 40ms timeout
  int dist = duration * 0.034 / 2; // cm

  if (dist <= 0 || dist > 400) return -1; // Out of range
  return dist;
}

// Function to display on LCD
void displayData(int angle, int dist) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Angle: ");
  lcd.print(angle);
  lcd.print((char)223); // degree symbol

  lcd.setCursor(0, 1);
  if (dist == -1) {
    lcd.print("No object");
  } else {
    lcd.print("Dist: ");
    lcd.print(dist);
    lcd.print(" cm");
  }
}
