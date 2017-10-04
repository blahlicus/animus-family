/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
BUILDER_REQUIREMENT_END
Remeber to change the mod_modname to your mod name
*/

#define LEDEXISTS true
#define mod_modname BledPWM

#define modMethod(str) conca(mod_modname, str)


const byte modMethod(LedPin) = 5;

const byte modMethod(MAX_BRIGHT) = 255;

byte modMethod(Brightness) = 50;

void modMethod(Startup)()
{
  // things to run during hardware startup
}

void modMethod(Loop)()
{
  // full speed master loop
  analogWrite(modMethod(LedPin), modMethod(Brightness));

  // things inside this if statement is ran every RefreshDelay milliseconds
  if (CheckMillis())
  {

  }
}

void modMethod(SetBright)(byte input)
{
  modMethod(Brightness) = input;
}

void modMethod(KeyDown)(char val, byte type)
{
  // ran when a key is pressed down




  // ran if this device's IS_MASTER flag is true
  if (IS_MASTER)
  {
    if (type == 10)
    {

      if (val < 101)
      {
        int adjust = val;

        if (modMethod(Brightness) + adjust < 0)
        {
          modMethod(Brightness) = 0;
        }
        else if (modMethod(Brightness) + adjust > modMethod(MAX_BRIGHT))
        {
          modMethod(Brightness) = modMethod(MAX_BRIGHT);
        }
        else
        {
          modMethod(Brightness) = modMethod(Brightness) + adjust;
        }
      }
      else if (val == 101)
      {
        modMethod(Brightness) = 0;
      }
      else if (val == 102)
      {
        modMethod(Brightness) = 32;
      }
      else if (val == 103)
      {
        modMethod(Brightness) = 64;
      }
      else if (val == 104)
      {
        modMethod(Brightness) = 96;
      }
      else if (val == 105)
      {
        modMethod(Brightness) = 128;
      }
      else if (val == 106)
      {
        modMethod(Brightness) = 160;
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

void modMethod(Serial)(String input)
{
  // ran when serial command of input is sent to device from host

  // do not delete this as this is for the identifier
  if (input.startsWith("uniquekgetmods"))
  {
    Serial.print(tokenToString(mod_modname));
  }
  else if (input.startsWith("uniqueksetbrightness"))
  {

    input = input.substring(input.indexOf('(')+1);
    byte bri = input.substring(0, input.indexOf('(')).toInt();

    modMethod(Brightness) = bri;
    Serial.print("set brightness()");
    Serial.println(modMethod(Brightness));
  }
  else if (input.startsWith("uniquekgetbrightness"))
  {
    Serial.print("get brightness()");
    Serial.println(modMethod(Brightness));

  }

}



#undef mod_modname
#undef modMethod
