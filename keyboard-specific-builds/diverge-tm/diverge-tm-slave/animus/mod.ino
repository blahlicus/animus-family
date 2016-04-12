#define builder_mstartup I2CSlaveStartup(); mediaStartup();
#define builder_mloop I2CSlaveLoop(); mediaLoop();
#define builder_mkeydown I2CSlaveKeyDown(val, type); mediaKeyDown(val, type);
#define builder_mkeyup I2CSlaveKeyUp(val, type); mediaKeyUp(val, type);
#define builder_mserial I2CSlaveSerial(input); mediaSerial(input);

void ModStartup()
{
  builder_mstartup
}

void ModLoop()
{
  if (CheckMillis())
  {
  }
  builder_mloop
}


void ModKeyDown(char val, byte type)
{
  builder_mkeydown
}

void ModKeyUp(char val, byte type)
{
  builder_mkeyup
}

void ModSerial(String input)
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
