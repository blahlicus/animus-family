#ifndef ANIMUS_MOD
#define ANIMUS_MOD
#include "Global.h"


class CMod
{
private:
  //TODO
public:
  CMod(void);
  void Begin(void);
  void Loop(void);
  void PrePress(char val, byte type);
  void PressKey(char val, byte type);
  void ReleaseKey(char val, byte type);
  void Serial(String input);
  void End(void);
};
extern CMod Mod;

#endif
