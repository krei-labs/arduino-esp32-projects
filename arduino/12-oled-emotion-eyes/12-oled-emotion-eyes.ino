#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int demo_mode = 1;
static const int max_animation_index = 10;  // number of emotions
int current_animation_index = 0;

int ref_eye_height = 40;
int ref_eye_width = 40;
int ref_space_between_eye = 10;
int ref_corner_radius = 10;

int left_eye_height = ref_eye_height;
int left_eye_width = ref_eye_width;
int left_eye_x = 32;
int left_eye_y = 32;
int right_eye_x = 32+ref_eye_width+ref_space_between_eye;
int right_eye_y = 32;
int right_eye_height = ref_eye_height;
int right_eye_width = ref_eye_width;

// ---------------- Helpers ----------------

void draw_eyes(bool update=true) {
  display.clearDisplay();        
  int x = int(left_eye_x-left_eye_width/2);
  int y = int(left_eye_y-left_eye_height/2);
  display.fillRoundRect(x,y,left_eye_width,left_eye_height,ref_corner_radius,SH110X_WHITE);
  x = int(right_eye_x-right_eye_width/2);
  y = int(right_eye_y-right_eye_height/2);
  display.fillRoundRect(x,y,right_eye_width,right_eye_height,ref_corner_radius,SH110X_WHITE);    
  if(update) display.display();
}

void center_eyes(bool update=true) {
  left_eye_height = ref_eye_height;
  left_eye_width = ref_eye_width;
  right_eye_height = ref_eye_height;
  right_eye_width = ref_eye_width;
  left_eye_x = SCREEN_WIDTH/2-ref_eye_width/2-ref_space_between_eye/2;
  left_eye_y = SCREEN_HEIGHT/2;
  right_eye_x = SCREEN_WIDTH/2+ref_eye_width/2+ref_space_between_eye/2;
  right_eye_y = SCREEN_HEIGHT/2;
  draw_eyes(update);
}

void blinkSmooth(int duration=200) {
  int steps = 8;
  int h = ref_eye_height;
  for (int i=0; i<=steps; i++) {
    left_eye_height = map(i, 0, steps, h, 2);
    right_eye_height = left_eye_height;
    draw_eyes(true);
    delay(duration/steps);
  }
  for (int i=0; i<=steps; i++) {
    left_eye_height = map(i, 0, steps, 2, h);
    right_eye_height = left_eye_height;
    draw_eyes(true);
    delay(duration/steps);
  }
}

void sleep() {
  left_eye_height = 2;
  right_eye_height = 2;
  draw_eyes(true);  
}

void wakeup() {
  sleep();
  for(int h=0; h <= ref_eye_height; h+=2) {
    left_eye_height = h;
    right_eye_height = h;
    draw_eyes(true);
    delay(15);
  }
}

// draw a heart (replacement for fillHeart)
void drawHeart(int x, int y, int size, uint16_t color) {
  display.fillCircle(x - size/2, y, size/2, color);
  display.fillCircle(x + size/2, y, size/2, color);
  display.fillTriangle(x - size, y, x + size, y, x, y + size, color);
}

// fake smile/frown arc using pixels
void drawSmile(int x, int y, int r, bool happy) {
  for (int i=-r; i<=r; i++) {
    int dy = sqrt(r*r - i*i);
    int yy = happy ? y + dy/3 : y - dy/3;
    display.drawPixel(x+i, yy, SH110X_WHITE);
  }
}

// transition blink before next emote
void transition_blink() {
  blinkSmooth(250);
  delay(100);
}

// ---------------- Emotions ----------------

void happy_eye() {
  center_eyes(false);
  display.clearDisplay();
  drawSmile(left_eye_x, left_eye_y, 12, true);
  drawSmile(right_eye_x, right_eye_y, 12, true);
  display.display();
  // giggle motion
  for(int i=0; i<3; i++) {
    display.startWrite();
    display.clearDisplay();
    drawSmile(left_eye_x, left_eye_y + ((i%2==0)?2:-2), 12, true);
    drawSmile(right_eye_x, right_eye_y + ((i%2==0)?2:-2), 12, true);
    display.endWrite();
    display.display();
    delay(120);
  }
  delay(500);
}

