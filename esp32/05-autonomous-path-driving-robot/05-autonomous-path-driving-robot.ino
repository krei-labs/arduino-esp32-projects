#define IN1 25
#define IN2 26

#define IN3 27
#define IN4 14

#define FORWARD_TIME 200
#define TURN_TIME 350
#define STOP_TIME 500

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  delay(2000);
}

void loop() {

  forward(); delay(FORWARD_TIME);
  stop(); delay(STOP_TIME);

  right(); delay(TURN_TIME);
  stop(); delay(STOP_TIME);
  forward(); delay(FORWARD_TIME);
  stop(); delay(STOP_TIME);

  left(); delay(TURN_TIME);
  stop(); delay(STOP_TIME);
  forward(); delay(FORWARD_TIME);
  stop(); delay(STOP_TIME);

  right(); delay(TURN_TIME);
  stop(); delay(STOP_TIME);
  forward(); delay(FORWARD_TIME);
  stop(); delay(STOP_TIME);

  left(); delay(TURN_TIME);
  stop(); delay(STOP_TIME);
  forward(); delay(FORWARD_TIME);
  stop(); delay(STOP_TIME);

  left(); delay(TURN_TIME);
  stop(); delay(STOP_TIME);
  forward(); delay(800);
  stop(); delay(STOP_TIME);

  left(); delay(TURN_TIME);
  stop(); delay(STOP_TIME);
  forward(); delay(FORWARD_TIME);
  stop(); delay(STOP_TIME);

  left(); delay(TURN_TIME);
  stop(); delay(STOP_TIME);
  forward(); delay(FORWARD_TIME);
  stop(); delay(STOP_TIME);

  right(); delay(TURN_TIME);
  stop(); delay(STOP_TIME);
  forward(); delay(FORWARD_TIME);
  stop(); delay(STOP_TIME);

  left(); delay(TURN_TIME);
  stop(); delay(STOP_TIME);
  forward(); delay(FORWARD_TIME);
  stop(); delay(STOP_TIME);

  right(); delay(TURN_TIME);
  stop(); delay(STOP_TIME);
  forward(); delay(FORWARD_TIME);

  stop(); delay(5000);
}

// ===== Motor Control =====

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
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
