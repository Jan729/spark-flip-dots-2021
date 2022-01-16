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

// Caution: the led array indexing is different on TinkerCAD
// than the wowki simulator

// leds[0][0] is the top left corner
// leds[0][31] is the top right corner
// leds[31][0] is the bottom left corner
// leds[31][31] is the bottom right corner
boolean leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

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

    CreateDummyPicture();
}

void loop()
{
    SendPunchSequence();

    delay(5000);
}

// Send all 256 pixels as a 1 or 0
void SendPunchSequence()
{
    for (int row = 0; row < NUM_STRIPS; row++)
    {
        Wire.beginTransmission(4); // transmit one row of data to device #4

        // After mapping 8 pixel values to 0 or 1,
        //write 1 byte of data at a time

        for (int col = 0; col < NUM_LEDS_PER_STRIP; col += 8)
        {
            byte compressedBits = CompressedColourData(row, col);
            Wire.write(compressedBits);
            Serial.print(compressedBits, BIN);
        }
        Serial.println();
        if (Wire.endTransmission() != 0)
        {
            Serial.println("Error transmitting!");
        }
    }
}

byte CompressedColourData(int row, int col)
{
    byte data = 0;

    for (int i = 0; i < 8; i++)
    {
        if (leds[row][col + i])
        {
            data |= (1 << i);
        }
    }
    return data;
}

void CreateDummyPicture()
{
    //left eye
    leds[4][3] = 0;
    leds[4][4] = 0;
    leds[5][3] = 0;
    leds[5][4] = 0;

    //right eye
    leds[4][27] = 0;
    leds[4][28] = 0;
    leds[5][27] = 0;
    leds[5][28] = 0;

    //mouth
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
