#include "ModDualRoles.h"

CModDualRoles::CModDualRoles(void)
{
  // nothing
}

void CModDualRoles::Begin(void)
{
  CModTemplate::Begin();
}

void CModDualRoles::LoadData(void)
{
  CModTemplate::LoadData();
}

void CModDualRoles::Loop(void)
{
  CModTemplate::Loop();
}

void CModDualRoles::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
}
void CModDualRoles::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);



}
void CModDualRoles::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);


}

void CModDualRoles::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModDualRoles ModDualRoles;
