#include "EEPROM.h"
#include "keyLib.h"

// constants: change this only to edit keyboard info
const int ROW = 4;
const int COL = 6;
const int LAY = 3;
String KBINFO = "DivergeTM,Diverge TM,animusDTM,Diverge TM QWERTY";
int vPins[ROW] = { A3, A2, 9, 16};
int hPins[COL] = { 10, 8, 7, 6, 5, 4};

int bitRate = 9600;
int refreshDelay = 10;
key keyLayout[COL][ROW][LAY];
// constants end



void loadLayout()
{
  int counter = 0;
  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < COL; j++)
    {
      for (int k = 0; k < LAY; k++)
      {
        char cval = EEPROM.read(counter);
        counter++;
        byte tval = EEPROM.read(counter);
        counter++;
        keyLayout[j][i][k].set(cval, tval);
      }
    }
  }
}


void setup()
{
  Keyboard.begin();
  Serial.begin(bitRate);
  resetPins();
  //inilayout2();
  //loadLayout();
  // serial delay
  delay(2000);
}
