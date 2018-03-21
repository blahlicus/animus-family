#define DEFAULT_ROW 20
#define DEFAULT_COL 20

#ifndef ANIMUS_GLOBAL
#define ANIMUS_GLOBAL
#include "Arduino.h"

#include "EEPROM.h"
class CGlobal
{
private:
public:
  byte RefreshDelay = 5; // default value, overriden on EEPROM load
  byte ROW = DEFAULT_ROW; // default value, overriden on EEPROM load
  byte COL = DEFAULT_COL; // default value, overriden on EEPROM load
  byte LAY = 1;

  byte VPins[DEFAULT_ROW]; // default value, overriden on EEPROM load
  byte HPins[DEFAULT_COL]; // default value, overriden on EEPROM load


  byte KeyLayer = 0;
  byte TempLayer = 0;


  byte KeyState[DEFAULT_COL][DEFAULT_ROW];
  byte PreviousState[DEFAULT_COL][DEFAULT_ROW];
  byte LayerState[DEFAULT_COL][DEFAULT_ROW];
  CGlobal(void);
};
extern CGlobal Global;

#endif
