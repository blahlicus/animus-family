#include "ModExample.h"

CModExample::CModExample(void)
{
  // nothing
}

void CModExample::Begin(void)
{
  CModTemplate::Begin();
  ModGUID = 3; // GUID of this specific mod


  // not needed, good against bad compilers
  for (byte i = 0; i < 20; i++)
  {
    FNDown[i] = false;
  }
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
    if (type == 30)
    {
      if (val == 0)
      {
        if (CtrlDown)
        {
          CtrlDown = false;
          Animus.ReleaseKey(ANIMUS_MOD_STICKY_LCTRL, 0);
        }
        else
        {
          CtrlDown = true;
          Animus.PressKey(ANIMUS_MOD_STICKY_LCTRL, 0);
        }

      }
      else if (val == 1)
      {
        if (ShiftDown)
        {
          ShiftDown = false;
          Animus.ReleaseKey(ANIMUS_MOD_STICKY_LSHIFT, 0);
        }
        else
        {
          ShiftDown = true;
          Animus.PressKey(ANIMUS_MOD_STICKY_LSHIFT, 0);
        }
      }
      else if (val == 2)
      {
        if (AltDown)
        {
          AltDown = false;
          Animus.ReleaseKey(ANIMUS_MOD_STICKY_LALT, 0);
        }
        else
        {
          AltDown = true;
          Animus.PressKey(ANIMUS_MOD_STICKY_LALT, 0);
        }
      }
      else if (val == 3)
      {
        if (AltgrDown)
        {
          AltgrDown = false;
          Animus.ReleaseKey(ANIMUS_MOD_STICKY_RALT, 0);
        }
        else
        {
          AltgrDown = true;
          Animus.PressKey(ANIMUS_MOD_STICKY_RALT, 0);
        }
      }
      else if (val == 4)
      {
        if (GuiDown)
        {
          GuiDown = false;
          Animus.ReleaseKey(ANIMUS_MOD_STICKY_LGUI, 0);
        }
        else
        {
          GuiDown = true;
          Animus.PressKey(ANIMUS_MOD_STICKY_RALT, 0);
        }
      }
      else
      {
        byte correctedVal = val - 5;
        if (FNDown[correctedVal])
        {
          FNDown[correctedVal] = false;
          Animus.ReleaseKey(correctedVal, 1);
        }
        else
        {
          FNDown[correctedVal] = false;
          Animus.PressKey(correctedVal, 1);
        }
      }
    }
  }
}
void CModExample::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (Global.HasUSB)
  {
    bool isMod = false;
    if (type == 0)
    {
      if (val == ANIMUS_MOD_STICKY_LCTRL)
      {
        isMod = true;
      }
      else if (val == ANIMUS_MOD_STICKY_LSHIFT)
      {
        isMod = true;
      }
      else if (val == ANIMUS_MOD_STICKY_LALT)
      {
        isMod = true;
      }
      else if (val == ANIMUS_MOD_STICKY_RALT)
      {
        isMod = true;
      }
      else if (val == ANIMUS_MOD_STICKY_LGUI)
      {
        isMod = true;
      }
    }

    if (type != 30 && isMod = false) // if this is not a sticky key or a modifier key
    {
      if (CtrlDown)
      {
        CtrlDown = false;
        Animus.ReleaseKey(ANIMUS_MOD_STICKY_LCTRL, 0);
      }
      if (ShiftDown)
      {
        ShiftDown = false;
        Animus.ReleaseKey(ANIMUS_MOD_STICKY_LSHIFT, 0);
      }
      if (AltDown)
      {
        AltDown = false;
        Animus.ReleaseKey(ANIMUS_MOD_STICKY_LALT, 0);
      }
      if (AltGrDown)
      {
        AltGrDown = false;
        Animus.ReleaseKey(ANIMUS_MOD_STICKY_RALT, 0);
      }
      if (GuiDown)
      {
        GuiDown = false;
        Animus.ReleaseKey(ANIMUS_MOD_STICKY_RALT, 0);

      }
      for (byte i = 0; i < 20; i++)
      {
        if (FNDown[i])
        {
          FNDown[i] = false;
          Animus.ReleaseKey(i, 1);
        }
      }
    }
  }
}

void CModExample::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModExample ModSticky;
