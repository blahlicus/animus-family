#include "Wire.h"

void I2CStartup()
{
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void I2CLoop()
{


  if (checkMillis())
  {
  }

}

void requestEvent()
{
  if (slaveCount>0)
  {
    Wire.write(1);
    Wire.write(slaveArray, slaveCount);
  }
}

void receiveEvent(int numBytes)
{
  byte type = Wire.read();
  if (type == 1)
  {
    byte input = Wire.read();
    tempLayer = input;
  }
  else if (type == 2)
  {
    byte x = Wire.read();
    byte y = Wire.read();
    byte z = Wire.read();
    char inputChar = Wire.read();
    byte inputType = Wire.read();
  }
  else if (type == 3)
  {
    byte input = Wire.read();
    EEPROM.write(1023, input);
  }
  else if (type == 4)
  {
    byte val = Wire.read();
    int addr = 0;
    while (0 < Wire.available())
    {
      addr = addr + Wire.read();
    }
    EEPROM.write(addr, val);
  }
}

/* references
1: layer
2: rebind
3: set layer
4: set EEPROM
*/

void I2CKeyDown(char val, byte type)
{

}

void I2CKeyUp(char val, byte type)
{

}

void I2CSerial(String input)
{

}
