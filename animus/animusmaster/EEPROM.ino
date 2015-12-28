void setEEPROM(char inputChar, byte inputType, int x, int y, int z)
{
  int addr = (z + (x * LAY) + (y * COL * LAY))*2;
  EEPROM.write(addr, inputChar);
  addr++;
  EEPROM.write(addr, inputType);
}

void setKeyEEPROM(int x, int y, int z, key input)
{
  int addr = (z + (x * LAY) + (y * COL * LAY))*2;
  EEPROM.write(addr, input.val);
  addr++;
  EEPROM.write(addr, input.type);
}
