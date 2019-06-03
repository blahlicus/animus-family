#define builder_row 4
#define builder_col 6
#define builder_kbname "Diverge TM 2 Slave"
#define builder_kbvariant "Diverge TM 2 Slave"
#define builder_kbdriver "Animus Innova x2.8"
#define builder_kbdriver_build "OEM"
#define builder_vpins 6, 7, 8, 9
#define builder_hpins A1, A0, 15, 14, 16, 10
#define builder_refresh 5
#define builder_keyup_delay 5
#include "EEPROM.h"
#include "KeyboardInterface.h"

// constants: change this only to edit keyboard info

const byte ROW = builder_row;
const byte COL = builder_col;
byte VPins[ROW] = {builder_vpins};
byte HPins[COL] = {builder_hpins};

byte RefreshDelay = builder_refresh;
byte KeyUpDelay = builder_keyup_delay;
