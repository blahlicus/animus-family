#define builder_row 5
#define builder_col 7
#define builder_kbname "Terminus 2 Slave"
#define builder_kbvariant "Terminus 2 Slave"
#define builder_kbdriver "Animus Innova 2.3"
#define builder_kbdriver_build "OEM"
#define builder_vpins A0, 15, 14, 16, 10
#define builder_hpins A1, A2, 9, 8, 7, 6, 4
#define builder_refresh 7
#include "EEPROM.h"
#include "AnimusKeyboard.h"

// constants: change this only to edit keyboard info

const int ROW = builder_row;
const int COL = builder_col;
int VPins[ROW] = {builder_vpins};
int HPins[COL] = {builder_hpins};

int RefreshDelay = builder_refresh;
