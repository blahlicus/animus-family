#include "ModDualRoles.h"

CModDualRoles::CModDualRoles(void)
{
  // nothing
}

void CModDualRoles::Begin(void)
{
  CModTemplate::Begin();

  TimeoutLength = GetData(0) * 5; // max value is 255 * 5 = about 1.275 seconds

  // I don't need to do this but just to be safe to the compiler
  GuiTimeout = 0;
  CtrlTimeout = 0;
  ShiftTimeout = 0;
  AltTimeout = 0;
  AltgrTimeout = 0;
  for (byte i = 0; i < 6; i++)
  {
    FNTimeout[i] = 0;
    FNDown[i] = false;
  }
}

void CModDualRoles::LoadData(void)
{
  CModTemplate::LoadData();
}

void CModDualRoles::Loop(void)
{
  CModTemplate::Loop();
  if (Animus.GetMillis())
  {
    // countdowns
    if (GuiTimeout > 0)
    {
      GuiTimeout--;
    }
    if (CtrlTimeout > 0)
    {
      CtrlTimeout--;
    }
    if (ShiftTimeout > 0)
    {
      ShiftTimeout--;
    }
    if (AltTimeout > 0)
    {
      AltTimeout--;
    }
    if (AltgrTimeout > 0)
    {
      AltgrTimeout--;
    }

    for (byte i = 0; i < 6; i++)
    {
      if (FNTimeout[i] > 0)
      {
        FNTimeout[i]--;
      }
    }
  }
}

