// ArrayOfLedArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers

//to view simulation: https://wokwi.com/arduino/projects/321063892073579091

/* Referenced from Janelle's simulation
  Leftmost encoder is for vertical movement, the middle is for horizontal
  and the last one is for colour picking (Note: It takes multiple clicks
  to go to the next colour. One colour is the eraser). Refer to the Notion
  (API Map ->Read Colour -> Open) for the colour wheel*/

// Differences between this simulator and our actual display:
// 1) The simulator is a bit laggy
// 2) The data, VSS, and GND pins are attached to the strip closest
// to the LED with index 0. We'll want to mount the LED strips with
// the wiring on the left side of the display if we want to keep this
// coordinate system

#include <FastLED.h>

#define NUM_STRIPS 32
#define NUM_LEDS_PER_STRIP 32

#define ENCODER_CLK_V 6
#define ENCODER_DT_V 7
#define ENCODER_CLK_H 2
#define ENCODER_DT_H 3

#define ENCODER_CLK_C 5
#define ENCODER_DT_C 4

#define CLEAR_PIN 18

volatile bool playEtchASketch = true;
volatile bool shouldClearDisplay = false;
int prevVertical = 0;
int prevHorizontal = 0;
volatile unsigned long lastActive = millis();
unsigned long IDLE_TIMEOUT = 10000;

uint8_t vertical = 0;
String Vertical;
uint8_t horizontal = 0;
String Horizontal;

int vCounter = 0;
int hCounter = 0;

int prevClk_H = HIGH;
int prevClk_V = HIGH;
int prevClk_C = HIGH;

int counter = 0;

//replaced leds[31][31] with leds[1] because I'm testing only one rgb led
// leds[0][0] is the bottom left corner
// leds[0][31] is the bottom right corner
// leds[31][0] is the top left corner
CRGB leds[1];

//contains rgb codes of the colour wheel
CRGB colours[20];


void setup() {

  //setting up the colours
  colours[0] = CRGB::White;
  colours[1] = CRGB(220, 20, 60);
  colours[2] = CRGB::Red;
  colours[3] = CRGB(255, 69, 0); //yellow
  colours[4] = CRGB(157, 194, 9); //light green
  colours[5] = CRGB(0, 128, 0); //green
  colours[6] = CRGB(1, 121, 111); //light blue
  colours[7] = CRGB(0, 0, 139); //blue
  colours[8] = CRGB(50, 23, 77); //purple
  colours[9] = CRGB(255, 140, 0); //yellow
  colours[10] = CRGB(75, 0, 130); //purple
  colours[11] = CRGB(75, 0, 130); //purple
  colours[12] = CRGB(75, 0, 130); //purple
  colours[13] = CRGB::Black; //eraser
  colours[14] = CRGB::Black; //eraser
  colours[15] = CRGB::Black; //eraser
  colours[16] = CRGB(28, 144, 217); //blue
  colours[17] = CRGB(28, 144, 217); //blue
  colours[18] = CRGB(28, 144, 217); //blue
  colours[19] = CRGB::Red;

  //setting up rotary encoder pins
  //pinMode(ENCODER_CLK_H, INPUT);
  //pinMode(ENCODER_DT_H, INPUT);
  pinMode(ENCODER_CLK_V, INPUT);
  pinMode(ENCODER_DT_V, INPUT);
  pinMode(ENCODER_CLK_C, INPUT);
  pinMode(ENCODER_DT_C, INPUT);
  pinMode(8, OUTPUT); //led test for rotary encoder (pixel movement)
  
  pinMode(CLEAR_PIN, INPUT); //interrupt pin for button
  pinMode(9, INPUT); //input pin to give info to the arduino about the button state
  pinMode(10, OUTPUT); //output pin to light up led when button is pressed
  pinMode(11, OUTPUT); //rgb led output

  attachInterrupt(digitalPinToInterrupt(CLEAR_PIN), HandleClearButton, RISING);
  FastLED.addLeds<WS2812, 11, GRB>(leds, 1);
}

//blinks the led based on the position of the pixel movement encoders
void blinkLED() {
  digitalWrite(8, HIGH);
  delay(vertical * 100);
  digitalWrite(8, LOW);
}

//updates the horizontal location of the "cursor" and bounds it
void updateValueH(int delta) {
  horizontal = constrain(horizontal + delta, 0, 31);
  return;
}

//updates the vertical location of the "cursor" and bounds it
void updateValueV(int delta) {
  vertical = constrain(vertical + delta, 0, 31);
  return;
}

//reads the vertical encoder and draws a new pixel depending on the input
void ReadVerticalEncoder() {
  int clk_V = digitalRead(ENCODER_CLK_V);
  if ((clk_V != prevClk_V) && (clk_V == LOW)) {
    int dtV = digitalRead(ENCODER_DT_V);
    int deltaV = dtV == HIGH ? 1 : -1;
    updateValueV(deltaV);
    blinkLED();
  }
  prevClk_V = clk_V;
}

//reads horizontal encoder and draws a new pixel depending on input

void ReadHorizontalEncoder() {
  int clk_H = digitalRead(ENCODER_CLK_H);
  if ((clk_H != prevClk_H) && (clk_H == LOW)) {
    int dtH = digitalRead(ENCODER_DT_H);
    int deltaH = dtH == HIGH ? 1 : -1;
    updateValueH(deltaH);
  }
  prevClk_H = clk_H;
}

//reads the colour wheel encoder and changes the position of the wheel by +1 or -1
void ReadColour() {
  int clk_C = digitalRead(ENCODER_CLK_C);
  if ((clk_C != prevClk_C) && (clk_C == LOW)) {
    int dtC = digitalRead(ENCODER_DT_C);
    int deltaC = dtC == HIGH ? 1 : -1;
    updateRotaryValue(deltaC);
  }
  updateColour();
  prevClk_C = clk_C;
}

//updates the position in the colour wheel, makes sure it does not go out of bounds
void updateRotaryValue(int delta) {
  if ((counter <= 0) && (delta < 0)) { //going left
    counter = 19;
  }
  else if ((counter >= 19) && (delta > 0)) {//going right
    counter = 0;
  }
  else { //add like normal
    counter = counter + delta;
  }
}

//updates the colour of the pixel depending on the position of the colour wheel (using the colours database)
void updateColour() {
  leds[0] = colours[counter];
  FastLED.show();
}

//interrup isr function for the button
void HandleClearButton()
{
  playEtchASketch = true;
  digitalWrite(10, HIGH);
  delay(1000);
  digitalWrite(10, LOW);
  //shouldClearDisplay = true;
}

void loop() {
  ReadVerticalEncoder();
  ReadColour();
  /*
    leds[0] = CRGB ( 0, 0, 255);
    FastLED.show();
    delay(500);
     leds[0] = CRGB ( 255, 0, 0);
    FastLED.show();
    delay(500);
     leds[0] = CRGB ( 0, 255, 0);
    FastLED.show();
    delay(500);*/

  //ReadVerticalEncoder();
  //ReadHorizontalEncoder();
}
