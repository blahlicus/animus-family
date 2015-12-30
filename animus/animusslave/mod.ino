void modStartup()
{
  I2CStartup();
}

void modLoop()
{
  if (checkMillis())
  {
  }
  I2CLoop();
}


void modKeyDown(char val, byte type)
{
  I2CKeyDown(val, type);
}

void modKeyUp(char val, byte type)
{
  I2CKeyUp(val, type);
}

void modSerial(String input)
{
  I2CSerial(input);
}
