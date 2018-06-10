#define builder_mstartup mediaStartup(); macroStartup(); dualRolesStartup(); tapDanceStartup(); stickyKeysStartup(); mouseKeysStartup();
#define builder_mloop mediaLoop(); macroLoop(); dualRolesLoop(); tapDanceLoop(); stickyKeysLoop(); mouseKeysLoop();
#define builder_mpresscoord mediaPressCoord(x, y); macroPressCoord(x, y); dualRolesPressCoord(x, y); tapDancePressCoord(x, y); stickyKeysPressCoord(x, y); mouseKeysPressCoord(x, y);
#define builder_mprepress mediaPrePress(val, type); macroPrePress(val, type); dualRolesPrePress(val, type); tapDancePrePress(val, type); stickyKeysPrePress(val, type); mouseKeysPrePress(val, type);
#define builder_mkeydown mediaKeyDown(val, type); macroKeyDown(val, type); dualRolesKeyDown(val, type); tapDanceKeyDown(val, type); stickyKeysKeyDown(val, type); mouseKeysKeyDown(val, type);
#define builder_mkeyup mediaKeyUp(val, type); macroKeyUp(val, type); dualRolesKeyUp(val, type); tapDanceKeyUp(val, type); stickyKeysKeyUp(val, type); mouseKeysKeyUp(val, type);
#define builder_mserial mediaSerial(input); macroSerial(input); dualRolesSerial(input); tapDanceSerial(input); stickyKeysSerial(input); mouseKeysSerial(input);

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
