//FIXME the high side switches seem to be flickering. not sure why

// Functions that will flip a single dot
// Pins 3, 4, 5 and 6 are connected to switches

// Pins connected to switches
#define SET_LOW_SIDE 3
#define SET_HIGH_SIDE 6

#define RESET_LOW_SIDE 2
#define RESET_HIGH_SIDE 7

// Switch values
int set_high_side = 0;
int set_low_side = 0;
int reset_high_side = 0;
int reset_low_side = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(SET_LOW_SIDE, OUTPUT);
  pinMode(SET_HIGH_SIDE, OUTPUT);
  pinMode(RESET_LOW_SIDE, OUTPUT);
  pinMode(RESET_HIGH_SIDE, OUTPUT);
  
  digitalWrite(SET_LOW_SIDE, LOW);
  digitalWrite(SET_HIGH_SIDE, LOW);
  digitalWrite(RESET_LOW_SIDE, LOW);
  digitalWrite(RESET_HIGH_SIDE, LOW);

  Serial.begin(9600);
}

void loop() {
  
  setDot();
  delay(1000);
  
  freezeDot();
  delay(500);
  
  resetDot();
  delay(1000);
  
  freezeDot();
  delay(500);
}

void sendLowSideSwitchSignals() {
  digitalWrite(SET_LOW_SIDE, set_low_side);
  digitalWrite(RESET_LOW_SIDE, reset_low_side);
}

void sendHighSideSwitchSignals() {
  digitalWrite(SET_HIGH_SIDE, set_high_side);
  digitalWrite(RESET_HIGH_SIDE, reset_high_side);
}

// dots that aren't flipping should not move
void freezeDot() {
  set_high_side = 0;
  set_low_side = 0;
  reset_high_side = 0;
  reset_low_side = 0;
}

// flip dot to lighter colour
void setDot() {
  Serial.println("White");
  set_low_side = 1;
  sendLowSideSwitchSignals();
  set_high_side = 1;
  sendHighSideSwitchSignals();

  waitForDotToFlip();
  
  set_high_side = 0;
  sendHighSideSwitchSignals();
  set_low_side = 0;
  sendLowSideSwitchSignals();
}

// flip dot to darker colour
void resetDot() {
  Serial.println("Blue");
  reset_low_side = 1;
  sendLowSideSwitchSignals();
  reset_high_side = 1;
  sendHighSideSwitchSignals();

  waitForDotToFlip();
  
  reset_high_side = 0;
  sendHighSideSwitchSignals();
  reset_low_side = 0;
  sendLowSideSwitchSignals();
}

//do we have to wait? if so, how long to wait?
void waitForDotToFlip() {
  delay(1000);
}
