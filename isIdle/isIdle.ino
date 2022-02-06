// Simulation: https://wokwi.com/arduino/projects/321524485770445396

// If you stop drawing and wait for IDLE_TIMEOUT (ms), the dummy animation function will start
// Press the red Clear button to clear the animation and draw agains

/* Referenced from Natasha's code
Leftmost encoder is for vertical movement, the middle is for horizontal
and the last one is for colour picking. Refer to the Notion
(API Map ->Read Colour -> Open) for the colour wheel
*/

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

// variables used in interrupt service routines should be volatile
// cuz it prevents weird stuff from happening
volatile bool playEtchASketch = true;
volatile bool shouldClearDisplay = false;
int prevVertical = 0;
int prevHorizontal = 0;
volatile unsigned long lastActive = millis();
unsigned long IDLE_TIMEOUT = 10000;

// leds[0][0] is the bottom left corner
// leds[0][31] is the bottom right corner
// leds[31][0] is the top left corner
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

void updateValueH(int delta)
{
    horizontal = constrain(horizontal + delta, 0, 31);
    return;
}

void updateValueV(int delta)
{
    vertical = constrain(vertical + delta, 0, 31);
    return;
}

void setup()
{

    pinMode(ENCODER_CLK_H, INPUT);
    pinMode(ENCODER_DT_H, INPUT);
    pinMode(ENCODER_CLK_V, INPUT);
    pinMode(ENCODER_DT_V, INPUT);
    pinMode(ENCODER_CLK_C, INPUT);
    pinMode(ENCODER_DT_C, INPUT);

    // Clear button will interrupt animations and clear display
    pinMode(CLEAR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(CLEAR_PIN), HandleClearButton, LOW);

    // tell FastLED there's 32 WS2812B leds on pins 10-41
    FastLED.addLeds<WS2812B, 22, GRB>(leds[0], NUM_LEDS_PER_STRIP);
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
    FastLED.addLeds<WS2812B, 50, GRB>(leds[28], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 51, GRB>(leds[29], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 52, GRB>(leds[30], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, 53, GRB>(leds[31], NUM_LEDS_PER_STRIP);

    leds[0][0] = CRGB::Red;
    FastLED.show();
}

void ReadVerticalEncoder()
{
    int clk_V = digitalRead(ENCODER_CLK_V);
    if ((clk_V != prevClk_V) && (clk_V == LOW))
    {
        int dtV = digitalRead(ENCODER_DT_V);
        int deltaV = dtV == HIGH ? 1 : -1;
        updateValueV(deltaV);
        updateColour();
    }
    prevClk_V = clk_V;
}

void ReadHorizontalEncoder()
{
    int clk_H = digitalRead(ENCODER_CLK_H);
    if ((clk_H != prevClk_H) && (clk_H == LOW))
    {
        int dtH = digitalRead(ENCODER_DT_H);
        int deltaH = dtH == HIGH ? 1 : -1;
        updateValueH(deltaH);
        updateColour();
    }
    prevClk_H = clk_H;
}

void ReadColour()
{
    int clk_C = digitalRead(ENCODER_CLK_C);
    if ((clk_C != prevClk_C) && (clk_C == LOW))
    {
        int dtC = digitalRead(ENCODER_DT_C);
        int deltaC = dtC == HIGH ? 1 : -1;
        updateRotaryValue(deltaC);
    }
    prevClk_C = clk_C;
}

void updateRotaryValue(int delta)
{
    if ((counter <= 0) && (delta < 0))
    { // going left
        counter = 19;
    }
    else if ((counter >= 19) && (delta > 0))
    { // going right
        counter = 0;
    }
    else
    { // add like normal
        counter = counter + delta;
    }
}
void updateColour()
{
    if ((((counter == 19) || (counter == 0)) || (counter == 1)) || (counter == 2))
    {
        leds[vertical][horizontal] = CRGB::Red;
        FastLED.show();
        // leds[i] = FF595E; from array of leds (leds is the name)
    }
    else if (((counter == 3) || (counter == 4)) || (counter == 5))
    {
        leds[vertical][horizontal] = CRGB::LightGreen;
        FastLED.show();
        // leds[i] = 8AC926;
    }
    else if ((((counter == 6) || (counter == 7)) || (counter == 8)) || (counter == 9))
    {
        leds[vertical][horizontal] = CRGB::Yellow;
        FastLED.show();
        // leds[i] = FFCA3A;
    }

    else if (((counter == 10) || (counter == 11)) || (counter == 12))
    {
        leds[vertical][horizontal] = CRGB::MediumPurple;
        FastLED.show();
        // leds[i] = 9478BA;
    }
    else if (((counter == 13) || (counter == 14)) || (counter == 15))
    {
        leds[vertical][horizontal] = CRGB::Black;
        FastLED.show();
        // leds[i] = 000000;
    }
    else if (((counter == 16) || (counter == 17)) || (counter == 18))
    {
        leds[vertical][horizontal] = CRGB::SkyBlue;
        FastLED.show();
        // leds[i] = 1C90D9;
    }
    else
    {
        leds[vertical][horizontal] = CRGB::Red;
        FastLED.show();
        // leds[i] = FF595E;
    }
    lastActive = millis();
}

void loop()
{
    if (shouldClearDisplay)
    {
        ClearDisplay();
        shouldClearDisplay = false;
        lastActive = millis();
    }

    if (playEtchASketch)
    {
        ReadVerticalEncoder();
        ReadHorizontalEncoder();
        ReadColour();
        CheckIfIdle();
    }
    else
    {
        PlayAnimations();
    }
}

void CheckIfIdle()
{

    if (millis() - lastActive > IDLE_TIMEOUT)
    {
        ClearDisplay();
        playEtchASketch = false;
    }
}

void PlayAnimations()
{

    for (int i = 0; i < NUM_STRIPS; i++)
    {
        for (int j = 0; j < NUM_LEDS_PER_STRIP; j++)
        {
            leds[i][j] = CRGB::Aquamarine;
        }
        FastLED.show();

        if (playEtchASketch)
        {
            return;
        }
    }
}

void HandleClearButton()
{
    playEtchASketch = true;
    shouldClearDisplay = true;
}

void ClearDisplay()
{
    for (int row = 0; row < NUM_STRIPS; row++)
    {
        for (int col = 0; col < NUM_LEDS_PER_STRIP; col++)
        {
            leds[row][col] = CRGB::CRGB::Black;
        }
    }
    FastLED.show();
}
