// Simulation: https://wokwi.com/arduino/projects/321524485770445396

// enter the date and time manually (cuz we don't have internet access to check time automatically)
// then start the simulation

#include <FastLED.h>

#define NUM_STRIPS 32
#define NUM_LEDS_PER_STRIP 32

int hour = 12;
int minute = 20;
#define MONTH 5
#define DAY 14
#define DAY_OF_WEEK "SAT"
#define DAY_OF_WEEK_LEN 8
#define CLOCK_GREEN CRGB(0xFF66FF66)

bool playEtchASketch = false; // wired to start/clear interrupt button

// 5x7 digits, MSB is top left, LSB is bottom right, every 5 bits is one row from left to right
const String nums[] = {
  "01110100011000100000100011000101110", //0
  "00000000010000100000000010000100000", //1
  "01110000010000101110100001000001110", //2
  "01110000010000101110000010000101110", //3
  "10001100011000101110000010000100000", //4
  "01110100001000001110000010000101110", //5
  "01110100001000001110100011000101110", //6
  "01110000010000100000000010000100000", //7
  "01110100011000101110100011000101110", //8
  "01110100011000101110000010000100000", //9
};

// leds[0][0] is the bottom left corner
// leds[0][31] is the bottom right corner
// leds[31][0] is the top left corner
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

uint32_t letToBin(char a){//returns top right to bottom left, with LSB botleft, MSB topright, top to bottom then left to right
  switch(a){
    case 'a': case 'A':
      return 0b0111110100101001010001111;
    case 'b': case 'B':
      return 0b0000001010101011000111111;
    case 'c': case 'C':
      return 0b0101010001100011000101110;
    case 'd': case 'D':
      return 0b0000001110100011000111111;
    case 'e': case 'E':
      return 0b1000110101101011010111111;
    case 'f': case 'F':
      return 0b1000010100101001010011111;
    case 'g': case 'G':
      return 0b0010000110101011000101110;
    case 'h': case 'H':
      return 0b1111100100001000010011111;
    case 'i': case 'I':
      return 0b1000110001111111000110001;
    case 'j': case 'J':
      return 0b1000011110100011000110110;
    case 'k': case 'K':
      return 0b0000010001010100010011111;
    case 'l': case 'L':
      return 0b0000000001000010000111111;
    case 'm': case 'M':
      return 0b0111110000111001000001111;
    case 'n': case 'N':
      return 0b1111100010001000100011111;
    case 'o': case 'O':
      return 0b0111010001100011000101110;
    case 'p': case 'P':
      return 0b0100010100101001010011111;
    case 'q': case 'Q':
      return 0b0110110010101011000101110;
    case 'r': case 'R':
      return 0b0101110100101001010011111;
    case 's': case 'S':
      return 0b1011010101101011010101101;
    case 't': case 'T':
      return 0b1000010000111111000010000;
    case 'u': case 'U':
      return 0b1111000001000010000111110;
    case 'v': case 'V':
      return 0b1110000010000010001011100;
    case 'w': case 'W':
      return 0b1111000001001110000111110;
    case 'x': case 'X':
      return 0b1000101010001000101010001;
    case 'y': case 'Y':
      return 0b1000001000001110100010000;
    case 'z': case 'Z':
      return 0b1000111001101011001110001;
    case ' ':
      return 0;
    default:
      return 0b0100010100101011000001000;

  }
}

void plotLetter(uint32_t let, int topRow, int leftCol) {
  Serial.println(let);
  uint32_t letter = let;
  for(int col=leftCol; col>leftCol-5; col--) {
    for(int row=topRow; row>topRow-5; row--) {
      Serial.print(letter & 1UL);
      leds[row][col] = letter & 1UL ? CLOCK_GREEN : CRGB::Black;
      letter >> 1UL;
    }
  }
}

// 'day' should be a three char string eg, 'MON', 'TUE'
// i'm too lazy to validate input
void plotDayOfWeek() {
  int topRow = 29;
  int leftMostCol = 8;
  String day = DAY_OF_WEEK;

  for(int i=0; i<=2; i++) { // plot letters from left to right
    plotLetter(letToBin(day[i]), topRow, leftMostCol + i*6);
  }
  FastLED.show();
}

