


/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
keyType(31)
keyType(32)
keyType(33)
keyType(34)
BUILDER_REQUIREMENT_END
Remeber to change the mod_modname to your mod name
*/

/* keytype index
24: x movement (128 = 0)
25: y movement
26: wheel movement
27: click type (bitwise)
*/
#define mod_modname mouseKeys

#define modMethod(str) conca(mod_modname, str)


byte modMethod(XVal) = 128;
byte modMethod(YVal) = 128;
byte modMethod(WheelVal) = 128;
boolean modMethod(IsRunning) = false;

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
    if (modMethod(XVal) == 128 && modMethod(YVal) == 128 && modMethod(WheelVal) == 128)
    {
      // do nothing
      if (modMethod(IsRunning))
      {
        modMethod(IsRunning) = false;
        Mouse.end();
      }
      
    }
    else
    {
      Mouse.begin();
      modMethod(IsRunning) = true;
      Mouse.move(modMethod(XVal)-128,modMethod(YVal)-128,modMethod(WheelVal)-128);
    }

  }
}

void modMethod(KeyDown)(char val, byte type)
{
  // ran when a key is pressed down


  // ran if this device's IS_MASTER flag is true
  if (IS_MASTER)
  {
    if (type == 31)
    {
      modMethod(XVal) += val - 128;


    }
    else if (type == 32)
    {
      modMethod(YVal) += val - 128;


    }
    else if (type == 33)
    {
      modMethod(WheelVal) += val - 128;

    }
    else if (type == 34)
    {
      if (val == 1)
      {
        Mouse.press(MOUSE_LEFT);
      }
      else if (val == 2)
      {
        Mouse.press(MOUSE_RIGHT);
      }
      else if (val == 3)
      {
        Mouse.press(MOUSE_MIDDLE);
      }
      else if (val == 4)
      {
        Mouse.press(MOUSE_PREV);
      }
      else if (val == 5)
      {
        Mouse.press(Mouse_NEXT);
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
    if (type == 31)
    {
      modMethod(XVal) -= val - 128;

    }
    else if (type == 32)
    {
      modMethod(YVal) -= val -128;

    }
    else if (type == 33)
    {
      modMethod(WheelVal) -= val -128;

    }
    else if (type == 34)
    {
      if (val == 1)
      {
        Mouse.release(MOUSE_LEFT);
      }
      else if (val == 2)
      {
        Mouse.release(MOUSE_RIGHT);
      }
      else if (val == 3)
      {
        Mouse.release(MOUSE_MIDDLE);
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

#undef mod_modname
#undef modMethod
