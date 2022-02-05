// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

//https://www.arduino.cc/en/Tutorial/LibraryExamples/MasterWriter

#include <Wire.h>
#define NUM_BYTES_PER_ROW 4

void setup()
{
    Wire.begin(4);                // join i2c bus with address #4
    Wire.onReceive(receiveEvent); // register event
    Serial.begin(9600);           // start serial for output
    Serial.println("I am receipt printer arduino");
}

void loop()
{
    delay(1000);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
    int rowIdx = 1;

    while (1 <= Wire.available())
    {
        byte data = Wire.read();

        Serial.print(data, BIN);
        if (rowIdx == NUM_BYTES_PER_ROW)
        {
            rowIdx = 1;
            Serial.println();
        }
        else
        {
            rowIdx++;
        }
    }
}
