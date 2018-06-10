#define builder_mstartup macroStartup(); mediaStartup(); dualRolesStartup(); tapDanceStartup(); mouseKeysStartup(); stickyKeysStartup();
#define builder_mloop macroLoop(); mediaLoop(); dualRolesLoop(); tapDanceLoop(); mouseKeysLoop(); stickyKeysLoop();
#define builder_mkeydown macroKeyDown(val, type); mediaKeyDown(val, type); dualRolesKeyDown(val, type); tapDanceKeyDown(val, type); mouseKeysKeyDown(val, type); stickyKeysKeyDown(val, type);
#define builder_mkeyup macroKeyUp(val, type); mediaKeyUp(val, type); dualRolesKeyUp(val, type); tapDanceKeyUp(val, type); mouseKeysKeyUp(val, type); stickyKeysKeyUp(val, type);
#define builder_mserial macroSerial(input); mediaSerial(input); dualRolesSerial(input); tapDanceSerial(input); mouseKeysSerial(input); stickyKeysSerial(input);

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
