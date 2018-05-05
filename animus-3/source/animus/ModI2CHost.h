#ifndef ANIMUS_MOD_ModI2CHost
#define ANIMUS_MOD_ModI2CHost
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
  byte EEPROMPacket[29];
  byte EEPROMPacketIndex = 0;
  byte EEPROMPacketCounter = 255;
  byte EEPROMPacketEOLSize = 255;
  bool EEPROMPacketReady = false;
  byte SignalType = 1;
  byte BrightnessRefreshValue = 127;


  void SetTempLayer(void);
  void SetSubEEPROM(void);
  void SetSubEEPROMEOL(void);
  void SetSubBoardSettings(void);
  void SetSubBoardEOL(void);
  void SetSubLEDBrightness(void);
  void SetSubRefreshRate(void);


public:
  CModI2CHost(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void RequestEvent(void); // really doesn't matter whether those are static or not, there's only one instance
  void ReceiveEvent(byte numBytes);
  static void RequestInfo(void);
  static void ReceiveInfo(byte numBytes);
  void SerialComms(byte mode);




};
extern CModI2CHost ModI2CHost;

#endif
