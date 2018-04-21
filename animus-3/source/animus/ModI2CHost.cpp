#include "ModI2CHost.h"

CModI2CHost::CModI2CHost(void)
{
  // nothing
}

void CModI2CHost::Begin(void)
{
  CModTemplate::Begin();
  ModGUID = 8; // GUID of this specific mod

  if (Global.HasUSB)
  {

  }
}

void CModI2CHost::LoadData(void)
{
  CModTemplate::LoadData();

  if (Global.HasUSB)
  {

  }
}

void CModI2CHost::Loop(void)
{
  CModTemplate::Loop();

  if (Animus.GetMillis())
  {

      if (Global.HasUSB)
      {

      }
  }
}

void CModI2CHost::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
    if (Global.HasUSB)
    {

    }
}
void CModI2CHost::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);

  if (Global.HasUSB)
  {

  }
}
void CModI2CHost::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (Global.HasUSB)
  {

  }
}

void CModI2CHost::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModI2CHost ModI2CHost;
