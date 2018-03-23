#ifndef ANIMUS_MOD_TEMPLATE
#define ANIMUS_MOD+TEMPLATE
#include "Global.h"


class CMod
{
private:
public:
  CMod(void);
  void Begin(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  String PrintMods();
  void End(void);
};
extern CMod Mod;

#endif
