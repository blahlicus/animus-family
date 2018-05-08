#include "ModTemplate.h"

CModTemplate::CModTemplate(void)
{
  //nothing
}

void CModTemplate::Begin(void)
{
  // gets and increments the mod counter for a unique mod id
  ModNo = Global.ModCount;
  Global.ModCount++;

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
  //nothing
  SerialComms(Comms.mode);
}

void CModTemplate::SerialComms(byte mode)
{
  //nothing
}

void CModTemplate::PressCoords(byte x, byte y)
{

}

void CModTemplate::PrePress(byte val, byte type)
{
  //nothing
}
void CModTemplate::PressKey(byte val, byte type)
{
  //nothing
}
void CModTemplate::ReleaseKey(byte val, byte type)
{
  //nothing
}

void CModTemplate::PrintMods()
{
  Serial.write(ModGUID);
}

byte CModTemplate::GetData(short addr)
{
  byte firstByte = EEPROM.read(MEM_DYNAMIC_ADDR + ModNo * 2);
  byte secondByte = EEPROM.read(MEM_DYNAMIC_ADDR + ModNo * 2 + 1);
  Serial.println(firstByte);
  Serial.println(secondByte);
  Serial.println(EEPROMAddress);
  return EEPROM.read(EEPROMAddress + addr);
}

void CModTemplate::SetData(short addr, byte data)
{
  EEPROM.update(EEPROMAddress + addr, data);
}
void CModTemplate::End(void)
{
  //nothing
}

CModTemplate ModTemplate;
