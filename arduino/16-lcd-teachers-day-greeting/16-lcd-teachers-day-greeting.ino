#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 4);

void setup() {
  lcd.init();        // initialize the LCD
  lcd.backlight();   // turn on the backlight

  lcd.setCursor(0, 0); 
  lcd.print("Happy Teacher's Day! ");

  lcd.setCursor(0, 1); 
  lcd.print("   TCC Professors ");

  lcd.setCursor(0, 2); 
  lcd.print("          &  ");

  lcd.setCursor(0, 3); 
  lcd.print("   Faculty Members ");
}

void loop() {
  // Nothing to repeat, static display
}
