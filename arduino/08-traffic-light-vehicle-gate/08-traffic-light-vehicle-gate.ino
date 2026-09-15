#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;

int ledPins[] = {2, 3, 4, 5, 7};
const int ledCount = 5;

const int redLed = 13;
const int yellowLed = 12;
const int greenLed = 11;

Servo myServo;

long duration;
int distance;

bool gateOpen = false;  

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  myServo.attach(6);
  myServo.write(0); 

  Serial.begin(9600);
}

void loop() {
  digitalWrite(greenLed, HIGH);
  delayWithCarCheck(5000);
  digitalWrite(greenLed, LOW);

  digitalWrite(yellowLed, HIGH);
  delayWithCarCheck(2000);
  digitalWrite(yellowLed, LOW);

  digitalWrite(redLed, HIGH);
  delayWithCarCheck(5000);
  digitalWrite(redLed, LOW);
}

void checkCar() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < 20 && !gateOpen) {
    for (int i = 0; i < ledCount; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(300);
    }

    myServo.write(0);
    gateOpen = true;
    Serial.println("Gate opened!");
  } 
  else if ((distance >= 20 || distance == 0) && gateOpen) {
    for (int i = ledCount - 1; i >= 0; i--) {
      digitalWrite(ledPins[i], LOW);
      delay(300);
    }

    myServo.write(90);
    gateOpen = false;
    Serial.println("Gate closed!");
  }
}

void delayWithCarCheck(long ms) {
  long start = millis();
  while (millis() - start < ms) {
    checkCar(); 
    delay(200); 
  }
}
