#include "ModModifier.h"


CModModifier::CModModifier(void)
{
  // nothing
}

void CModModifier::Begin(void)
{
  CModTemplate::Begin();
}

void CModModifier::LoadData(void)
{
  CModTemplate::LoadData();
}

void CModModifier::Loop(void)
{
  CModTemplate::Loop();
}

void CModModifier::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
}
void CModModifier::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);


  if (type == 4) // ctrl
  {

  }
  else if (type == 5) // shift
  {
  }
  else if (type == 6) // alt
  {

  }
  else if (type == 7) // win
  {

  }
  else if (type == 8) // ctrl shift
  {

  }
  else if (type == 9) // ctrl alt
  {

  }
  else if (type == 10) // ctrl win
  {

  }
  else if (type == 11) // shift alt
  {

  }
  else if (type == 12) // shift win
  {

  }
  else if (type == 13) // alt win
  {

  }
  else if (type == 14) // ctrl shift alt
  {

  }
  else if (type == 15) // ctrl shift win
  {

  }
  else if (type == 16) // ctrl alt win
  {

  }
  else if (type == 17) // shift alt win
  {

  }
  else if (type == 18) // ctrl alt shift win
  {

  }

  if (type >= 4 && type <= 18)
  {
    Animus.PressKey(val, 0);
  }



}
void CModModifier::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (type >= 4 && type <= 18)
  {
    Animus.ReleaseKey(val, 0);
  }

}

void CModModifier::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModModifier ModModifier;
