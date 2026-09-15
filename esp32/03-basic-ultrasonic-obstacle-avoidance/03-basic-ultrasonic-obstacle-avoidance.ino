#define IN1 25
#define IN2 26
#define IN3 27
#define IN4 14

#define TRIG_PIN 5
#define ECHO_PIN 18

#define SAFE_DISTANCE 30  // cm (early stop)
#define BACK_TIME 350      // reverse duration
#define TURN_TIME 350
#define STOP_TIME 150

long duration;
int distance;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
  randomSeed(analogRead(0));
  delay(2000);
}

void loop() {
  distance = getDistance();
  Serial.println(distance);

  if (distance > SAFE_DISTANCE && distance != 0) {
    forward();
  } else {
    earlyAvoid();
  }

  delay(40); // ultrasonic stability
}

// ===== EARLY OBSTACLE AVOID =====
void earlyAvoid() {
  stop();                    // INSTANT STOP
  delay(STOP_TIME);

  backward();                // BACK UP
  delay(BACK_TIME);

  stop();
  delay(STOP_TIME);

  bool turnRight = random(0, 2);

  if (turnRight) {
    right();
  } else {
    left();
  }
  delay(TURN_TIME);

  stop();
  delay(STOP_TIME);

  // check again before moving
  int check = getDistance();
  if (check <= SAFE_DISTANCE && check != 0) {
    // still blocked → turn opposite
    if (turnRight) left();
    else right();

    delay(TURN_TIME);
    stop();
    delay(STOP_TIME);
  }
}

// ===== ULTRASONIC =====
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 25000);

  if (duration == 0) return 0;

  return duration * 0.034 / 2;
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
