// ArrayOfLedArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers

// To view simulation: see https://wokwi.com/arduino/projects/316548175614706242
// To edit simulation: go to the above link, click "Login" (eg with github or email),
// then click the arrow next to "Save" > make a copy

// Differences between this simulator and our actual display:
// 1) The simulator is a bit laggy
// 2) The data, VSS, and GND pins are attached to the strip closest
// to the LED with index 0. We'll want to mount the LED strips with
// the wiring on the left side of the display if we want to keep this
// coordinate system

#include <FastLED.h>

#define NUM_STRIPS 32
#define NUM_LEDS_PER_STRIP 32

// leds[0][0] is the bottom left corner
// leds[0][31] is the bottom right corner
// leds[31][0] is the top left corner
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

void setup() {
  // tell FastLED there's 32 WS2812B leds on pins 10-41
  FastLED.addLeds<WS2812B, 10, GRB>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 11, GRB>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 12, GRB>(leds[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 13, GRB>(leds[3], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 14, GRB>(leds[4], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 15, GRB>(leds[5], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 16, GRB>(leds[6], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 17, GRB>(leds[7], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 18, GRB>(leds[8], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 19, GRB>(leds[9], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 20, GRB>(leds[10], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 21, GRB>(leds[11], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 22, GRB>(leds[12], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 23, GRB>(leds[13], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 24, GRB>(leds[14], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 25, GRB>(leds[15], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 26, GRB>(leds[16], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 27, GRB>(leds[17], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 28, GRB>(leds[18], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 29, GRB>(leds[19], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 30, GRB>(leds[20], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 31, GRB>(leds[21], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 32, GRB>(leds[22], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 33, GRB>(leds[23], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 34, GRB>(leds[24], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 35, GRB>(leds[25], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 36, GRB>(leds[26], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 37, GRB>(leds[27], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 38, GRB>(leds[28], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 39, GRB>(leds[29], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 40, GRB>(leds[30], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 41, GRB>(leds[31], NUM_LEDS_PER_STRIP);

}

void loop() {
  // This outer loop will go over each strip, one at a time
  for(int x = 0; x < NUM_STRIPS; x++) {
    // This inner loop will go over each led in the current strip, one at a time
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      leds[x][i] = CRGB::Red;
      FastLED.show();
      leds[x][i] = CRGB::Black;
    }
  }
}
