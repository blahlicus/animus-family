#include "Wire.h"

void I2CStartup()
{
  Wire.begin();
}

void I2CLoop()
{

  /* references
  1: layer
  2: rebind
  3: set layer*/

}


void I2CSelectLayer(int input)
{
  Wire.beginTransmission(8);
  Wire.write(1);
  Wire.write(input);
  Wire.endTransmission();
}


void I2CSetKey(int x, int y, int z, char inputChar, byte inputType)
{
  Wire.beginTransmission(8);
  Wire.write(2);
  Wire.write(x);
  Wire.write(y);
  Wire.write(z);
  Wire.write(inputChar);
  Wire.write(inputType);
  Wire.endTransmission();
}

void I2CSetLayer(int input)
{
  Wire.beginTransmission(8);
  Wire.write(3);
  Wire.write(input);
  Wire.endTransmission();
}


void I2CKeyDown(char val, byte type)
{

}

void I2CKeyUp(char val, byte type)
{

}
