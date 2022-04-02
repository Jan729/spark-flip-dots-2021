// LINK TO SIMULATION: https://www.tinkercad.com/things/lewHedJkHkf-sendpunchsequencebinarydataonly/editel?sharecode=ONtNzXR60xOcqX0Z4z3sRgWzjzQAYXEAMgc4vC_exHc
// Connect the arduinos togther as follows:
// GND to GND, 20 to 20, 21 to 21

// WARNING: this file will not compile because it's missing the stuff inside setup()

/* Overview of file:
* sendPunchSequence() - to be called in the Print button interrupt handler
* generatePunchPattern() - algo #1. punch a hole when the led is lit
* generateShadedPunchPattern() - algo #2. printer pattern algo that makes 2x2 shaded pixels
* compressSingleColourData() - helper function for generatePunchPattern
* printLeadingZeroes() - for debugging only. serial.print the bytes sent
*/ 

// TODO: Decide which printer algorithm to use. which one looks better?
// Alternatively, you could program a second button and have a second print button if you can't decide.


#include <Wire.h>
#include <FastLED.h>

#define NUM_STRIPS 32
#define NUM_LEDS_PER_STRIP 32
#define NUM_PRINTER_PATTERN_BYTES 32
#define ROWS_PER_SHADED_PIXEL 2
#define BYTES_PER_ROW 4


CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

boolean sendSingleColourPattern = true;

void printLeadingZeroes(byte var) {
  for (int i = 0; i < 7; i++) {
    Serial.write((var >> i) & 1 ? '1' : '0');
  }
}

// maps 8 leds to one byte
// eg compressSingleColourData(0, 0) will create a byte with
// the least signficant bit as leds[0][0] and the most significant bit as leds[0][7]
byte compressSingleColourData(int row, int col)
{
    byte data = 0;

    for (int i = 0; i < 8; i++)
    {
        data |= ((leds[row][col+i] == CRGB(0x000000)) << i);
    }
    return data;
}

void generateShadedPunchPattern(byte *patternBuffer)
{
    byte *shadedPatternRow = (byte *)malloc(NUM_LEDS_PER_STRIP * ROWS_PER_SHADED_PIXEL * sizeof(byte));
    byte compressedData;
    byte byteIdx = 0;

    // average the colours and map it to a shaded 2x2 punch pattern
    // the final image resolution will be reduced to 16x16, with 2x2 pixels
    // see the Notion page for more info
    // https://www.notion.so/SendPunchSequence-struct-punch_encoding-pattern-78d25b63250348c6a8cfb363eebb98ca
    for (int rowTopLeft = 0; rowTopLeft < NUM_LEDS_PER_STRIP; rowTopLeft += 2)
    {
        for (int colTopLeft = 0; colTopLeft < NUM_STRIPS; colTopLeft += 2)
        {
            // TODO use the actual CRGB colour mapping when prototyping IRL
            // where yellow = 1, green = 2, red = 3, blue or purple = 4
            CRGB avgColour = (leds[rowTopLeft][colTopLeft] + leds[rowTopLeft + 1][colTopLeft] + leds[rowTopLeft][colTopLeft + 1] + leds[rowTopLeft + 1][colTopLeft + 1]) / 4;
            
            byte topLeftHole = colTopLeft;
            byte topRightHole = colTopLeft + 1;
            byte bottomLeftHole = 32 + colTopLeft;
            byte bottomRightHole = 32 + colTopLeft + 1;

            // intentionally omitting the "break;"" because
            // i want the remaining holes to get punched too
            switch (avgColour)
            {
            case 4:
                shadedPatternRow[bottomLeftHole] = 1;
            case 3:
                shadedPatternRow[topRightHole] = 1;
            case 2:
                shadedPatternRow[bottomRightHole] = 1;
            case 1:
                shadedPatternRow[topLeftHole] = 1;
            case 0:; // if we get here without entering the above cases, we leave the paper untouched
            }
        }

        for (int i = 0; i < NUM_LEDS_PER_STRIP * ROWS_PER_SHADED_PIXEL; i++)
        {
            if (shadedPatternRow[i] == 1)
            {
                compressedData |= (1 << i);
            }

            if ((i + 1) % 8 == 0)
            {
                patternBuffer[byteIdx] = compressedData;
                compressedData = 0;
                byteIdx++;
            }
        }
    }
    free(shadedPatternRow);
}

// punches a hole (sets a bit to 1) if the led is lit
void generatePunchPattern(byte *patternBuffer)
{
    int i = 0;
    for (int row = 0; row < NUM_STRIPS; row++)
    {
        for (int col = 0; col < NUM_LEDS_PER_STRIP; col += 8)
        {
            patternBuffer[i] = compressSingleColourData(row, col);
            i++;
        }
    }
}

// Send all 256 pixels as a 1 or 0
void sendPunchSequence()
{
    boolean doneGeneratingPattern = false;
    byte * patternBuffer = (byte *)malloc(NUM_PRINTER_PATTERN_BYTES * sizeof(byte));

    if (sendSingleColourPattern)
    {
        generatePunchPattern(patternBuffer);
    }
    else
    {
        generateShadedPunchPattern(patternBuffer);
    }

    int byteIdx = 0;
    for (int row = 0; row < NUM_STRIPS; row++)
    {
        Wire.beginTransmission(4); 

      	// transmit one row of data to device #4
        for (int bytes = 0; bytes < BYTES_PER_ROW; bytes++)
        {
            Wire.write(patternBuffer[byteIdx]);
            printLeadingZeroes(patternBuffer[byteIdx]);// TODO remove prints when done debugging
            byteIdx++;
        }
        Serial.println();
        if (Wire.endTransmission() != 0)
        {
            Serial.println("Error!");
        }
    }
    free(patternBuffer);
}

void checkPrintButton() {
    int printButton = digitalRead(buttonPin);

    if (printButton == HIGH) {
        sendPunchSequence();
    } 

    // TODO: how long should we wait until printing is complete before resuming gameplay?
    // we don't want the leds to change while printing
    delay(10000); 
}

void setup()
{
    Wire.begin(); // join i2c bus (address optional for master)
    Serial.begin(9600);
}

void loop()
{
    checkPrintButton();
}
