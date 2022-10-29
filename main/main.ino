//The way to beat the interrupt is to check for state variables

#include <SD.h>
#include <FastLED.h>
#include "names.h"
#include "shader.h"
#include "fsm.h"

void setup() {
  pinMode(CLEAR_PIN, INPUT);
  // attachInterrupt(digitalPinToInterrupt(CLEAR_PIN), HandleClearButton, RISING);
  
  pinMode(ENCODER_CLK_H, INPUT);
  pinMode(ENCODER_DT_H, INPUT);
  pinMode(ENCODER_CLK_V, INPUT);
  pinMode(ENCODER_DT_V, INPUT);
  pinMode(ENCODER_CLK_C, INPUT);
  pinMode(ENCODER_DT_C, INPUT);
  // tell FastLED there's 32 WS2812B leds on pins
  //a
  FastLED.addLeds<NEOPIXEL, 29>(leds[0], 32);
  FastLED.addLeds<NEOPIXEL, 28>(leds[1], 32);
  FastLED.addLeds<NEOPIXEL, 27>(leds[2], 32);
  FastLED.addLeds<NEOPIXEL, 26>(leds[3], 32);
  FastLED.addLeds<NEOPIXEL, 25>(leds[4], 32);
  FastLED.addLeds<NEOPIXEL, 24>(leds[5], 32);
  FastLED.addLeds<NEOPIXEL, 23>(leds[6], 32);
  FastLED.addLeds<NEOPIXEL, 22>(leds[7], 32);
  //b
  FastLED.addLeds<NEOPIXEL, 36>(leds[8], 32);
  FastLED.addLeds<NEOPIXEL, 37>(leds[9], 32);
  FastLED.addLeds<NEOPIXEL, 35>(leds[10], 32);
  FastLED.addLeds<NEOPIXEL, 34>(leds[11], 32);
  FastLED.addLeds<NEOPIXEL, 33>(leds[12], 32);
  FastLED.addLeds<NEOPIXEL, 32>(leds[13], 32);
  FastLED.addLeds<NEOPIXEL, 31>(leds[14], 32);
  FastLED.addLeds<NEOPIXEL, 30>(leds[15], 32);

  FastLED.addLeds<NEOPIXEL, 45>(leds[16], 32);
  FastLED.addLeds<NEOPIXEL, 44>(leds[17], 32);
  FastLED.addLeds<NEOPIXEL, 43>(leds[18], 32);
  FastLED.addLeds<NEOPIXEL, 42>(leds[19], 32);
  FastLED.addLeds<NEOPIXEL, 39>(leds[20], 32);
  FastLED.addLeds<NEOPIXEL, 40>(leds[21], 32);
  FastLED.addLeds<NEOPIXEL, 41>(leds[22], 32);
  FastLED.addLeds<NEOPIXEL, 38>(leds[23], 32);
  //d
  FastLED.addLeds<NEOPIXEL, 57>(leds[24], 32);
  FastLED.addLeds<NEOPIXEL, 56>(leds[25], 32);
  FastLED.addLeds<NEOPIXEL, 55>(leds[26], 32);
  FastLED.addLeds<NEOPIXEL, 54>(leds[27], 32);
  FastLED.addLeds<NEOPIXEL, 49>(leds[28], 32);
  FastLED.addLeds<NEOPIXEL, 48>(leds[29], 32);
  FastLED.addLeds<NEOPIXEL, 47>(leds[30], 32);
  FastLED.addLeds<NEOPIXEL, 46>(leds[31], 32);
  SD.begin(CS_PIN);
  FastLED.setBrightness(125);

  //setup colours array
  int hue = 12;
  for (int i = 0; i < 20; i++) {
    colours[i] = CHSV(hue * i, 255, 255);
  }

  // colours[19] = CRGB::Black;
  // set board to black
  for (int i = 0; i < NUM_STRIPS; i++) {
    for (int k = 0; k < NUM_LEDS_PER_STRIP; k++) {
      leds[i][k] = CRGB::Black;
    }
  }

  //start in middle
  leds[16][16] = CRGB::Red;
  FastLED.show();
  //REMOVE THIS
  clearDisplay();
  // pong();
}

void loop() {
  HandleClearButton(); //rpress reset to change from idle to rainbow
  if (shouldClearDisplay)
  {
    clearDisplay();
    shouldClearDisplay = false;
    lastActive = millis();
  }

  if (playEtchASketch)
  {
    BlinkEtchASketchCursor();
    ReadVerticalEncoder();
    ReadHorizontalEncoder();
    ReadColour();
    CheckIfIdle();
  }
  else
  {
    run_shader();
    // int idleOption = random(0, 3);
    // switch (idleOption) {
    //   case 0:
    //     // showRandomAnimation();
    //     run_shader();
    //     break;
    //   case 1:
    //     gameOfLife(1500,1500);
    //     break;
    //   case 2:
    //     run_shader();
    //     break;
    // }
  }
}

void BlinkEtchASketchCursor(){
    int clk_div = 10;
    cursor_counter++;
    
    if(cursor_counter % 100 > 80){
      leds[vertical][horizontal] = CRGB::Black;
    }
    else{
      leds[vertical][horizontal] = colours[counter];
    }
    FastLED.show();
    
    // cursor_counter++;
    // if (cursor_counter % switch_cursor == 0) {
    //   if (!black) {
    //     leds[vertical][horizontal] = CRGB::Black;
    //     black = true;
    //   }
    //   else {
    //     // eraser
    //     if (counter == 19) {
    //       leds[vertical][horizontal].setRGB(255, 20, 147);
    //     }
    //     // show current color
    //     else {
    //       leds[vertical][horizontal] = colours[counter];
    //     }
    //     black = false;
    //   }
    //   FastLED.show(); 
    // }
}

