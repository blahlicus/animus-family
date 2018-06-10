#define builder_mstartup BledPWMStartup(); I2CSlaveStartup(); mediaStartup(); macroStartup(); dualRolesStartup(); tapDanceStartup(); stickyKeysStartup();
#define builder_mloop BledPWMLoop(); I2CSlaveLoop(); mediaLoop(); macroLoop(); dualRolesLoop(); tapDanceLoop(); stickyKeysLoop();
#define builder_mpresscoord BledPWMPressCoord(x, y); I2CSlavePressCoord(x, y); mediaPressCoord(x, y); macroPressCoord(x, y); dualRolesPressCoord(x, y); tapDancePressCoord(x, y); stickyKeysPressCoord(x, y);
#define builder_mprepress BledPWMPrePress(val, type); I2CSlavePrePress(val, type); mediaPrePress(val, type); macroPrePress(val, type); dualRolesPrePress(val, type); tapDancePrePress(val, type); stickyKeysPrePress(val, type);
#define builder_mkeydown BledPWMKeyDown(val, type); I2CSlaveKeyDown(val, type); mediaKeyDown(val, type); macroKeyDown(val, type); dualRolesKeyDown(val, type); tapDanceKeyDown(val, type); stickyKeysKeyDown(val, type);
#define builder_mkeyup BledPWMKeyUp(val, type); I2CSlaveKeyUp(val, type); mediaKeyUp(val, type); macroKeyUp(val, type); dualRolesKeyUp(val, type); tapDanceKeyUp(val, type); stickyKeysKeyUp(val, type);
#define builder_mserial BledPWMSerial(input); I2CSlaveSerial(input); mediaSerial(input); macroSerial(input); dualRolesSerial(input); tapDanceSerial(input); stickyKeysSerial(input);

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
