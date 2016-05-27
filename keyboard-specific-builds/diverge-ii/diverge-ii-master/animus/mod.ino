#define builder_mstartup I2CStartup(); mediaStartup(); macroStartup(); dualRolesStartup();
#define builder_mloop I2CLoop(); mediaLoop(); macroLoop(); dualRolesLoop();
#define builder_mkeydown I2CKeyDown(val, type); mediaKeyDown(val, type); macroKeyDown(val, type); dualRolesKeyDown(val, type);
#define builder_mkeyup I2CKeyUp(val, type); mediaKeyUp(val, type); macroKeyUp(val, type); dualRolesKeyUp(val, type);
#define builder_mserial I2CSerial(input); mediaSerial(input); macroSerial(input); dualRolesSerial(input);

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
