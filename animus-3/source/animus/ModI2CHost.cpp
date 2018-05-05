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
    Wire.begin(8);
    Wire.onRequest(CModI2CHost::RequestInfo);
    Wire.onReceive(CModI2CHost::ReceiveInfo);
  }
}

void CModI2CHost::RequestEvent()
{
  // first byte is the type of the packet
  // second byte always sends the templayer
  // third byte forward is the data of the packet
  /*
  type 0 procs any layer change, then sends templayer
  type 1 sends templayer (templayer) as a routine ping
  type 2 is a full reflash type that writes sub eeprom from 0 to 1024 (byte0, byte1, byte2, ...)
  type 3 signals EOL for other continuous types (length, byte0, byte1, byte2, ...)
  type 4 writes sub eeprom starting from 900 (byte0, byte1, byte2, ...)
  type 5 EOL for type 4
  type 6 changes the LED setting (brightness)
  type 7 changes the refresh rate (refresh)
  */

  if (Global.HasUSB)
  {
    if (SignalType == 0)
    {
      Animus.PrePress(255, 255); // sends blank signal to trigger any layer changes
      if (BrightnessRefreshValue == Global.LEDBrightness)
      {
        SetTempLayer();
      }
      else
      {
        SetSubLEDBrightness();
        BrightnessRefreshValue = Global.LEDBrightness;
      }
    }
    else if (SignalType == 1)
    {
      if (BrightnessRefreshValue == Global.LEDBrightness)
      {
        SetTempLayer();
      }
      else
      {
        SetSubLEDBrightness();
        BrightnessRefreshValue = Global.LEDBrightness;
      }
      SignalType = 0;
    }
    else if (SignalType == 2)
    {
      SetSubEEPROM();
      EEPROMPacketIndex = 0;
      EEPROMPacketCounter--;
      SignalType == 0;
    }
    else if (SignalType == 3)
    {
      SetSubEEPROMEOL();
      EEPROMPacketIndex = 255; // resets packet index and counter
      EEPROMPacketCounter = 255;
      SignalType == 0;
    }
    else if (SignalType == 4)
    {
      SetSubBoardSettings();
      EEPROMPacketIndex = 0;
      EEPROMPacketCounter--;
      SignalType == 0;
    }
    else if (SignalType == 5)
    {
      SetSubBoardEOL();
      EEPROMPacketIndex = 255; // resets packet index and counter
      EEPROMPacketCounter = 255;
      SignalType == 0;
    }
    else if (SignalType == 6)
    {
      SetSubLEDBrightness();
      SignalType == 0;
    }
    else if (SignalType == 7)
    {
      SetSubRefreshRate();
      SignalType == 0;
    }
  }
}

void CModI2CHost::ReceiveEvent(byte numBytes)
{
  if (Global.HasUSB)
  {
    if (numBytes > 1) // this means that the request from guest is asking to proc layer changes
    {
      while (Wire.available())
      {
        byte keyVal = Wire.read();
        byte keyType = Wire.read();
        byte keyDown = Wire.read();
        if (keyDown == 1)
        {
          Animus.PrePress(keyVal, keyType);
          Animus.PressKey(keyVal, keyType);
        }
        else
        {
          Animus.ReleaseKey(keyVal, keyType);
        }
      }
    }
    else // this means that the request from guest is doing a routine ping
    {
      SignalType = 1;
    }
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

  if (Animus.GetMillis())
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

    if (mode == 6 || mode == 7) // start of package transfer TODO: you could remove the length in non-EOL packets
    {
      if (Serial.available()>0)
      {
        if (EEPROMPacketCounter == 255) // if first byte from message is not read
        {
          EEPROMPacketCounter = Serial.read(); // read first byte as packet counter
        }
        else if (EEPROMPacketEOLSize == 255) // if second byte from message is not read
        {
          EEPROMPacketEOLSize = Serial.read();
        }
        else // length and number of packets is currently known
        {
          if (SignalType == 1) // if packet buffer is free
          {
            if (EEPROMPacketCounter-1 > 0) // if there are still pending packets
            {
              if (EEPROMPacketIndex < 29) // if i2c transfer buffer is not filled then fill buffer
              {
                EEPROMPacket[EEPROMPacketIndex] = Serial.read();
                EEPROMPacketIndex++;
              }
              else // when buffer is filled, signal package ready to send
              {
                if (mode == 6) // this is for addresses 0 to 900
                {
                  SignalType = 2;
                }
                else if (mode == 7) // this is for addresses 900 to 1023
                {
                  SignalType = 4;
                }
              }
            }
            else // this is the EOL packet
            {
              if (EEPROMPacketIndex < EEPROMPacketEOLSize) // if EOL packet reaches designated size
              {
                EEPROMPacket[EEPROMPacketIndex] = Serial.read();
                EEPROMPacketIndex++;
              }
              else // last package ready, signal package ready to send
              {
                if (mode == 6)
                {
                  SignalType = 3;
                }
                else if (mode == 7)
                {
                  SignalType = 5;
                }
                Comms.mode = 0;// comms is reset
              }
            }
          }
        }
      }
    }
  }

}

void CModI2CHost::RequestInfo(void)
{
  ModI2CHost.RequestEvent();
}

void CModI2CHost::ReceiveInfo(byte numBytes)
{
  ModI2CHost.ReceiveEvent(numBytes);
}

// first byte is the type of the packet
// second byte always sends the templayer
// third byte forward is the data of the packet
/*
type 0 does nothing
type 1 sends templayer (templayer)
type 2 is a full reflash type that writes sub eeprom from 0 to 1024 (byte0, byte1, byte2, ...)
type 3 signals EOL for other continuous types (length, byte0, byte1, byte2, ...)
type 4 writes sub eeprom starting from 900 (byte0, byte1, byte2, ...)
type 5 EOL for type 4
type 6 changes the LED setting (brightness)
type 7 changes the refresh rate (refresh)
*/

void CModI2CHost::SetTempLayer()
{
  Wire.write(1);
  Wire.write(Global.TempLayer);
}

void CModI2CHost::SetSubEEPROM(void)
{
  Wire.write(2);
  Wire.write(Global.TempLayer);
  Wire.write(EEPROMPacket, EEPROMPacketIndex);
}

void CModI2CHost::SetSubEEPROMEOL(void)
{
  Wire.write(3);
  Wire.write(Global.TempLayer);
  Wire.write(EEPROMPacketIndex);
  Wire.write(EEPROMPacket, EEPROMPacketIndex);
}

void CModI2CHost::SetSubBoardSettings(void)
{
  Wire.write(4);
  Wire.write(Global.TempLayer);
  Wire.write(EEPROMPacket, EEPROMPacketIndex);
}


void CModI2CHost::SetSubBoardEOL(void)
{
  Wire.write(5);
  Wire.write(Global.TempLayer);
  Wire.write(EEPROMPacketIndex);
  Wire.write(EEPROMPacket, EEPROMPacketIndex);
}

void CModI2CHost::SetSubLEDBrightness(void)
{
  Wire.write(6);
  Wire.write(Global.TempLayer);
  Wire.write(Global.LEDBrightness);
}

void CModI2CHost::SetSubRefreshRate(void)
{
  Wire.write(7);
  Wire.write(Global.TempLayer);
  Wire.write(Global.RefreshDelay);
}




CModI2CHost ModI2CHost;
