#include "Comms.h"

CSerial::CSerial(void)
{

}

void CSerial::Begin(int baud)
{
  mode = 0;
  Serial.begin(baud);
  delay(300);
}

void CSerial::Loop(void)
{
  if (mode == 0) // mode 0 is standby mode which waits for another mode input
  {
    if (Serial.available()>0)
    {
      byte keyByte = Serial.read(); // read byte, if useless, then discard it, helps clear the buffer
      if (keyMode == 0) // keyMode is at default mode
      {
        if (keyByte == COMM_KEY_0) // first key check passed
        {
          keyMode = 1;
        }
      }
      else if (keyMode == 1) // keyMode is at second key check
      {
        if (keyByte == COMM_KEY_1) // second key check passed
        {
          keyMode = 2;
        }
        else
        {
          keyMode = 0; // resets keyMode to 0 if key is incorrect
        }
      }
      else if (keyMode == 2) // keyMode is at third key check
      {
        if (keyByte == COMM_KEY_2) // third key check passed
        {
          keyMode = 3;
        }
        else
        {
          keyMode = 0; // resets keyMode to 0 if key is incorrect
        }
      }
      else if (keyMode == 3) // keyMode is at fourth key check
      {
        if (keyByte == COMM_KEY_3) // fourth key check passed
        {
          keyMode = 4;
        }
        else
        {
          keyMode = 0; // resets keyMode to 0 if second key is incorrect
        }
      }
      else if (keyMode == 4) // all key checks passed, setting mode
      {
        mode = keyByte;
        keyMode = 0;
      }
    }
  }

  if (mode == 1) // load bytes to eeprom, do not use this, use modes 4 or 5 instead to load layout or board data
  {
    if (Serial.available()>0)
    {
      PersMem.SetEEPROM(loadCounter, (byte)Serial.read());
      loadCounter++;
    }
    if (loadCounter >= 1024)
    {
      PersMem.LoadData();
      loadCounter = 0;
      mode = 0;
    }
  }
  else if (mode == 2) // received RTS to send entire EEPROM
  {
    for (short i = 0; i < 1024; i++)
    {
      Serial.write(PersMem.GetEEPROM(i));
    }
    mode = 0;
  }
  else if (mode == 3) // print mod list in order of mem id
  {
    // reserved for mod.cpp
  }
  else if (mode == 4) // load 900 bytes to 0-899 EEPROM for layout and mod data
  {

    if (Serial.available()>0) //TODO I might want to work in a timeout or fail check for this
    {
      PersMem.SetEEPROM(loadCounter, (byte)Serial.read());
      loadCounter++;
    }
    if (loadCounter >= 900)
    {
      mode = 0;
      loadCounter = 0;
    }
  }
  else if (mode == 5) // load 124 bytes to 900-1023 EEPROM for board data
  {

    if (Serial.available()>0) //TODO I might want to work in a timeout or fail check for this
    {
      PersMem.SetEEPROM(loadCounter+900, (byte)Serial.read());
      loadCounter++;
    }
    if (loadCounter+900 >= 1024)
    {
      PersMem.LoadData();
      loadCounter = 0;
      mode = 0;
    }
  }
  else if (mode == 6) // reserved for i2i2chost
  {
    // do nothing
  }
  else if (mode == 7) // update basic info
  {

    if (Serial.available()>0)
    {
      PersMem.SetEEPROM(MEM_LAY_COUNT, (byte)Serial.read());
    }
    if (Serial.available()>0)
    {
      PersMem.SetEEPROM(MEM_NKRO_MODE, (byte)Serial.read());
    }
    if (Serial.available()>0)
    {
      PersMem.SetEEPROM(MEM_IS_USBHOST, (byte)Serial.read());
    }
    if (Serial.available()>0)
    {
      PersMem.SetEEPROM(MEM_REFRESH_RATE, (byte)Serial.read());
    }
  }
  else if (mode == 255) // idle mode
  {

  }
}


void CSerial::End(void)
{

}

CSerial Comms;