void angry_eye() {
  center_eyes(false);
  for (int step=0; step<10; step++) {
    display.clearDisplay();
    draw_eyes(false);
    display.drawLine(left_eye_x-20, left_eye_y-15+step, left_eye_x+20, left_eye_y-10, SH110X_WHITE);
    display.drawLine(right_eye_x-20, right_eye_y-10, right_eye_x+20, right_eye_y-15+step, SH110X_WHITE);
    display.display();
    delay(25);
  }
  delay(700);
}

void sad_eye() {
  center_eyes(false);
  display.clearDisplay();
  drawSmile(left_eye_x, left_eye_y+5, 12, false);
  drawSmile(right_eye_x, right_eye_y+5, 12, false);
  display.display();
  delay(800);
}

void surprised_eye() {
  center_eyes(false);
  for(int r=2; r<=20; r+=2) {
    display.clearDisplay();
    display.fillCircle(left_eye_x, left_eye_y, r, SH110X_WHITE);
    display.fillCircle(right_eye_x, right_eye_y, r, SH110X_WHITE);
    display.display();
    delay(40);
  }
  delay(800);
}

void wink() {
  center_eyes(false);
  display.clearDisplay();
  // left eye open
  display.fillRoundRect(left_eye_x-20, left_eye_y-20, 40, 40, 10, SH110X_WHITE);
  // right eye closed
  display.drawLine(right_eye_x-20, right_eye_y, right_eye_x+20, right_eye_y, SH110X_WHITE);
  display.display();
  delay(500);
  // reopen
  transition_blink();
}

void love_eye() {
  center_eyes(false);
  for(int i=8; i<=12; i++) {
    display.clearDisplay();
    drawHeart(left_eye_x, left_eye_y, i, SH110X_WHITE);
    drawHeart(right_eye_x, right_eye_y, i, SH110X_WHITE);
    display.display();
    delay(80);
  }
  // giggle motion for heart
  for(int j=0; j<4; j++) {
    display.clearDisplay();
    drawHeart(left_eye_x, left_eye_y + ((j%2==0)?2:-2), 12, SH110X_WHITE);
    drawHeart(right_eye_x, right_eye_y + ((j%2==0)?2:-2), 12, SH110X_WHITE);
    display.display();
    delay(120);
  }
  delay(800);
}

// ---------------- Setup & Loop ----------------

void setup() {
  display.begin(SCREEN_ADDRESS, true);
  Serial.begin(115200);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0,0);
  display.println(F("Intellar.ca"));  
  display.display();  
  delay(2000);
  sleep();
  delay(1000);
}

void launch_animation_with_index(int animation_index) {
  switch(animation_index) {
    case 0: wakeup(); break;
    case 1: center_eyes(true); break;
    case 2: blinkSmooth(200); break;
    case 3: happy_eye(); break;
    case 4: angry_eye(); break;
    case 5: sad_eye(); break;
    case 6: surprised_eye(); break;
    case 7: wink(); break;
    case 8: love_eye(); break;
    case 9: sleep(); break;
    case 10: blinkSmooth(250); break;
  }
}

void loop() {
  if(demo_mode == 1) {
    launch_animation_with_index(current_animation_index++);
    if(current_animation_index > max_animation_index) {
      // smooth transition back to start
      transition_blink();
      current_animation_index = 0;
    }
  }
  if(Serial.available()) {
    String data = Serial.readString();
    data.trim();
    char cmd = data[0];
    if(cmd == 'A') {
      demo_mode = 0;
      String arg = data.substring(1,data.length());
      int anim = arg.toInt();
      launch_animation_with_index(anim);
      Serial.print(cmd);
      Serial.print(arg);   
    }
  }
}
