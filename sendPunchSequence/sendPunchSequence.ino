// To run this, create a tinkercad with two arduinos
// Connect the arduinos togther as follows:
// GND to GND, A4 to A4, A5 to A5

// Differences between real project and this simulation:
// 1) For arduino megas, connect pins 20 together
// and pins 21 together instead of A4 and A5
// 2) SendPunchSequence() will be called when
// someone presses the Print button

#include <Wire.h>
// TinkerCAD doesn't have FastLED :'( #include <FastLED.h>
// I'll use boolean 1 or 0 instead

#define NUM_STRIPS 32
#define NUM_LEDS_PER_STRIP 32

// Caution: the led array indexing is different on TinkerCAD
// than the wowki simulator

// leds[0][0] is the top left corner
// leds[0][31] is the top right corner
// leds[31][0] is the bottom left corner
// leds[31][31] is the bottom right corner
boolean leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)

  Serial.begin(9600);
  Serial.println("I am etch a sketch arduino");
  
  for (int row=0; row<NUM_STRIPS; row++)
  {
    for (int col=0; col<NUM_LEDS_PER_STRIP; col++) {
      leds[row][col] = col % 2;
    }
  }
  
  //CreateDummyPicture();
}

void loop() {
  SendPunchSequence();
  
  delay(2000);
}

void SendPunchSequence()
{
  Wire.beginTransmission(4); // transmit to device #4
    
  // idea #1: to compress the image to 16x16,
  // imagine a large pixel is 2x2 leds.
  // We send the value at the top left corner 
  // of each large pixel
  // (we'll need to revise this during prototyping)
  for (int row=0; row<NUM_STRIPS; row+=2)
  {
    // assuming each led value is either 0 or 1,
    //write 1 byte (aka 8 bits) of data at a time
    for (int col=0; col<NUM_LEDS_PER_STRIP; col+=8) {
      byte compressedBit = CompressedColourData(row, col);
      Wire.write(compressedBit);
      Serial.print(compressedBit, BIN);
      Serial.print(" ");
    }
    Serial.println();
  }
  
   Serial.println();
   Serial.println();
   Serial.println();
  
  if(Wire.endTransmission() != 0) {    // stop transmitting
	Serial.println("Error transmitting");
  }
}
  
  byte CompressedColourData(int row, int col) {  
    byte colour = B00000000;

    for (int i=0; i<8; i++) {
        byte nextBit = leds[row][col+i] > 0 ? B00000001 : B00000000;
        colour = colour | nextBit;
        colour << 1;
    }

    return colour;
  }

void CreateDummyPicture() {
  //left eye
  leds[4][2] = 1;
  leds[4][4] = 1;
  leds[6][2] = 1;
  leds[6][4] = 1;
  
  //right eye
  leds[4][28] = 1;
  leds[4][26] = 1;
  leds[6][28] = 1;
  leds[6][26] = 1;
  
  //mouth
  leds[20][2] = 1;
  leds[20][28] = 1;
  for(int col = 4; col<=26; col+=2) {
    leds[22][col] = 1;
  }
}
