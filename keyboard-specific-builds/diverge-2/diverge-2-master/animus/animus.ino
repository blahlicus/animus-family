#define builder_row 5
#define builder_col 8
#define builder_kbname "Diverge 2 Master"
#define builder_kbvariant "Diverge 25"
#define builder_kbdriver "Animus Innova x2.6"
#define builder_kbdriver_build "OEM"
#define builder_vpins 5, 6, 7, 8, 9
#define builder_hpins A3, A2, A1, A0, 15, 14, 16, 10
#define builder_refresh 1
#include "EEPROM.h"
#include "KeyboardInterface.h"

// constants: change this only to edit keyboard info

const byte ROW = builder_row;
const byte COL = builder_col;
byte VPins[ROW] = {builder_vpins};
byte HPins[COL] = {builder_hpins};

byte RefreshDelay = builder_refresh;
