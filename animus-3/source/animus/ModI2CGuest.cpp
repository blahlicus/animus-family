#include "ModI2CGuest.h"

CModI2CGuest::CModI2CGuest(void)
{
  // nothing
}

void CModI2CGuest::Begin(void) //TODO add method to return entire EEPROM to host
{
  CModTemplate::Begin();
  ModGUID = 9; // GUID of this specific mod

  if (!Global.HasUSB) // if no usb
  {
    Wire.begin(8);
    Wire.onRequest(RequestEvent);
    Wire.onReceive(ReceiveEvent);
  }
}

void CModI2CGuest::OnRequest()
{
  if (SlaveIndex == 0) // if slave array is empty, add single byte
  {
    Wire.write(0);
  }
  Wire.write(SlaveArray, SlaveIndex);
  SlaveIndex = 0;
}

void CModI2CGuest::OnReceive(int numBytes)
{

  byte type = Wire.read();
  if (type == 1) // received templay
  {
    byte input = Wire.read();
    Global.TempLayer = input;
  }
  else if (type == 2) // setEEPROM
  {

    byte byteA = Wire.read();
    byte byteB = Wire.read();
    short startAddr = (byteA << 8) | byteB;
    while (Wire.available())
    {
      PersMem.SetEEPROM(startAddr, Wire.read());
      startAddr++;
    }
  }
  else if (type == 3) // return part of the EEPROM
  {
    byte byteA = Wire.read();
    byte byteB = Wire.read();
    short startAddr = (byteA << 8) | byteB;
    SlaveIndex = 0;
    while (SlaveIndex < 32 && startAddr < 1024)
    {
      SlaveArray[SlaveIndex] = PersMem.GetEEPROM(startAddr);
      SlaveIndex++;
      startAddr++;
    }
  }
  else if (type == 4) // update brightness
  {
    Global.LEDBrightness = Wire.read();
  }
  else if (type == 5) // update refresh rate
  {
    Global.RefreshDelay = Wire.read();
  }
  else if (type == 6) // resend for erreneous key
  {
    byte x = Wire.read();
    byte y = Wire.read();
    Global.LayerState[x][y] = Global.TempLayer;
    if (SlaveIndex < 32)
    {
      SlaveArray[SlaveIndex] = PersMem.GetKeyData(x, y, Global.TempLayer);
      SlaveIndex++;
      SlaveArray[SlaveIndex] = PersMem.GetKeyType(x, y, Global.TempLayer);
      SlaveIndex++;
    }
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

  if (Animus.Async1MSDelay())
  {

    if (Global.HasUSB)
    {

    }
  }
}

void CModI2CGuest::PressCoords(byte x, byte y)
{
  CModTemplate::PressCoords(x, y);
  if (!Global.HasUSB)
  {
    if (SlaveIndex < 32)
    {
      byte Coord = (y << 4) | x; // bitwise format is YYYYXXXX
      SlaveArray[SlaveIndex] = Coord;
      SlaveIndex++;
    }
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

  if (!Global.HasUSB)
  {
    if (SlaveIndex < 32)
    {
      SlaveArray[SlaveIndex] = val;
      SlaveIndex++;
      SlaveArray[SlaveIndex] = type;
      SlaveIndex++;
      SlaveArray[SlaveIndex] = 5;
      SlaveIndex++;
    }
  }
}
void CModI2CGuest::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (!Global.HasUSB)
  {
    if (SlaveIndex < 32)
    {
      SlaveArray[SlaveIndex] = 0;
      SlaveIndex++;
      SlaveArray[SlaveIndex] = val;
      SlaveIndex++;
      SlaveArray[SlaveIndex] = type;
      SlaveIndex++;
      SlaveArray[SlaveIndex] = 1;
      SlaveIndex++;
    }
  }
}

static void CModI2CGuest::RequestEvent()
{
  ModI2CGuest.OnRequest();
}

static void CModI2CGuest::ReceiveEvent(int numBytes)
{
  ModI2CGuest.OnReceive(numBytes);
}

void CModI2CGuest::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModI2CGuest ModI2CGuest;
