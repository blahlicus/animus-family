#define builder_mstartup BledPWMStartup(); I2CStartup(); mediaStartup(); macroStartup(); dualRolesStartup(); tapDanceStartup(); mouseKeysStartup(); stickyKeysStartup(); shiftedStartup();
#define builder_mloop BledPWMLoop(); I2CLoop(); mediaLoop(); macroLoop(); dualRolesLoop(); tapDanceLoop(); mouseKeysLoop(); stickyKeysLoop(); shiftedLoop();
#define builder_mpresscoord BledPWMPressCoord(x, y); I2CPressCoord(x, y); mediaPressCoord(x, y); macroPressCoord(x, y); dualRolesPressCoord(x, y); tapDancePressCoord(x, y); mouseKeysPressCoord(x, y); stickyKeysPressCoord(x, y); shiftedPressCoord(x, y);
#define builder_mprepress BledPWMPrePress(val, type); I2CPrePress(val, type); mediaPrePress(val, type); macroPrePress(val, type); dualRolesPrePress(val, type); tapDancePrePress(val, type); mouseKeysPrePress(val, type); stickyKeysPrePress(val, type); shiftedPrePress(val, type);
#define builder_mkeydown BledPWMKeyDown(val, type); I2CKeyDown(val, type); mediaKeyDown(val, type); macroKeyDown(val, type); dualRolesKeyDown(val, type); tapDanceKeyDown(val, type); mouseKeysKeyDown(val, type); stickyKeysKeyDown(val, type); shiftedKeyDown(val, type);
#define builder_mkeyup BledPWMKeyUp(val, type); I2CKeyUp(val, type); mediaKeyUp(val, type); macroKeyUp(val, type); dualRolesKeyUp(val, type); tapDanceKeyUp(val, type); mouseKeysKeyUp(val, type); stickyKeysKeyUp(val, type); shiftedKeyUp(val, type);
#define builder_mserial BledPWMSerial(input); I2CSerial(input); mediaSerial(input); macroSerial(input); dualRolesSerial(input); tapDanceSerial(input); mouseKeysSerial(input); stickyKeysSerial(input); shiftedSerial(input);

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
