#define builder_row 5
#define builder_col 7
#define builder_kbname "Terminus 2 Slave"
#define builder_kbvariant "Terminus 2 Slave"
#define builder_kbdriver "Animus Innova 2.7.0"
#define builder_kbdriver_build "OEM"
#define builder_vpins A0, 15, 14, 16, 10
#define builder_hpins A1, A2, 9, 8, 7, 6, 4
#define builder_refresh 1
#include "EEPROM.h"
#include "KeyboardInterface.h"

// constants: change this only to edit keyboard info

const byte ROW = builder_row;
const byte COL = builder_col;
byte VPins[ROW] = {builder_vpins};
byte HPins[COL] = {builder_hpins};

byte RefreshDelay = builder_refresh;
