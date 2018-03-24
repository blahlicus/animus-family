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
  if (type == 0) // normal HID keystroke
  {
    AnimusKeyboard.Press(val);
  }
  else if (type == 1) // FN keys
  {
    Global.TempLayer = val;
  }
  else if (type == 2) // DEPRECIATED spaceFN, use mod_spaceFN instead
  {
    // do nothing
  }
  else if (type == 3) // move main layer up or down or bitwise rotate the layer
  {
    if (val == 0)
    {
      SwitchLayer(true);
    }
    else if (val == 1)
    {
      SwitchLayer(false);
    }
    else
    {
      RotateLayer(val);
    }
  }
  else if (type == 5) // toggle layers
  {
    if (Global.TempLayer == val)
    {
      Global.TempLayer = Global.KeyLayer;
    }
    else
    {
      Global.TempLayer = val;
    }
  }
  // for other key types, use a mod
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
  if (increment) // if true, go up a layer
  {
    Global.KeyLayer++;
  }
  else
  {
    Global.KeyLayer--;
  }
  if (Global.KeyLayer > 254) // rollover handling
  {
    Global.KeyLayer = Global.LAY -1;
  }
  else if (Global.KeyLayer >= Global.LAY)
  {
    Global.KeyLayer = 0;
  }

}

void RotateLayer(byte val) // bitwise layer shift
{
  byte newLayer = Global.KeyLayer;
  byte mask = 1 << newLayer;
  if (!val)
  {
    /* No layers are allowed. Do nothing. */
    return;
  }

  /*
  Find the next layer within the bitfield.
  Limit iterations to 10, to ensure no infinite loop.
  */
  for (byte i = 0; i < 10; i++)
  {
    newLayer++;
    mask <<= 1;
    if ((! mask) || (newLayer >= Global.LAY))
    {
      newLayer = 0;
      mask = 1;
    }

    if (val & mask)
    {
      /* newLayer is an allowed layer within the bitfield. */
      break;
    }
  }
  Global.KeyLayer = newLayer;
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
