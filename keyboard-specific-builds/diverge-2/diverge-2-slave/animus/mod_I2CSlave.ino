/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
I2C
BUILDER_REQUIREMENT_END
*/

#define mod_modname I2CSlave

#include "Wire.h"

// slave data
byte slaveCount = 1;
const byte MAX_SLAVE_COUNT = 31;
byte slaveArray[MAX_SLAVE_COUNT];

void I2CSlaveStartup()
{
  Wire.begin(8);
  IS_MASTER = false;
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void I2CSlaveLoop()
{


  if (CheckMillis())
  {
  }

}

void requestEvent()
{
  slaveArray[0] = slaveCount;
  Wire.write(slaveArray, slaveCount);
  slaveCount = 1;
}

void receiveEvent(int numBytes)
{

  byte type = Wire.read();
  if (type == 1)
  {
    byte input = Wire.read();
    TempLayer = input;
  }
  else if (type == 2)
  {
    byte x = Wire.read();
    byte y = Wire.read();
    byte z = Wire.read();
    char inputChar = Wire.read();
    byte inputType = Wire.read();
    SetEEPROM(x, y, z, inputChar, inputType);
  }
  else if (type == 3)
  {
    byte input = Wire.read();
    EEPROM.update(1023, input);
  }
  else if (type == 4)
  {
    byte val = Wire.read();
    int addr = 0;
    while (0 < Wire.available())
    {
      addr = addr + Wire.read();
    }
    EEPROM.update(addr, val);
  }
  else if (type == 5)
  {
    byte input = Wire.read();
    KeyLayer = input;
  }
  else if (type == 6)
  {
    byte input = Wire.read();
    #ifndef LEDEXISTS
    ledPWMSetBright(input);
    #endif
  }
}

/* references
1: set TempLayer
2: rebind
3: set number of layers
4: set EEPROM
5: set KeyLayer
*/

void I2CSlaveKeyDown(char val, byte type)
{
  if (slaveCount < MAX_SLAVE_COUNT)
  {
    slaveArray[slaveCount] = val;
    slaveCount++;
    slaveArray[slaveCount] = type;
    slaveCount++;
    slaveArray[slaveCount] = 5;
    slaveCount++;
  }
}

void I2CSlaveKeyUp(char val, byte type)
{
  if (slaveCount < MAX_SLAVE_COUNT)
  {
    slaveArray[slaveCount] = val;
    slaveCount++;
    slaveArray[slaveCount] = type;
    slaveCount++;
    slaveArray[slaveCount] = 1;
    slaveCount++;
  }
}

void I2CSlaveSerial(String input)
{
  if (input.startsWith("uniquekgetmods"))
  {
    Serial.print("I2CSlave");
  }
}
