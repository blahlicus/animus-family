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
    if (Global.RefreshDelay != I2CRefresh)
    {
      SetSubRefreshRate();
      I2CRefresh = Global.RefreshDelay;
    }
    // gets keystrokes from guest
    Wire.requestFrom(8, 32);
    bool hasInput = true;
    byte keyData[8];
    byte keyType[8];
    byte keyMode[8];
    byte keyX[8];
    byte keyY[8];
    byte keyIndex = 0;
    while (hasInput)
    {

      if (Wire.available()) // need to put ifs in here so trailing bytes are left out
      {
        byte tempByte = Wire.read();
        keyX[keyIndex] = tempByte & 0x0f; // bitwise structure is YYYYXXXX
        keyY[keyIndex] = tempByte >> 4;
      }
      else
      {
        hasInput = false;
      }

      if (Wire.available()) // need to put ifs in here so trailing bytes are left out
      {
        keyData[keyIndex] = Wire.read();
      }
      else
      {
        hasInput = false;
      }

      if (Wire.available()) // need to put ifs in here so trailing bytes are left out
      {
        keyType[keyIndex] = Wire.read();
      }
      else
      {
        hasInput = false;
      }

      if (Wire.available()) // need to put ifs in here so trailing bytes are left out
      {
        keyMode[keyIndex] = Wire.read();
        keyIndex++;
      }
      else
      {
        hasInput = false;
      }
    }

    for (byte i = 0; i < keyIndex; i++)
    {

      if (keyMode[i] == 1) // release key
      {
        Animus.ReleaseKey(keyData[i], keyType[i]);
      }
      else if (keyMode[i] == 5) // press key
      {
        Animus.PrePress(keyData[i], keyType[i]);
        if (Global.TempLayer != I2CTempLayer)
        {
          SetTempLayer();
          I2CTempLayer = Global.TempLayer;
          Wire.beginTransmission(8);
          Wire.write(6);
          Wire.write(keyX[i]);
          Wire.write(keyY[i]);
          Wire.endTransmission();
          Wire.requestFrom(8, 2);
          if (Wire.available()) // need to put ifs in here so trailing bytes are left out
          {
            keyData[i] = Wire.read();
          }
          if (Wire.available()) // need to put ifs in here so trailing bytes are left out
          {
            keyType[i] = Wire.read();
          }
        }
        Animus.PressKey(keyData[i], keyType[i]);
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



  // serial communication

  if (Global.HasUSB)
  {
    if (Comms.mode == 6) // write to guest eeprom starting at addr = 0 or 900, ending at first short read from serial
    {
      EEPROM.update(0, 5);
      if (Serial.available()) //TODO I might want to work in a timeout or fail check for this
      {
        if (SerialLoaderByteStatus == 0) // if this is the first time mode 6 has made contact
        {
          EEPROMPacket[0] = (byte)Serial.read();
          SerialLoaderByteStatus = 1;
        }
        else if (SerialLoaderByteStatus == 1) // if this is the second time mode 6 has made contact
        {
          EEPROMPacket[1] = (byte)Serial.read();
          SerialLoaderByteStatus = 2;

        }
        else if (SerialLoaderByteStatus == 2) // if status is 2, get packet size
        {
          EEPROMPacketSize = (byte)Serial.read();
          SerialLoaderByteStatus = 3;

        }
        else if (SerialLoaderByteStatus == 3) // if mode 6 has obtained the start address and package length
        {
          if (EEPROMPacketSize > 0)
          {
            EEPROMPacket[EEPROMPacketIndex] = (byte)Serial.read();
            EEPROMPacketIndex++;
            EEPROMPacketSize--;
          }
          if (EEPROMPacketSize <= 0)
          {
            SetSubEEPROM();
            EEPROMPacketIndex = 2;
            SerialLoaderByteStatus = 0;
            Comms.mode = 0;
          }
        }
      }
    }
    else if (Comms.mode == 7) // request read sub EEPROM
    {
      short addr = 0;
      while(addr < 1024)
      {
        GetSubEEPROM(addr);
        Wire.requestFrom(8, 32);
        while(Wire.available())
        {
          Serial.println(Wire.read());
        }
        addr = addr + 32;
      }
      Comms.mode = 0;
    }
  }
}




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
  Wire.write(EEPROMPacket, EEPROMPacketIndex);
  Wire.endTransmission();
}

void CModI2CHost::GetSubEEPROM(short startAddr)
{
  Wire.beginTransmission(8);
  Wire.write(3);
  byte byteA = startAddr >> 8; // this gets the bytes 1111111100000000
  byte byteB = startAddr & 0xff; // this gets the bytes 0000000011111111
  Wire.write(byteA);
  Wire.write(byteB);
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
