#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

int x = 0;
int y = 0;
int col = 0;
bool btn = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
  // Serial1.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
    if (mySerial.available()) {
      byte in = mySerial.read();
      Serial.print("RAW ");
      Serial.println(in,BIN);
      x += bitRead(in, 7) * (bitRead(in, 6)?1:-1);
      y += bitRead(in, 5) * (bitRead(in, 4)?1:-1);
      col += bitRead(in, 3) * (bitRead(in, 2)?1:-1);
      if(bitRead(in, 1)){
        //btn down
        x = 0;
        y = 0;
        col = 0;
      }
      Serial.print(x);
      Serial.print(", ");
      Serial.print(y);
      Serial.print(" | COL = ");
      Serial.println(col);
    }
    

}
