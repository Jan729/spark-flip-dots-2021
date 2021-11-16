//removed OLED code
/*There are two rotary encoders, the left one for horizontal dir. (CW for RIGHT, CCW for LEFT)
 *and the right one for vertical dir. (CW for UP, CCW for DOWN). Constrained (0,31) for both directions.
 *One input == 2 clicks on the rotary encoder
 *Outputs: vertical and horizontal
*/

//reference code https://wokwi.com/arduino/projects/304919215794553409

#define ENCODER_CLK_V 2
#define ENCODER_DT_V 3
#define ENCODER_CLK_H 6
#define ENCODER_DT_H 7

uint8_t vertical = 0;
String Vertical;
uint8_t horizontal = 0;
String Horizontal;

int vCounter = 0;
int hCounter = 0;

//updates the horizontal counter 
void updateValueH(int delta) {
  if (hCounter == 1){
    horizontal = constrain(horizontal + delta, 0, 31);
    hCounter = 0;
    return;
  }
  hCounter++;
}

//updates the vertical counter
void updateValueV(int delta) {
  if (vCounter == 1){
    vertical = constrain(vertical + delta, 0, 31);
    vCounter = 0;
    return;
  }
  vCounter++;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ENCODER_CLK_H, INPUT);
  pinMode(ENCODER_DT_H, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //updates horizontal first
  int clk_H = digitalRead(ENCODER_CLK_H);
  if ((clk_H != prevClk_H) && (clk_H == LOW)){
    int dtH = digitalRead(ENCODER_DT_H);
    int deltaH = dtH == HIGH ? 1: -1;
    updateValueH(deltaH);
  }
  prevClk_H = clk_H;

  int clk_V = digitalRead(ENCODER_CLK_V);
  if ((clk_V != prevClk_V) && (clk_V == LOW)){
    int dtV = digitalRead(ENCODER_DT_V);
    int deltaV = dtV == HIGH ? 1: -1;
    updateValueV(deltaV);
  }
  prevClk_V = clk_V;
}
