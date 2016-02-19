#define builder_mstartup mediaStartup(); NKROStartup(); 
#define builder_mloop mediaLoop(); NKROLoop(); 
#define builder_mkeydown mediaKeyDown(val, type); NKROKeyDown(val, type); 
#define builder_mkeyup mediaKeyUp(val, type); NKROKeyUp(val, type); 
#define builder_mserial mediaSerial(input); NKROSerial(input); 

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
