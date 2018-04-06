#include "ModMedia.h"

CModMedia::CModMedia(void)
{
  // nothing
}

void CModMedia::Begin(void)
{
  CModTemplate::Begin();
  ModGUID = 4; // GUID of this specific mod
}

void CModMedia::LoadData(void)
{
  CModTemplate::LoadData();
}

void CModMedia::Loop(void)
{
  CModTemplate::Loop();
}

void CModMedia::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
}
void CModMedia::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);

  if (Global.HasUSB)
  {
    if (type == 31)
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
void CModMedia::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (Global.HasUSB)
  {

  }
}

void CModMedia::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModMedia ModMedia;
