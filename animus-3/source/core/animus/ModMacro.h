#ifndef ANIMUS_MOD_MODMACRO
#define ANIMUS_MOD_MODMACRO
#include "ModTemplate.h"
#include "Animus.h"

class CModMacro : public CModTemplate
{
private:
  byte MacroCount = 0;
  byte KeyDelay = 5;
  void PressMacro(byte id);
  void ReleaseMacro(byte id);
public:
  CModMacro(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModMacro ModMacro;

#endif
