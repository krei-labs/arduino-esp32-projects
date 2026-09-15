#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd_1(0x27, 16, 4); 

#define BEAT 400  // ~156 BPM

void setup() {
  lcd_1.init();
  lcd_1.backlight();
  lcd_1.begin(16, 4);

  // ---------------------

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("And "); delay(BEAT);
  lcd_1.print("I'd "); delay(BEAT);
  lcd_1.print("give "); delay(BEAT);
  lcd_1.print("up"); delay(BEAT * 2);

  lcd_1.setCursor(0, 1);
  lcd_1.print("forever "); delay(BEAT);
  lcd_1.print("to "); delay(BEAT);
  lcd_1.print("touch "); delay(BEAT);
  lcd_1.print("you"); delay(BEAT * 2);

  lcd_1.setCursor(0, 2);
  lcd_1.print("'Cause "); delay(BEAT);
  lcd_1.print("I "); delay(BEAT);
  lcd_1.print("know "); delay(BEAT);
  lcd_1.print("that"); delay(BEAT
  
  
  );

  lcd_1.setCursor(0, 3);
  lcd_1.print("you feel me"); delay(BEAT * 2);

  // ---------------------

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("somehow"); delay(BEAT * 6);

  lcd_1.setCursor(0, 1);
  lcd_1.print("You're "); delay(BEAT);
  lcd_1.print("the "); delay(BEAT);
  lcd_1.print("closest"); delay(BEAT * 2);

  lcd_1.setCursor(0, 2);
  lcd_1.print("to Heaven"); delay(BEAT * 2);

  lcd_1.setCursor(0, 3);
  lcd_1.print("that I'll ever"); delay(BEAT * 3);

  // ---------------------

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("be"); delay(BEAT * 2.5);

  lcd_1.setCursor(0, 1);
  lcd_1.print("And I don't"); delay(BEAT * 3);

  lcd_1.setCursor(0, 2);
  lcd_1.print("wanna go"); delay(BEAT * 3);

  lcd_1.setCursor(0, 3);
  lcd_1.print("home right now"); delay(BEAT * 7);

  // ---------------------

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("And all I can"); delay(BEAT * 2.5);

  lcd_1.setCursor(0, 1);
  lcd_1.print("taste is this"); delay(BEAT * 3);

  lcd_1.setCursor(0, 2);
  lcd_1.print("moment"); delay(BEAT * 5);

  lcd_1.setCursor(0, 3);
  lcd_1.print("And all I can"); delay(BEAT * 2.5);

  // ---------------------

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("breathe is"); delay(BEAT * 3);

  lcd_1.setCursor(0, 1);
  lcd_1.print("your life"); delay(BEAT * 6);

  lcd_1.setCursor(0, 2);
  lcd_1.print("And sooner or"); delay(BEAT * 3);

  lcd_1.setCursor(0, 3);
  lcd_1.print("later it's over"); delay(BEAT * 7);

  // ---------------------

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("I just don't"); delay(BEAT * 3);

  lcd_1.setCursor(0, 1);
  lcd_1.print("wanna miss"); delay(BEAT * 3);

  lcd_1.setCursor(0, 2);
  lcd_1.print("you tonight"); delay(BEAT * 6);

  lcd_1.setCursor(0, 3);
  lcd_1.print("And I don't"); delay(BEAT * 3);

  // ---------------------

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("want the world"); delay(BEAT * 4);

  lcd_1.setCursor(0, 1);
  lcd_1.print("to see me"); delay(BEAT * 4);

  lcd_1.setCursor(0, 2);
  lcd_1.print("'Cause I don't"); delay(BEAT * 3);

  lcd_1.setCursor(0, 3);
  lcd_1.print("think that they'd"); delay(BEAT * 3);

  // ---------------------

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("understand"); delay(BEAT * 7);

  lcd_1.setCursor(0, 1);
  lcd_1.print("When everything's"); delay(BEAT * 4);

  lcd_1.setCursor(0, 2);
  lcd_1.print("made to be"); delay(BEAT * 2);

  lcd_1.setCursor(0, 3);
  lcd_1.print("broken"); delay(BEAT * 6);

  // ---------------------

  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print("I just want you"); delay(BEAT * 3);

  lcd_1.setCursor(0, 1);
  lcd_1.print("to know who"); delay(BEAT * 2);

  lcd_1.setCursor(0, 2);
  lcd_1.print("I am"); delay(BEAT);
  lcd_1.print(" :(( - krei "); delay(BEAT * 8);

}

void loop() {
  // play once only
}