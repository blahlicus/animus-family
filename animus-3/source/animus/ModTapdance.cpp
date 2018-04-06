#include "ModTapdance.h"

CModTapdance::CModTapdance(void)
{
  // nothing
}

void CModTapdance::Begin(void)
{
  CModTemplate::Begin();
  ModGUID = 6; // GUID of this specific mod

  for (byte i = 0; i < 10; i++)
  {
    KeyID[i] = 255; // if 255 then slot is not used
    KeyTimeout[i] = 0;
    KeyCounter[i] = 0;
  }
}

void CModTapdance::LoadData(void)
{
  CModTemplate::LoadData();

  TapdanceCount = GetData(0);
  TimeoutSetting = GetData(1);
}

void CModTapdance::PressMacro(byte id)
{
  short startingAddr = 2;
  byte tapdanceID = 0;
  for (byte i = 0; i < id; i++) // this retrieves the starting address of the specific macro
  {
    startingAddr = startingAddr + 1 + GetData(startingAddr) * 2;
    tapdanceID = i;
  }

  byte keyLength = GetData(startingAddr);

  bool exists = false;
  for (byte i = 0; i < 10; i++) // iterate through the arrays
  {
    if (KeyID[i] == tapdanceID) // it was previously pressed
    {
      exists = true;
      if (KeyTimeout[i] > 0)
      {
        KeyTimeout[i] = TimeoutSetting;
        KeyCounter[i]++;
      }
    }
  }

  if (!exists)
  {
    for (byte i = 0; i < 10; i++) // iterate through the arrays
    {
      if (KeyID[i] == 255) // find first occurance of an empty slot
      {
        exists = true;
        KeyTimeout[i] = TimeoutSetting;
        KeyCounter[i] = 0;
      }
    }
  }

  for (byte i = 0; i < macroLength; i++) // iterates and executes the macros
  {
    Animus.PressKey(GetData(startingAddr + 1 + i * 2), GetData(startingAddr + 2 + i * 2));
    delay(KeyDelay);
  }
}

void CModTapdance::ReleaseMacro(byte id)
{
  short startingAddr = 2;
  for (byte i = 0; i < id; i++) // this retrieves the starting address of the specific macro
  {
    startingAddr = startingAddr + 1 + GetData(startingAddr) * 2;
  }

  byte macroLength = GetData(startingAddr);

  for (byte i = 0; i < macroLength; i++) // iterates and releases the keys in the macro backwards
  {
    Animus.ReleaseKey(GetData(startingAddr + 1 + (macroLength - 1 - i) * 2), GetData(startingAddr + 2 + (macroLength - 1 - i) * 2));
    delay(KeyDelay);
  }
}

void CModTapdance::Loop(void)
{
  CModTemplate::Loop();
}

void CModTapdance::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
}
void CModTapdance::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);

  if (Global.HasUSB)
  {
    if (type == 32)
    {
      PressMacro(val);
    }
  }
}
void CModTapdance::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (Global.HasUSB)
  {

    if (type == 32)
    {
      ReleaseMacro(val);
    }
  }
}

void CModTapdance::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModTapdance ModTapdance;
