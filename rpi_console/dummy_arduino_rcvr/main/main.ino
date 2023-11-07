#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
    if (mySerial.available()) {
      // packet = mySerial.read();
      // packet = mySerial.read();
      // if(packet)
      Serial.println((char)mySerial.read());
    }
}
