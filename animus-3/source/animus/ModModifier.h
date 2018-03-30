#ifndef ANIMUS_MOD_MODIFIER
#define ANIMUS_MOD_MODIFIER
#include "ModTemplate.h"
#include "AnimusKeyboard.h"

#define ANIMUS_MOD_MODIFIER_LCTRL 224
#define ANIMUS_MOD_MODIFIER_LSHIFT 225
#define ANIMUS_MOD_MODIFIER_LALT 226
#define ANIMUS_MOD_MODIFIER_LGUI 227
#define ANIMUS_MOD_MODIFIER_RCTRL 228
#define ANIMUS_MOD_MODIFIER_RSHIFT 229
#define ANIMUS_MOD_MODIFIER_RALT 230
#define ANIMUS_MOD_MODIFIER_RGUI 231

class CModModifier : public CModTemplate
{
private:
public:
  byte ModNo; // this is the EEPROM memory address ID
  short EEPROMAddress;
  const byte ModGUID; // this is the GUID for all list of mods, used for identification by arbites
  CModModifier(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModModifier ModModifier;

#endif
