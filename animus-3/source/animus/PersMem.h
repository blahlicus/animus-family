#ifndef ANIMUS_MEM
#define ANIMUS_MEM

// TODO redo this and delete the dynamic configurations
#if defined (ARDUINO_AVR_LEONARDO) // this is running on an Atmega32u4
#include "EEPROM.h"
#define MEM_EEPROM_SIZE 1024
#define MEM_NKRO_MODE MEM_EEPROM_SIZE - 124
#define MEM_LAY_COUNT MEM_EEPROM_SIZE - 123
#define MEM_IS_USBHOST MEM_EEPROM_SIZE - 122
#define MEM_DYNAMIC_ADDR MEM_EEPROM_SIZE - 121

#elif defined (ARDUINO_SAMD_ZERO) // this is running on SAMD

// note: because of this bug, the FlashAsEEPROM library is moved to its separate folder
//TODO create in-house builder for platform specific code
#include "FlashAsEEPROM.h" //NOTE: The Atmega32u4 version is not supposed to include this, but the Arduino precompiler sucks and it is included anyway


#define MEM_EEPROM_SIZE EEPROM_EMULATION_SIZE // retrieved from FlashAsEEPROM
#define MEM_NKRO_MODE MEM_EEPROM_SIZE - 124
#define MEM_LAY_COUNT MEM_EEPROM_SIZE - 123
#define MEM_IS_USBHOST MEM_EEPROM_SIZE - 122
#define MEM_DYNAMIC_ADDR MEM_EEPROM_SIZE - 121

#else
#error unknown target device
#endif

#include "Global.h"


class CMem
{
private:
  //TODO remove these private methods when it is confirmed that these aren't used elsewhere
  void SetKey(byte x, byte y, byte z, byte inputChar, byte inputType);
public:
  CMem(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void SetEEPROM(short address, byte data);
  void SetEEPROMForced(short address, byte data);
  void CommitEEPROM(void); // This is used for SAMD21 devices only


  byte GetEEPROM(short address);
  byte GetKeyData(byte x, byte y, byte z);
  byte GetKeyType(byte x, byte y, byte z);
  byte GetLayCount();
  byte GetNKROType();
  byte GetUSBHostType();

  byte GetModData(short addr, byte modNo);
  
  void SetLayCount(byte input);
  void SetNKROType(byte input);
  void SetUSBHostType(byte input);

  void End(void);
};
extern CMem PersMem;

#endif
