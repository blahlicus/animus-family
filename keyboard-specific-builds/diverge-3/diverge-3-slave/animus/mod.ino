#define builder_mstartup BledPWMStartup(); I2CSlaveStartup(); dualRolesStartup(); mediaStartup(); macroStartup(); stickyKeysStartup(); tapDanceStartup(); mouseKeysStartup(); shiftedStartup();
#define builder_mloop BledPWMLoop(); I2CSlaveLoop(); dualRolesLoop(); mediaLoop(); macroLoop(); stickyKeysLoop(); tapDanceLoop(); mouseKeysLoop(); shiftedLoop();
#define builder_mpresscoord BledPWMPressCoord(x, y); I2CSlavePressCoord(x, y); dualRolesPressCoord(x, y); mediaPressCoord(x, y); macroPressCoord(x, y); stickyKeysPressCoord(x, y); tapDancePressCoord(x, y); mouseKeysPressCoord(x, y); shiftedPressCoord(x, y);
#define builder_mprepress BledPWMPrePress(val, type); I2CSlavePrePress(val, type); dualRolesPrePress(val, type); mediaPrePress(val, type); macroPrePress(val, type); stickyKeysPrePress(val, type); tapDancePrePress(val, type); mouseKeysPrePress(val, type); shiftedPrePress(val, type);
#define builder_mkeydown BledPWMKeyDown(val, type); I2CSlaveKeyDown(val, type); dualRolesKeyDown(val, type); mediaKeyDown(val, type); macroKeyDown(val, type); stickyKeysKeyDown(val, type); tapDanceKeyDown(val, type); mouseKeysKeyDown(val, type); shiftedKeyDown(val, type);
#define builder_mkeyup BledPWMKeyUp(val, type); I2CSlaveKeyUp(val, type); dualRolesKeyUp(val, type); mediaKeyUp(val, type); macroKeyUp(val, type); stickyKeysKeyUp(val, type); tapDanceKeyUp(val, type); mouseKeysKeyUp(val, type); shiftedKeyUp(val, type);
#define builder_mserial BledPWMSerial(input); I2CSlaveSerial(input); dualRolesSerial(input); mediaSerial(input); macroSerial(input); stickyKeysSerial(input); tapDanceSerial(input); mouseKeysSerial(input); shiftedSerial(input);

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
