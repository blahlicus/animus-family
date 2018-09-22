#include "ModLED.h"

CModLED::CModLED(void)
{
  // nothing
}

void CModLED::Begin(void)
{
  CModTemplate::Begin();
  ModGUID = 10; // GUID of this specific mod

  if (Global.HasUSB)
  {

  }
  for (byte i = 0; i < Global.ROW; i++)
  {
    if (Global.VPins[i] == 5)
    {
      Enabled = false;
    }
  }
  for (byte i = 0; i < Global.COL; i++)
  {
    if (Global.HPins[i] == 5)
    {
      Enabled = false;
    }
  }
}

void CModLED::LoadData(void)
{
  CModTemplate::LoadData();

  if (Global.HasUSB)
  {

  }
}

void CModLED::Loop(void)
{
  CModTemplate::Loop();
  if (Enabled)
  {
    analogWrite(5, Global.LEDBrightness);
  }
  if (Animus.Async1MSDelay())
  {

    if (Global.HasUSB)
    {

    }
  }
}

void CModLED::PressCoords(byte x, byte y)
{
  CModTemplate::PressCoords(x, y);

}

void CModLED::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
  if (Global.HasUSB)
  {

  }
}
void CModLED::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);

  if (Global.HasUSB)
  {
    if (type == 38) // LED type
    {

      if (val < 101)
      {
        byte adjust = val;

        if (Global.LEDBrightness + adjust < 0)
        {
          Global.LEDBrightness = 0;
        }
        else if (Global.LEDBrightness + adjust > 255)
        {
          Global.LEDBrightness = 255;
        }
        else
        {
          Global.LEDBrightness = Global.LEDBrightness + adjust;
        }
      }
      else if (val == 101)
      {
        Global.LEDBrightness = 0;
      }
      else if (val == 102)
      {
        Global.LEDBrightness = 32;
      }
      else if (val == 103)
      {
        Global.LEDBrightness = 64;
      }
      else if (val == 104)
      {
        Global.LEDBrightness = 96;
      }
      else if (val == 105)
      {
        Global.LEDBrightness = 128;
      }
      else if (val == 106)
      {
        Global.LEDBrightness = 160;
      }
    }
  }
}
void CModLED::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (Global.HasUSB)
  {

  }
}

void CModLED::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModLED ModLED;
