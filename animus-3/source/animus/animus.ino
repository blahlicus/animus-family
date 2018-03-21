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
