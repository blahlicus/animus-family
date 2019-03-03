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
    isMaster = true;
    SetMaster(false);
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
    if (Comms.mode == 6) // write to guest eeprom starting at addr = 0 or MEM_BOARD_TYPE, ending at first short read from serial
    {
      if (Serial.available()) // TODO I might want to work in a timeout or fail check for this
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
            pendingEEPROMUpdate = true;
            Comms.mode = 0;
          }
        }
      }
    }
    else if (Comms.mode == 7) // request read sub EEPROM
    {
      short addr = 0;
      while (addr < MEM_EEPROM_SIZE)
      {
        GetSubEEPROM(addr); // TODO
        Wire.requestFrom(I2C_GUEST_ADDRESS, 32);
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
  Wire.write(1);
  Wire.write(Global.TempLayer);
}

void CModI2CHost::SetSubEEPROM(void)
{
  Wire.write(2);
  Wire.write(EEPROMPacket, EEPROMPacketIndex);
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
  Wire.write(4);
  Wire.write(Global.LEDBrightness);
}

void CModI2CHost::SetSubKeyboardDelay(void)
{
  Wire.write(5);
  Wire.write(Global.KeyDownDelay);
  Wire.write(Global.KeyUpDelay);
}



void CModI2CHost::OnReceive(int numBytes)
{
  SetMaster (true);
  Wire.beginTransmission(I2C_GUEST_ADDRESS);

  // Parse package
  byte buffer[numBytes];
  Wire.readBytes(buffer, numBytes);

  byte keyData[8];
  byte keyType[8];
  byte keyMode[8];
  byte keyX[8];
  byte keyY[8];
  byte keyIndex = 0;

  for (int i = 0; i < numBytes; i+=4, keyIndex++)
  {
    keyX[keyIndex]    = buffer[i+0] & 0x0f; // bitwise structure is YYYYXXXX
    keyY[keyIndex]    = buffer[i+0] >> 4;
    keyData[keyIndex] = buffer[i+1];
    keyType[keyIndex] = buffer[i+2];
    keyMode[keyIndex] = buffer[i+3];
  }

  // Execute keypresses
  for (byte i = 0; i < keyIndex; i++)
  {
    if (keyMode[i] == 1) // release key
    {
      Animus.ReleaseKey(keyData[i], keyType[i]);
    }
    else if (keyMode[i] == 5) // press key
    {
      if (Global.TempLayer != I2CTempLayer) // Wrong layout!
      {
        SetTempLayer();
        I2CTempLayer = Global.TempLayer;
        Wire.write(6);
        Wire.write(keyX[i]);
        Wire.write(keyY[i]);
      }
      else
      {
        Animus.PrePress(keyData[i], keyType[i]);
        Animus.PressKey(keyData[i], keyType[i]);
      }
    }
  }

  // Send updates
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
  if (Global.KeyDownDelay != I2CKeyDown || Global.KeyUpDelay != I2CKeyUp)
  {
    SetSubKeyboardDelay();
    I2CKeyDown = Global.KeyDownDelay;
    I2CKeyUp = Global.KeyUpDelay;
  }
  if (pendingEEPROMUpdate)
  {
    SetSubEEPROM();
    EEPROMPacketIndex = 2;
    SerialLoaderByteStatus = 0;
    pendingEEPROMUpdate = false;
  }

  Wire.endTransmission();
  SetMaster(false);
}

void CModI2CHost::SetMaster(bool value)
{
  if (isMaster == value) return;

  isMaster = value;
  Wire.end();

  if (value)
  {
    Wire.begin();
  }
  else
  {
    Wire.begin(I2C_HOST_ADDRESS);
    Wire.onReceive([] (int numBytes) {ModI2CHost.OnReceive(numBytes);});
  }
}


CModI2CHost ModI2CHost;
