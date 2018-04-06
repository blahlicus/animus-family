#ifndef ANIMUS_MOD
#define ANIMUS_MOD

#define builder_mod_begin ModDualRoles.Begin(); ModModifier.Begin();  ModSticky.Begin(); ModMedia.Begin(); ModMacro.Begin();
#define builder_mod_loop ModDualRoles.Loop(); ModModifier.Loop();  ModSticky.Loop(); ModMedia.Loop(); ModMacro.Loop();
#define builder_mod_loaddata ModDualRoles.LoadData(); ModModifier.LoadData();  ModSticky.LoadData(); ModMedia.LoadData(); ModMacro.LoadData();
#define builder_mod_prepress ModDualRoles.PrePress(val, type); ModModifier.PrePress(val, type);  ModSticky.PrePress(val, type); ModMedia.PrePress(val, type); ModMacro.PrePress(val, type);
#define builder_mod_press ModDualRoles.PressKey(val, type); ModModifier.PressKey(val, type);  ModSticky.PressKey(val, type); ModMedia.PressKey(val, type); ModMacro.PressKey(val, type);
#define builder_mod_release ModDualRoles.ReleaseKey(val, type); ModModifier.ReleaseKey(val, type);  ModSticky.ReleaseKey(val, type); ModMedia.ReleaseKey(val, type); ModMacro.ReleaseKey(val, type);
#define builder_mod_print ModDualRoles.PrintMods(); ModModifier.PrintMods();  ModSticky.PrintMods(); ModMedia.PrintMods(); ModMacro.PrintMods();


// mod dependencies below
#include "ModModifier.h"
#include "ModDualRoles.h"
#include "ModSticky.h"
#include "ModMedia.h"
#include "ModMacro.h"
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
