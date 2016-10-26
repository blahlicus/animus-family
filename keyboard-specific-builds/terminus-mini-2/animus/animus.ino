#define builder_row 5
#define builder_col 10
#define builder_kbname "Terminus Mini 2"
#define builder_kbvariant "Terminus Mini 2 typeZERO"
#define builder_kbdriver "Animus Innova 2.1"
#define builder_kbdriver_build "OEM"
#define builder_vpins 16, 14, 15, A0, A1
#define builder_hpins 10, 9, 8, 7, 6, 4, 3, 2, A2, A3
#define builder_refresh 6
#include "EEPROM.h"
#include "AnimusKeyboard.h"

// constants: change this only to edit keyboard info

const int ROW = builder_row;
const int COL = builder_col;
int VPins[ROW] = {builder_vpins};
int HPins[COL] = {builder_hpins};

int RefreshDelay = builder_refresh;
