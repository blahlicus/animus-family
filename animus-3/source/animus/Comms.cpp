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

  if (mode == 1) // load bytes to eeprom until end of EEPROM reached
  {
    if (Serial.available()>0)
    {
      PersMem.SetEEPROM(loadCounter, (byte)Serial.read());
      loadCounter++;
    }
    if (loadCounter >= MEM_EEPROM_SIZE)
    {
      PersMem.CommitEEPROM();
      PersMem.LoadData();
      loadCounter = 0;
      mode = 0;
    }
  }
  else if (mode == 2) // entire EEPROM data to serial
  {
    for (short i = 0; i < MEM_EEPROM_SIZE; i++)
    {
      Serial.write(PersMem.GetEEPROM(i));
    }
    mode = 0;
  }
  else if (mode == 3) // print mod list in order of mem id to serial
  {
    // reserved for mod.cpp
  }
  else if (mode == 4) // load MEM_BOARD_TYPE bytes to 0-MEM_BOARD_TYPE EEPROM for layout and mod data
  {

    if (Serial.available()>0) //TODO I might want to work in a timeout or fail check for this
    {
      PersMem.SetEEPROM(loadCounter, (byte)Serial.read());
      loadCounter++;
    }
    if (loadCounter >= MEM_BOARD_TYPE)
    {
      PersMem.CommitEEPROM();
      mode = 0;
      loadCounter = 0;
    }
  }
  else if (mode == 5) // load 124 bytes to MEM_BOARD_TYPE-MEM_EEPROM_SIZE EEPROM for board data
  {

    if (Serial.available()>0) //TODO I might want to work in a timeout or fail check for this
    {
      PersMem.SetEEPROM(loadCounter+MEM_BOARD_TYPE, (byte)Serial.read());
      loadCounter++;
    }
    if (loadCounter+MEM_BOARD_TYPE >= MEM_EEPROM_SIZE)
    {
      PersMem.CommitEEPROM();
      PersMem.LoadData();
      loadCounter = 0;
      mode = 0;
    }
  }
  else if (mode == 6) // reserved for i2chost for sending data to the slave
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
    PersMem.CommitEEPROM();
  }
  else if (mode == 8) // upload from STARTBYTE with LENGTH
  {
    //TODO test this code
    if (Serial.available()>0) //TODO I might want to work in a timeout or fail check for this
    {
      if (startAddress == -2) // mode 8 has not started yet
      {
        startByte = (byte)Serial.read(); // get first byte
        startAddress = -1;
      }
      else if (startAddress == -1) // mode 8 received first byte
      {
        byte startByteB = (byte)Serial.read(); // get second byte
        startAddress =(startByte << 8) | startByteB; // calculate 16 bit data
      }
      else // mode 8 obtained starting address (16 bit data)
      {
        if (inputLength == -2) // mode 8 has obtained length
        {
          startByte = (byte)Serial.read(); // get first byte
          inputLength = -1;
        }
        else if (inputLength == -1) // mode 8 received first byte
        {
          byte inputByteB = (byte)Serial.read(); // get second byte
          inputLength =(startByte << 8) | inputByteB; // calculate 16 bit data
        }
        else // start address and length obtained
        {
          // write to EEPROM
          PersMem.SetEEPROM(loadCounter, (byte)Serial.read());
          loadCounter++;

          if (loadCounter >= inputLength)
          {
            PersMem.CommitEEPROM();
            mode = 0;
            loadCounter = 0;
            startAddress = -2;
            inputLength = -2;
          }
        }
      }
    }
  }
  else if (mode == 9) // reverse upload mode for mod data
  {
    //TODO get this done for mod data
  }
  else if (mode == 255) // idle mode
  {

  }
}


void CSerial::End(void)
{

}

CSerial Comms;
