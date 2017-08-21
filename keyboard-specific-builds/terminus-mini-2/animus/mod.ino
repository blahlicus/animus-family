#define builder_mstartup BledPWMStartup(); dualRolesStartup(); macroStartup(); mediaStartup(); stickyKeysStartup(); tapDanceStartup(); mouseKeysStartup();
#define builder_mloop BledPWMLoop(); dualRolesLoop(); macroLoop(); mediaLoop(); stickyKeysLoop(); tapDanceLoop(); mouseKeysLoop();
#define builder_mkeydown BledPWMKeyDown(val, type); dualRolesKeyDown(val, type); macroKeyDown(val, type); mediaKeyDown(val, type); stickyKeysKeyDown(val, type); tapDanceKeyDown(val, type); mouseKeysKeyDown(val, type);
#define builder_mkeyup BledPWMKeyUp(val, type); dualRolesKeyUp(val, type); macroKeyUp(val, type); mediaKeyUp(val, type); stickyKeysKeyUp(val, type); tapDanceKeyUp(val, type); mouseKeysKeyUp(val, type);
#define builder_mserial BledPWMSerial(input); dualRolesSerial(input); macroSerial(input); mediaSerial(input); stickyKeysSerial(input); tapDanceSerial(input); mouseKeysSerial(input);

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
