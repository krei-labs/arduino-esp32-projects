#include<DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  
  float t = dht.readTemperature();
  float h = dht.readTemperature(true);

  Serial.print("Farenh: ");
  Serial.print(h);
  Serial.println("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");

  delay(2000);
}