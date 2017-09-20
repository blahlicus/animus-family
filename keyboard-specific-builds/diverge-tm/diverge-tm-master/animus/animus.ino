#define builder_row 4
#define builder_col 6
#define builder_kbname "Diverge TM Master"
#define builder_kbvariant "Diverge TM Master"
#define builder_kbdriver "Animus Innova 2.5.1"
#define builder_kbdriver_build "OEM"
#define builder_vpins A3, A2, 9, 16
#define builder_hpins 10, 8, 7, 6, 5, 4
#define builder_refresh 5
#include "EEPROM.h"
#include "KeyboardInterface.h"

// constants: change this only to edit keyboard info

const int ROW = builder_row;
const int COL = builder_col;
int VPins[ROW] = {builder_vpins};
int HPins[COL] = {builder_hpins};

int RefreshDelay = builder_refresh;
