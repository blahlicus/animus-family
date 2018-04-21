#ifndef ANIMUS_MOD_ModI2CHost
#define ANIMUS_MOD_ModI2CHost
#include "ModTemplate.h"
#include "Animus.h"

class CModI2CHost : public CModTemplate
{
private:
public:
  CModI2CHost(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModI2CHost ModI2CHost;

#endif
