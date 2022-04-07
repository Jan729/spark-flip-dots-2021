// ArrayOfLedArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers
// TOD FIX COLOURS STINKY
// Differences between this simulator and our actual display:
// 1) The simulator is a bit laggy
// 2) The data, VSS, and GND pins are attached to the strip closest
// to the LED with index 0. We'll want to mount the LED strips with
// the wiring on the left side of the display if we want to keep this
// coordinate system
#include <SD.h>
#include <FastLED.h>
#define CS_PIN 53
#define NUM_STRIPS 32
#define NUM_LEDS_PER_STRIP 32
#define ANIFRAMES 7//Number of frames in the animation to be shown
// leds[0][0] is the bottom left corner
// leds[0][31] is the bottom right corner
// leds[31][0] is the top left corner
File root;
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
//DELETING THIS ARRAY SEEMS TO MAKE EVERYTHING GO HUNKY DORY AND I AM WAY TOO TIRED TO FIGURE OUT WHY

void setup() {
  // tell FastLED there's 32 WS2812B leds on pins 10-41
  FastLED.addLeds<WS2812B, 10, GRB>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 11, GRB>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 12, GRB>(leds[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 13, GRB>(leds[3], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 14, GRB>(leds[4], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 15, GRB>(leds[5], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 16, GRB>(leds[6], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 17, GRB>(leds[7], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 18, GRB>(leds[8], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 19, GRB>(leds[9], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 20, GRB>(leds[10], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 21, GRB>(leds[11], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 22, GRB>(leds[12], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 23, GRB>(leds[13], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 24, GRB>(leds[14], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 25, GRB>(leds[15], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 26, GRB>(leds[16], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 27, GRB>(leds[17], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 28, GRB>(leds[18], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 29, GRB>(leds[19], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 30, GRB>(leds[20], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 31, GRB>(leds[21], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 32, GRB>(leds[22], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 33, GRB>(leds[23], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 34, GRB>(leds[24], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 35, GRB>(leds[25], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 36, GRB>(leds[26], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 37, GRB>(leds[27], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 38, GRB>(leds[28], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 39, GRB>(leds[29], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 40, GRB>(leds[30], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812B, 41, GRB>(leds[31], NUM_LEDS_PER_STRIP);
  //FastLED.clear();
  Serial.begin(9600);
  Serial.println("Serial start");//The serial is only starting this...
  //int *randomImage=(int *)malloc(32*32*3*sizeof(int));
  //generateRandomImage(randomImage);
  //displayImage(randomImage);
  Serial.print("Initializing SD card... ");

  if (!SD.begin(CS_PIN)) {
    Serial.println("Card initialization failed!");
    while (true);
  }

  Serial.println("initialization done.");

  Serial.println("Files in the card:");
  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("");

  // Example of reading file from the card:
  /*File f=SD.open("wokwi.txt", FILE_WRITE);
  if(f){
    f.println("I fucking hate robert irish");
    f.println("And what's more, I KNOW he fucked that chicken");

  }
  f.close();*/
  /*Serial.println("Printing bytes!");
  File textFile = SD.open("wokwi.txt");
  if (textFile) {
    Serial.print("wokwi.txt: ");
    while (textFile.available()) {
      char t=textFile.read();
      Serial.print(t, HEX);
      Serial.print(" ");
      Serial.print(t);
      Serial.print(" ");
      delay(4000);
    }
    textFile.close();
  } else {
    Serial.println("error opening wokwi.txt!");
  }*/
  File textFile = SD.open("wokwi.txt");
  if(textFile){
    Serial.println("Wokwi.txt opened!");
    showBytes(textFile,0);
  }
}

void loop() {
  //animate(new_piskel_data, 10, ANIFRAMES-1);
  /*Serial.println(leds[11][7].r);
  Serial.println(leds[11][7].g);
  Serial.println(leds[11][7].b);*/
  leds[0][0].r=2*'f';
  delay(1000);
  FastLED.show();
  //moveRow(0,1,500,0xffffff,-1);
  //scrollLetter(0xffffff,0,27,100,'A',-1);
  //scrollLetters(2,10,0xff0000,"AS?",3);
  delay(500);
}
//Two choices for animation:
//1. Write the whole gif to a single txt file (this might overload Arduino memory)
//2. Name the files systematically and store them in a directory with an appropriate name
//Then just animate each file separately
void showBytes(File f, int del){
  clearDisplay();
  char r,g,b;
  int count=0;
  while(f.available()){
  for(int i=0; i<NUM_STRIPS; i++){
    for(int j=0; j<NUM_LEDS_PER_STRIP; j++){
      if(f.available()){
        leds[NUM_STRIPS-i-1][j].r=2*f.read();
        leds[NUM_STRIPS-i-1][j].g=2*f.read();
        leds[NUM_STRIPS-i-1][j].b=2*f.read();
        count++;
        /*Serial.println(F("Current position (strip, col)"));
        Serial.print(NUM_STRIPS-i-1);
        Serial.print(" ");
        Serial.print(j);
        Serial.println();
        Serial.println("RGB");
        Serial.print(leds[NUM_STRIPS-i-1][j].r);
        Serial.print(" ");
        Serial.print(leds[NUM_STRIPS-i-1][j].g);
        Serial.print(" ");
        Serial.print(leds[NUM_STRIPS-i-1][j].b);
        Serial.println();
        Serial.println();
        delay(1);
        FastLED.show();*/
        /*FastLED.show();
        delay(5);
        Serial.println("Current position (strip, row)");
        Serial.print(i);
        Serial.print(" ");
        Serial.print(j);
        Serial.println();
        if(i==2 && j==24){
          
          Serial.println("RGB");
          Serial.print(leds[i][j].r);
          Serial.print(" ");
          Serial.print(leds[i][j].g);
          Serial.print(" ");
          Serial.print(leds[i][j].b);
          Serial.println();
          delay(10000);
        }
        */
      }
    }
  }
  if(f.available()){
    //Serial.println("Delaying!");
    delay(f.read()/3);
  }
  FastLED.show();
  }
  Serial.println("DOne displaying!");
}

//current note to self on how I could do this (scrolltext):
/*Since I'm using 5x5s in the same font, here's what I could do.
Each letter is just 5 sequences of 5-bit numbers. Those 5 numbers represent whether a pixel is ON or OFF. So, in the case of A:

So each letter is stored by its 25-bit sequence. From there, for each letter, just scroll it sequence by sequence.
Note to self: make a function that generates these 25-bIt numbers
*/
void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
uint32_t letToBin(char a){//returns top right to bottom left, with LSB botleft, MSB topright, top to bottom then left to right
  switch(a){
    case 'a': case 'A':
      return 0b0111110100101001010001111;
    case 'b': case 'B':
      return 0b0000001010101011000111111;
    case 'c': case 'C':
      return 0b0101010001100011000101110;
    case 'd': case 'D':
      return 0b0000001110100011000111111;
    case 'e': case 'E':
      return 0b1000110101101011010111111;
    case 'f': case 'F':
      return 0b1000010100101001010011111;
    case 'g': case 'G':
      return 0b0010000110101011000101110;
    case 'h': case 'H':
      return 0b1111100100001000010011111;
    case 'i': case 'I':
      return 0b1000110001111111000110001;
    case 'j': case 'J':
      return 0b1000011110100011000110110;
    case 'k': case 'K':
      return 0b0000010001010100010011111;
    case 'l': case 'L':
      return 0b0000000001000010000111111;
    case 'm': case 'M':
      return 0b0111110000111001000001111;
    case 'n': case 'N':
      return 0b1111100010001000100011111;
    case 'o': case 'O':
      return 0b0111010001100011000101110;
    case 'p': case'P':
      return 0b0100010100101001010011111;
    case 'q': case'Q':
      return 0b0110110010101011000101110;
    case 'r': case'R':
      return 0b0101110100101001010011111;
    case 's': case 'S':
      return 0b1011010101101011010101101;
    case 't': case 'T':
      return 0b1000010000111111000010000;
    case 'u': case 'U':
      return 0b1111000001000010000111110;
    case 'v': case 'V':
      return 0b1110000010000010001011100;
    case 'w': case 'W':
      return 0b1111000001001110000111110;
    case 'x': case 'X':
      return 0b1000101010001000101010001;
    case 'y': case 'Y':
      return 0b1000001000001110100010000;
    case 'z': case 'Z':
      return 0b1000111001101011001110001;
    case ' ':
      return 0;
    default:
      return 0b0100010100101011000001000;

  }
}
void scrollLetters(int row, int del, uint32_t fill, char *message, int len){
  row=(row>NUM_STRIPS-5)?(NUM_STRIPS-5):row;
  for(int i=0; i<len; i++){

    uint32_t repchar=letToBin(message[i]);
    for(int j=0; j<5; j++){
    //scroll eevrything over by 1
      moveRows(row,1,1,0,-1,5);
      /*for(int x=0; x<5; x++){
        moveRowNoDisplay(row+x,1,1,0,-1);
      }*/
      FastLED.show();
      for(int x=0; x<5; x++){
        if(repchar&0b1){
          leds[row+x][NUM_LEDS_PER_STRIP-1]=CRGB(fill);
        }
        repchar=repchar>>1;
      }
      delay(del);
      FastLED.show();
    }  
    moveRows(row,1,1,0,-1,5);
  }
  clearDisplay();
}

void moveAllRows(int del, int dir){
  for(int i=0; i<NUM_LEDS_PER_STRIP; i++){
    moveRow(i,NUM_LEDS_PER_STRIP,del,0,dir);
  }
}

void moveRow(int row, int howFar, int del, uint32_t fill, int dir){
  if(dir==1){
    for(int j=0; j<howFar; j++){
      for(int i=NUM_LEDS_PER_STRIP-1; i>0; i--){
        leds[row][i]=leds[row][i-1];
      }
      leds[row][0]=CRGB(fill);
      FastLED.show();
      delay(del);
    }
  }else if(dir==-1){
    for(int j=0; j<howFar; j++){
      for(int i=0; i<NUM_LEDS_PER_STRIP-1; i++){
        leds[row][i]=leds[row][i+1];
      }
      leds[row][NUM_LEDS_PER_STRIP-1]=CRGB(fill);
      FastLED.show();
      delay(del);
    }
  }
}
//THIS COULD JUST BE A PART OF THE OTHER FUNCTION
void moveRowNoDisplay(int row, int howFar, int del, uint32_t fill, int dir){
  if(dir==1){
    for(int j=0; j<howFar; j++){
      for(int i=NUM_LEDS_PER_STRIP-1; i>0; i--){
        leds[row][i]=leds[row][i-1];
      }
      leds[row][0]=CRGB(fill);
      //FastLED.show();
      delay(del);
    }
  }else if(dir==-1){
    for(int j=0; j<howFar; j++){
      for(int i=0; i<NUM_LEDS_PER_STRIP-1; i++){
        leds[row][i]=leds[row][i+1];
      }
      leds[row][NUM_LEDS_PER_STRIP-1]=CRGB(fill);
      
      delay(del);
    }
  }
}


void moveRows(int row, int howFar, int del, uint32_t fill, int dir, int howmany){
  for(int i=row; i<row+howmany; i++){
    moveRowNoDisplay(i, howFar,1,fill,dir);
  }
  delay(del);
  FastLED.show();
}

//This one generates a random picture, shows it, and then frees the memory. USE AT YOUR OWN RISK:
//This one generates a 32x32x32 (7.4kB) array so it will almost definitely fuck up your SRAM and not work unless you don't have much code.
void showRandomPic(){
  uint8_t * rando=(uint8_t *)malloc(NUM_STRIPS*NUM_LEDS_PER_STRIP*3*sizeof(uint8_t));
  for(int x = 0; x < NUM_STRIPS*NUM_LEDS_PER_STRIP*3; x++) {
    rando[x]=(uint8_t)random(0,256);
  }
  displayImage(rando);
  free(rando);
}

void animate(uint32_t frames[][NUM_STRIPS*NUM_LEDS_PER_STRIP], int frameDelay, int aniframes){
  for(int j=0; j<aniframes; j++){
    for(int x = 0; x < NUM_STRIPS; x++) {
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      leds[x][i]=CRGB(pgm_read_dword(&(frames[j][32*x+i])));
    }
  }
  FastLED.show();
    delay(frameDelay);
  }
}


//Read in and display an image from a PROGMEM-saved 32x96 array of RGB values. (Note: if it's generated by Piskel, might have to flip R and B.)
void displayImagePGM(uint8_t rgbs[NUM_STRIPS][3*NUM_LEDS_PER_STRIP]){//Change red to blu and vice versa if handling from a Piskel
  for(byte i=0; i<NUM_STRIPS; i++){
    for(byte j=0; j<NUM_LEDS_PER_STRIP; j++){
      uint8_t red=pgm_read_byte(&(rgbs[i][3*j]));
      uint8_t grn=pgm_read_byte(&(rgbs[i][3*j+1]));
      uint8_t blu=pgm_read_byte(&(rgbs[i][3*j+2]));
      leds[i][j]=CRGB(red,grn,blu);
    }
  }
  FastLED.show();
  delay(500);
}

//Read in and display an image from a PROGMEM-saved 1024 array of hex values. (Note: if it's generated by Piskel, might have to flip R and B.)
void displayImagePGMHex(uint32_t * hexs){
  for(int x = 0; x < NUM_STRIPS; x++) {
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      leds[x][i]=CRGB(pgm_read_dword(&(hexs[32*x+i])));
    }
  }
  FastLED.show();
  delay(500);
}

//For when the given array is a set of hex colour codes in SRAM.
void displayImage(uint32_t * add){
  for(int x = 0; x < NUM_STRIPS; x++) {
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      leds[x][i]=add[NUM_STRIPS*x+i];
    }
  }
  FastLED.show();
  delay(500);
}

//For when the given array is a 3072 array of RGB colours (in R, G, B order) in SRAM.
void displayImage(uint8_t * rgbs){
  for(int x = 0; x < NUM_STRIPS; x++) {
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      int mem=3*(NUM_STRIPS*x+i);
      leds[x][i]=CRGB(rgbs[mem],rgbs[mem+1],rgbs[mem+2]);
    }
  }
  FastLED.show();
  delay(500);
}


//Clear the display
void clearDisplay(){
  
  FastLED.clear();
  FastLED.show();
}


void changePixel(uint32_t hex, int i, int j){
  leds[i][j]=CRGB(hex);
  FastLED.show();
}

void changePixel(uint8_t R, uint8_t G, uint8_t B, int i, int j){
  leds[i][j]=CRGB(R,G,B);
  FastLED.show();
}

void scrollLetter(uint32_t color, int rrow, int rcol, int del, char scroll, int dir){
  if(rcol<0||rcol+5>NUM_LEDS_PER_STRIP){
    return;
  }
  int row=(rrow<NUM_STRIPS)? rrow:(NUM_STRIPS-1);
  uint32_t letter[5][5]={{color,-1,-1,-1,color},{color,color,color,-1,color},{color,-1,-1,-1,color},{-1,color,-1,color,-1},{-1,-1,color,-1,-1}};
  CRGB prev[5][5];
  switch(scroll){
    case 'A':
      
      break;
  }

  //letter={{0,0,color,0,0},{0,color,0,color,0},{color,0,0,0,color},{color,0,0,0,color},{color,0,0,0,color}};
      for(int i=0 ;i<5; i++){
        for(int j=0; j<5; j++){
          prev[i][j]=leds[row+i][rcol+j];
          if(letter[i][j]!=-1)
            leds[row+i][rcol+j]=CRGB(letter[i][j]);
          
        }
      }
      FastLED.show();
      delay(del);
      for(int i=0 ;i<5; i++){
        for(int j=0; j<5; j++){
          leds[row+i][rcol+j]=prev[i][j];

        }
      }
      FastLED.show();
      free(letter);
      scrollLetter(color,rrow,rcol+dir,del,scroll, dir);
}

//Needs to return to what it was before.
void scrollPixel(uint32_t color, int rrow, int del){

  int row=(rrow<NUM_STRIPS)? rrow:(NUM_STRIPS-1);
  row=(row>=0)?row:0;
  CRGB prev=leds[row][0];
  for(int i=0; i<NUM_LEDS_PER_STRIP; i++){
    if(i>0){
      leds[row][i-1]=prev;
    }
    prev=leds[row][i];
    leds[row][i]=CRGB(color);
    FastLED.show();
    delay(del);
  }
  leds[row][NUM_LEDS_PER_STRIP-1]=CRGB::Black;
  FastLED.show();
}

/*
void sweepRando(){
for(int x = 0; x < NUM_STRIPS; x++) {
    // This inner loop will go over each led in the current strip, one at a time
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      leds[x][i] = CRGB(0xFF00FF);
      FastLED.show();
      delay(200);
      clearDisplay();
      delay(200);
    }
  }
}
void showPicHex(){
  for(int x = 0; x < NUM_STRIPS; x++) {
    // This inner loop will go over each led in the current strip, one at a time
    for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      leds[x][i]=fake[NUM_STRIPS*x+i];
    }
  }
  FastLED.show();
  delay(500);
}
*/

