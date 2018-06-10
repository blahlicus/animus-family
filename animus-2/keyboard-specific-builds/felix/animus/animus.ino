#define builder_row 5
#define builder_col 4
#define builder_kbname "Felix"
#define builder_kbvariant "Felix typeZERO"
#define builder_kbdriver "Animus Innova x2.6"
#define builder_kbdriver_build "Felix OEM"
#define builder_vpins 16, 14, 15, A0, A1
#define builder_hpins 9, 8, 7, 6
#define builder_refresh 1
#include "EEPROM.h"
#include "KeyboardInterface.h"

// constants: change this only to edit keyboard info

const byte ROW = builder_row;
const byte COL = builder_col;
byte VPins[ROW] = {builder_vpins};
byte HPins[COL] = {builder_hpins};

byte RefreshDelay = builder_refresh;
