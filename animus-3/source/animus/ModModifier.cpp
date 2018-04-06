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

void CModModifier::PressModifiers(bool ctrl, bool shift, bool alt, bool gui)
{
  if (shift) // if mod has to press shift
  {
    if (NaturalLShift)
    {
      Animus.ReleaseKey(ANIMUS_MOD_MODIFIER_LSHIFT, 0);
      NaturalLShift = true;
    }
    if (NaturalRShift)
    {
      Animus.ReleaseKey(ANIMUS_MOD_MODIFIER_RSHIFT, 0);
      NaturalRShift = true;
    }

    // this runs after the above two checks, if the statement below is true,
    // then the modifiers are definitely up naturally
    if (NaturalLShift == false && NaturalRShift == false) // perhaps i should use NaturalLShift + NaturalRShift == 0? i don't know
    {
      Animus.PressKey(ANIMUS_MOD_MODIFIER_LSHIFT, 0);
      NaturalLShift = false;
    }
  }

  if (ctrl)
  {
    Animus.PressKey(ANIMUS_MOD_MODIFIER_LCTRL, 0);
  }
  if (alt)
  {
    Animus.PressKey(ANIMUS_MOD_MODIFIER_LALT, 0);
  }
  if (gui)
  {
    Animus.PressKey(ANIMUS_MOD_MODIFIER_LGUI, 0);
  }

}

void CModModifier::ReleaseModifiers(bool ctrl, bool shift, bool alt, bool gui)
{
  if (shift) // if mod has to return shift to previous state (not the same as simply releasing shift)
  {
    if (NaturalLShift)
    {
      Animus.PressKey(ANIMUS_MOD_MODIFIER_LSHIFT, 0);
    }
    else
    {
      Animus.ReleaseKey(ANIMUS_MOD_MODIFIER_LSHIFT, 0);
    }

    if (NaturalRShift)
    {
      Animus.PressKey(ANIMUS_MOD_MODIFIER_RSHIFT, 0);
    }
    else
    {
      Animus.ReleaseKey(ANIMUS_MOD_MODIFIER_RSHIFT, 0);

    }
  }

  if (ctrl)
  {
    Animus.ReleaseKey(ANIMUS_MOD_MODIFIER_LCTRL, 0);
  }
  if (alt)
  {
    Animus.ReleaseKey(ANIMUS_MOD_MODIFIER_LALT, 0);
  }
  if (gui)
  {
    Animus.ReleaseKey(ANIMUS_MOD_MODIFIER_LGUI, 0);
  }
}

void CModModifier::PressKey(byte val, byte type)
{
  CModTemplate::PressKey(val, type);

  if (Global.HasUSB)
  {
    if (type == 0)
    {
      if (val == ANIMUS_MOD_MODIFIER_LSHIFT)
      {
        NaturalLShift = true;
      }
      else if (val == ANIMUS_MOD_MODIFIER_RSHIFT)
      {
        NaturalRShift = true;
      }
    }

    bool ctrl = false;
    bool shift = false;
    bool alt = false;
    bool gui = false;

    if (type == 4) // ctrl
    {
      ctrl = true;
    }
    else if (type == 5) // shift
    {
      shift = true;
    }
    else if (type == 6) // alt
    {
      alt = true;
    }
    else if (type == 7) // win
    {
      gui = true;
    }
    else if (type == 8) // ctrl shift
    {
      ctrl = true;
      shift = true;
    }
    else if (type == 9) // ctrl alt
    {
      ctrl = true;
      alt = true;
    }
    else if (type == 10) // ctrl win
    {
      ctrl = true;
      gui = true;
    }
    else if (type == 11) // shift alt
    {
      shift = true;
      alt = true;
    }
    else if (type == 12) // shift win
    {
      shift = true;
      gui = true;
    }
    else if (type == 13) // alt win
    {
      alt = true;
      gui = true;
    }
    else if (type == 14) // ctrl shift alt
    {
      ctrl = true;
      shift = true;
      alt = true;
    }
    else if (type == 15) // ctrl shift win
    {
      ctrl = true;
      shift = true;
      gui = true;
    }
    else if (type == 16) // ctrl alt win
    {
      ctrl = true;
      alt = true;
      gui = true;
    }
    else if (type == 17) // shift alt win
    {
      shift = true;
      alt = true;
      gui = true;
    }
    else if (type == 18) // ctrl alt shift win
    {
      ctrl = true;
      alt = true;
      shift = true;
      gui = true;
    }

    PressModifiers(ctrl, shift, alt, gui);

    if (type >= 4 && type <= 18)
    {
      Animus.PressKey(val, 0);
    }
  }
}
void CModModifier::ReleaseKey(byte val, byte type)
{
  CModTemplate::ReleaseKey(val, type);

  if (Global.HasUSB)
  {
    if (type == 0)
    {
      if (val == ANIMUS_MOD_MODIFIER_LSHIFT)
      {
        NaturalLShift = false;
      }
      else if (val == ANIMUS_MOD_MODIFIER_RSHIFT)
      {
        NaturalRShift = false;
      }
    }

    bool ctrl = false;
    bool shift = false;
    bool alt = false;
    bool gui = false;

    if (type == 4) // ctrl
    {
      ctrl = true;
    }
    else if (type == 5) // shift
    {
      shift = true;
    }
    else if (type == 6) // alt
    {
      alt = true;
    }
    else if (type == 7) // win
    {
      gui = true;
    }
    else if (type == 8) // ctrl shift
    {
      ctrl = true;
      shift = true;
    }
    else if (type == 9) // ctrl alt
    {
      ctrl = true;
      alt = true;
    }
    else if (type == 10) // ctrl win
    {
      ctrl = true;
      gui = true;
    }
    else if (type == 11) // shift alt
    {
      shift = true;
      alt = true;
    }
    else if (type == 12) // shift win
    {
      shift = true;
      gui = true;
    }
    else if (type == 13) // alt win
    {
      alt = true;
      gui = true;
    }
    else if (type == 14) // ctrl shift alt
    {
      ctrl = true;
      shift = true;
      alt = true;
    }
    else if (type == 15) // ctrl shift win
    {
      ctrl = true;
      shift = true;
      gui = true;
    }
    else if (type == 16) // ctrl alt win
    {
      ctrl = true;
      alt = true;
      gui = true;
    }
    else if (type == 17) // shift alt win
    {
      shift = true;
      alt = true;
      gui = true;
    }
    else if (type == 18) // ctrl alt shift win
    {
      ctrl = true;
      alt = true;
      shift = true;
      gui = true;
    }

    ReleaseModifiers(ctrl, shift, alt, gui);

    if (type >= 4 && type <= 18)
    {
      Animus.ReleaseKey(val, 0);
    }
  }

}

void CModModifier::SerialComms(byte mode)
{
  CModTemplate::SerialComms(mode);
}


CModModifier ModModifier;
