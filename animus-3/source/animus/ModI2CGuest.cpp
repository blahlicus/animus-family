#include "ModI2CGuest.h"
CModI2CGuest::CModI2CGuest(void)
{
  // nothing
}

void CModI2CGuest::Begin(void)
{
  CModTemplate::Begin();
  ModGUID = 9; // GUID of this sspecific mod

  if (Global.HasUSB) // i2c guest only activates if this device is not plugged into the PC
  {
    // do nothing
  }
  else
  {
    Wire.begin(); // start i2c as master
  }
}

void CModI2CGuest::LoadData(void)
{
  CModTemplate::LoadData();

  if (Global.HasUSB)
  {

  }
}

void CModI2CGuest::Loop(void)
{
  CModTemplate::Loop();

  if (Animus.GetMillis())
  {
    if (!Global.HasUSB)
    {


      for (byte i = 0; i < Global.ROW; i++)
      {
        for (byte j = 0; j < Global.COL; j++)
        {
          if (Global.KeyState[j][i] == HIGH) // if key is down
          {
            if (Global.KeyStateCoolDown[j][i] == 0) // if key was not recently released
            {
              KeyXBuffer[KeyIndex] = j;
              KeyYBuffer[KeyIndex] = i;
              KeyModeBuffer[KeyIndex] = 1;
              KeyIndex++;
              Global.KeyStateCoolDown[j][i] = 255;
            }
          }
          else if (Global.KeyState[j][i] == LOW) // if key is up
          {
            if (Global.KeyStateCoolDown[j][i] == 255) // if key was previously held down
            {
              KeyXBuffer[KeyIndex] = j;
              KeyYBuffer[KeyIndex] = i;
              KeyModeBuffer[KeyIndex] = 0;
              KeyIndex++;
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


      if (KeyIndex > 0)
      {
        Wire.requestFrom(8, 32); //request non-routine transmission from host
        ProcessPacket();
        for (byte i = 0; i < KeyIndex; i++)
        {
          if (KeyModeBuffer[i] == 1) // keydown
          {
            Mod.PrePress(PersMem.GetKeyData(KeyXBuffer[i], KeyYBuffer[i], Global.TempLayer), PersMem.GetKeyType(KeyXBuffer[i], KeyYBuffer[i], Global.TempLayer));
            Global.LayerState[KeyXBuffer[i]][KeyYBuffer[i]] = Global.TempLayer;
            PressKey(PersMem.GetKeyData(KeyXBuffer[i], KeyYBuffer[i], Global.TempLayer), PersMem.GetKeyType(KeyXBuffer[i], KeyYBuffer[i], Global.TempLayer));
            I2CBuffer[I2CBufferIndex] = PersMem.GetKeyData(KeyXBuffer[i], KeyYBuffer[i], Global.TempLayer);
            I2CBufferIndex++;
            I2CBuffer[I2CBufferIndex] = PersMem.GetKeyType(KeyXBuffer[i], KeyYBuffer[i], Global.TempLayer);
            I2CBufferIndex++;
            I2CBuffer[I2CBufferIndex] = 1;
            I2CBufferIndex++;
          }
          else // keyup
          {
            ReleaseKey(PersMem.GetKeyData(KeyXBuffer[i], KeyYBuffer[i], Global.LayerState[KeyXBuffer[i]][KeyYBuffer[i]]), PersMem.GetKeyType(KeyXBuffer[i], KeyYBuffer[i], Global.LayerState[KeyXBuffer[i]][KeyYBuffer[i]]));
            I2CBuffer[I2CBufferIndex] = PersMem.GetKeyData(KeyXBuffer[i], KeyYBuffer[i], Global.TempLayer);
            I2CBufferIndex++;
            I2CBuffer[I2CBufferIndex] = PersMem.GetKeyType(KeyXBuffer[i], KeyYBuffer[i], Global.TempLayer);
            I2CBufferIndex++;
            I2CBuffer[I2CBufferIndex] = 0;
            I2CBufferIndex++;
          }
        }
        Wire.beginTransmission(8);
        Wire.write(I2CBuffer, I2CBufferIndex);
        Wire.endTransmission();
        I2CBufferIndex = 0;
        KeyIndex = 0;
      }
      else
      {

        Wire.beginTransmission(8);
        Wire.write(255); // random bit, this lets the host know this is a routine transmission
        Wire.endTransmission();
        Wire.requestFrom(8, 32); // request routine transmission from host
        ProcessPacket();
      }
    }
  }


}

void CModI2CGuest::ProcessPacket(void)
{
  byte arr[32];
  byte arrIndex = 0;
  while (Wire.available())
  {
    arr[arrIndex] = Wire.read();
    arrIndex++;
  }

  if (arr[0] == 1) // temp layer only
  {
    Global.TempLayer = arr[1];
  }
  else if (arr[0] == 2) // load data to eeprom
  {
    Global.TempLayer = arr[1];
    for (byte i = 2; i < arrIndex; i++)
    {
      EEPROM.update(EEPROMLoadIndex, arr[i]);
    }
  }
  else if (arr[0] == 3) // EOL for type 2
  {
    Global.TempLayer = arr[1];
    for (byte i = 2; i < arrIndex; i++)
    {
      EEPROM.update(EEPROMLoadIndex, arr[i]);
    }
    EEPROMLoadIndex = 0;
  }
  else if (arr[0] == 4) // load data to board info zone (addr >900)
  {
    Global.TempLayer = arr[1];
    if (EEPROMLoadIndex < 900)
    {
      EEPROMLoadIndex = 900;
    }
    for (byte i = 2; i < arrIndex; i++)
    {
      EEPROM.update(EEPROMLoadIndex, arr[i]);
    }
  }
  else if (arr[0] == 5) // EOL for type 5
  {
    Global.TempLayer = arr[1];
    if (EEPROMLoadIndex < 900)
    {
      EEPROMLoadIndex = 900;
    }
    for (byte i = 2; i < arrIndex; i++)
    {
      EEPROM.update(EEPROMLoadIndex, arr[i]);
    }
    EEPROMLoadIndex = 0;
  }
  else if (arr[0] == 6) // refresh LED
  {
    Global.TempLayer = arr[1];
    Global.LEDBrightness = arr[2];
  }
  else if (arr[0] == 7) // update refresh rate
  {
    Global.TempLayer = arr[1];
    PersMem.SetRefreshRate(arr[2]);
  }
}


void CModI2CGuest::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
  if (Global.HasUSB)
  {

  }
}
void CModI2CGuest::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);

  if (Global.HasUSB)
  {

  }
}
void CModI2CGuest::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (Global.HasUSB)
  {

  }
}

void CModI2CGuest::SerialComms(byte mode) // holy shit this is complicated
{
  CModTemplate::SerialComms(mode);



}





CModI2CGuest ModI2CGuest;
