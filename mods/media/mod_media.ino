/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
BUILDER_REQUIREMENT_END
*/

#define mod_modname media
#define modMethod(str) conca(mod_modname, str)

#include "AnimusMedia.h"

void mediaStartup()
{

}

void mediaLoop()
{
  if (CheckMillis())
  {

  }
}

void mediaKeyDown(char val, byte type)
{
  if (IS_MASTER)
  {
    if (type == 4)
    {
      if (val == 0)
      {
        Remote.increase();
        Remote.clear();
      }
      else if (val == 1)
      {
        Remote.decrease();
        Remote.clear();
      }
      else if (val == 2)
      {
        Remote.mute();
        Remote.clear();
      }
      else if (val == 3)
      {
        Remote.play();
        Remote.clear();
      }
      else if (val == 4)
      {
        Remote.pause();
        Remote.clear();
      }
      else if (val == 5)
      {
        Remote.next();
        Remote.clear();
      }
      else if (val == 6)
      {
        Remote.previous();
        Remote.clear();
      }
    }
  }
}

void mediaKeyUp(char val, byte type)
{

}

void mediaSerial(String input)
{
  if (input.startsWith("uniquekgetmods"))
  {
    Serial.print("media");
  }

}

#undef mod_modname
#undef modMethod