void CModDualRoles::PrePress(byte val, byte type)
{
  CModTemplate::PrePress(val, type);
}
void CModDualRoles::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);
  PressedKey = true;
  if (Global.HasUSB)
  {
    if (type == 19) // gui
    {
      if (GuiDown == 0) // gui was not down by this mod before
      {
        Animus.PressKey(ANIMUS_MOD_DUALROLES_LGUI, 0);
        PressedKey = false;
        GuiTimeout = TimeoutLength;
      }
      else // gui was already down, pretend to be an ordinary key
      {
        Animus.PressKey(val, 0);
      }
      GuiDown++;
    }
    else if (type == 20) // ctrl
    {

      if (CtrlDown == 0) // ctrl was not down by this mod before
      {
        Animus.PressKey(ANIMUS_MOD_DUALROLES_LCTRL, 0);
        PressedKey = false;
        CtrlTimeout = TimeoutLength;
      }
      else // ctrl was already down, pretend to be an ordinary key
      {
        Animus.PressKey(val, 0);
      }
      CtrlDown++;
    }
    else if (type == 21) // shift
    {
      if (ShiftDown == 0) // shift was not down by this mod before
      {
        Animus.PressKey(ANIMUS_MOD_DUALROLES_LSHIFT, 0);
        PressedKey = false;
        ShiftTimeout = TimeoutLength;
      }
      else // shift was already down, pretend to be an ordinary key
      {
        Animus.PressKey(val, 0);
      }
      ShiftDown++;
    }
    else if (type == 22) // alt
    {
      if (AltDown == 0) // ctrl was not down by this mod before
      {
        Animus.PressKey(ANIMUS_MOD_DUALROLES_LALT, 0);
        PressedKey = false;
        AltTimeout = TimeoutLength;
      }
      else // alt was already down, pretend to be an ordinary key
      {
        Animus.PressKey(val, 0);
      }
      AltDown++;
    }
    else if (type == 23) // altgr
    {
      if (AltgrDown == 0) // altgr was not down by this mod before
      {
        Animus.PressKey(ANIMUS_MOD_DUALROLES_RALT, 0);
        PressedKey = false;
        AltgrTimeout = TimeoutLength;
      }
      else // altgr was already down, pretend to be an ordinary key
      {
        Animus.PressKey(val, 0);
      }
      AltgrDown++;
    }
    else if (type > 23 && type < 30) // fn
    {
      byte fnIndex = type - 24; // behaviour change, 24 is master layer, 25 is layer 1
      if (FNDown[fnIndex] == 0) // fn key of this index was not down by this mod before
      {
        Animus.PressKey(fnIndex, 1); // press fn key
        PressedKey = false;
        FNTimeout[fnIndex] = TimeoutLength;
      }
      else // fn key of this index was already down, pretend to be an ordinary key
      {
        Animus.PressKey(val, 0);
      }
      FNDown[fnIndex]++;
    }
  }
}
void CModDualRoles::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);
  if (Global.HasUSB)
  {
    if (type == 19) // gui
    {

      GuiDown--;
      if (GuiDown == 0) // all mod keys released, release the mod
      {
        Animus.ReleaseKey(ANIMUS_MOD_DUALROLES_LGUI, 0);
      }
      
      if (PressedKey == false && GuiTimeout > 0) // no key was pressed and gui CD has not finished, output dual character
      {
        Animus.PressKey(val, 0);
      }
      Animus.ReleaseKey(val, 0); // always release, if key was not down then it doesn't matter
      // now clear states

    }
    else if (type == 20) // ctrl
    {


      CtrlDown--;
      if (CtrlDown == 0) // all mod keys released, release the mod
      {
        Animus.ReleaseKey(ANIMUS_MOD_DUALROLES_LCTRL, 0);
      }
      
      if (PressedKey == false && CtrlTimeout > 0) // no key was pressed and ctrl CD has not finished, output dual character
      {
        Animus.PressKey(val, 0);
      }
      Animus.ReleaseKey(val, 0); // always release, if key was not down then it doesn't matter
      // now clear states

    }
    else if (type == 21) // shift
    {

      ShiftDown--;
      if (ShiftDown == 0) // all mod keys released, release the mod
      {
        Animus.ReleaseKey(ANIMUS_MOD_DUALROLES_LSHIFT, 0);
      }
      
      if (PressedKey == false && ShiftTimeout > 0) // no key was pressed and shift CD has not finished, output dual character
      {
        Animus.PressKey(val, 0);
      }
      Animus.ReleaseKey(val, 0); // always release, if key was not down then it doesn't matter
      // now clear states

    }
    else if (type == 22) // alt
    {

      AltDown--;
      if (AltDown == 0) // all mod keys released, release the mod
      {
        Animus.ReleaseKey(ANIMUS_MOD_DUALROLES_LALT, 0);
      }
      
      if (PressedKey == false && AltTimeout > 0) // no key was pressed and ctrl CD has not finished, output dual character
      {
        Animus.PressKey(val, 0);
      }
      Animus.ReleaseKey(val, 0); // always release, if key was not down then it doesn't matter
      // now clear states

    }
    else if (type == 23) // altgr
    {

      AltgrDown--;
      if (AltgrDown == 0) // all mod keys released, release the mod
      {
        Animus.ReleaseKey(ANIMUS_MOD_DUALROLES_RALT, 0);
      }
      
      if (PressedKey == false && AltgrTimeout > 0) // no key was pressed and altgr CD has not finished, output dual character
      {
        Animus.PressKey(val, 0);
      }
      Animus.ReleaseKey(val, 0); // always release, if key was not down then it doesn't matter
      // now clear states

    }
    else if (type > 23 && type < 30) // fn
    {
      byte fnIndex = type - 24; // behaviour change, 24 is master layer, 25 is layer 1

      FNDown[fnIndex]--;
      if (FNDown[fnIndex] == 0) // all mod keys released, release the mod
      {
        Animus.ReleaseKey(fnIndex, 1);
      }
      
      if (PressedKey == false && FNTimeout[fnIndex] > 0) // no key was pressed and altgr CD has not finished, output dual character
      {
        Animus.PressKey(val, 0);
      }
      Animus.ReleaseKey(val, 0); // always release, if key was not down then it doesn't matter
      // now clear states

    }
  }

}

void CModDualRoles::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModDualRoles ModDualRoles;