void setup()
{

    // pinMode(ENCODER_CLK_H, INPUT);
    // pinMode(ENCODER_DT_H, INPUT);
    // pinMode(ENCODER_CLK_V, INPUT);
    // pinMode(ENCODER_DT_V, INPUT);
    // pinMode(ENCODER_CLK_C, INPUT);
    // pinMode(ENCODER_DT_C, INPUT);

    // Clear button will interrupt animations and clear display
    // pinMode(CLEAR_PIN, INPUT);
    // attachInterrupt(digitalPinToInterrupt(CLEAR_PIN), HandleClearButton, LOW);

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

    // leds[0][0] = CRGB::Red;
    // FastLED.show();

    Serial.begin(9600);
}

void loop()
{
    // if (shouldClearDisplay)
    // {
    //     clearDisplay();
    //     shouldclearDisplay = false;
    //     lastActive = millis();
    // }

    // if (playEtchASketch)
    // {
    //     ReadVerticalEncoder();
    //     ReadHorizontalEncoder();
    //     ReadColour();
    //     CheckIfIdle();
    // }
    // else
    // {
        clearDisplay();
        PlayAnimations();
    // }
}

void PlayAnimations()
{
    // question: how do we choose which animation to play next? fixed order or random?
    showClock();
}

void clearDisplay()
{
    FastLED.clear();
    FastLED.show();
}

void showClock() {

    // start time
    int hourBig = hour / 10;
    int hourSmall = hour % 10;
    int minuteBig = minute / 10;
    int minuteSmall = minute % 10;

    plotDateSlash();
    plotDate();
    plotDayOfWeek();

    while(true) { // TODO: how long to leave the clock display up for?
    // TODO adjust time dynamically based on millis(). if you play animations in between
    // showClock() calls, the clock will start at the same time, every time

    plotDigit(hourBig, 18, 2);
    plotDigit(hourSmall, 18, 8);
    plotDigit(minuteBig, 18, 16);
    plotDigit(minuteSmall, 18, 22);
    plotColon(16, 15, CLOCK_GREEN);

    if (playEtchASketch)
    {
        return;
    }

    // UNCOMMENT THIS LOOP FOR A HOURS:MINUTES clock
    // COMMENT OUT THIS LOOP FOR A MINUTE:SECONDS clock
    for (int sec = 0; sec <= 59; sec++) {
        delay(900);
        plotColon(13, 15, CRGB::Black); // blink colon
        delay(100);
    }


    // set max time to 23:59
    if(hourBig == 2 
        && hourSmall == 3 
        && minuteBig == 5
        && minuteSmall == 9) {
        hourBig = 0;
        hourSmall = 0;
        minuteBig = 0;
        minuteSmall = -1; //adjust for inc below
    }

    minuteSmall++;

    if (minuteSmall > 9) {
        minuteSmall = 0;
        minuteBig++;
        if(minuteBig > 5) {
        minuteBig = 0;
        hourSmall++;
        }
    }

    if(hourSmall > 9) {
        hourSmall = 0;
        hourBig++;
    }
    }
}

// tip: the numbers are only 5x7, but you can overlap the 7x7 numbers array images
// by one col because the first and last col is just black
void plotDigit(int number, int topLeftRow, int topLeftCol) {
    int i = 0;
    for(int row = topLeftRow; row > topLeftRow - 7; row--) {
        for(int col = topLeftCol; col < topLeftCol + 5; col++) {
            leds[row][col] = nums[number].charAt(i) == '1' ? CLOCK_GREEN : CRGB::Black;
            i++;
        }
    }
    FastLED.show();
}

void plotColon(int row, int col, CRGB colour) {
    leds[row][col] = colour;
    leds[row+2][col] = colour;
    FastLED.show();
}

void plotDateSlash() {
    leds[10][16] = CLOCK_GREEN;
    leds[9][16] = CLOCK_GREEN;
    leds[8][16] = CLOCK_GREEN;
    leds[7][15] = CLOCK_GREEN;
    leds[6][15] = CLOCK_GREEN;
    leds[5][15] = CLOCK_GREEN;
    leds[4][14] = CLOCK_GREEN;
    leds[3][14] = CLOCK_GREEN;
    leds[2][14] = CLOCK_GREEN;
    FastLED.show();
}

void plotDate() {
    plotDigit(DAY / 10, 9, 19);
    plotDigit(DAY % 10, 9, 25);
    plotDigit(MONTH / 10, 9, 1);
    plotDigit(MONTH % 10, 9, 7);
}