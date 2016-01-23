void setEEPROM(int x, int y, int z, char inputChar, byte inputType)
{
  int addr = getEEPROMValue(x, y, z);
  EEPROM.write(addr, inputChar);
  addr++;
  EEPROM.write(addr, inputType);
}

int getLayEEPROM()
{
  return EEPROM.read(1023);
}

char getValEEPROM(int x, int y, int z)
{
  int addr = getEEPROMValue(x, y, z);
  return EEPROM.read(addr);
}

byte getTypeEEPROM(int x, int y, int z)
{
  int addr = getEEPROMValue(x, y, z);
  addr++;
  return EEPROM.read(addr);
}

int getEEPROMValue(int x, int y, int z)
{
  return ((x + (y * COL) + (z * COL * ROW))*2);
}
