//WORK IN PROGRESS, THIS MOD DOES NOT WORK

/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
EEPROM(600-800)
Keytype(7)
BUILDER_REQUIREMENT_END
Remeber to change the mod_modname to your mod name
*/


#define mod_modname macro


int macroMinAddr = 600;
int macroMaxAddr = 800;

int macroDelay = 5;
int currentMacroCount = 1;

#define modMethod(str) conca(mod_modname, str)



void modMethod(Startup)()
{
  // things to run during hardware startup
}

void modMethod(Loop)()
{
  // full speed master loop


  // things inside this if statement is ran every RefreshDelay milliseconds
  if (CheckMillis())
  {

  }
}

void modMethod(KeyDown)(char val, byte type)
{
  // ran when a key is pressed down


  // ran if this device's IS_MASTER flag is true
  if (IS_MASTER)
  {
    if (type == 7)
    {
      // sends the macro sequence with id = val
      macroSend(val);
    }
  }
}

void modMethod(KeyUp)(char val, byte type)
{
  // ran when a key is pressed up


  // ran if this device's IS_MASTER flag is true
  if (IS_MASTER)
  {
  }
}

void modMethod(Serial)(String input)
{
  // ran when serial command of input is sent to device from host

  // do not delete this as this is for the identifier
  if (input.startsWith("uniquekgetmods"))
  {
    Serial.print(tokenToString(mod_modname));
  }

}

void macroSend(int id)
{
  if (id < currentMacroCount)
  {
    int keystrokes = getMacroEEPROM(id);
    for (int i = 0; i < keystrokes; i++)
    {
      if (getMacroEEPROM(id, i * 3 + 1) == 0)
      {
        // press key
        PressKey(getMacroEEPROM(id, i * 3 + 2), getMacroEEPROM(id, i * 3 + 3));
      }
      else if (getMacroEEPROM(id, i * 3 + 1) == 1)
      {
        // release key
        ReleaseKey(getMacroEEPROM(id, i * 3 + 2), getMacroEEPROM(id, i * 3 + 3));
      }
      delay(macroDelay);
    }

  }
}

int getMacroEEPROM(int id, int shift)
{
  if (id < currentMacroCount)
  {
    int addr = macroMinAddr;
    for(int i = 0; i < id; i++)
    {
      addr = addr + EEPROM.read(addr) * 3 + 1;
    }
    return EEPROM.read(addr + shift);
  }
}

#undef mod_modname
#undef modMethod
