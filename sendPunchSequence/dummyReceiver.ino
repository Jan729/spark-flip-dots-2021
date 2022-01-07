//Source: https://www.arduino.cc/en/Tutorial/LibraryExamples/MasterWriter

//Endlessly waits for data from I2C bus and prints out the data it received

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
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  int byteIdx = 1;
  //FIXME bytes received are not in order
  while(1 <= Wire.available())
  {
    byte i = Wire.read();
    Serial.print(i, BIN);
    Serial.print(" ");
    if(byteIdx == NUM_BYTES_PER_ROW) {
      byteIdx = 1;
      Serial.println();
      //Serial.print("Wire.available(): ");
      //Serial.print(Wire.available());
    } else {
      byteIdx++;
    }      
  }
  
  Serial.println();
}
