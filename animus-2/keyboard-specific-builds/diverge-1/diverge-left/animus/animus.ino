#define builder_row 8
#define builder_col 5
#define builder_kbname "Diverge Left"
#define builder_kbvariant "Diverge"
#define builder_kbdriver "Animus Innova x2.6"
#define builder_kbdriver_build "OEM"
#define builder_vpins 10, 16, 14, 15, A0, A1, A2, A3
#define builder_hpins 9, 8, 7, 6, 5
#define builder_refresh 1
#include "EEPROM.h"
#include "KeyboardInterface.h"

// constants: change this only to edit keyboard info

const byte ROW = builder_row;
const byte COL = builder_col;
byte VPins[ROW] = {builder_vpins};
byte HPins[COL] = {builder_hpins};

byte RefreshDelay = builder_refresh;
