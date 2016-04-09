#define builder_row 4
#define builder_col 12
#define builder_kbname "Terminus Mini"
#define builder_kbvariant "Terminus Mini"
#define builder_kbdriver "Animus Innova 1"
#define builder_kbdriver_build "OEM"
#define builder_vpins 9, 8, 7, 6
#define builder_hpins A3, A2, A1, A0, 14, 15, 10, 16, 2, 3, 4, 5
#define builder_refresh 10
#include "EEPROM.h"
#include "AnimusKeyboard.h"

// constants: change this only to edit keyboard info

const int ROW = builder_row;
const int COL = builder_col;
int vPins[ROW] = {builder_vpins};
int hPins[COL] = {builder_hpins};

int refreshDelay = builder_refresh;

// diverge ii
/*
const int ROW = 5;
const int COL = 8;
String KBINFO = "Diverge II,Diverge II,Animus,Diverge II OEM";
int vPins[ROW] = { 5, 6, 7, 8, 9};
int hPins[COL] = { A3, A2, A1, A0, 15, 14, 16, 10};

int refreshDelay = 10;

//*/

// constants end

// diverge ii
/*
const int ROW = 4;
const int COL = 12;
String KBINFO = "Terminus Mini,Terminus Mini,Animus,Terminus Mini OEM";
int vPins[ROW] = { 9, 8, 7, 6};
int hPins[COL] = { A3, A2, A0, A1, 14, 15, 10, 16, 2, 3, 4, 5};

int refreshDelay = 10;

//*/
