int ledPin = 2;

void setup(){
    pinMode (ledPin, OUTPUT);
    Serial.begin(9600);
}

void loop(){
  Serial.println("ON");
  digitalWrite(ledPin,HIGH);
  delay(500);

  Serial.println("OFF");
  digitalWrite(ledPin,LOW);
  delay(500);
  }
