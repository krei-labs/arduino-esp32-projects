#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myServo;
const int servoPin = 11;
const int ledPin = 10; 
int pos = 0;
bool forward = true;

void setup() {
  lcd.init();
  lcd.backlight();

  myServo.attach(servoPin);

  pinMode(ledPin, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Hi,I'm Christian");
  lcd.setCursor(0, 1);
  lcd.print("Bored na.. :(");
  delay(2500);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Ginawa ko 'to ");
  lcd.setCursor(0, 1);
  lcd.print(" for you <3 ");
  delay(2500);

  lcd.clear();
}

void showLyric(const char* line1, const char* line2, int durationMs) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);

  unsigned long start = millis();
  while (millis() - start < durationMs) {
    if (forward) {
      pos++;
      if (pos >= 180) forward = false;
    } else {
      pos--;
      if (pos <= 0) forward = true;
    }
    myServo.write(pos);

    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
    delay(200);
  }
}

void loop() {
  showLyric("I want you to", " notice '-' ", 6000);
  showLyric("When I'm not", " around --> ", 5000);
  showLyric("You're so f***ing", "special :)", 5000);
  showLyric("I wish I was", "special  :'(", 5000);

  showLyric("But I'm a creep", " T_T", 5000);
  showLyric("I'm a weirdo", " @_@", 5000);
  showLyric("What the hell am", "I doing here???", 5000);
  showLyric("I don't belong", "here ://", 3000);

  showLyric(" Oh, oh ", " :o ", 3400);

  showLyric("She's running", "out again", 10500);
  showLyric("She's running", "out ///* ", 5100);
  showLyric("She run, run,", "run, run ~~~~", 14500);
  showLyric(" Run :( ", " byeee ---- ", 100000);
}
