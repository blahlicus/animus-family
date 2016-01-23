

#define builder_row 5
#define builder_col 8
#define builder_kbname "Diverge II"
#define builder_kbvariant "Diverge II Dash"
#define builder_kbdriver "Animus Renascentia 2"
#define builder_kbdriver_build "Diverge II OEM"
#define builder_vpins 5, 6, 7, 8, 9
#define builder_hpins A3, A2, A1, A0, 15, 14, 16, 10
#define builder_refresh 10
#include "EEPROM.h"
//#include "Keyboard.h"

// constants: change this only to edit keyboard info

const int ROW = builder_row;
const int COL = builder_col;
String KBINFO = builder_kbname "," builder_kbvariant "," builder_kbdriver "," builder_kbdriver_build;
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
