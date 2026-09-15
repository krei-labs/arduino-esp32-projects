#include "BluetoothSerial.h"
#include <ESP32Servo.h>

BluetoothSerial SerialBT;

// --- PIN ASSIGNMENTS ---
const int PIN_SERVO_1 = 26; 
const int PIN_SERVO_2 = 27;

// Motor Pins (L298N)
const int PIN_IN1 = 22; 
const int PIN_IN2 = 21; 
const int PIN_IN3 = 19; 
const int PIN_IN4 = 18; 
const int PIN_ENA = 5;  
const int PIN_ENB = 23;

Servo leftServo;
Servo rightServo;
char command;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("TEAMUHAW");

  // Motor Pin Setup
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_ENB, OUTPUT);

  // Enable motors (Full Speed)
  digitalWrite(PIN_ENA, HIGH);
  digitalWrite(PIN_ENB, HIGH);

  // Servo Setup
  leftServo.attach(PIN_SERVO_1);
  rightServo.attach(PIN_SERVO_2);

  // Initial Positions
  leftServo.write(0);
  rightServo.write(90); // Adjusted to match your Y button logic
}

void loop() {
  if (SerialBT.available()) {
    command = SerialBT.read();

    // FORWARD
    if (command == 'F') { // Standardized: F usually means Forward
      digitalWrite(PIN_IN1, HIGH);
      digitalWrite(PIN_IN2, LOW);
      digitalWrite(PIN_IN3, HIGH);
      digitalWrite(PIN_IN4, LOW);
    }
    // BACKWARD
    else if (command == 'B') {
      digitalWrite(PIN_IN1, LOW);
      digitalWrite(PIN_IN2, HIGH);
      digitalWrite(PIN_IN3, LOW);
      digitalWrite(PIN_IN4, HIGH);
    }
    // LEFT
    else if (command == 'L') {
      digitalWrite(PIN_IN1, LOW);
      digitalWrite(PIN_IN2, HIGH);
      digitalWrite(PIN_IN3, HIGH);
      digitalWrite(PIN_IN4, LOW);
    }
    // RIGHT
    else if (command == 'R') {
      digitalWrite(PIN_IN1, HIGH);
      digitalWrite(PIN_IN2, LOW);
      digitalWrite(PIN_IN3, LOW);
      digitalWrite(PIN_IN4, HIGH);
    }
    // STOP
    else if (command == 'S') {
      digitalWrite(PIN_IN1, LOW);
      digitalWrite(PIN_IN2, LOW);
      digitalWrite(PIN_IN3, LOW);
      digitalWrite(PIN_IN4, LOW);
    }
    // X BUTTON -> LEFT SERVO
    else if (command == 'X') {
      leftServo.write(0);   
      delay(500);           
      leftServo.write(90);    
    }
    // Y BUTTON -> RIGHT SERVO
    else if (command == 'Y') {
      rightServo.write(90);  
      delay(500);           
      rightServo.write(0); 
    }
  }
}