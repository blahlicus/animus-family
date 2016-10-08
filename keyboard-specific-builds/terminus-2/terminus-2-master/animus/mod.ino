#define builder_mstartup BledPWMStartup(); dualRolesStartup(); I2CStartup(); macroStartup(); mediaStartup();
#define builder_mloop BledPWMLoop(); dualRolesLoop(); I2CLoop(); macroLoop(); mediaLoop();
#define builder_mkeydown BledPWMKeyDown(val, type); dualRolesKeyDown(val, type); I2CKeyDown(val, type); macroKeyDown(val, type); mediaKeyDown(val, type);
#define builder_mkeyup BledPWMKeyUp(val, type); dualRolesKeyUp(val, type); I2CKeyUp(val, type); macroKeyUp(val, type); mediaKeyUp(val, type);
#define builder_mserial BledPWMSerial(input); dualRolesSerial(input); I2CSerial(input); macroSerial(input); mediaSerial(input);

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