void CheckIfIdle()
{
  if (millis() - lastActive > IDLE_TIMEOUT)
  {
    clearDisplay();
    playEtchASketch = false;
  }
}

//Clear the display
void clearDisplay() {
  FastLED.clear();
  FastLED.show();
}



void HandleClearButton()
{
  const int debounceTime =250;

  if(prevBtn == LOW && digitalRead(CLEAR_PIN)==HIGH){ //on posedge, start timer
    btnDebounceTimer = millis();
    prevBtn = HIGH;
  }
  
  else if(prevBtn == HIGH && digitalRead(CLEAR_PIN)==LOW && millis()-btnDebounceTimer > debounceTime){
      playEtchASketch = true;
      shouldClearDisplay = true;
      prevBtn = LOW;
  }
}

void updateValueH(int delta) {
  horizontal = wrap_constrain(horizontal + delta, 0, 31);
  return;
}

//updates the vertical location of the "cursor" and bounds it
void updateValueV(int delta) {
  vertical = wrap_constrain(vertical + delta, 0, 31);
  return;
}

//reads the vertical encoder and draws a new pixel depending on the input
void ReadVerticalEncoder() {
  int clk_V = digitalRead(ENCODER_CLK_V);
  if ((clk_V != prevClk_V) && (clk_V == LOW)) {
    leds[vertical][horizontal] = colours[counter];
    int dtV = digitalRead(ENCODER_DT_V);
    int deltaV = dtV == HIGH ? 1 : -1;
    updateValueV(deltaV);
    updateColour();
  }
  prevClk_V = clk_V;
}

//reads horizontal encoder and draws a new pixel depending on input
void ReadHorizontalEncoder() {
  int clk_H = digitalRead(ENCODER_CLK_H);
  if ((clk_H != prevClk_H) && (clk_H == LOW)) {
    leds[vertical][horizontal] = colours[counter];
    int dtH = digitalRead(ENCODER_DT_H);
    int deltaH = dtH == HIGH ? -1 : 1;
    updateValueH(deltaH);
    updateColour();
  }
  prevClk_H = clk_H;
}

//reads the colour wheel encoder and changes the position of the wheel by +1 or -1
void ReadColour() {
  int clk_C = digitalRead(ENCODER_CLK_C);
  if ((clk_C != prevClk_C) && (clk_C == LOW)) {
    int dtC = digitalRead(ENCODER_DT_C);
    int deltaC = dtC == HIGH ? -1 : 1;
    updateRotaryValue(deltaC);
  }
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

//updates the colour of the pixel depending on the position of the colour wheel
void updateColour() {
  leds[vertical][horizontal] = colours[counter];
  FastLED.show();
  lastActive = millis();
}

void showRandomAnimation() {
  int randy = random(1, NUMFILES+1);
  String filename = "anis/" + String(randy) + ".txt";
  //Serial.println(filename);
  File f = SD.open(filename);
  //Serial.println(f.name());
  showBytes(f, 100);
  f.close();

}

//Function for showing textfile
void showBytes(File f, int del) {
  clearDisplay();
  char r, g, b;
  int count = 0;
  while (f.available()) {
    for (int i = 0; i < NUM_STRIPS; i++) {
      for (int j = 0; j < NUM_LEDS_PER_STRIP; j++) {
        if (f.available()) {
          leds[i][NUM_LEDS_PER_STRIP - j - 1].r = 2 * f.read();
          leds[i][NUM_LEDS_PER_STRIP - j - 1].g = 2 * f.read();
          leds[i][NUM_LEDS_PER_STRIP - j - 1].b = 2 * f.read();
          count++;
        }
      }
    }
    if (f.available()) {
      delay(f.read() / 3);
    } else {
      delay(500);
    }
    if (shouldClearDisplay) {
      f.close();
      return;
    }
    FastLED.show();
  }
}


void changePixel(uint32_t hex, int i, int j) {
  leds[i][j] = CRGB(hex);
  FastLED.show();
}


/*
 * 
 * FastLED.addLeds<WS2812B, 22, GRB>(leds[0], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 23, GRB>(leds[1], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 24, GRB>(leds[2], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 25, GRB>(leds[3], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 26, GRB>(leds[4], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 27, GRB>(leds[5], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 28, GRB>(leds[6], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 29, GRB>(leds[7], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 30, GRB>(leds[8], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 31, GRB>(leds[9], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 32, GRB>(leds[10], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 33, GRB>(leds[11], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 34, GRB>(leds[12], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 35, GRB>(leds[13], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 36, GRB>(leds[14], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 37, GRB>(leds[15], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 38, GRB>(leds[16], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 39, GRB>(leds[17], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 40, GRB>(leds[18], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 41, GRB>(leds[19], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 42, GRB>(leds[20], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 43, GRB>(leds[21], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 44, GRB>(leds[22], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 45, GRB>(leds[23], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 46, GRB>(leds[24], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 47, GRB>(leds[25], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 48, GRB>(leds[26], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 49, GRB>(leds[27], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, A0, GRB>(leds[28], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, A1, GRB>(leds[29], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, A2, GRB>(leds[30], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, A3, GRB>(leds[31], NUM_LEDS_PER_STRIP);
 */
