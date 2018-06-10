#ifndef ANIMUS_MOD_ModI2CHOST
#define ANIMUS_MOD_ModI2CHOST
#include "ModTemplate.h"
#include "Animus.h"
#include "Wire.h"





/* references
below are types of i2c transmissions from the host to guest
1: send layer statuses (tlayer, klayer) (ping from guest before guest wants to send keystrokes)
2: ping from guest to check whether there's a new layout to send (maybe check every 100 ms?)
3: EOL for type 2
4:

*/

class CModI2CHost : public CModTemplate
{
private:
  byte EEPROMPacket[31]; // these are not local variables for faster access
  byte EEPROMPacketIndex = 2;
  byte I2CTempLayer = 0;
  byte I2CLEDBrightness = 0;
  byte I2CRefresh = 0;
  byte SerialLoaderByteStatus = 0;
  byte EEPROMPacketSize = 0;
  void SetTempLayer(void);
  void SetSubEEPROM(void);
  void SetSubBoardSettings(void);
  void SetSubLEDBrightness(void);
  void SetSubRefreshRate(void);
  void GetSubEEPROM(short startAddr);


public:
  CModI2CHost(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PressCoords(byte x, byte y);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);




};
extern CModI2CHost ModI2CHost;

#endif
