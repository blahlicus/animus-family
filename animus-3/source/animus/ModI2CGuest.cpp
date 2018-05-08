#include "ModI2CGuest.h"

CModI2CGuest::CModI2CGuest(void)
{
  // nothing
}

void CModI2CGuest::Begin(void)
{
  CModTemplate::Begin();
  ModGUID = 8; // GUID of this specific mod

  if (!Global.HasUSB) // if no usb
  {
    Wire.begin(8);
    Wire.onRequest();
    Wire.onReceive();
  }
}

void CModI2CGuest::LoadData(void)
{
  CModTemplate::LoadData();

  if (Global.HasUSB)
  {

  }
}

void CModI2CGuest::Loop(void)
{
  CModTemplate::Loop();

  if (Animus.Async1MSDelay())
  {

      if (Global.HasUSB)
      {

      }
  }
}

void CModI2CGuest::PressCoords(byte x, byte y)
{
  CModTemplate::PressCoords(x, y);

}

void CModI2CGuest::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
    if (Global.HasUSB)
    {

    }
}
void CModI2CGuest::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);

  if (Global.HasUSB)
  {

  }
}
void CModI2CGuest::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (Global.HasUSB)
  {

  }
}

static void CModI2CGuest::RequestEvent()
{
  ModI2CGuest.OnRequest();
}

static void CModI2CGuest::ReceiveEvent(int numBytes)
{
  ModI2CGuest.OnReceive(numBytes);
}

void CModI2CGuest::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModI2CGuest ModI2CGuest;
