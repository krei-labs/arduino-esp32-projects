#include <ESP32Servo.h>  // ESP32-compatible Servo library

#define IN1 25
#define IN2 26
#define IN3 27
#define IN4 14

#define TRIG_PIN 5
#define ECHO_PIN 18

#define SAFE_DISTANCE 50  // cm
#define BACK_TIME 250
#define TURN_TIME 300

#define SERVO_PIN 13
#define SERVO_LEFT 0
#define SERVO_CENTER 90
#define SERVO_RIGHT 180

Servo myServo;

long duration;
int distance;
int leftDist = 0, centerDist = 0, rightDist = 0;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(115200);
  randomSeed(analogRead(0));

  myServo.attach(SERVO_PIN, 500, 2400); // min & max pulse width for ESP32
  myServo.write(SERVO_CENTER); // start forward
  delay(500);
}

// ===== MAIN LOOP =====
void loop() {
  // Continuously scan while moving forward
  centerDist = getDistance();
  if (centerDist > SAFE_DISTANCE || centerDist == 0) {
    forward();
  } else {
    stop();
    avoidObstacle();
  }

  delay(30); // small delay for stability
}

// ===== AVOID OBSTACLE SMARTLY =====
void avoidObstacle() {
  // Read distances for left, center, right quickly
  leftDist = scanServo(SERVO_LEFT);
  centerDist = scanServo(SERVO_CENTER);
  rightDist = scanServo(SERVO_RIGHT);

  Serial.print("Left: "); Serial.print(leftDist);
  Serial.print(" Center: "); Serial.print(centerDist);
  Serial.print(" Right: "); Serial.println(rightDist);

  // Backup a little before turning
  backward();
  delay(BACK_TIME);
  stop();
  delay(50);

  // Decide direction based on max distance
  int maxDist = max(leftDist, max(centerDist, rightDist));

  if (maxDist == centerDist && centerDist > SAFE_DISTANCE) {
    forward();
  } else if (maxDist == leftDist && leftDist > SAFE_DISTANCE) {
    left();
  } else if (maxDist == rightDist && rightDist > SAFE_DISTANCE) {
    right();
  } else {
    // all blocked → random turn
    bool turnRight = random(0, 2);
    if (turnRight) right();
    else left();
  }

  delay(TURN_TIME);
  stop();
  delay(50);

  // Reset servo to center
  myServo.write(SERVO_CENTER);
}

// ===== FAST SERVO SCAN =====
int scanServo(int angle) {
  myServo.write(angle);
  delay(100); // very short delay for servo to reach position
  return getDistance();
}

// ===== ULTRASONIC =====
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 25000); // 25ms timeout
  if (duration == 0) return 0;

  return duration * 0.034 / 2; // cm
}

// ===== MOTOR CONTROL =====
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
