#include "EEPROM.h"
void setup()
{
  Serial.begin(19200);
  delay(300);


}
int counter = 0;
void loop()
{
  if (Serial.available()>0)
  {
    EEPROM.update(counter, (byte)Serial.read());
    counter++;
  }

}
