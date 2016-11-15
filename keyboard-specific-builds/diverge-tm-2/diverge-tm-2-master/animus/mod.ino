#define builder_mstartup BledPWMStartup(); I2CStartup(); mediaStartup(); macroStartup(); dualRolesStartup(); tapDanceStartup(); stickyKeysStartup();
#define builder_mloop BledPWMLoop(); I2CLoop(); mediaLoop(); macroLoop(); dualRolesLoop(); tapDanceLoop(); stickyKeysLoop();
#define builder_mkeydown BledPWMKeyDown(val, type); I2CKeyDown(val, type); mediaKeyDown(val, type); macroKeyDown(val, type); dualRolesKeyDown(val, type); tapDanceKeyDown(val, type); stickyKeysKeyDown(val, type);
#define builder_mkeyup BledPWMKeyUp(val, type); I2CKeyUp(val, type); mediaKeyUp(val, type); macroKeyUp(val, type); dualRolesKeyUp(val, type); tapDanceKeyUp(val, type); stickyKeysKeyUp(val, type);
#define builder_mserial BledPWMSerial(input); I2CSerial(input); mediaSerial(input); macroSerial(input); dualRolesSerial(input); tapDanceSerial(input); stickyKeysSerial(input);

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
