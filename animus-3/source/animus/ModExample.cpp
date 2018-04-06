#include "ModExample.h"

CModExample::CModExample(void)
{
  // nothing
}

void CModExample::Begin(void)
{
  CModTemplate::Begin();
}

void CModExample::LoadData(void)
{
  CModTemplate::LoadData();
}

void CModExample::Loop(void)
{
  CModTemplate::Loop();
}

void CModExample::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
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
