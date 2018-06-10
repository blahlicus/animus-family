#define builder_row 4
#define builder_col 12
#define builder_kbname "Terminus Mini"
#define builder_kbvariant "Terminus Mini"
#define builder_kbdriver "Animus Innova x2.6"
#define builder_kbdriver_build "OEM"
#define builder_vpins 9, 8, 7, 6
#define builder_hpins A3, A2, A0, A1, 14, 15, 10, 16, 2, 3, 4, 5
#define builder_refresh 1
#include "EEPROM.h"
#include "KeyboardInterface.h"

// constants: change this only to edit keyboard info

const byte ROW = builder_row;
const byte COL = builder_col;
byte VPins[ROW] = {builder_vpins};
byte HPins[COL] = {builder_hpins};

byte RefreshDelay = builder_refresh;
