/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
keyType(30)
BUILDER_REQUIREMENT_END
Remeber to change the mod_modname to your mod name
*/


#define mod_modname stickyKeys

#define modMethod(str) conca(mod_modname, str)

#define STICKY_KEY_MAX 20

boolean modMethod(State)[STICKY_KEY_MAX] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

boolean modMethod(PressedKey) = false;

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
    // ctrlDualRole
    if (type == 30)
    {


      modMethod(State)[val] = !modMethod(State)[val];
      if (modMethod(State)[val])
      {


        if (val == 0)
        {
          AnimusKeyboard.press(224); // ctrl
        }
        else if (val == 1)
        {
          AnimusKeyboard.press(225); // shift
        }
        else if (val == 2)
        {
          AnimusKeyboard.press(226); //alt
        }
        else if (val == 3)
        {
          AnimusKeyboard.press(230); //altgr
        }
        else if (val > 3 && val < STICKY_KEY_MAX)
        {
          TempLayer = val-3;
        }
        modMethod(PressedKey) = false;
      }
      else
      {
        modMethod(ReleaseAll)();
      }


    }
    else
    {
      modMethod(ReleaseAll)();
    }
  }
}

void modMethod(ReleaseAll)()
{

    modMethod(PressedKey) = true;
    for (int i = 0; i < STICKY_KEY_MAX; i++)
    {
      if (modMethod(State)[i])
      {
        if (i == 0)
        {
          AnimusKeyboard.release(224); // ctrl
        }
        else if (i == 1)
        {
          AnimusKeyboard.release(225); // shift
        }
        else if (i == 2)
        {
          AnimusKeyboard.release(226); //alt
        }
        else if (i == 3)
        {
          AnimusKeyboard.release(230); //altgr
        }
        else if (i > 3 && i < STICKY_KEY_MAX)
        {
          TempLayer = KeyLayer;
        }
        modMethod(State)[i] = false;
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

#undef mod_modname
#undef modMethod
