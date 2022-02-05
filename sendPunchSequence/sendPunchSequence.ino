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
#define NUM_PRINTER_PATTERN_BYTES 32
#define BYTES_PER_ROW 4

// Caution: the led array indexing is different on TinkerCAD
// than the wowki simulator

// temporary array to make TinkerCAD simulation work
boolean leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

// use me for the real code
// CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

byte printerEncodingPattern[NUM_PRINTER_PATTERN_BYTES];

// TODO: program two receipt printer buttons if we want to use both
// algorithms for generating punch patterns
boolean sendSingleColourPattern = true;
void createDummyPicture()
{
    // left eye
    leds[4][3] = 0;
    leds[4][4] = 0;
    leds[5][3] = 0;
    leds[5][4] = 0;

    // right eye
    leds[4][27] = 0;
    leds[4][28] = 0;
    leds[5][27] = 0;
    leds[5][28] = 0;

    // mouth
    for (int col = 7; col <= 21; col++)
    {
        leds[10][col] = 0;
        leds[11][col] = 0;
    }
    for (int col = 7; col <= 21; col++)
    {
        leds[10][col] = col % 2;
    }
}

// maps 8 leds to one byte, row by row, 4 bytes per row
byte compressSingleColourData(int row, int col)
{
    byte data = 0;

    for (int i = 0; i < 8; i++)
    {
        // TODO: uncomment the following condition for the real prototype
        if (leds[row][col + i]) // leds[row][col + i] == CRGB(0x000000)
        {
            data |= (1 << i);
        }
    }
    return data;
}

// can free memory

void generateShadedPunchPattern()
{
    // FIXME find a more memory-efficient way to do this
    boolean uncompressedPattern[NUM_LEDS_PER_STRIP][NUM_STRIPS];

    // for each 2x2 square of leds, average the colours and map it to a shaded 2x2 punch pattern
    // the final image resolution will be reduced to 16x16
    // see the Notion page for more info
    // https://www.notion.so/SendPunchSequence-struct-punch_encoding-pattern-78d25b63250348c6a8cfb363eebb98ca
    for (int rowTopLeft = 0; rowTopLeft < NUM_LEDS_PER_STRIP; rowTopLeft += 2)
    {
        for (int colTopLeft = 0; colTopLeft < NUM_STRIPS; colTopLeft += 2)
        {
            // TODO use the actual CRGB data type when prototyping IRL
            int avgColour = (leds[rowTopLeft][colTopLeft] + leds[rowTopLeft + 1][colTopLeft] + leds[rowTopLeft][colTopLeft + 1] + leds[rowTopLeft + 1][colTopLeft + 1]) / 4;

            // intentionally omitting the break; because
            // i want the remaining holes to get punched too
            switch (avgColour)
            {
            case 4: // punch bottom left
                uncompressedPattern[rowTopLeft + 1][colTopLeft] = 1;
            case 3: // punch top right
                uncompressedPattern[rowTopLeft][colTopLeft + 1] = 1;
            case 2: // punch bottom right
                uncompressedPattern[rowTopLeft + 1][colTopLeft + 1] = 1;
            case 1: // punch top left
                uncompressedPattern[rowTopLeft][colTopLeft] = 1;
            case 0:; // if we get here without entering the above cases, we haven't punched anything
            }
        }
    }

    // compress 32x32 array into 32 bytes
    int byteIdx = 0;
    for (int row = 0; row < NUM_STRIPS; row++)
    {
        for (int col = 0; col < NUM_LEDS_PER_STRIP; col += 8)
        {
            byte data = 0;

            for (int i = 0; i < 8; i++)
            {
                if (uncompressedPattern[row][col + i])
                {
                    data |= (1 << i);
                }

                printerEncodingPattern[byteIdx] = data;
                byteIdx++;
            }
        }
    }
}

// punches a hole (sets a bit to 1) if the led is lit
// image resolution is 32x32
void generatePunchPattern()
{
    int i = 0;
    for (int row = 0; row < NUM_STRIPS; row++)
    {
        for (int col = 0; col < NUM_LEDS_PER_STRIP; col += 8)
        {
            printerEncodingPattern[i] = compressSingleColourData(row, col);
            i++;
        }
    }
}

// Send all 256 pixels as a 1 or 0
void sendPunchSequence()
{
    boolean doneGeneratingPattern = false;
    if (sendSingleColourPattern)
    {
        generatePunchPattern();
    }
    else
    {
        generateShadedPunchPattern();
    }

    int byteIdx = 0;
    for (int row = 0; row < NUM_STRIPS; row++)
    {
        Wire.beginTransmission(4); // transmit one row of data to device #4

        for (int bytes = 0; bytes < BYTES_PER_ROW; bytes++)
        {
            Wire.write(printerEncodingPattern[byteIdx]);
            // Serial.print(printerEncodingPattern[byteIdx], BIN); // TODO remove me when done debugging
            byteIdx++;
        }
        // Serial.println(); // TODO remove me when done debugging
        if (Wire.endTransmission() != 0)
        {
            Serial.println("Error transmitting!");
        }
    }
}

void setup()
{
    Wire.begin(); // join i2c bus (address optional for master)
    Serial.begin(9600);
    Serial.println("I am etch a sketch arduino");

    for (int row = 0; row < NUM_STRIPS; row++)
    {
        for (int col = 0; col < NUM_LEDS_PER_STRIP; col++)
        {
            leds[row][col] = 1;
        }
    }

    createDummyPicture();
}

void loop()
{
    sendPunchSequence();

    // TODO program print button

    delay(5000);
}