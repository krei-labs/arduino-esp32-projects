#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);

int b = 3;
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.init();
  lcd.backlight();   
  dht.begin();

  pinMode(b,OUTPUT);

}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readTemperature(true);


  if (isnan(h) || isnan(t)){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT11 ERROR");
    delay(2000);
    return;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DHT11 SENSOR");

  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(t);
  lcd.print(" C");

  lcd.setCursor(0, 2);
  lcd.print("Farenh: ");
  lcd.print(h);
  lcd.print(" F");

if (t >=30 ){
  tone(b,500);
} else {
  noTone(b);
}
  delay(2000);

}
