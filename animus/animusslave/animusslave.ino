#include "EEPROM.h"

// constants: change this only to edit keyboard info
const int ROW = 5;
const int COL = 8;
String KBINFO = "DivergeTM,Diverge TM,Animus,Diverge TM QWERTY";
int vPins[ROW] = { 5, 6, 7, 8, 9};
int hPins[COL] = { A3, A2, A1, A0, 15, 14, 16, 10};

int refreshDelay = 10;
// constants end
