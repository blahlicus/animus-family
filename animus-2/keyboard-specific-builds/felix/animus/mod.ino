#define builder_mstartup mediaStartup(); macroStartup(); stickyKeysStartup(); BledPWMStartup(); dualRolesStartup(); tapDanceStartup(); mouseKeysStartup(); shiftedStartup();
#define builder_mloop mediaLoop(); macroLoop(); stickyKeysLoop(); BledPWMLoop(); dualRolesLoop(); tapDanceLoop(); mouseKeysLoop(); shiftedLoop();
#define builder_mpresscoord mediaPressCoord(x, y); macroPressCoord(x, y); stickyKeysPressCoord(x, y); BledPWMPressCoord(x, y); dualRolesPressCoord(x, y); tapDancePressCoord(x, y); mouseKeysPressCoord(x, y); shiftedPressCoord(x, y);
#define builder_mprepress mediaPrePress(val, type); macroPrePress(val, type); stickyKeysPrePress(val, type); BledPWMPrePress(val, type); dualRolesPrePress(val, type); tapDancePrePress(val, type); mouseKeysPrePress(val, type); shiftedPrePress(val, type);
#define builder_mkeydown mediaKeyDown(val, type); macroKeyDown(val, type); stickyKeysKeyDown(val, type); BledPWMKeyDown(val, type); dualRolesKeyDown(val, type); tapDanceKeyDown(val, type); mouseKeysKeyDown(val, type); shiftedKeyDown(val, type);
#define builder_mkeyup mediaKeyUp(val, type); macroKeyUp(val, type); stickyKeysKeyUp(val, type); BledPWMKeyUp(val, type); dualRolesKeyUp(val, type); tapDanceKeyUp(val, type); mouseKeysKeyUp(val, type); shiftedKeyUp(val, type);
#define builder_mserial mediaSerial(input); macroSerial(input); stickyKeysSerial(input); BledPWMSerial(input); dualRolesSerial(input); tapDanceSerial(input); mouseKeysSerial(input); shiftedSerial(input);

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
