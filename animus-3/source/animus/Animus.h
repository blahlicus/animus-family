#ifndef ANIMUS
#define ANIMUS
#include "AnimusKeyboard.h"
#include "Mod.h"


#define BAUD 19200
#define DRIVER_VERSION "Animus Janus x3.0"

class CAnimus
{
private:
void MillisLoop(void);
public:
  CAnimus(void);
  void Begin(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SwitchLayer(bool increment);
  void RotateLayer(byte val);
  void KeyScan(void);
  bool GetMillis(void);

};
extern CAnimus Animus;

#endif
