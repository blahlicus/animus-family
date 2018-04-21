#ifndef ANIMUS_MOD_ModI2CHost
#define ANIMUS_MOD_ModI2CHost
#include "ModTemplate.h"
#include "Animus.h"
#include "Wire.h"





/* references
below are types of i2c transmissions from the host to guest
1: set TempLayer (type, tlayer)
2: set KeyLayer (type, klayer)
3: set eeprom data (packages of more than 30 bytes) (type, byte0, byte1, ...)
4: EOL for setting eeprom data, if setting less than 30 bytes, use this (type, length, byte0, byte 1, ...)
5: change max layer count (type, maxlay)
6: change refresh rate (type, refreshRate)
7: change board type (type, boardType)
8: change rows and row count (type, rowCount, rowPin0, rowPin1, ...)
9: change cols and col count (type, colCount, colPin0, colPin1, ...)
10: change brightness (type, brightness value)
*/

class CModI2CHost : public CModTemplate
{
private:
public:
  CModI2CHost(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModI2CHost ModI2CHost;

#endif
