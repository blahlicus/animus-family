#ifndef ANIMUS_MOD_MODTAPDANCE
#define ANIMUS_MOD_MODTAPDANCE
#include "ModTemplate.h"
#include "Animus.h"

class CModTapdance : public CModTemplate
{
private:
  byte tickTock = 0; // this is the counter for the main loop

  byte TapdanceCount = 0;
  byte TimeoutSetting = 100; // this really ought to be shorts but i'm saving them srams
  byte KeyID[10];
  byte KeyTimeout[10];
  byte KeyCounter[10];
  bool IsDown[10];

  void PressTapdance(byte id);
  void ReleaseTapdance(byte id);
  void PressTapKey(byte id, byte counter);
  void ReleaseTapKey(byte id, byte counter);
public:
  CModTapdance(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModTapdance ModTapdance;

#endif
