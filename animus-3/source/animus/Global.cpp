#include "Global.h"
CGlobal::CGlobal(void)
{
  //nothing
}


void CGlobal::MillisLoop()
{
  CurrentMillis = millis();

  if(CurrentMillis - PreviousMillis >= 1) // this elapses every 1-1.5 ms
  {
    PreviousMillis = CurrentMillis;
    ReadyMillis = true;
  }
  else
  {
    ReadyMillis = false;
  }
}

CGlobal Global;
