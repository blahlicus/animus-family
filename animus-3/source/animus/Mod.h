#ifndef ANIMUS_MOD
#define ANIMUS_MOD

#define builder_mod_begin ModExample.Begin();
#define builder_mod_loop ModExample.Loop();
#define builder_mod_loaddata ModExample.LoadData();
#define builder_mod_prepress ModExample.PrePress(val, type);
#define builder_mod_press ModExample.PressKey(val, type);
#define builder_mod_release ModExample.ReleaseKey(val, type);
#define builder_mod_print ModExample.PrintMods();


// mod dependencies below
#include "ModExample.h"
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
