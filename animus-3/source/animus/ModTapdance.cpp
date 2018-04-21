#include "ModTapdance.h"

CModTapdance::CModTapdance(void)
{
  // nothing
}

void CModTapdance::Begin(void)
{
  CModTemplate::Begin();
  ModGUID = 6; // GUID of this specific mod

  if (Global.HasUSB)
  {

    // resets all arrays, not needed but nice against compilers
    for (byte i = 0; i < 10; i++)
    {
      KeyID[i] = 255; // if 255 then slot is not used
      KeyTimeout[i] = 0;
      KeyCounter[i] = 0;
      IsDown[i] = false;
    }
  }
}

void CModTapdance::LoadData(void)
{
  CModTemplate::LoadData();

  // loads number of tapdance keys and timeout settings
  if (Global.HasUSB)
  {

    TapdanceCount = GetData(0);
    TimeoutSetting = GetData(1);
  }
}

void CModTapdance::PressTapdance(byte id)
{
  bool exists = false;
  for (byte i = 0; i < 10; i++) // iterate through the arrays
  {
    if (KeyID[i] == id) // it was previously pressed
    {
      exists = true;
      IsDown[i] = true;
      if (KeyTimeout[i] > 0) // it wasn't timed out
      {
        KeyTimeout[i] = TimeoutSetting;
        KeyCounter[i]++; // increment tapdance value
      }
      break;
    }
  }

  if (!exists) // run this if it was not pressed before
  {
    for (byte i = 0; i < 10; i++) // iterate through the arrays
    {
      if (KeyID[i] == 255) // find first occurance of an empty slot
      {
        exists = true;
        IsDown[i] = true;
        KeyID[i] = id;
        KeyTimeout[i] = TimeoutSetting;
        KeyCounter[i] = 0;
        break; // breaks out of the loop so that not every 255 gets infected
      }
    }
  }

}

void CModTapdance::ReleaseTapdance(byte id)
{

  for (byte i = 0; i < 10; i++) // iterate through the arrays
  {
    if (KeyID[i] == id) // it was previously pressed
    {
      IsDown[i] = false;
      if (KeyTimeout[i] > 0)
      {
        // do nothing
      }
      else
      {
        ReleaseTapKey(id, KeyCounter[i]);
        KeyID[i] = 255; // clears keyid state;
      }
    }
  }
}

void CModTapdance::Loop(void)
{
  CModTemplate::Loop();

  if (Animus.GetMillis())
  {

    if (Global.HasUSB)
    {

      if (tickTock < 5)
      {
        tickTock++;
      }
      else // runs once every 5 cycles (about 5ms)
      {
        for (byte i = 0; i < 10; i++)
        {

          if (KeyID[i] != 255) // it was previously pressed
          {
            if (KeyTimeout[i] > 0)
            {
              KeyTimeout[i]--;
            }
            else
            {
              PressTapKey(KeyID[i], KeyCounter[i]);
              if (!IsDown[i])
              {
                ReleaseTapKey(KeyID[i], KeyCounter[i]);
                KeyID[i] = 255; // clears keyid state;
              }
            }
          }
        }
        tickTock = 0;
      }
    }
  }
}

void CModTapdance::PressTapKey(byte id, byte counter)
{
  short startingAddr = 2;
  for (byte i = 0; i < id; i++) // this retrieves the starting address of the specific macro
  {
    startingAddr = startingAddr + 1 + GetData(startingAddr) * 2;
  }

  byte keyLength = GetData(startingAddr);
  if (counter <= keyLength)
  {
    Animus.PressKey(GetData(startingAddr + 1 + counter * 2), GetData(startingAddr + 2 + counter * 2));
  }
}

void CModTapdance::ReleaseTapKey(byte id, byte counter)
{
  short startingAddr = 2;
  for (byte i = 0; i < id; i++) // this retrieves the starting address of the specific macro
  {
    startingAddr = startingAddr + 1 + GetData(startingAddr) * 2;
  }

  byte keyLength = GetData(startingAddr);
  if (counter <= keyLength)
  {
    Animus.ReleaseKey(GetData(startingAddr + 1 + counter * 2), GetData(startingAddr + 2 + counter * 2));
  }
}


void CModTapdance::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);

  if (Global.HasUSB)
  {

    for (byte i = 0; i < 10; i++) // iterate through the arrays
    {
      if (KeyID[i] != 255) // it was previously pressed
      {
        if (val == KeyID[i] && type == 33) // same key as self, ignore
        {
          // do nothing
        }
        else if (KeyTimeout[i] > 0) // press tap key if another key is pressed
        {
          PressTapKey(KeyID[i], KeyCounter[i]);
          if (!IsDown[i])
          {
            ReleaseTapKey(KeyID[i], KeyCounter[i]);
            KeyID[i] = 255; // clears keyid state;
          }
        }
      }
    }
  }
}
void CModTapdance::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);

  if (Global.HasUSB)
  {
    if (type == 33)
    {
      PressTapdance(val);
    }
    else if (type == 34)
    {
      PressTapKey(1,1);
    }
  }
}
void CModTapdance::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (Global.HasUSB)
  {

    if (type == 33)
    {
      ReleaseTapdance(val);
    }
  }
}

void CModTapdance::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModTapdance ModTapdance;
