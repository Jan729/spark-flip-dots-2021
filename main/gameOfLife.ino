#include "names.h"

void gameOfLife(int seed, int tDelay) {
  randomSeed(seed);
  CRGB cellColour = CRGB(random(120, 250), random(120, 250), random(120, 250));
  //Each byte is a row from bottom to top
  byte state[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  byte newstate[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < 8; i++) {
    newstate[i] = (byte)random(100, 255);
  }
  int statesum = 1;
  int statediff = 1;
  int loopno = 1;
  while (statesum > 0 && statediff != 0) {
    //Serial.println("Loopno: ");
    //Serial.println(loopno);
    loopno++;
    clearDisplay();
    //check if the automaton is dead
    statesum = 0;
    statediff = 0;
    //draw state and check if automaton is dead
    for (int i = 7; i > -1; i--) {
      statediff += abs(state[i] - newstate[i]);
      state[i] = newstate[i];
      statesum += state[i];
      //Serial.println(state[i], BIN);
      for (int j = 0; j < 8; j++) {
        if (bitRead(state[i], 7 - j)) {
          for (int r = 4 * j; r < 4 * j + 4; r++) {
            for (int q = 4 * i; q < 4 * i + 4; q++) {
              leds[q][r] = cellColour;
            }
          }
        }
      }
    }
    if (shouldClearDisplay) {
      return;
    }
    FastLED.show();
    delay(tDelay);
    if (shouldClearDisplay) {
      return;
    }
    //update state
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        int self = bitRead(state[i], j);
        int newSelf = 0;
        int num = 0;
        byte above = (i == 7) ? (0) : (state[i + 1]);
        byte below = (i == 0) ? (0) : (state[i - 1]);
        num += bitRead(state[i] >> 1, j) + bitRead(state[i] << 1, j) + bitRead(above, j) + bitRead(below, j) + bitRead(above >> 1, j) + bitRead(above << 1, j) + bitRead(below << 1, j) + bitRead(below >> 1, j);
        /*byte bitgetter=1<<j;
          int self=to1(bitgetter&state[i]);
          int newself=0;
          int num=0;
          byte above=(i==7)?(0):(state[i+1]);
          byte below=(i==0)?(0):(state[i-1]);
          num+=to1((bitgetter>>1)&state[i])+to1(((bitgetter>>1)&state[i]))+to1(above&bitgetter)+to1(below&bitgetter);//horizontal and vertical checks
          num+=to1((bitgetter>>1)&above)+to1((bitgetter<<1)&above)+to1((bitgetter>>1)&below)+to1((bitgetter<<1)&below);
        */
        if (self == 1 && (num == 2 || num == 3)) {
          bitSet(newstate[i], j);
        } else if (self == 0 && num == 3) {
          bitSet(newstate[i], j);
        } else bitClear(newstate[i], j);
      }
    }
  }
  //free(state); // @ reece you can't free these, you did not malloc for them; they are on the stack
  //free(newstate);
}

void gameOfLife() {
  int tdel = 1500;
  CRGB cellColour = CRGB(random(120, 250), random(120, 250), random(120, 250));
}