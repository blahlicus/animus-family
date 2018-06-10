/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
BUILDER_REQUIREMENT_END
Remeber to change the mod_modname to your mod name
*/


#define mod_modname uktemplate

#define modMethod(str) conca(mod_modname, str)

void modMethod(Startup)()
{
  // things to run during hardware startup
}

void modMethod(Loop)()
{
  // full speed master loop


  // this is an async clock that runs once every ms, put non-critically responsive code in here to reduce processor stress
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
