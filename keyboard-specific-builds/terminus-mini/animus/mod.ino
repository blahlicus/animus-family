#define builder_mstartup mediaStartup(); macroStartup(); dualRolesStartup(); tapDanceStartup();
#define builder_mloop mediaLoop(); macroLoop(); dualRolesLoop(); tapDanceLoop();
#define builder_mkeydown mediaKeyDown(val, type); macroKeyDown(val, type); dualRolesKeyDown(val, type); tapDanceKeyDown(val, type);
#define builder_mkeyup mediaKeyUp(val, type); macroKeyUp(val, type); dualRolesKeyUp(val, type); tapDanceKeyUp(val, type);
#define builder_mserial mediaSerial(input); macroSerial(input); dualRolesSerial(input); tapDanceSerial(input);

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
