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
  if (mode == 0)
  {
    if (Serial.available()>5) // this will keep clearing the serial buffer once it reaches size 5
    {
      byte arr[4];
      arr[0] = Serial.read();
      arr[1] = Serial.read();
      arr[2] = Serial.read();
      arr[3] = Serial.read();
      if (arr[0] == COMM_KEY_0 && arr[1] == COMM_KEY_1 && arr[2] == COMM_KEY_2 && arr[3] == COMM_KEY_3)
      {
        mode = Serial.read();
      }
    }
  }

  if (mode == 1) // load bytes to eeprom, do not use this, use modes 4 or 5 instead to load layout or board data
  {
    loadCounter = 0;
    if (Serial.available()>0) //TODO I might want to work in a timeout or fail check for this
    {
       EEPROM.update(loadCounter, (byte)Serial.read());
       loadCounter++;
    }
    if (loadCounter == 1024)
    {
      mode = 0;
    }
  }
  else if (mode == 2) // received RTS to send entire EEPROM
  {
    for (short i = 0; i < 1024; i++)
    {
      Serial.write(EEPROM.read(i));
    }
  }
  else if (mode == 3) // print mod list in order of mem id
  {
    Serial.print(Mod.PrintMods());
  }
  else if (mode == 4) // load 900 bytes to 0-899 EEPROM for layout and mod data
  {

      loadCounter = 0;
      if (Serial.available()>0) //TODO I might want to work in a timeout or fail check for this
      {
         EEPROM.update(loadCounter, (byte)Serial.read());
         loadCounter++;
      }
      if (loadCounter == 900)
      {
        mode = 0;
      }
  }
  else if (mode == 5) // load 124 bytes to 900-1023 EEPROM for board data
  {

      loadCounter = 900;
      if (Serial.available()>0) //TODO I might want to work in a timeout or fail check for this
      {
         EEPROM.update(loadCounter, (byte)Serial.read());
         loadCounter++;
      }
      if (loadCounter == 1024)
      {
        mode = 0;
      }
  }
}


void CSerial::End(void)
{

}

CSerial Comms;
