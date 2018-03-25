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
  AnimusKeyboard.Press(98);
}
void CModExample::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);
  AnimusKeyboard.Release(98);


}

void CModExample::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModExample ModExample;
