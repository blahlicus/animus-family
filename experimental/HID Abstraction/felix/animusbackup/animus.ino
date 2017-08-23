#define builder_row 5
#define builder_col 4
#define builder_kbname "Felix"
#define builder_kbvariant "Felix typeZERO"
#define builder_kbdriver "Animus Innova 2.4.1x"
#define builder_kbdriver_build "Felix OEM"
#define builder_vpins 16, 14, 15, A0, A1
#define builder_hpins 9, 8, 7, 6
#define builder_refresh 5
#include "EEPROM.h"
#include "KeyboardInterface.h"

// constants: change this only to edit keyboard info

const int ROW = builder_row;
const int COL = builder_col;
int VPins[ROW] = {builder_vpins};
int HPins[COL] = {builder_hpins};

int RefreshDelay = builder_refresh;
