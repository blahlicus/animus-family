void SetEEPROM(int x, int y, int z, char inputChar, byte inputType)
{
  int addr = GetEEPROMValue(x, y, z);
  EEPROM.update(addr, inputChar);
  addr++;
  EEPROM.update(addr, inputType);
}

byte GetLayEEPROM()
{
  return EEPROM.read(1023);
}

char GetValEEPROM(int x, int y, int z)
{
  int addr = GetEEPROMValue(x, y, z);
  return EEPROM.read(addr);
}

byte GetTypeEEPROM(int x, int y, int z)
{
  int addr = GetEEPROMValue(x, y, z);
  addr++;
  return EEPROM.read(addr);
}

int GetEEPROMValue(int x, int y, int z)
{
  return ((x + (y * COL) + (z * COL * ROW))*2);
}
