#ifndef ANIMUS_MOD_MODEXAMPLE
#define ANIMUS_MOD_MODEXAMPLE
#include "ModTemplate.h"
#include "AnimusKeyboard.h"

class CModExample : public CModTemplate
{
private:
public:
  byte ModNo; // this is the EEPROM memory address ID
  short EEPROMAddress;
  const byte ModGUID; // this is the GUID for all list of mods, used for identification by arbites
  CModExample(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModExample ModExample;

#endif
