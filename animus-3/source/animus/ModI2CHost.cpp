#include "ModI2CHost.h"
CModI2CHost::CModI2CHost(void)
{
  // nothing
}

void CModI2CHost::Begin(void)
{
  CModTemplate::Begin();
  ModGUID = 8; // GUID of this sspecific mod

  if (Global.HasUSB) // i2c host only activates if this device is plugged into the PC
  {
    Wire.begin();
  }
}


void CModI2CHost::LoadData(void)
{
  CModTemplate::LoadData();

  if (Global.HasUSB)
  {

  }
}

void CModI2CHost::Loop(void)
{
  CModTemplate::Loop();

  if (Global.HasUSB)
  {
    // syncs templayer value with guest
    if (Global.TempLayer != I2CTempLayer)
    {
      SetTempLayer();
      I2CTempLayer = Global.TempLayer;
    }
    if (Global.LEDBrightness != I2CLEDBrightness)
    {
      SetSubLEDBrightness();
      I2CLEDBrightness = Global.LEDBrightness;
    }
    // gets keystrokes from guest
    Wire.requestFrom(8, 32);
    bool hasInput = true;
    byte keyData;
    byte keyType;
    byte keyMode;
    byte keyX;
    byte keyY;
    while (hasInput)
    {
      if (Wire.available()) // need to put ifs in here so trailing bytes are left out
      {
        keyData = Wire.read();
      }
      else
      {
        hasInput = false;
        keyMode = 255;
      }
      if (Wire.available()) // need to put ifs in here so trailing bytes are left out
      {
        keyType = Wire.read();
      }
      else
      {
        hasInput = false;
        keyMode = 255;
      }
      if (Wire.available()) // need to put ifs in here so trailing bytes are left out
      {
        keyMode = Wire.read();
      }
      else
      {
        hasInput = false;
        keyMode = 255;
      }
      if (Wire.available()) // need to put ifs in here so trailing bytes are left out
      {
        byte tempByte = Wire.read();
        keyX = tempByte & 0x0f; // bitwise structure is YYYYXXXX
        keyY = tempByte >> 4;
      }
      else
      {
        hasInput = false;
        keyMode = 255;
      }

      if (keyMode == 1) // release key
      {
        Animus.ReleaseKey(keyData, keyType);
      }
      else if (keyMode == 5) // press key
      {
        Animus.PrePress(keyData, keyType);
        if (Global.TempLayer != I2CTempLayer)
        {
          SetTempLayer();
          I2CTempLayer = Global.TempLayer;
          Wire.beginTransmission(8);
          Wire.write(7);
          Wire.write(keyX);
          Wire.write(keyY);
          Wire.endTransmission();
          Wire.requestFrom(8, 2);
          if (Wire.available()) // need to put ifs in here so trailing bytes are left out
          {
            keyData = Wire.read();
          }
          if (Wire.available()) // need to put ifs in here so trailing bytes are left out
          {
            keyType = Wire.read();
          }
        }
        Animus.PressKey(keyData, keyType);
      }
    }
  }



  if (Animus.Async1MSDelay())
  {

    if (Global.HasUSB)
    {

    }
  }
}

void CModI2CHost::PressCoords(byte x, byte y)
{
  CModTemplate::PressCoords(x, y);

  if (Global.HasUSB)
  {

  }

}
void CModI2CHost::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
  if (Global.HasUSB)
  {

  }
}
void CModI2CHost::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);

  if (Global.HasUSB)
  {

  }
}
void CModI2CHost::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (Global.HasUSB)
  {

  }
}

void CModI2CHost::SerialComms(byte mode) // holy shit this is complicated
{
  CModTemplate::SerialComms(mode);
  if (Global.HasUSB)
  {
    if (mode == 6 || mode == 7)
    {
      if (Serial.available()) //TODO I might want to work in a timeout or fail check for this
      {
        if (SerialLoadCounter > 1024) // if this is the first time mode 6 has made contact
        {
          byte firstByte = (byte)Serial.read();
          byte secondByte = 0;
          bool hasAddr = false;
          if (Serial.available())
          {
            secondByte = (byte)Serial.read();
            hasAddr = true;
          }
          if (hasAddr)
          {
            SerialLoadCounter = (firstByte << 8) | secondByte;
          }
        }
        else
        {
          if (EEPROMPacketIndex < 30)
          {
            EEPROMPacket[EEPROMPacketIndex] = (byte)Serial.read();
            EEPROMPacketIndex++;
            SerialLoadCounter--;
          }
          if (EEPROMPacketIndex >= 30 || SerialLoadCounter <= 0) // do not use else here to make sure the message is sent in the same cycle
          {
            if (mode == 6)
            {
              SetSubEEPROM();
            }
            else if (mode == 7)
            {
              SetSubBoardSettings();
            }
            EEPROMPacketIndex = 0;
            if (SerialLoadCounter <= 0)
            {
              SerialLoadCounter = 1200;
              Comms.mode = 0;
            }
          }

        }
      }
    }
  }
}


// first byte is the type of the packet
// second byte always sends the templayer
// third byte forward is the data of the packet
/*
type 0 does nothing
type 1 sends templayer (templayer)
type 2 is a full reflash type that writes sub eeprom from 0 to 1024 (byte0, byte1, byte2, ...)
type 3 writes sub eeprom starting from 900 (byte0, byte1, byte2, ...)
type 4 changes the LED setting (brightness)
type 5 changes the refresh rate (refresh)
*/

void CModI2CHost::SetTempLayer()
{
  Wire.beginTransmission(8);
  Wire.write(1);
  Wire.write(Global.TempLayer);
  Wire.endTransmission();
}

void CModI2CHost::SetSubEEPROM(void)
{
  Wire.beginTransmission(8);
  Wire.write(2);
  Wire.write(EEPROMPacketIndex);
  Wire.write(EEPROMPacket, EEPROMPacketIndex);
  Wire.endTransmission();
}

void CModI2CHost::SetSubBoardSettings(void)
{
  Wire.beginTransmission(8);
  Wire.write(3);
  Wire.write(EEPROMPacketIndex);
  Wire.write(EEPROMPacket, EEPROMPacketIndex);
  Wire.endTransmission();
}



void CModI2CHost::SetSubLEDBrightness(void)
{
  Wire.beginTransmission(8);
  Wire.write(4);
  Wire.write(Global.LEDBrightness);
  Wire.endTransmission();
}

void CModI2CHost::SetSubRefreshRate(void)
{
  Wire.beginTransmission(8);
  Wire.write(5);
  Wire.write(Global.RefreshDelay);
  Wire.endTransmission();
}




CModI2CHost ModI2CHost;
