void setEEPROM(int x, int y, int z, char inputChar, byte inputType)
{
  int addr = (z + (x * LAY) + (y * COL * LAY))*2;
  EEPROM.write(addr, inputChar);
  addr++;
  EEPROM.write(addr, inputType);
}


char getValEEPROM(int x, int y, int z)
{
    int addr = (z + (x * LAY) + (y * COL * LAY))*2;
    return EEPROM.read(addr);
}

byte getTypeEEPROM(int x, int y, int z)
{
    int addr = (z + (x * LAY) + (y * COL * LAY))*2;
    addr++;
    return EEPROM.read(addr);
}
