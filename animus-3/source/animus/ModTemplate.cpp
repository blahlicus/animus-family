#include "ModTemplate.h"

CModTemplate::CModTemplate(void)
{
  //TODO
}

void CModTemplate::Begin(void)
{
  // gets and increments the mod counter for a unique mod id
  ModNo = Mod.ModCount;
  Mod.ModCount++;

  LoadData();
}

void CModTemplate::LoadData(void)
{
    // loads the EEPROM start address for the mod
    byte firstByte = EEPROM.read(MEM_DYNAMIC_ADDR + ModNo * 2);
    byte secondByte = EEPROM.read(MEM_DYNAMIC_ADDR + ModNo * 2 + 1);
    EEPROMAddress = (firstByte << 8) | secondByte;
}

void CModTemplate::Loop(void)
{
  //TODO
  SerialComms(Comms.mode);
}

void CModTemplate::PrePress(byte val, byte type)
{
  //TODO
}
void CModTemplate::PressKey(byte val, byte type)
{
  //TODO
}
void CModTemplate::ReleaseKey(byte val, byte type)
{
  //TODO
}

void CModTemplate::PrintMods()
{
  Serial.write(ModGUID);
}

byte CModTemplate::GetData(short addr)
{
  return EEPROM.read(EEPROMAddress + addr);
}

void CModTemplate::SetData(short addr, byte data)
{
  EEPROM.update(EEPROMAddress + addr, data);
}
void CModTemplate::End(void)
{
  //TODO
}

CModTemplate ModTemplate;
