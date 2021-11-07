// data matrix stores state of LEDs
// 0 = off, 1 = on
// TinkerCAD demo: https://www.tinkercad.com/things/fR6m3BTW82e-copy-of-8-bit-shift-register-led-onoff-with-ldr/editel?tenant=circuits

// 1 shift register can output 1 byte of data aka 8 bits
// to make the shift registers easier to program,
// these values can be multiples of 8 
#define NUM_ROWS 16
#define NUM_COLS 16
#define NUM_BYTES 32 //(NUM_ROWS*NUM_COLS)/8
#define FIRST_SHIFT_REG_PIN 6

int selectedRow = 0; //0 is the bottommost row
int selectedCol = 0;//0 is the leftmost column
byte displayMatrix[NUM_BYTES] = {0}; //initialized to 0

int latchPin = 4;  // Latch pin of 74HC595 is connected to Digital pin 4
int clockPin = 5; // Clock pin of 74HC595 is connected to Digital pin 5
int shiftRegDataPins[NUM_BYTES];
// source: https://lastminuteengineers.com/74hc595-shift-register-arduino-tutorial/

void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);  

  //initialize shift register data pins
  // TODO: will we need to chain multiple shift registers together?
  for(int pinNum = 0; pinNum < NUM_BYTES; pinNum++){
    shiftRegDataPins[pinNum + FIRST_SHIFT_REG_PIN] = pinNum;
    pinMode(pinNum, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  fillEntireDisplay(B00000000);
  delay(1000);

  fillEntireDisplay(B11111111);
  delay(1000);

}

void fillEntireDisplay(byte data) {
  for (int idx = 0; idx < NUM_BYTES; idx++) {
    displayMatrix[idx] = data;
  }
  updateDisplayShiftRegisters();
}

void updateDisplayShiftRegisters() {
  digitalWrite(latchPin, LOW);
  writeDataToAllRegisters();
  digitalWrite(latchPin, HIGH);
}

void writeDataToAllRegisters() {
  for (int idx = 0; idx < NUM_BYTES; idx++) {
  shiftOut(shiftRegDataPins[idx], clockPin, LSBFIRST, displayMatrix[idx]);
  }
}
