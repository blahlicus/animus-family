#define builder_mstartup macroStartup(); mediaStartup(); dualRolesStartup();
#define builder_mloop macroLoop(); mediaLoop(); dualRolesLoop();
#define builder_mkeydown macroKeyDown(val, type); mediaKeyDown(val, type); dualRolesKeyDown(val, type);
#define builder_mkeyup macroKeyUp(val, type); mediaKeyUp(val, type); dualRolesKeyUp(val, type);
#define builder_mserial macroSerial(input); mediaSerial(input); dualRolesSerial(input);

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
