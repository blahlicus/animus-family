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
  ResetPins();
  delay(300);

}


void loop()
{

  if (GetMillis()) // should run once every 1 to 1.5ms
  {

    // layering checks in case of layout remapping
    if (Global.KeyLayer > Global.LAY || Global.TempLayer > Global.LAY)
    {
      Global.KeyLayer = 0;
      Global.TempLayer = 0;
    }

    KeyScan(); // physical key layers scanned

      for (byte i = 0; i < Global.ROW; i++)
      {
        for (byte j = 0; j < Global.COL; j++)
        {
          if (Global.KeyState[j][i] == HIGH) // if key is down
          {
            if (Global.KeyStateCoolDown[j][i] == 0) // if key is still down after debounce time
            {
              ModPressCoord(j, i);
              ModPrePress(GetValEEPROM(j, i, TempLayer), GetTypeEEPROM(j, i, TempLayer));
              LayerState[j][i] = TempLayer;
              PressKey(GetValEEPROM(j, i, TempLayer), GetTypeEEPROM(j, i, TempLayer));
              Global.KeyStateCoolDown[j][i] = Global.RefreshDelay;

            }
            else if (KeyStateCountDown[j][i] == 0) // if key is still down after debounce time
            {
              KeyStateCountDown[j][i] = builder_refresh+1;
            }

          }
          else if (KeyState[j][i] == LOW)
          {
            if (KeyStateCountDown[j][i] == 255)
            {
              ReleaseKey(GetValEEPROM(j, i, LayerState[j][i]), GetTypeEEPROM(j, i, LayerState[j][i]));

              KeyStateCountDown[j][i] = 0;
            }

          }


  }


  PersMem.Loop();
  Mod.Loop();
  Comms.Loop();
}

void PrePress(char val, byte type)
{
  Mod.PrePress(val, type);
}

void PressKey(char val, byte type)
{
  Mod.PressKey(val, type);
}

void ReleaseKey(char val, byte type)
{
  Mod.ReleaseKey(val, type);
}

void SwitchLayer(boolean increment)
{

}

void RotateLayer(byte val)
{

}

void ResetPins()
{
  for (int i = 0; i < Global.ROW; i++)
  {
    pinMode(Global.VPins[i], INPUT);
    digitalWrite(Global.VPins[i], HIGH);
  }

  for (int i = 0; i < Global.COL; i++)
  {
    pinMode(Global.HPins[i], INPUT);
    digitalWrite(Global.HPins[i], LOW);
  }

  for (int i = 0; i < Global.ROW; i++)
  {
    for (int j = 0; j < Global.COL; j++)
    {
      Global.KeyState[j][i] = 0;
      Global.PreviousState[j][i] = 0;
    }
  }
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
  unsigned long currentMillis = millis();

  if(CurrentMillis - PreviousMillis >= 1) // this elapses every 1 ms
  {
    PreviousMillis = CurrentMillis;
    ReadyMillis = true;
  }
  elapses
  {
    ReadyMillis = false;
  }
}

boolean GetMillis()
{
  return ReadyMillis;
}
