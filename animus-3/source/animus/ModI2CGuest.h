#ifndef ANIMUS_MOD_ModI2CGuest
#define ANIMUS_MOD_ModI2CGuest
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

class CModI2CGuest : public CModTemplate
{
private:
  short EEPROMLoadIndex = 0;
  byte I2CBuffer[32];
  byte I2CBufferIndex = 0;
  byte KeyXBuffer[10];
  byte KeyYBuffer[10];
  byte KeyModeBuffer[10];
  byte KeyIndex = 0;

public:
  CModI2CGuest(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
  void ProcessPacket(void);



};
extern CModI2CGuest ModI2CGuest;

#endif
