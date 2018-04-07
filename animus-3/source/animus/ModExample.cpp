#include "ModExample.h"

CModExample::CModExample(void)
{
  // nothing
}

void CModExample::Begin(void)
{
  CModTemplate::Begin();
  ModGUID = 0; // GUID of this specific mod

  if (Global.HasUSB)
  {

  }
}

void CModExample::LoadData(void)
{
  CModTemplate::LoadData();

  if (Global.HasUSB)
  {

  }
}

void CModExample::Loop(void)
{
  CModTemplate::Loop();

  if (Animus.GetMillis())
  {

      if (Global.HasUSB)
      {

      }
  }
}

void CModExample::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
    if (Global.HasUSB)
    {

    }
}
void CModExample::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);

  if (Global.HasUSB)
  {

  }
}
void CModExample::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (Global.HasUSB)
  {

  }
}

void CModExample::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModExample ModExample;
