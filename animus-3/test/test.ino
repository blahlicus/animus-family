#include "EEPROM.h"
void setup()
{
  Serial.begin(19200);
  delay(20000);


  for (int i = 0; i < 1024; i++)
  {
    Serial.print(EEPROM.read(i));
    Serial.println();
  }
}

void loop()
{
  /*
  byte arr[64];
  for (byte i = 0; i < 16)
  {
    for (byte j = 0; j < 64)
    {
      arr[j] = EEPROM.read(i*64+j);
    }
    Serial.println(arr);
  }
  */


}
