#ifndef ANIMUS_MOD
#define ANIMUS_MOD

#define builder_mod_begin ModModifier.Begin();
#define builder_mod_loop ModModifier.Loop();
#define builder_mod_loaddata ModModifier.LoadData();
#define builder_mod_prepress ModModifier.PrePress(val, type);
#define builder_mod_press ModModifier.PressKey(val, type);
#define builder_mod_release ModModifier.ReleaseKey(val, type);
#define builder_mod_print ModModifier.PrintMods();


// mod dependencies below
#include "ModModifier.h"
// mod dependencies above


#include "Comms.h"



class CMod
{
private:
public:
  CMod(void);
  void Begin(void);
  void Loop(void);
  void LoadData(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void PrintMods();
  void End(void);
};
extern CMod Mod;

#endif
