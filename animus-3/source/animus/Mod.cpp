#define builder_mod_begin
#define builder_mod_loop
#define builder_mod_loaddata
#define builder_mod_prepress
#define builder_mod_press
#define builder_mod_release
#define builder_mod_print

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
    PrintMods();
  }

}

void CMod::LoadData(void)
{
  builder_mod_loaddata
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
  builder_mod_release
}

void CMod::End(void)
{
  //nothing
}

CMod Mod;
