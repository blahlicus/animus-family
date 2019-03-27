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
    isMaster = false;
    SetMaster(true);
  }
}

void CModI2CGuest::OnReceive(int numBytes)
{
  byte errorOffset = 0;

  while (Wire.available())
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
      if (startAddr == 65535) // this is end of packets signal
      {
        pullRate = DEFAULT_I2C_PULL_RATE; // lowers the pull rate
        PersMem.CommitEEPROM(); // commits EEPROM
        Global.RequiresLoadData = true; // reloads persistent data to SRAM
      }
      else
      {
        pullRate = 1;
        for (short i = startAddr; i < MEM_EEPROM_SIZE && Wire.available(); i++)
        {
          PersMem.SetEEPROM(i, Wire.read());
        }
      }

    }
    else if (type == 3) // return part of the EEPROM
    {
      byte byteA = Wire.read();
      byte byteB = Wire.read();
      SlaveIndex = 0;
      for (short i = (byteA << 8) | byteB; i < MEM_EEPROM_SIZE; i++)
      {
        SlaveArray[SlaveIndex] = PersMem.GetEEPROM(i);
        SlaveIndex++;
      }
    }
    else if (type == 4) // update brightness
    {
      Global.LEDBrightness = Wire.read();
    }
    else if (type == 5) // update refresh rate
    {
      Global.KeyDownDelay = Wire.read();
      Global.KeyUpDelay   = Wire.read();
    }
    else if (type == 6) // erreneous key
    {
      byte x = Wire.read();
      byte y = Wire.read();
      Global.LayerState[x][y] = Global.TempLayer;

      if (32 - SlaveIndex >= 3)
      {
        // We want all erreneous keys to appear before any keypresses that might have
        // occured, in chronological order.
        if (SlaveIndex > 0)
        {
          memcpy(SlaveArray + errorOffset + 3, SlaveArray + errorOffset, SlaveIndex - errorOffset);
        }
        SlaveArray[errorOffset + 0] = PersMem.GetKeyData(x, y, Global.TempLayer);
        SlaveArray[errorOffset + 1] = PersMem.GetKeyType(x, y, Global.TempLayer);
        SlaveArray[errorOffset + 2] = 5;
        SlaveIndex += 3;
        errorOffset += 3;
      }
    }
  }

  SetMaster(true);
  pullTimeout = 0;
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

  if (!Global.HasUSB && isMaster)
  {
    if (SlaveIndex > 0)
    {
      Wire.beginTransmission(I2C_HOST_ADDRESS);
      Wire.write(SlaveArray, SlaveIndex);
      Wire.endTransmission();
      SlaveIndex = 0;
      SetMaster(false);
    }
    else if (Animus.Async1MSDelay())
    {
      pullTimeout++;
      if (pullTimeout >= pullRate) // Send an empty message to pull updates from the host
      {
        Wire.beginTransmission(I2C_HOST_ADDRESS);
        Wire.endTransmission();
        SetMaster(false);
      }
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
/* TODO: Remove this part when everything is confirmed to work
static void CModI2CGuest::RequestEvent()
{
ModI2CGuest.OnRequest();
}

static void CModI2CGuest::ReceiveEvent(int numBytes)
{
ModI2CGuest.OnReceive(numBytes);
}
//*/
void CModI2CGuest::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


void CModI2CGuest::SetMaster(bool value)
{
  if (isMaster == value) return;

  isMaster = value;
  Wire.end();

  if (value)
  {
    Wire.begin();
    Wire.onReceive([] (int numBytes) {ModI2CGuest.OnReceive(numBytes);});
  }
  else
  {
    Wire.begin(I2C_GUEST_ADDRESS);
  }
}


CModI2CGuest ModI2CGuest;
