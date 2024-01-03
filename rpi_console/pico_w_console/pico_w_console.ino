// Robust Rotary encoder reading
//
// Copyright John Main - best-microcontroller-projects.com
//

#include <Wire.h>
// UNO definitions
// #define CLK 6
// #define DATA 7
// #define CLK1 8
// #define DATA1 9
// #define CLK2 10
// #define DATA2 11

// PICOW definitions - ensure vcc = 3v3 for rotenc.
#define CLK 2
#define DATA 3
#define CLK1 4
#define DATA1 5
#define CLK2 6
#define DATA2 7
#define BTN 8

bool btnDown;

void setup() {
  pinMode(CLK, INPUT);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DATA, INPUT);
  pinMode(DATA, INPUT_PULLUP);

  pinMode(CLK1, INPUT);
  pinMode(CLK1, INPUT_PULLUP);
  pinMode(DATA1, INPUT);
  pinMode(DATA1, INPUT_PULLUP);
  
  pinMode(CLK2, INPUT);
  pinMode(CLK2, INPUT_PULLUP);
  pinMode(DATA2, INPUT);
  pinMode(DATA2, INPUT_PULLUP);

  pinMode(BTN, INPUT_PULLDOWN);


  // Wire.begin();
  Serial.begin (9600);
  Serial1.begin(9600);
  Serial.println("KY-040 Test Start:");
  btnDown = false;
}

static uint8_t prevNextCode = 0;
static uint16_t store=0;

static uint8_t prevNextCode1 = 0;
static uint16_t store1=0;


static uint8_t prevNextCode2 = 0;
static uint16_t store2=0;
void loop() {
  static int8_t c,val;
  static int8_t c1,val1;
  static int8_t c2,val2;
  bool wasInput = false;
  
  if( val=read_rotary() ) {
      c +=val;
      Serial.print(c);Serial.print("X ");
      wasInput = true;
   
   }

  if( val1=read_rotary1() ) {
      c1 +=val1;
      Serial.print(c1);Serial.print("Y ");
      wasInput = true;
   }


   if (val2=read_rotary2()){
      c2 += val2;
      Serial.print(c2);Serial.println("COL ");
      wasInput = true;
   }

  // catch button rising edge only
  if(!btnDown && digitalRead(BTN)){
    Serial.println("BUTTON READ");
    btnDown = true;
    wasInput = true;

  }
  if(btnDown && !digitalRead(BTN)){
    btnDown = false;
  }


   if(wasInput){
      int masterAddress = 0;
      byte packet = 0;
      if(val){
        packet |= 1<<7;
        packet |= (val==1?1:0)<<6; 
      }
      if(val1){
        packet |= 1 <<5;
        packet |= (val1==1?1:0) << 4;
      }
      if(val2){
        packet |= 1 <<3;
        packet |= (val2==1?1:0) << 2;
      }
      if(btnDown){
        packet |= 1<<1;
      }
      Serial.print("Packet ");
      Serial.println(packet, BIN);
      // Wire.beginTransmission(masterAddress);
      // Wire.write(packet);
      // Wire.endTransmission();
      Serial1.write(packet);
   }
   
}

// A vald CW or  CCW move returns 1, invalid returns 0.
int8_t read_rotary() {
  static int8_t rot_enc_table[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};

  prevNextCode <<= 2;
  if (digitalRead(DATA)) prevNextCode |= 0x02;
  if (digitalRead(CLK)) prevNextCode |= 0x01;
  prevNextCode &= 0x0f;

   // If valid then store as 16 bit data.
   if  (rot_enc_table[prevNextCode] ) {
      store <<= 4;
      store |= prevNextCode;
      //if (store==0xd42b) return 1;
      //if (store==0xe817) return -1;
      if ((store&0xff)==0x2b) return -1;
      if ((store&0xff)==0x17) return 1;
   }
   
   return 0;
}

int8_t read_rotary1() {
  static int8_t rot_enc_table1[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};

  prevNextCode1 <<= 2;
  if (digitalRead(DATA1)) prevNextCode1 |= 0x02;
  if (digitalRead(CLK1)) prevNextCode1 |= 0x01;
  prevNextCode1 &= 0x0f;

   // If valid then store as 16 bit data.
   if  (rot_enc_table1[prevNextCode1] ) {
      store1 <<= 4;
      store1 |= prevNextCode1;
      //if (store==0xd42b) return 1;
      //if (store==0xe817) return -1;
      if ((store1&0xff)==0x2b) return -1;
      if ((store1&0xff)==0x17) return 1;
   }
   
   return 0;
}

int8_t read_rotary2() {
  static int8_t rot_enc_table2[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};

  prevNextCode2 <<= 2;
  if (digitalRead(DATA2)) prevNextCode2 |= 0x02;
  if (digitalRead(CLK2)) prevNextCode2 |= 0x01;
  prevNextCode2 &= 0x0f;

   // If valid then store as 16 bit data.
   if  (rot_enc_table2[prevNextCode2] ) {
      store2 <<= 4;
      store2 |= prevNextCode2;
      //if (store==0xd42b) return 1;
      //if (store==0xe817) return -1;
      if ((store2&0xff)==0x2b) return -1;
      if ((store2&0xff)==0x17) return 1;
   }
   
   return 0;
}