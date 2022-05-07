// Simulation: https://wokwi.com/projects/324794736893231698

// Turn the horizontal rotary encoder (the middle encoder) clockwise to make
// bigger splashes

// Needs both Natasha's rotary encoder code and Reece's microsd card code

// Warning: Don't put underscores in the file names! File will fail to open.

#include <FastLED.h>
#include <SD.h>

#define NUM_STRIPS 32
#define NUM_LEDS_PER_STRIP 32

#define ENCODER_CLK_V 6
#define ENCODER_DT_V 7
#define ENCODER_CLK_H 2
#define ENCODER_DT_H 3

#define ENCODER_CLK_C 5
#define ENCODER_DT_C 4

#define CLEAR_PIN 18

#define CS_PIN 53

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

File root;

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

void ReadHorizontalEncoder()
{
    int clk_H = digitalRead(ENCODER_CLK_H);
    if ((clk_H != prevClk_H) && (clk_H == LOW))
    {
        int dtH = digitalRead(ENCODER_DT_H);
        int deltaH = dtH == HIGH ? 1 : -1;
        updateValueH(deltaH);
        // updateColour();
    }
    prevClk_H = clk_H;
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

#define FLUID_SIM_TIMER 100000 // total time to display fluid sim
#define FRAMES_PER_SPLASH 7 // frames for one wave period
// each splash loop starts at the same position to make the animation appear continuous

void FluidSim()
{
    // set horiztonal encoder position to middle of range
    horizontal = 16;
    int frameDelay = 67; // ms

    // measure encoder while animation is playing
    attachInterrupt(digitalPinToInterrupt(ENCODER_DT_H), ReadHorizontalEncoder, CHANGE);

    unsigned long startFluidSim = millis();

    // simulation will stop after timer runs out 
    while(millis() - startFluidSim < FLUID_SIM_TIMER) {
        // For now, alter the wave period based on the encoder value
        int splashiness = horizontal; // 0 = not splashy, 31 = very splashy

        // TODO alter the delay to make the splashes more realistic
        // frameDelay = map(splashiness, 0, 31, 166, 43);
        
        switch(splashiness) {
            case 0 ... 4:
                playAnimationFile("splashFlat.txt", frameDelay);
                break;
            case 5 ... 8:
                playAnimationFile("splashXS.txt", frameDelay);
                break;
            case 9 ... 12:
                playAnimationFile("splashS.txt", frameDelay);
                break;
            case 13 ... 16:
                playAnimationFile("splashM.txt", frameDelay);
                break;
            case 17 ... 20:
                playAnimationFile("splashL.txt", frameDelay); //splash_l_frame_data
                break;
            case 21 ... 24:
                playAnimationFile("splashXL.txt", frameDelay); //splash_xl_frame_data
                break;
            case 25 ... 31:
                playAnimationFile("splashXXL.txt", frameDelay);
                break;
        }

        // make the wave appear to diminish as time passes
        horizontal-=2;
    }

    detachInterrupt(digitalPinToInterrupt(ENCODER_DT_H));

}

void playAnimationFile(String filename, int delay) {
    File textFile = SD.open(filename);

    if(textFile){
        showBytes(textFile, delay);
    } else {
        Serial.print("Error: failed to open ");
        Serial.print(filename);
        Serial.println();
    }
}

void HandleClearButton()
{
    playEtchASketch = true;
    shouldClearDisplay = true;
}

void clearDisplay()
{
    FastLED.clear();
    FastLED.show();
}

// microSD card stuff

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void showBytes(File f, int del){
  clearDisplay();
  char r,g,b;
  int count=0;
  while(f.available()){
  for(int i=0; i<NUM_STRIPS; i++){
    for(int j=0; j<NUM_LEDS_PER_STRIP; j++){
      if(f.available()){
        leds[NUM_STRIPS-i-1][j].r=2*f.read();
        leds[NUM_STRIPS-i-1][j].g=2*f.read();
        leds[NUM_STRIPS-i-1][j].b=2*f.read();
        count++;
      }
    }
  }
  if(f.available()){
    delay(f.read()/3);
  }
  FastLED.show();
  }
  Serial.println("DOne displaying!");
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
    FastLED.addLeds<WS2812B, A0, GRB>(leds[28], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, A1, GRB>(leds[29], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, A2, GRB>(leds[30], NUM_LEDS_PER_STRIP);
    FastLED.addLeds<WS2812B, A3, GRB>(leds[31], NUM_LEDS_PER_STRIP);

    Serial.begin(9600);
    Serial.println("Serial start");
    if (!SD.begin(CS_PIN)) {
        Serial.println("Card initialization failed!");
        while (true);
    }

    Serial.println("initialization done.");

    Serial.println("Files in the card:");
    root = SD.open("/");
    printDirectory(root, 0);
    Serial.println("");
}

void loop()
{
    // if (shouldClearDisplay)
    // {
    //     clearDisplay();
    //     shouldClearDisplay = false;
    //     lastActive = millis();
    // }

    FluidSim();

}

