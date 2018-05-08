#ifndef ANIMUS_MOD_ModI2CGuest
#define ANIMUS_MOD_ModI2CGuest
#include "ModTemplate.h"
#include "Animus.h"

class CModI2CGuest : public CModTemplate
{
private:
public:
  CModI2CGuest(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PressCoords(byte x, byte y);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModI2CGuest ModI2CGuest;

#endif
