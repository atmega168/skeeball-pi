#include <Adafruit_NeoPixel.h>
#include <TimerOne.h>
#include <Keyboard.h>


unsigned int buttonsp = 0;
unsigned int buttons = 0;
unsigned int pressed = 0;

char keys[] = { '1','2','3','4','5','6','7','8','9','A','B','C','D','E' };

#define set(x) \
  buttons |= 1 << x;
#define clr(x) \
  buttons &= ~(1 << x);
#define tog(x) \
  buttons ^= 1 << x;
#define chk(x) \ 
  (pressed >> x) & 1

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 14, NEO_GRB + NEO_KHZ800);
  
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setPixelColor(30, 255, 0, 255);
  strip.show(); 
  int x;
  for (x = 2; x<13; x++)
    pinMode(x,INPUT_PULLUP);
  Timer1.initialize(200000);
  Timer1.attachInterrupt(buttonHandle);
  Serial.begin(9600);

}

char btn;

void buttonHandle() {
  for (btn = 2; btn < 13; btn++) {
    if(digitalRead(btn)) 
      clr(btn-2)
     else 
      set(btn-2);
  }
  pressed |= (buttons ^ buttonsp) & ~buttonsp;
  randLight();
}


void randLight() {
  int i;
  for (i=0;i<60;i++) {
    if(random(0,4)==0) {
      strip.setPixelColor(i, random(0,256),random(0,256),random(0,256));
    } else {
      strip.setPixelColor(i,0,0,0);
    }
  }
  strip.show();
}

void sendButtons() {
  //Serial.print(pressed,BIN);
  Serial.write((char *)&pressed,sizeof(pressed));
  pressed = 0;
}


void loop() {

  if (Serial.available() > 0) {
    // read the incoming byte:
     char cmd = Serial.read();
     if (cmd == 'B') {
       sendButtons();
     }
  }
}
