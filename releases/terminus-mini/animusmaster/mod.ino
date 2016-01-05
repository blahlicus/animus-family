void modStartup()
{
  mediaStartup();
}

void modLoop()
{
  if (checkMillis())
  {
  }
  mediaLoop();
}


void modKeyDown(char val, byte type)
{
  mediaKeyDown(val, type);
}

void modKeyUp(char val, byte type)
{
  mediaKeyUp(val, type);
}

void modSerial(String input)
{
  if (input == "uniquekgetmods")
  {
    Serial.print("get mods(");
  }
  mediaSerial(input);
  if (input == "uniquekgetmods")
  {
    Serial.print("\r\n");
  }
}
