#ifndef ANIMUS_MOD_MODMOUSE
#define ANIMUS_MOD_MODMOUSE
#include "ModTemplate.h"
#include "Animus.h"

// from nicehood
#include "HID.h"
#include "HID-Project.h"
#include "HID-Settings.h"


class CModMouse : public CModTemplate
{
private:
  byte XVal = 128;
  byte YVal = 128;
  byte WheelVal = 128;
  bool IsRunning = false;
public:
  CModMouse(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModMouse ModMouse;

#endif
