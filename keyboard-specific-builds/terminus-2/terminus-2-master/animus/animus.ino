#define builder_row 5
#define builder_col 7
#define builder_kbname "Terminus 2 Master"
#define builder_kbvariant "Terminus 2 Master"
#define builder_kbdriver "Animus Innova 2.3.1"
#define builder_kbdriver_build "Terminus 2 OEM"
#define builder_vpins 4, 6, 7, 8, 9
#define builder_hpins A3, A2, A1, A0, 15, 14, 16
#define builder_refresh 7
#include "EEPROM.h"
#include "AnimusKeyboard.h"

// constants: change this only to edit keyboard info

const int ROW = builder_row;
const int COL = builder_col;
int VPins[ROW] = {builder_vpins};
int HPins[COL] = {builder_hpins};

int RefreshDelay = builder_refresh;
