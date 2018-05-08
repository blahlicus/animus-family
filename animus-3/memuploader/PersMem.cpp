#include "PersMem.h"

CMem::CMem(void)
{

}

void CMem::Begin(void)
{
  LoadData();
}

void CMem::LoadData(void)
{
  // loads EEPROM data to SRAM
  Global.RefreshDelay = GetRefreshRate();
  if (Global.RefreshDelay < 1)
  {
    Global.RefreshDelay = 5;
  }
  Global.ROW = GetRowCount();
  Global.COL = GetColCount();
  Global.LAY = GetLayCount();

  for(byte i = 0; i < Global.ROW; i++)
  {
    Global.VPins[i] = GetRowPin(i);
  }
  for(byte i = 0; i < Global.COL; i++)
  {
    Global.HPins[i] = GetColPin(i);
  }

  if (Global.LAY < 1)
  {
    Global.LAY = 1;
  }
  if (Global.ROW < 1)
  {
    Global.ROW = 5;
    Global.VPins[0] = 4;
    Global.VPins[1] = 6;
    Global.VPins[2] = 7;
    Global.VPins[3] = 8;
    Global.VPins[4] = 9;
  }
  if (Global.COL < 1)
  {
    Global.COL = 5;
    Global.HPins[0] = 21;
    Global.HPins[1] = 20;
    Global.HPins[2] = 19;
    Global.HPins[3] = 18;
    Global.HPins[4] = 15;
  }



  Global.RequiresLoadData = true;
  // loads mod EEPROM addresses to SRAM


  // resets pin statuses
  for (int i = 0; i < Global.ROW; i++)
  {
    pinMode(Global.VPins[i], INPUT);
    digitalWrite(Global.VPins[i], HIGH);
  }

  for (int i = 0; i < Global.COL; i++)
  {
    pinMode(Global.HPins[i], INPUT);
    digitalWrite(Global.HPins[i], LOW);
  }

  for (int i = 0; i < Global.ROW; i++)
  {
    for (int j = 0; j < Global.COL; j++)
    {
      Global.KeyState[j][i] = 0;
      Global.PreviousState[j][i] = 0;
      Global.KeyStateCoolDown[j][i] = 0;
    }
  }
}

void CMem::Loop(void)
{

}

// Start of Setters

void CMem::SetKey(byte x, byte y, byte z, byte inputChar, byte inputType)
{
  EEPROM.update(((x + (y * Global.COL) + (z * Global.COL * Global.ROW)) * 2), inputChar);
  EEPROM.update(((x + (y * Global.COL) + (z * Global.COL * Global.ROW)) * 2) + 1, inputType);
}

void CMem::SetRowCount(byte input)
{
  EEPROM.update(MEM_ROW_COUNT, input);

}

void CMem::SetColCount(byte input)
{
  EEPROM.update(MEM_COL_COUNT, input);

}

void CMem::SetLayCount(byte input)
{
  EEPROM.update(MEM_LAY_COUNT, input);

}

void CMem::SetRowPin(byte pinNo, byte rowNo)
{
  EEPROM.update(MEM_ROW_0 + pinNo, rowNo);

}

void CMem::SetColPin(byte pinNo, byte colNo)
{
  EEPROM.update(MEM_COL_0 + pinNo, colNo);

}

void CMem::SetBoardType(byte input)
{
  EEPROM.update(MEM_BOARD_TYPE, input);

}

void CMem::SetNKROType(byte input)
{
  EEPROM.update(MEM_NKRO_MODE, input);

}

void CMem::SetRefreshRate(byte input)
{
  EEPROM.update(MEM_REFRESH_RATE, input);
}

// End of Setters

//Start of Getters

byte CMem::GetKeyData(byte x, byte y, byte z)
{
  return EEPROM.read(((x + (y * Global.COL) + (z * Global.COL * Global.ROW)) * 2));
}

byte CMem::GetKeyType(byte x, byte y, byte z)
{
  return EEPROM.read(((x + (y * Global.COL) + (z * Global.COL * Global.ROW)) * 2) + 1);


}

byte CMem::GetRowCount()
{
  return EEPROM.read(MEM_ROW_COUNT);
}

byte CMem::GetColCount()
{
  return EEPROM.read(MEM_COL_COUNT);
}

byte CMem::GetLayCount()
{
  return EEPROM.read(MEM_LAY_COUNT);
}

byte CMem::GetRowPin(byte rowNo)
{
  return EEPROM.read(MEM_ROW_0 + rowNo);
}

byte CMem::GetColPin(byte colNo)
{
  return EEPROM.read(MEM_COL_0 + colNo);

}

byte CMem::GetBoardType()
{
  return EEPROM.read(MEM_BOARD_TYPE);
}

byte CMem::GetNKROType()
{
  return EEPROM.read(MEM_NKRO_MODE);
}

byte CMem::GetRefreshRate()
{
  return EEPROM.read(MEM_REFRESH_RATE);
}



// End of Getters


void CMem::End(void)
{

}

CMem PersMem;