#include "Comms.h"

CSerial::CSerial(void)
{

}

void CSerial::Begin(int baud)
{
  mode = 0;
  preloadCounter = 0;
  Serial.begin(baud);
  delay(300);
}

void CSerial::Loop(void)
{
  if (mode == 0) // mode 0 is standby mode which waits for another mode input
  {
    if (Serial.available()>0) //TODO if the key is incorrrect then the port is forever jammed
    {
      buffer[preloadCounter] = Serial.read();
      preloadCounter++;
      if (preloadCounter >=5)
      {
        if (buffer[0] == COMM_KEY_0 && buffer[1] == COMM_KEY_1 && buffer[2] == COMM_KEY_2 && buffer[3] == COMM_KEY_3)
        {
          mode = buffer[4];

          loadCounter = 0;
        }
        preloadCounter = 0;
      }
    }
  }

  if (mode == 1) // load bytes to eeprom, do not use this, use modes 4 or 5 instead to load layout or board data
  {
    if (Serial.available()>0) //TODO I might want to work in a timeout or fail check for this
    {
      EEPROM.update(loadCounter, (byte)Serial.read());
      loadCounter++;
    }
    if (loadCounter >= 1024)
    {
      PersMem.LoadData();
      mode = 0;
    }
  }
  else if (mode == 2) // received RTS to send entire EEPROM
  {
    for (short i = 0; i < 1024; i++)
    {
      Serial.write(EEPROM.read(i));
    }
    mode = 0;
  }
  else if (mode == 3) // print mod list in order of mem id
  {
    // reserved for mod.cpp
    mode = 0;

  }
  else if (mode == 4) // load 900 bytes to 0-899 EEPROM for layout and mod data
  {

    if (Serial.available()>0) //TODO I might want to work in a timeout or fail check for this
    {
      EEPROM.update(loadCounter, (byte)Serial.read());
      loadCounter++;
    }
    if (loadCounter >= 900)
    {
      mode = 0;
    }
  }
  else if (mode == 5) // load 124 bytes to 900-1023 EEPROM for board data
  {

    if (Serial.available()>0) //TODO I might want to work in a timeout or fail check for this
    {
      EEPROM.update(loadCounter+900, (byte)Serial.read());
      loadCounter++;
    }
    if (loadCounter+900 >= 1024)
    {
      PersMem.LoadData();
      mode = 0;
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
