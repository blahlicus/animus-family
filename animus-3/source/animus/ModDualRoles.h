#ifndef ANIMUS_MOD_MODDUALROLES
#define ANIMUS_MOD_MODDUALROLES
#include "ModTemplate.h"
#include "Animus.h"

#define ANIMUS_MOD_DUALROLES_LCTRL 224
#define ANIMUS_MOD_DUALROLES_LSHIFT 225
#define ANIMUS_MOD_DUALROLES_LALT 226
#define ANIMUS_MOD_DUALROLES_LGUI 227
#define ANIMUS_MOD_DUALROLES_RCTRL 228
#define ANIMUS_MOD_DUALROLES_RSHIFT 229
#define ANIMUS_MOD_DUALROLES_RALT 230
#define ANIMUS_MOD_DUALROLES_RGUI 231

class CModDualRoles : public CModTemplate
{
private:
  bool PressedKey = false; // only true if HIDs of non-modifiers are pressed
  short TimeoutLength = 1000; // this is the starting timeout length, this should not be changed after load

  short GuiTimeout;
  short CtrlTimeout;
  short ShiftTimeout;
  short AltTimeout;
  short AltgrTimeout;
  short FNTimeout[6];

  byte GuiDown = false;
  byte CtrlDown = false;
  byte ShiftDown = false;
  byte AltDown = false;
  byte AltgrDown = false;
  byte FNDown[6];

public:
  CModDualRoles(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModDualRoles ModDualRoles;

#endif
