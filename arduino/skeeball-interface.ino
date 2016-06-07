#include <Keyboard.h>

unsigned int buttonsp = 0;
unsigned int buttons = 0;
unsigned int edge = 0;

char keys[] = { '1','2','3','4','5','6','7','8','9','A','B','C','D','E' };

#define set(x) \
  buttons |= 1 << x;
#define clr(x) \
  buttons &= ~(1 << x);
#define tog(x) \
  buttons ^= 1 << x;
#define chk(x) \ 
  (edge >> x) & 1

  
void setup() {
  int x;
  for (x = 2; x<13; x++)
    pinMode(x,INPUT_PULLUP);
   Keyboard.begin();
   //Serial.begin(9600);
}


char btn;

void loop() {
 for (btn = 2; btn < 13; btn++) {
  if(digitalRead(btn)) {
    clr(btn)
  } else {
    set(btn)
  }
 }
 
 edge = (buttons ^ buttonsp) & ~buttons;

  if (edge > 0) {
   for (btn = 2; btn < 13; btn++) {
    if (chk(btn))
      Keyboard.write(keys[(btn-2)]);
   }
  }
  /*
  Serial.println(buttonsp,BIN);
  Serial.println(buttons,BIN);
  Serial.println(edge,BIN);
  Serial.println("======");*/
  delay(500);
  buttonsp = buttons;
}
