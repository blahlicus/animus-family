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
  Global.LAY = GetLayCount();
  if (Global.LAY == 255) // if EEPROM data is not set, then load default values
  {
    SetLayCount(1);
    Global.LAY = GetLayCount();
    //* default
    SetUSBHostType(1); // set mode to USB host
    SetNKROType(0); // set KRO mode to 6KRO
  }
  Global.HasUSB = GetUSBHostType();
  Global.NKROMode = GetNKROType();
  Global.RequiresLoadData = true; // loads mod EEPROM addresses to SRAM


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

void CMem::SetLayCount(byte input)
{
  SetEEPROM(MEM_LAY_COUNT, input);

}

void CMem::SetNKROType(byte input)
{
  SetEEPROM(MEM_NKRO_MODE, input);

}

void CMem::SetUSBHostType(byte input)
{
  SetEEPROM(MEM_IS_USBHOST, input);
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

byte CMem::GetLayCount()
{
  return GetEEPROM(MEM_LAY_COUNT);
}

byte CMem::GetNKROType()
{
  return GetEEPROM(MEM_NKRO_MODE);
}

byte CMem::GetUSBHostType()
{
  return GetEEPROM(MEM_IS_USBHOST);
}
// End of Getters


void CMem::End(void)
{

}

CMem PersMem;
