#include <SPI.h>
#include <SD.h>

const int chipSelect=53;
File pubfolder;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }
  File peepee=SD.open("testes.txt");
  printFile(peepee);
  peepee.close();
  pubfolder=SD.open("ran");
  //printRandom(folder);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  printFile(fileRandom(pubfolder));
}

int countFiles(File dir)
{
  if(!dir){
    Serial.println("File not found!");
  }else if(!dir.isDirectory()){
    Serial.println("Not a directory!");
  }
  int counter = 0;
  while(true)
  {
    File entry = dir.openNextFile();
    if (! entry)
    {
      dir.rewindDirectory();
      break;
    }
    //Serial.println(entry.name());
    counter++;
    entry.close();
  }
  return counter;
}


//Use this and pass it the directory to get the random file
File fileRandom(File dir){
  int numFiles=countFiles(dir);
  //Serial.println(numFiles);
  dir.rewindDirectory();
  int jumps=random(0,numFiles)+1;
  File ret;
  int counter=0;
  while(true)
  {
    File entry = dir.openNextFile();
    if (! entry)
    {
      Serial.println("Last file reached");
      dir.rewindDirectory();
      break;
    }
    //Serial.println(entry.name());
    counter++;
    if(counter==jumps)
    {
      ret = entry;
      dir.rewindDirectory();
      break;
    }
    entry.close();
  }
  return ret;
}

void printFile(File d){
  if(!d){
    Serial.println("No file found to print!");
  }
  Serial.println(d.name());
  while(d.available()){
    Serial.write(d.read());
  }
  Serial.println();
}
