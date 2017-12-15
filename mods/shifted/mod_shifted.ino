/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
Keytype(11)
BUILDER_REQUIREMENT_END
Remeber to change the mod_modname to your mod name
*/


#define mod_modname shifted

#define modMethod(str) conca(mod_modname, str)

char modMethod(Shifted) = 0;
char modMethod(LastVal) = 0;

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
    // shifted
    if (type == 11)
    {
      PressKey(225, 0);
      PressKey(val, 0);
      modMethod(Shifted) = val;
    }
  }
}

void modMethod(PrePress)(char val, byte type)
{
  if (IS_MASTER)
  {
    if (type == 0)
    {
      modMethod(LastVal) = val;
      if (modMethod(Shifted))
      {
        ReleaseKey(modMethod(Shifted), 0);
        ReleaseKey(225, 0);
        modMethod(Shifted) = 0;
      }
    }
    else if (type == 11)
    {
      if (val == modMethod(LastVal))
      {
        ReleaseKey(modMethod(LastVal), 0);
      }
    }
  }
}

void modMethod(KeyUp)(char val, byte type)
{
  // ran when a key is pressed up


  // ran if this device's IS_MASTER flag is true
  if (IS_MASTER)
  {
    // shifted
    if (type == 11)
    {
      ReleaseKey(val, 0);
      ReleaseKey(225, 0);
      modMethod(Shifted) = 0;
    }
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

#undef mod_modname
#undef modMethod
