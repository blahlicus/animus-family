#define builder_mstartup mediaStartup(); macroStartup();
#define builder_mloop mediaLoop(); macroLoop();
#define builder_mkeydown mediaKeyDown(val, type); macroKeyDown(val, type);
#define builder_mkeyup mediaKeyUp(val, type); macroKeyUp(val, type);
#define builder_mserial mediaSerial(input); macroSerial(input);

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
