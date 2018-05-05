#ifndef ANIMUS_MOD
#define ANIMUS_MOD

#define builder_mod_begin ModDualRoles.Begin(); ModModifier.Begin();  ModSticky.Begin(); ModMedia.Begin(); ModMacro.Begin(); ModTapdance.Begin(); ModMouse.Begin();ModI2CHost.Begin(); ModI2CGuest.Begin();
#define builder_mod_loop ModDualRoles.Loop(); ModModifier.Loop();  ModSticky.Loop(); ModMedia.Loop(); ModMacro.Loop(); ModTapdance.Loop(); ModMouse.Loop();ModI2CHost.Loop(); ModI2CGuest.Loop();
#define builder_mod_loaddata ModDualRoles.LoadData(); ModModifier.LoadData();  ModSticky.LoadData(); ModMedia.LoadData(); ModMacro.LoadData(); ModTapdance.LoadData(); ModMouse.LoadData();ModI2CHost.LoadData(); ModI2CGuest.LoadData();
#define builder_mod_prepress ModDualRoles.PrePress(val, type); ModModifier.PrePress(val, type);  ModSticky.PrePress(val, type); ModMedia.PrePress(val, type); ModMacro.PrePress(val, type); ModTapdance.PrePress(val, type); ModMouse.PrePress(val, type);ModI2CHost.PrePress(val, type); ModI2CGuest.PrePress(val, type);
#define builder_mod_press ModDualRoles.PressKey(val, type); ModModifier.PressKey(val, type);  ModSticky.PressKey(val, type); ModMedia.PressKey(val, type); ModMacro.PressKey(val, type); ModTapdance.PressKey(val, type); ModMouse.PressKey(val, type);ModI2CHost.PressKey(val, type); ModI2CGuest.PressKey(val, type);
#define builder_mod_release ModDualRoles.ReleaseKey(val, type); ModModifier.ReleaseKey(val, type);  ModSticky.ReleaseKey(val, type); ModMedia.ReleaseKey(val, type); ModMacro.ReleaseKey(val, type); ModTapdance.ReleaseKey(val, type); ModMouse.ReleaseKey(val, type);ModI2CHost.ReleaseKey(val, type); ModI2CGuest.ReleaseKey(val, type);
#define builder_mod_print ModDualRoles.PrintMods(); ModModifier.PrintMods();  ModSticky.PrintMods(); ModMedia.PrintMods(); ModMacro.PrintMods(); ModTapdance.PrintMods(); ModMouse.PrintMods();ModI2CHost.PrintMods(); ModI2CGuest.PrintMods();


// mod dependencies below
#include "ModModifier.h"
#include "ModDualRoles.h"
#include "ModSticky.h"
#include "ModMedia.h"
#include "ModMacro.h"
#include "ModTapdance.h"
#include "ModMouse.h"
#include "ModI2CHost.h"
#include "ModI2CGuest.h"
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
