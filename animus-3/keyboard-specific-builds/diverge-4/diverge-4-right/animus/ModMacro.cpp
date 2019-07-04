#include "ModMacro.h"

CModMacro::CModMacro(void)
{
  // nothing
}

void CModMacro::Begin(void)
{
  CModTemplate::Begin();
  ModGUID = 5; // GUID of this specific mod
  if (Global.HasUSB)
  {

  }
}

void CModMacro::LoadData(void)
{
  CModTemplate::LoadData();

  if (Global.HasUSB)
  {

    MacroCount = GetData(0);
    KeyDelay = GetData(1);
  }
}

void CModMacro::PressMacro(byte id)
{
  short startingAddr = 2;
  for (byte i = 0; i < id; i++) // this retrieves the starting address of the specific macro
  {
    startingAddr = startingAddr + 1 + GetData(startingAddr) * 2;
  }

  byte macroLength = GetData(startingAddr);

  for (byte i = 0; i < macroLength; i++) // iterates and executes the macros
  {
    Animus.PressKey(GetData(startingAddr + 1 + i * 2), GetData(startingAddr + 2 + i * 2));
    delay(KeyDelay);
  }
}

void CModMacro::ReleaseMacro(byte id)
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

void CModMacro::Loop(void)
{
  CModTemplate::Loop();
  if (Animus.Async1MSDelay())
  {

    if (Global.HasUSB)
    {

    }
  }
}

void CModMacro::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
  if (Global.HasUSB)
  {

  }
}
void CModMacro::PressKey(byte val, byte type)
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
void CModMacro::ReleaseKey(byte val, byte type)
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

void CModMacro::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModMacro ModMacro;
