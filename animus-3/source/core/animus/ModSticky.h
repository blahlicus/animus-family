#ifndef ANIMUS_MOD_MODSTICKY
#define ANIMUS_MOD_MODSTICKY
#include "ModTemplate.h"
#include "Animus.h"

#define ANIMUS_MOD_STICKY_LCTRL 224
#define ANIMUS_MOD_STICKY_LSHIFT 225
#define ANIMUS_MOD_STICKY_LALT 226
#define ANIMUS_MOD_STICKY_LGUI 227
#define ANIMUS_MOD_STICKY_RCTRL 228
#define ANIMUS_MOD_STICKY_RSHIFT 229
#define ANIMUS_MOD_STICKY_RALT 230
#define ANIMUS_MOD_STICKY_RGUI 231

class CModSticky : public CModTemplate
{
private:
  bool CtrlDown = false;
  bool ShiftDown = false;
  bool AltDown = false;
  bool AltGrDown = false;
  bool GuiDown = false;
  bool FNDown[20];
public:
  CModSticky(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModSticky ModSticky;

#endif
