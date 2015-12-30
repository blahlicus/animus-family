#include "EEPROM.h"
#include "Wire.h"

// constants: change this only to edit keyboard info
const int ROW = 4;
const int COL = 6;
String KBINFO = "DivergeTM,Diverge TM,Animus,Diverge TM QWERTY";
int vPins[ROW] = { A3, A2, 9, 16};
int hPins[COL] = { 10, 8, 7, 6, 5, 4};

int refreshDelay = 10;
// constants end
