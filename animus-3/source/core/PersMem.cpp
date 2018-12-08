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
  Global.COL = GetColCount();
  if (Global.COL != 0) // if the rows and cols are configured, then load further data
  {
    Global.RefreshDelay = GetRefreshRate();
    Global.ROW = GetRowCount();
    Global.LAY = GetLayCount();

    for(byte i = 0; i < Global.ROW; i++)
    {
      Global.VPins[i] = GetRowPin(i);
    }
    for(byte i = 0; i < Global.COL; i++)
    {
      Global.HPins[i] = GetColPin(i);
    }

    Global.HasUSB = GetUSBHostType();

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
}

void CMem::Loop(void)
{

}

// Start of Setters

// don't use EEPROM.update elsewhere to maintain platform agnosticity
void CMem::SetEEPROM(short address, byte data) // this updates the eeprom
{
  EEPROM.update(address, data);
}

void CMem::SetEEPROMForced(short address, byte data) // this hard rewrites the eeprom
{
  EEPROM.write(address, data);
}

void CMem::CommitEEPROM(void)
{
  #if defined (ARDUINO_SAMD_ZERO) // only run this if in SAMD21
  EEPROM.commit();
  #endif
}

void CMem::SetKey(byte x, byte y, byte z, byte inputChar, byte inputType)
{
  SetEEPROM(((x + (y * Global.COL) + (z * Global.COL * Global.ROW)) * 2), inputChar);
  SetEEPROM(((x + (y * Global.COL) + (z * Global.COL * Global.ROW)) * 2) + 1, inputType);
}

void CMem::SetRowCount(byte input)
{
  SetEEPROM(MEM_ROW_COUNT, input);

}

void CMem::SetColCount(byte input)
{
  SetEEPROM(MEM_COL_COUNT, input);

}

void CMem::SetLayCount(byte input)
{
  SetEEPROM(MEM_LAY_COUNT, input);

}

void CMem::SetRowPin(byte pinNo, byte rowNo)
{
  SetEEPROM(MEM_ROW_0 + pinNo, rowNo);

}

void CMem::SetColPin(byte pinNo, byte colNo)
{
  SetEEPROM(MEM_COL_0 + pinNo, colNo);

}

void CMem::SetBoardType(byte input)
{
  SetEEPROM(MEM_BOARD_TYPE, input);

}

void CMem::SetNKROType(byte input)
{
  SetEEPROM(MEM_NKRO_MODE, input);

}

void CMem::SetUSBHostType(byte input)
{
  SetEEPROM(MEM_IS_USBHOST, input);
}

void CMem::SetRefreshRate(byte input)
{
  SetEEPROM(MEM_REFRESH_RATE, input);
}

// End of Setters

//Start of Getters

// do not use EEPROM.read elsewhere to maintain platform agnosticity
byte CMem::GetEEPROM(short address)
{
  return EEPROM.read(address);
}

byte CMem::GetKeyData(byte x, byte y, byte z)
{
  return GetEEPROM(((x + (y * Global.COL) + (z * Global.COL * Global.ROW)) * 2));
}

byte CMem::GetKeyType(byte x, byte y, byte z)
{
  return GetEEPROM(((x + (y * Global.COL) + (z * Global.COL * Global.ROW)) * 2) + 1);


}

byte CMem::GetRowCount()
{
  return GetEEPROM(MEM_ROW_COUNT);
}

byte CMem::GetColCount()
{
  return GetEEPROM(MEM_COL_COUNT);
}

byte CMem::GetLayCount()
{
  return GetEEPROM(MEM_LAY_COUNT);
}

byte CMem::GetRowPin(byte rowNo)
{
  return GetEEPROM(MEM_ROW_0 + rowNo);
}

byte CMem::GetColPin(byte colNo)
{
  return GetEEPROM(MEM_COL_0 + colNo);

}

byte CMem::GetBoardType()
{
  return GetEEPROM(MEM_BOARD_TYPE);
}

byte CMem::GetNKROType()
{
  return GetEEPROM(MEM_NKRO_MODE);
}

byte CMem::GetUSBHostType()
{
  return GetEEPROM(MEM_IS_USBHOST);
}

byte CMem::GetRefreshRate()
{
  return GetEEPROM(MEM_REFRESH_RATE);
}



// End of Getters


void CMem::End(void)
{

}

CMem PersMem;
