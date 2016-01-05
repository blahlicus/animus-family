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
    if (tempLayer != I2CLayer)
    {
      I2CSelectLayer(tempLayer);
      I2CLayer = tempLayer;
    }


    byte slaveArray[31];
    byte slaveCount = 0;
    boolean slaveExists = false;
    Wire.requestFrom(8, 31);    // request 6 bytes from slave device #8
    while (Wire.available())
    { // slave may send less than requested
      byte out = Wire.read(); // receive a byte as character
      slaveArray[slaveCount] = out;
      slaveExists = true;
      slaveCount++;
    }
    if (slaveExists)
    {
      slaveCount = slaveArray[0];
      for (int i = 1; i < slaveCount; i=i+3)
      {
        char cinput = slaveArray[i];
        byte tinput = slaveArray[i+1];
        if (slaveArray[i+2]>1)
        {
          pressKey(cinput, tinput);
        }
        else
        {
          releaseKey(cinput, tinput);
        }
      }
    }

  }

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
  else if (input.startsWith("uniquekgetmods"))
  {
    Serial.print("I2C");
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
  byte type = 2;
  Wire.beginTransmission(8);
  Wire.write(type);
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



// TODO
// bool I2CDetectDevice(byte addr)
