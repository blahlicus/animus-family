#define builder_row 4
#define builder_col 6
#define builder_kbname "lets split v2 test2"
#define builder_kbvariant "lets split v2 R0"
#define builder_kbdriver "Animus Innova 2.3.1"
#define builder_kbdriver_build "OEM"
#define builder_hpins A1, A0, 15, 14, 16, 10
#define builder_vpins 6, 7, 8, 9
#define builder_refresh 5
#include "EEPROM.h"
#include "AnimusKeyboard.h"

// constants: change this only to edit keyboard info

const int ROW = builder_row;
const int COL = builder_col;
int VPins[ROW] = {builder_vpins};
int HPins[COL] = {builder_hpins};

int RefreshDelay = builder_refresh;
