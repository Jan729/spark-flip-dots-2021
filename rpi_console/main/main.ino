//#include "rotaryEncoder.h"
#include <FastLED.h>

#define HORIZ_CLK 6
#define HORIZ_DAT 7
#define VERT_CLK 8
#define VERT_DAT 9
#define COLOR_CLK 10
#define COLOR_DAT 11
#define RST_BTN 19

int buf[4];
char* createStr(char c, int v);
char* outbuf;

uint8_t prevNextCode1 = 0;
uint16_t store1=0;

uint8_t prevNextCode2 = 0;
uint16_t store2=0;

int8_t read_rotary1(int pinData, int pinClk) {
  int8_t rot_enc_table[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};
  // Serial.println("Read Rotary 1");
  prevNextCode1 <<= 2;
  if (digitalRead(HORIZ_CLK)) prevNextCode1 |= 0x02;
  if (digitalRead(HORIZ_DAT)) prevNextCode1 |= 0x01;
  prevNextCode1 &= 0x0f;

   // If valid then store as 16 bit data.
   if  (rot_enc_table[prevNextCode1] ) {
      // Serial.println("Something happened");
      store1 <<= 4;
      store1 |= prevNextCode1;
      //if (store==0xd42b) return 1;
      //if (store==0xe817) return -1;
      if ((store1&0xff)==0x2b) return -1;
      if ((store1&0xff)==0x17) return 1;
   }
  //  Serial.println("Detec zero happened");

   return 0;
}

// int8_t read_rotary2(int pinData, int pinClk) {
//   int8_t rot_enc_table[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};

//   prevNextCode2 <<= 2;
//   if (digitalRead(VERT_CLK)) prevNextCode2 |= 0x02;
//   if (digitalRead(VERT_DAT)) prevNextCode2 |= 0x01;
//   prevNextCode2 &= 0x0f;

//    // If valid then store as 16 bit data.
//    if  (rot_enc_table[prevNextCode2] ) {
//       store2 <<= 4;
//       store2 |= prevNextCode2;
//       //if (store==0xd42b) return 1;
//       //if (store==0xe817) return -1;
//       if ((store2&0xff)==0x2b) return -1;
//       if ((store2&0xff)==0x17) return 1;
//    }
//    return 0;
// }

void setup(){
  Serial.begin(9600);
  // Serial1.begin(9600);
  Serial.println("Hello");
  
  
  pinMode(HORIZ_CLK, INPUT);
  pinMode(HORIZ_CLK, INPUT_PULLUP);
  pinMode(HORIZ_DAT, INPUT);
  pinMode(HORIZ_DAT, INPUT_PULLUP);
  
  // pinMode(VERT_CLK, INPUT_PULLUP);
  // pinMode(COLOR_CLK, INPUT_PULLUP);
  // pinMode(VERT_DAT, INPUT_PULLUP);
  // pinMode(COLOR_DAT, INPUT_PULLUP);
  // pinMode(RST_BTN, INPUT_PULLDOWN);
  outbuf = (char*)malloc(sizeof(char) * 2);

}

void loop(){
  // Serial.println("Loop Read Rotary");

  int8_t delta_horiz = read_rotary1(HORIZ_DAT, HORIZ_CLK); // if static, optimized out
  // static int8_t delta_vert = read_rotary2(VERT_DAT, VERT_CLK);
  // int delta_color = read_rotary(COLOR_DAT, COLOR_CLK);
  // int rst_button = digitalRead(RST_BTN);
  // Serial.print("Delta Vertical: ");
  // Serial.println(delta_vert);
  // Serial.print("Delta Color: ");
  // Serial.println(delta_color);
  // Serial.print("Button Status: ");
  // Serial.println(rst_button);

  // buf[0] = delta_horiz;
  // buf[1] = delta_vert;
  // buf[2] = delta_color;
  // buf[3]= rst_button;
  // Serial1.write(buf,4);
  // Serial1.write("#");
  bool verbose = 1;
   if(verbose||delta_horiz!=0) {
    // Serial1.write(delta_horiz ==0 ? "h0": delta_horiz > 0 ? "h+":"h-");
    Serial.print("Delta Horizontal: ");
    Serial.println(delta_horiz);
    
  }
    //  if(verbose||delta_vert!=0) {
    // // Serial1.write(delta_horiz ==0 ? "h0": delta_horiz > 0 ? "h+":"h-");
    // Serial.print("Delta Vertical: ");
    // Serial.println(delta_vert);
    
  // }
    // if(verbose||delta_horiz!=0) Serial1.write(createStr('h', delta_horiz));
  // if(verbose||delta_vert!=0) Serial1.write(createStr('v', delta_vert));
  // if(verbose||delta_color!=0) Serial1.write(createStr('c',delta_color));
  // if(verbose||rst_button!=0) Serial1.write(createStr('r', rst_button));
  // Serial1.write(";");
}

char* createStr(char indicator, int val){
  String s ="";
  s +=  indicator;
  s += val;
  s.toCharArray(outbuf, 2);
  return outbuf;
}