#include <ESP32Servo.h>
#include "BluetoothSerial.h"

// =============================================================
//  ADJUSTABLE SETTINGS (Change these for each servo)
// =============================================================
// Servo 1 (Pin 26)
const int S1_STRIKE_ANGLE = 90;   // The "Hit" position
const int S1_REST_ANGLE   = 0;    // The "Home" position
const int S1_DELAY        = 3000; // 3 seconds

// Servo 2 (Pin 27)
const int S2_STRIKE_ANGLE = 110;  // The "Hit" position (adjustable)
const int S2_REST_ANGLE   = 0;    // The "Home" position
const int S2_DELAY        = 3000; // 3 seconds

// =============================================================
//  OBJECTS & PINS
// =============================================================
BluetoothSerial SerialBT;
Servo servo1;
Servo servo2;

const int PIN_SERVO_1 = 26; 
const int PIN_SERVO_2 = 27;

// Motor Pins (L298N/Driver)
const int PIN_IN1 = 22; const int PIN_IN2 = 21; 
const int PIN_IN3 = 19; const int PIN_IN4 = 18; 
const int PIN_ENA = 5;  const int PIN_ENB = 23;

// Timing States
unsigned long s1Timer = 0;
bool s1Active = false;
unsigned long s2Timer = 0;
bool s2Active = false;

void setup() {
    Serial.begin(9600);
    SerialBT.begin("magandaako"); 

    // REQUIRED: ESP32 needs timer allocation for multiple servos
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);

    // Motor setup
    pinMode(PIN_IN1, OUTPUT); pinMode(PIN_IN2, OUTPUT);
    pinMode(PIN_IN3, OUTPUT); pinMode(PIN_IN4, OUTPUT);
    ledcAttach(PIN_ENA, 1000, 8);
    ledcAttach(PIN_ENB, 1000, 8);

    // Servo Setup
    servo1.setPeriodHertz(50);
    servo2.setPeriodHertz(50);
    
    // Attaching with standard pulse widths
    servo1.attach(PIN_SERVO_1, 500, 2400);
    servo2.attach(PIN_SERVO_2, 500, 2400);

    // Move to rest immediately
    servo1.write(S1_REST_ANGLE);
    servo2.write(S2_REST_ANGLE);

    stopMotors();
    Serial.println("Sumo Car Ready. Separate Angles Active.");
}

void loop() {
    if (SerialBT.available()) {
        char cmd = SerialBT.read();
        
        // Basic movement
        if (cmd == 'F')      move(HIGH, LOW, HIGH, LOW);
        else if (cmd == 'B') move(LOW, HIGH, LOW, HIGH);
        else if (cmd == 'L') move(LOW, HIGH, HIGH, LOW);
        else if (cmd == 'R') move(HIGH, LOW, LOW, HIGH);
        else if (cmd == 'S') stopMotors();

        // SERVO 1 TRIGGER (X)
        else if (cmd == 'X') {
            servo1.write(S1_STRIKE_ANGLE);
            s1Timer = millis();
            s1Active = true;
            Serial.println("Servo 1: STRIKE");
        }
        // SERVO 2 TRIGGER (Y)
        else if (cmd == 'Y') {
            servo2.write(S2_STRIKE_ANGLE);
            s2Timer = millis();
            s2Active = true;
            Serial.println("Servo 2: STRIKE");
        }
    }

    // --- NON-BLOCKING AUTOMATIC RETURN ---
    
    // Servo 1 Return
    if (s1Active && (millis() - s1Timer >= S1_DELAY)) {
        servo1.write(S1_REST_ANGLE);
        s1Active = false;
        Serial.println("Servo 1: RETURN");
    }
    
    // Servo 2 Return
    if (s2Active && (millis() - s2Timer >= S2_DELAY)) {
        servo2.write(S2_REST_ANGLE);
        s2Active = false;
        Serial.println("Servo 2: RETURN");
    }
}

// --- HELPER FUNCTIONS ---
void move(int i1, int i2, int i3, int i4) {
    digitalWrite(PIN_IN1, i1); digitalWrite(PIN_IN2, i2);
    digitalWrite(PIN_IN3, i3); digitalWrite(PIN_IN4, i4);
    ledcWrite(PIN_ENA, 255); ledcWrite(PIN_ENB, 255);
}

void stopMotors() {
    digitalWrite(PIN_IN1, LOW); digitalWrite(PIN_IN2, LOW);
    digitalWrite(PIN_IN3, LOW); digitalWrite(PIN_IN4, LOW);
    ledcWrite(PIN_ENA, 0); ledcWrite(PIN_ENB, 0);
}