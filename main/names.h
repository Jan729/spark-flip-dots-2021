#ifndef NAMES_H
#define NAMES_H

#include "Arduino.h"
#define CS_PIN 53
#define NUM_STRIPS 32
#define NUM_LEDS_PER_STRIP 32
#define ENCODER_CLK_V 6
#define ENCODER_DT_V 7
#define ENCODER_CLK_H 2
#define ENCODER_DT_H 4
#define ENCODER_CLK_C 3
#define ENCODER_DT_C 5
#define CLEAR_PIN 18
#define NUMFILES 34

uint8_t vertical = 31;
uint8_t horizontal = 31;

int vCounter = 0;
int hCounter = 0;

int prevClk_H = HIGH;
int prevClk_V = HIGH;
int prevClk_C = HIGH;

int counter = 0;

volatile bool playEtchASketch = true;
volatile bool shouldClearDisplay = false;
int prevVertical = 0;
int prevHorizontal = 0;
volatile unsigned long lastActive = millis();
unsigned long IDLE_TIMEOUT = 30000;

CRGB colours[20];
bool black = false;
int switch_cursor = 10000;
int cursor_counter = 0;
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

volatile int lpaddle = 0;
volatile int rpaddle = 0;

// pong decl
void pong();
void clearDisplay();

//gol decl
void gameOfLife(int seed, int tDelay);
void gameOfLife();

#endif

