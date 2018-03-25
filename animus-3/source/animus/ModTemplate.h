#ifndef ANIMUS_MOD_TEMPLATE
#define ANIMUS_MOD_TEMPLATE
#include "Mod.h"


#define MEM_DYNAMIC_ADDR 950

class CModTemplate
{
private:
  void SerialComms(byte mode);
public:
  byte ModNo; // this is the EEPROM memory address ID
  short EEPROMAddress;
  const byte ModGUID; // this is the GUID for all list of mods, used for identification by arbites
  CModTemplate(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void PrintMods();
  byte GetData(short addr);
  void SetData(short addr, byte data);
  void End(void);
};
extern CModTemplate ModTemplate;

#undef mod_modname
#undef modMethod
#endif
