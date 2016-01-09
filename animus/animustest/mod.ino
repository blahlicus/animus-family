#define builder_mstartup// I2CStartup(); mediaStartup();

#define builder_mloop// I2CLoop(); mediaLoop();
#define builder_mloop_milis

#define builder_mkeydown// I2CKeyDown(val, type); mediaKeyDown(val, type);

#define builder_mkeyup// I2CKeyUp(val, type); mediaKeyUp(val, type);

#define builder_mserial// I2CSerial(input); mediaSerial(input);
void modStartup()
{
  builder_mstartup
}

void modLoop()
{
  if (checkMillis())
  {
  }
  builder_mloop
}


void modKeyDown(char val, byte type)
{
  builder_mkeydown
}

void modKeyUp(char val, byte type)
{
  builder_mkeyup
}

void modSerial(String input)
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
