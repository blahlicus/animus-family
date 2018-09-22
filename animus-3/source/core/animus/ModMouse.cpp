#include "ModMouse.h"

CModMouse::CModMouse(void)
{
  // nothing
}

void CModMouse::Begin(void)
{
  CModTemplate::Begin();
  ModGUID = 7; // GUID of this specific mod
  if (Global.HasUSB)
  {

  }
}

void CModMouse::LoadData(void)
{
  CModTemplate::LoadData();
  if (Global.HasUSB)
  {

  }
}

void CModMouse::Loop(void)
{
  CModTemplate::Loop();

  if (Animus.Async1MSDelay())
  {

    if (Global.HasUSB)
    {

      if (XVal == 128 && YVal == 128 && WheelVal == 128)
      {
        if (IsRunning)
        {
          IsRunning = false;
          Mouse.end();
        }
      }
      else
      {
        Mouse.begin();
        IsRunning = true;
        Mouse.move(XVal-128, YVal-128, WheelVal-128);
      }
    }
  }
}

void CModMouse::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
  if (Global.HasUSB)
  {

  }
}
void CModMouse::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);
  if (Global.HasUSB)
  {

    if (type == 34)
    {
      XVal += val - 128;
    }
    else if (type == 35)
    {
      YVal += val - 128;
    }
    else if (type == 36)
    {
      WheelVal += val - 128;
    }
    else if (type == 37)
    {
      if (val == 1)
      {
        Mouse.press(MOUSE_LEFT);
      }
      else if (val == 2)
      {
        Mouse.press(MOUSE_RIGHT);
      }
      else if (val == 3)
      {
        Mouse.press(MOUSE_MIDDLE);
      }
      else if (val == 4)
      {
        Mouse.press(MOUSE_PREV);
      }
      else if (val == 5)
      {
        Mouse.press(MOUSE_NEXT);
      }

    }
  }
}
void CModMouse::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);
  if (Global.HasUSB)
  {
    if (type == 34)
    {
      XVal -= val - 128;
    }
    else if (type == 35)
    {
      YVal -= val -128;
    }
    else if (type == 36)
    {
      WheelVal -= val -128;
    }
    else if (type == 37)
    {
      if (val == 1)
      {
        Mouse.release(MOUSE_LEFT);
      }
      else if (val == 2)
      {
        Mouse.release(MOUSE_RIGHT);
      }
      else if (val == 3)
      {
        Mouse.release(MOUSE_MIDDLE);
      }
      else if (val == 4)
      {
        Mouse.release(MOUSE_PREV);
      }
      else if (val == 5)
      {
        Mouse.release(MOUSE_NEXT);
      }
    }
  }
}

void CModMouse::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModMouse ModMouse;
