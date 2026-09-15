int ir = 2;
int LED = 3;

void setup() {
  pinMode(ir, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  if(digitalRead(ir) == LOW) {
  digitalWrite(LED,HIGH);
  }
  else {
    digitalWrite(LED,LOW);
  }
}
