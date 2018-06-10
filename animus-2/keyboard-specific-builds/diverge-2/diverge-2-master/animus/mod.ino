#define builder_mstartup I2CStartup(); mediaStartup(); macroStartup(); dualRolesStartup(); tapDanceStartup(); mouseKeysStartup(); stickyKeysStartup();
#define builder_mloop I2CLoop(); mediaLoop(); macroLoop(); dualRolesLoop(); tapDanceLoop(); mouseKeysLoop(); stickyKeysLoop();
#define builder_mkeydown I2CKeyDown(val, type); mediaKeyDown(val, type); macroKeyDown(val, type); dualRolesKeyDown(val, type); tapDanceKeyDown(val, type); mouseKeysKeyDown(val, type); stickyKeysKeyDown(val, type);
#define builder_mkeyup I2CKeyUp(val, type); mediaKeyUp(val, type); macroKeyUp(val, type); dualRolesKeyUp(val, type); tapDanceKeyUp(val, type); mouseKeysKeyUp(val, type); stickyKeysKeyUp(val, type);
#define builder_mserial I2CSerial(input); mediaSerial(input); macroSerial(input); dualRolesSerial(input); tapDanceSerial(input); mouseKeysSerial(input); stickyKeysSerial(input);

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
