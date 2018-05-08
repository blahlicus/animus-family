#ifndef ANIMUS_MOD_MODEXAMPLE
#define ANIMUS_MOD_MODEXAMPLE
#include "ModTemplate.h"
#include "Animus.h"

class CModExample : public CModTemplate
{
private:
public:
  CModExample(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PressCoords(byte x, y);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModExample ModExample;

#endif
