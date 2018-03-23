#ifndef ANIMUS_MOD
#define ANIMUS_MOD
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
  void Serial(byte mode);
  String PrintMods();
  void End(void);
};
extern CMod Mod;

#endif
