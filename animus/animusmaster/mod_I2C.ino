#include "Wire.h"

int I2CLayer = 0;

void I2CStartup()
{
  Wire.begin();
}

void I2CLoop()
{


  if (checkMillis())
  {
    Wire.requestFrom(8, 31);
    {
      while(Wire.available())
      {
        char cinput = Wire.read();
        byte binput = Wire.read();
        bool down = Wire.read();
        if (down)
        {
          pressKey(cinput, binput);
        }
        else
        {
          releaseKey(cinput, binput);
        }
      }
    }

    if (tempLayer != I2CLayer)
    {
      I2CLayer = tempLayer;
      I2CSelectLayer(tempLayer);
    }
  }

}

/* references
1: layer
2: rebind
3: set layer
4: set EEPROM
*/

void I2CSelectLayer(byte input)
{
  Wire.beginTransmission(8);
  Wire.write(1);
  Wire.write(input);
  Wire.endTransmission();
}


void I2CSetKey(byte x, byte y, byte z, char inputChar, byte inputType)
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

void I2CSetLayer(byte input)
{
  Wire.beginTransmission(8);
  Wire.write(3);
  Wire.write(input);
  Wire.endTransmission();
}

void I2CSetEEPROM(int addr, byte val)
{

  Wire.beginTransmission(8);
  Wire.write(4);
  Wire.write(val);
  while (addr >255)
  {
    Wire.write(255);
    addr = addr - 255;
  }
  Wire.write(addr);
  Wire.endTransmission();
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
    EEPROM.write(addr, val);
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
}
