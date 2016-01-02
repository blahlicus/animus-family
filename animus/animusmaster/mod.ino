void modStartup()
{
  I2CStartup();
  mediaStartup();
}

void modLoop()
{
  if (checkMillis())
  {
  }
  I2CLoop();
  mediaLoop();
}


void modKeyDown(char val, byte type)
{
  I2CKeyDown(val, type);
  mediaKeyDown(val, type);
}

void modKeyUp(char val, byte type)
{
  I2CKeyUp(val, type);
  mediaKeyUp(val, type);
}

void modSerial(String input)
{
  if (input == "uniquekgetmods")
  {
    Serial.print("get mods(");
  }
  I2CSerial(input);
  mediaSerial(input);
  if (input == "uniquekgetmods")
  {
    Serial.print("\r\n");
  }
}
