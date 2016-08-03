#define builder_mstartup I2CSlaveStartup(); dualRolesStartup(); ledPWMStartup(); mediaStartup(); macroStartup(); stickyKeysStartup();
#define builder_mloop I2CSlaveLoop(); dualRolesLoop(); ledPWMLoop(); mediaLoop(); macroLoop(); stickyKeysLoop();
#define builder_mkeydown I2CSlaveKeyDown(val, type); dualRolesKeyDown(val, type); ledPWMKeyDown(val, type); mediaKeyDown(val, type); macroKeyDown(val, type); stickyKeysKeyDown(val, type);
#define builder_mkeyup I2CSlaveKeyUp(val, type); dualRolesKeyUp(val, type); ledPWMKeyUp(val, type); mediaKeyUp(val, type); macroKeyUp(val, type); stickyKeysKeyUp(val, type);
#define builder_mserial I2CSlaveSerial(input); dualRolesSerial(input); ledPWMSerial(input); mediaSerial(input); macroSerial(input); stickyKeysSerial(input);

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
