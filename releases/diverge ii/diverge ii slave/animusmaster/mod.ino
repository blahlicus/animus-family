#define builder_mstartup I2CSlaveStartup();

#define builder_mloop I2CSlaveLoop();
#define builder_mloop_milis

#define builder_mkeydown I2CSlaveKeyDown(val, type);

#define builder_mkeyup I2CSlaveKeyUp(val, type);

#define builder_mserial I2CSlaveSerial(input);
void modStartup()
{
  builder_mstartup
}

void modLoop()
{
  if (checkMillis())
  {
  }
  builder_mloop
}


void modKeyDown(char val, byte type)
{
  builder_mkeydown
}

void modKeyUp(char val, byte type)
{
  builder_mkeyup
}

void modSerial(String input)
{
  if (input == "uniquekgetmods")
  {
    Serial.print("get mods(");
  }
  builder_mserial
  if (input == "uniquekgetmods")
  {
    Serial.print("\r\n");
  }
}
