#ifndef ANIMUS_MOD_MODIFIER
#define ANIMUS_MOD_MODIFIER
#include "ModTemplate.h"
#include "Animus.h"
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
  bool NaturalLShift = false; // status of shift keys not affected by this mod
  bool NaturalRShift = false;
public:
  CModModifier(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PressModifiers(bool ctrl, bool shift, bool alt, bool gui);
  void ReleaseModifiers(bool ctrl, bool shift, bool alt, bool gui);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModModifier ModModifier;

#endif
