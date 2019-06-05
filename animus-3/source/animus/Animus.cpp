#include "Animus.h"

CAnimus::CAnimus(void)
{

}

void CAnimus::Begin()
{
  PersMem.Begin(); // loads data from EEPROM to RAM
  AnimusKeyboard.Begin(); // initialise keyboard module
  Comms.Begin(BAUD); // start comms
  Mod.Begin(); // initialise mods
}

void CAnimus::Loop()
{
  MillisLoop(); // checks pseudoRTOS status

  // start of pseudo rtos code
  if (Async1MSDelay()) // should run once every 1 to 1.5ms
  {

    // layering checks in case of layout remapping
    if (Global.KeyLayer >= Global.LAY || Global.TempLayer >= Global.LAY)
    {
      Global.KeyLayer = 0;
      Global.TempLayer = 0;
    }

    KeyScan(); // physical key layers scanned
    // start of physical key loops
    for (byte i = 0; i < Global.ROW; i++) // this is placed inside the 1ms delay to slow it down a bit
    {
      for (byte j = 0; j < Global.COL; j++)
      {
        if (Global.KeyState[j][i] == HIGH) // if key is down
        {
          if (Global.KeyStateCoolDown[j][i] == 0) // if key was not recently released
          {
            PressCoords(j, i);
            Global.LayerState[j][i] = Global.TempLayer;
            PrePress(PersMem.GetKeyData(j, i, Global.TempLayer), PersMem.GetKeyType(j, i, Global.TempLayer));
            PressKey(PersMem.GetKeyData(j, i, Global.TempLayer), PersMem.GetKeyType(j, i, Global.TempLayer));
            Global.KeyStateCoolDown[j][i] = 255;
          }
        }
        else if (Global.KeyState[j][i] == LOW) // if key is up
        {
          if (Global.KeyStateCoolDown[j][i] == 255 - Global.KeyUpDelay) // if key was previously held down AND is currently up after KeyUpDelay amount of time
          {
            ReleaseKey(PersMem.GetKeyData(j, i, Global.LayerState[j][i]), PersMem.GetKeyType(j, i, Global.LayerState[j][i]));
            Global.KeyStateCoolDown[j][i] = Global.KeyDownDelay;
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
        // what we did here saved 16 bits per key
        if (Global.KeyStateCoolDown[j][i] > 0 && Global.KeyStateCoolDown[j][i] != 255 - Global.KeyUpDelay)
        {
          Global.KeyStateCoolDown[j][i]--; // decrement KeyStateCoolDown if the key is being held down or if it was released, thus activating the keyup and keydown cooldowns
        }
      }
    }
    //end of countdowns
  }
  // end of pesudo rtos
  PersMem.Loop();
  Mod.Loop();
  Comms.Loop();
}

void CAnimus::PressCoords(byte x, byte y)
{
  Mod.PressCoords(x, y);
}

void CAnimus::PrePress(byte val, byte type)
{
  Mod.PrePress(val, type);
}

void CAnimus::PressKey(byte val, byte type)
{
  if (Global.HasUSB)
  {
    if (type == 0) // normal HID keystroke
    {
      AnimusKeyboard.Press(val);
    }
    else if (type == 1) // FN keys
    {
      Global.TempLayer = val;
    }
    else if (type == 2) // move main layer up or down or bitwise rotate the layer
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
    else if (type == 3) // toggle layers
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
  }

  // for other key types, use a mod
  Mod.PressKey(val, type);
}

void CAnimus::ReleaseKey(byte val, byte type)
{
  if (Global.HasUSB)
  {
    if (type == 0)
    {
      AnimusKeyboard.Release(val);

    }
    else if (type == 1)
    {
      Global.TempLayer = Global.KeyLayer;
    }
  }
  Mod.ReleaseKey(val, type);
}

void CAnimus::SwitchLayer(bool increment)
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

void CAnimus::RotateLayer(byte val) // bitwise layer shift
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


void CAnimus::KeyScan()
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




void CAnimus::MillisLoop()
{
  CurrentMillis = millis();

  if(CurrentMillis - PreviousMillis >= 1) // this elapses every 1-1.5 ms
  {
    PreviousMillis = CurrentMillis;
    ReadyMillis = true;
  }
  else
  {
    ReadyMillis = false;
  }
}

bool CAnimus::Async1MSDelay()
{
  return ReadyMillis;
}

CAnimus Animus;
