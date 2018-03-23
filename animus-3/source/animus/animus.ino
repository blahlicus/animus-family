#define BAUD 19200
#define DRIVER_VERSION "Animus Janus x3.0"
#include "AnimusKeyboard.h"
#include "Mod.h"
#include "PersMem.h"
#include "Comms.h"
#include "Global.h"



void setup()
{
  PersMem.Begin(); // loads data from EEPROM to RAM
  AnimusKeyboard.Begin();
  Comms.Begin(BAUD);
  Mod.Begin();
}

void loop()
{
  MillisLoop();

  // start of pesudo rtos code
  if (GetMillis()) // should run once every 1 to 1.5ms
  {

    // layering checks in case of layout remapping
    if (Global.KeyLayer >= Global.LAY || Global.TempLayer >= Global.LAY)
    {
      Global.KeyLayer = 0;
      Global.TempLayer = 0;
    }

    KeyScan(); // physical key layers scanned
    // start of physical key loops
    for (byte i = 0; i < Global.ROW; i++)
    {
      for (byte j = 0; j < Global.COL; j++)
      {
        if (Global.KeyState[j][i] == HIGH) // if key is down
        {
          if (Global.KeyStateCoolDown[j][i] == 0) // if key was not recently released
          {
            Mod.PrePress(PersMem.GetKeyData(j, i, Global.TempLayer), PersMem.GetKeyType(j, i, Global.TempLayer));
            Global.LayerState[j][i] = Global.TempLayer;
            PressKey(PersMem.GetKeyData(j, i, Global.TempLayer), PersMem.GetKeyType(j, i, Global.TempLayer));
            Global.KeyStateCoolDown[j][i] = 255;
          }
        }
        else if (Global.KeyState[j][i] == LOW) // if key is up
        {
          if (Global.KeyStateCoolDown[j][i] == 255) // if key was previously held down
          {
            ReleaseKey(PersMem.GetKeyData(j, i, Global.LayerState[j][i]), PersMem.GetKeyType(j, i, Global.LayerState[j][i]));

            Global.KeyStateCoolDown[j][i] = Global.RefreshDelay;
          }
        }
      }
    }
    // end of physical key loops
    // start of countdowns
    for (byte i = 0; i < Global.ROW; i++)
    {
      for (byte j = 0; j < Global.COL; j++)
      {
        if (Global.KeyStateCoolDown[j][i] > 0 && Global.KeyStateCoolDown[j][i] != 255)
        {
          Global.KeyStateCoolDown[j][i]--;
        }
      }
    }
    //end of countdowns
    //*/
  }
  // end of pesudo rtos
  PersMem.Loop();
  Mod.Loop();
  Comms.Loop();
}


void PrePress(byte val, byte type)
{
}

void PressKey(byte val, byte type)
{
  if (type == 0)
  {
    AnimusKeyboard.Press(val);

  }
  Mod.PressKey(val, type);
}

void ReleaseKey(byte val, byte type)
{
  if (type == 0)
  {
    AnimusKeyboard.Release(val);

  }
  Mod.ReleaseKey(val, type);
}

void SwitchLayer(boolean increment)
{

}

void RotateLayer(byte val)
{

}


void KeyScan()
{
  for (int i = 0; i < Global.COL; i++)
  {
    pinMode(Global.HPins[i], OUTPUT);

    for (int j = 0; j < Global.ROW; j++)
    {
      byte val = digitalRead(Global.VPins[j]);
      Global.KeyState[i][j] = (val == LOW);
    }

    pinMode(Global.HPins[i], INPUT);
  }
}


unsigned long PreviousMillis = 0;
unsigned long CurrentMillis = 0;
boolean ReadyMillis = false;

void MillisLoop()
{
  CurrentMillis = millis();

  if(CurrentMillis - PreviousMillis >= 1) // this elapses every 1 ms
  {
    PreviousMillis = CurrentMillis;
    ReadyMillis = true;
  }
  else
  {
    ReadyMillis = false;
  }
}

boolean GetMillis()
{
  return ReadyMillis;
}
