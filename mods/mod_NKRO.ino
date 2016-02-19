#define mod_modname NKRO

#define modMethod(str) conca(mod_modname, str)

#define NKROMAX 3

void modMethod(Startup)()
{
  // things to run during hardware startup
  Keyboard.setNKROMode(EEPROM.read(1022));
}

void modMethod(Loop)()
{
  // full speed master loop


  // things inside this if statement is ran every refreshDelay milliseconds
  if (checkMillis())
  {

  }
}

void modMethod(KeyDown)(char val, byte type)
{
  // ran when a key is pressed down


  // ran if this device's IS_MASTER flag is true
  if (IS_MASTER)
  {
    if (type == 6)
    {
      if (Keyboard.getNKROMode() == val)
      {
        Keyboard.setNKROMode(0);
      }
      else
      {
        Keyboard.setNKROMode(val);
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
  }
}

void modMethod(SetMode)(int val)
{
  if (val < NKROMAX)
  {
    EEPROM.update(1022, val);
    Keyboard.setNKROMode(val);
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
  else if (input.startsWith("uniqueksetnkro"))
  {
    input = input.substring(input.indexOf('(')+1);
    byte val = input.toInt();

    if (val < NKROMAX)
    {
      modMethod(SetMode)(val);
      Serial.print("set NKRO mode(");
      Serial.println(val);
    }
    else
    {
      Serial.println("error: invalid NKRO option");
    }

  }
  else if (input == "uniquekgetnkro")
  {
    Serial.println(EEPROM.read(1022));
  }

}
#undef NKROMAX
#undef mod_modname
#undef modMethod
