/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
I2C
BUILDER_REQUIREMENT_END
*/

#define mod_modname I2C
#define modMethod(str) conca(mod_modname, str)

#define LEDBRIGHTSETTER I2CSetLEDBrightness

#include "Wire.h"
byte modMethod(EEPROMPacket)[31];
byte modMethod(EEPROMPacketIndex) = 2;

byte modMethod(TempLayer) = 0;
byte modMethod(LEDBrightness) = 0;
byte modMethod(KeyDownDelay) = 0;
byte modMethod(KeyUpDelay) = 0;
byte modMethod(SerialLoaderByteStatus) = 0;
byte modMethod(EEPROMPacketSize) = 0;
bool modMethod(IsMaster) = false;
bool modMethod(pendingEEPROMUpdate) = false;

void I2CStartup()
{
  Wire.begin();
  if (IS_MASTER)
  {
    modMethod(IsMaster) = true;
    modMethod(SetMaster)(false);
  }
}

void modMethod(SetMaster)(bool value)
{
  if (modMethod(IsMaster) == value) return;

  modMethod(IsMaster) = value;
  Wire.end();
  if (value)
  {
    Wire.begin();
  }
  else
  {
    Wire.begin(I@C_HOST_ADDRESS);
    Wire.onReceive([] (int numBytes) {modMethod(onReceive)(numBytes);});
  }
}

void I2CLoop()
{

  // do nothing
}


void I2CKeyDown(char val, byte type)
{
}

void I2CKeyUp(char val, byte type)
{

}

void I2CSerial(String input)
{
  if (input.startsWith("uniqueksetsubkey"))
  {
    input = input.substring(input.indexOf('(')+1);
    byte x = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte y = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte z = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte val = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte type = input.toInt();
    I2CSetKey(x, y, z, val, type);
    Serial.print("sub key set: ");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.print(", ");
    Serial.print(z);
    Serial.print(", ");
    Serial.print(val);
    Serial.print(", ");
    Serial.println(type);
  }
  else if (input.startsWith("uniqueksetsubeeprom"))
  {
    input = input.substring(input.indexOf('(')+1);
    int addr = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte val = input.toInt();
    I2CSetEEPROM(addr, val);
    Serial.print("Wrote to sub EEPROM: ");
    Serial.print(addr);
    Serial.print(", ");
    Serial.println(val);
  }
  else if (input.startsWith("uniqueksetsublay"))
  {
    input = input.substring(input.indexOf('(')+1);
    byte val = input.toInt();

    if (val <= (500  / (ROW * COL)))
    {
      I2CSetEEPROM(1023, val);
      Serial.print("Edited layer count to: ");
      Serial.println(val);
    }
    else
    {
      Serial.println("Layer count edit aborted, insufficient EEPROM");
    }

  }
  else if (input.startsWith("uniqueksetsubbright"))
  {
    input = input.substring(input.indexOf('(')+1);
    byte val = input.toInt();
    I2CSetLEDBrightness(val);
    Serial.println("Set sub brightness");
  }
  else if (input.startsWith("uniquekgetmods"))
  {
    Serial.print("I2C");
  }
}

void modMethod(SetTempLayer)(void)
{
  Wire.write(1);
  Wire.write(TempLayer);
}


void modMethod(SetSubLEDBrightness)(void)
{
  #ifdef LEDEXISTS
  Wire.write(4);
  Wire.write(modMethod(SetLEDBrightness)(BledPWMBrightness));
  #endif
}

void modMethod(SetSubKeyboardDelay)(void)
{
  Wire.write(5);
  Wire.write(RefreshDelay);
  Wire.write(KeyUpDelay);
}

void modMethod(onReceive)(int numBytes)
{
  modMethod(SetMaster)(true);
  Wire.beginTransmission(I2C_Guest_Address);

  // parse message
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
      ReleaseKey(keyData[i], keyType[i]);
    }
    else if (keyMode[i] == 5) // press key
    {
      if (TempLayer != modMethod(TempLayer)) // Wrong layout!
      {
        modMethod(SetTempLayer)();
        modMethod(TempLayer) = TempLayer;
        Wire.write(6);
        Wire.write(keyX[i]);
        Wire.write(keyY[i]);
      }
      else
      {
        ModPrePress(keyData[i], keyType[i]);
        PressKey(keyData[i], keyType[i]);
      }
    }
  }

  // Send updates
  if (TempLayer != modMethod(TempLayer))
  {
    modMethod(SetTempLayer)();
    modMethod(TempLayer) = TempLayer;
  }

  #ifdef LEDEXISTS
  if (BledPWMBrightness != modMethod(LEDBrightness))
  {
    modMethod(SetSubLEDBrightness)();
    modMethod(LEDBrightness) = BledPWMBrightness;
  }
  #endif

  if (RefreshDelay != modMethod(KeyDownDelay) || KeyUpDelay != modMethod(KeyUpDelay))
  {
    modMethod(SetSubKeyboardDelay);
    modMethod(KeyDownDelay) = RefreshDelay;
    modMethod(KeyUpDelay) = KeyUpDelay;
  }
  if (modMethod(pendingEEPROMUpdate)) //TODO remove this and backport compatibility mode for animus 2 comms protocol
  {
    modMethod(SetSubEEPROM)();
    modMethod(EEPROMPacketIndex) = 2;
    modMethod(SerialLoaderByteStatus) = 0;
    modMethod(pendingEEPROMUpdate) = false;
  }

  Wire.endTransmission();
  SetMaster(false);
}

void modMethod(SetSubEEPROM)(short addr, byte val)
{
  // TODO
}



#undef mod_modname
#undef modMethod
// TODO
// bool I2CDetectDevice(byte addr)
