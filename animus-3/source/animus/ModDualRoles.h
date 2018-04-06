#ifndef ANIMUS_MOD_MODDUALROLES
#define ANIMUS_MOD_MODDUALROLES
#include "ModTemplate.h"

class CModDualRoles : public CModTemplate
{
private:
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
