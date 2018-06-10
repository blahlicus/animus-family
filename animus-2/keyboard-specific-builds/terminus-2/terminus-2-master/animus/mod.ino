#define builder_mstartup BledPWMStartup(); dualRolesStartup(); I2CStartup(); macroStartup(); mediaStartup(); tapDanceStartup(); stickyKeysStartup(); mouseKeysStartup();
#define builder_mloop BledPWMLoop(); dualRolesLoop(); I2CLoop(); macroLoop(); mediaLoop(); tapDanceLoop(); stickyKeysLoop(); mouseKeysLoop();
#define builder_mpresscoord BledPWMPressCoord(x, y); dualRolesPressCoord(x, y); I2CPressCoord(x, y); macroPressCoord(x, y); mediaPressCoord(x, y); tapDancePressCoord(x, y); stickyKeysPressCoord(x, y); mouseKeysPressCoord(x, y);
#define builder_mprepress BledPWMPrePress(val, type); dualRolesPrePress(val, type); I2CPrePress(val, type); macroPrePress(val, type); mediaPrePress(val, type); tapDancePrePress(val, type); stickyKeysPrePress(val, type); mouseKeysPrePress(val, type);
#define builder_mkeydown BledPWMKeyDown(val, type); dualRolesKeyDown(val, type); I2CKeyDown(val, type); macroKeyDown(val, type); mediaKeyDown(val, type); tapDanceKeyDown(val, type); stickyKeysKeyDown(val, type); mouseKeysKeyDown(val, type);
#define builder_mkeyup BledPWMKeyUp(val, type); dualRolesKeyUp(val, type); I2CKeyUp(val, type); macroKeyUp(val, type); mediaKeyUp(val, type); tapDanceKeyUp(val, type); stickyKeysKeyUp(val, type); mouseKeysKeyUp(val, type);
#define builder_mserial BledPWMSerial(input); dualRolesSerial(input); I2CSerial(input); macroSerial(input); mediaSerial(input); tapDanceSerial(input); stickyKeysSerial(input); mouseKeysSerial(input);

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


void ModPressCoord(byte x, byte y)
{
  builder_mpresscoord
}

void ModPrePress(char val, byte type)
{
  builder_mprepress
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
