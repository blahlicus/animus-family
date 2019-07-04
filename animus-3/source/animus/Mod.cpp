

#include "Mod.h"

CMod::CMod(void)
{
  //nothing
}

void CMod::Begin(void)
{
  builder_mod_begin
}

void CMod::Loop(void)
{
  builder_mod_loop
  if (Comms.mode == 3) // print mod guid list
  {
    Comms.TimeoutMillis = Global.CurrentMillis;
    PrintMods();
    Comms.mode == 0; // need this to reset comms back to normal mode
  }

  if (Global.RequiresLoadData == true)
  {
    Global.RequiresLoadData = false;
    LoadData();
  }

  builder_mod_serial

}

void CMod::LoadData(void) // to future self: this is called by the for loop above, search Global.RequiresLoadData, this is jank but oh well
{
  builder_mod_loaddata
}

void CMod::PressCoords(byte x, byte y)
{
  builder_mod_presscoords
}

void CMod::PrePress(byte val, byte type)
{
  builder_mod_prepress
}
void CMod::PressKey(byte val, byte type)
{
  builder_mod_press
}
void CMod::ReleaseKey(byte val, byte type)
{
  builder_mod_release
}

void CMod::PrintMods()
{
  builder_mod_print
}

void CMod::End(void)
{
  //nothing
}

CMod Mod;
