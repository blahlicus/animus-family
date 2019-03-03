#ifndef ANIMUS_MOD_MODI2CGUEST
#define ANIMUS_MOD_MODI2CGUEST
#include "ModTemplate.h"
#include "Animus.h"
#include "Wire.h"

#define PULL_RATE 50

class CModI2CGuest : public CModTemplate
{
private:
  byte SlaveArray[32];
  byte SlaveIndex = 0;
  bool isMaster = false;
  byte pullTimeout = 0;
public:
  CModI2CGuest(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PressCoords(byte x, byte y);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void OnReceive(int numBytes);
  static void RequestEvent();
  static void ReceiveEvent(int numBytes);
  void SerialComms(byte mode);
  void SetMaster(bool value);
};
extern CModI2CGuest ModI2CGuest;

#endif
