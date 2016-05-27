#define builder_mstartup I2CStartup(); mediaStartup(); macroStartup();
#define builder_mloop I2CLoop(); mediaLoop(); macroLoop();
#define builder_mkeydown I2CKeyDown(val, type); mediaKeyDown(val, type); macroKeyDown(val, type);
#define builder_mkeyup I2CKeyUp(val, type); mediaKeyUp(val, type); macroKeyUp(val, type);
#define builder_mserial I2CSerial(input); mediaSerial(input); macroSerial(input);

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
