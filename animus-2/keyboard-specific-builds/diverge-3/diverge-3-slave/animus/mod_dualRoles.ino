/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
Keytype(20)
Keytype(21)
Keytype(22)
Keytype(23)
Keytype(24)
Keytype(25)
Keytype(26)
Keytype(27)
Keytype(28)
Keytype(29)
BUILDER_REQUIREMENT_END
Remeber to change the mod_modname to your mod name
*/


#define mod_modname dualRoles

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
    // ctrlDualRole
    if (type == 20)
    {
      PressKey(224, 0);
      PressedKey = false;
    }
    else if (type == 21) // shiftDualRolee
    {
      PressKey(225, 0);
      PressedKey = false;
    }
    else if (type == 22) // alt
    {
      PressKey(226, 0);
      PressedKey = false;
    }
    else if (type == 23) // altgr
    {
      PressKey(230, 0);
      PressedKey = false;
    }
    else if (type > 23 && type < 30) // fn
    {
      PressedKey = false;
      TempLayer = type - 23;
    }
  }
}

void modMethod(KeyUp)(char val, byte type)
{
  // ran when a key is pressed up


  // ran if this device's IS_MASTER flag is true
  if (IS_MASTER)
  {
    if (type >= 20 && type < 30)
    {

      // ctrlDualRole
      if (type == 20)
      {
        ReleaseKey(224, 0);
      }
      else if (type == 21) // shiftDualRolee
      {
        ReleaseKey(225, 0);
      }
      else if (type == 22) // alt
      {
        ReleaseKey(226, 0);
      }
      else if (type == 23) // altgr
      {
        ReleaseKey(230, 0);
      }
      else if (type > 23 && type < 30) // fn
      {
        TempLayer = KeyLayer;
      }


      if (PressedKey == false)
      {
        AnimusKeyboard.write(val);
      }

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

void modMethod(PressCoord)(byte x, byte y) { }
void modMethod(PrePress)(char val, byte type) { }
#undef mod_modname
#undef modMethod
