#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo radarServo;
const int servoPin = 11;
const int trigPin = 9;
const int echoPin = 8;
LiquidCrystal_I2C lcd(0x27, 16, 2);
long duration;
int distance;

void setup() {
  radarServo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Radar System ");
  delay(2000);
  lcd.clear();

  // Serial for debugging
  Serial.begin(9600);
}

void loop() {
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

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 40000); // wait for echo
  int dist = duration * 0.034 / 2;

  // Debug print
  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.print(" us -> Distance: ");
  Serial.print(dist);
  Serial.println(" cm");

  if (dist <= 0 || dist > 400) return -1;
  return dist;
}

void displayData(int angle, int dist) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Angle: ");
  lcd.print(angle);
  lcd.print((char)223);

  lcd.setCursor(0, 1);
  if (dist == -1) {
    lcd.print("No object");
  } else {
    lcd.print("Dist: ");
    lcd.print(dist);
    lcd.print(" cm");
  }
}
