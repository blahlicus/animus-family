#ifndef ANIMUS_MEM
#define ANIMUS_MEM

#if defined (ARDUINO_AVR_LEONARDO) // this is running on an Atmega32u4
#define MEM_EEPROM_SIZE 1024
#define MEM_BOARD_TYPE MEM_EEPROM_SIZE - 124
#define MEM_REFRESH_RATE MEM_EEPROM_SIZE - 123
#define MEM_ROW_COUNT MEM_EEPROM_SIZE - 122
#define MEM_COL_COUNT MEM_EEPROM_SIZE - 121
#define MEM_ROW_0 MEM_EEPROM_SIZE - 120
#define MEM_ROW_1 MEM_EEPROM_SIZE - 119
#define MEM_ROW_2 MEM_EEPROM_SIZE - 118
#define MEM_ROW_3 MEM_EEPROM_SIZE - 117
#define MEM_ROW_4 MEM_EEPROM_SIZE - 116
#define MEM_ROW_5 MEM_EEPROM_SIZE - 115
#define MEM_ROW_6 MEM_EEPROM_SIZE - 114
#define MEM_ROW_7 MEM_EEPROM_SIZE - 113
#define MEM_ROW_8 MEM_EEPROM_SIZE - 112
#define MEM_ROW_9 MEM_EEPROM_SIZE - 111
#define MEM_ROW_10 MEM_EEPROM_SIZE - 110
#define MEM_ROW_11 MEM_EEPROM_SIZE - 109
#define MEM_ROW_12 MEM_EEPROM_SIZE - 108
#define MEM_ROW_13 MEM_EEPROM_SIZE - 107
#define MEM_ROW_14 MEM_EEPROM_SIZE - 106
#define MEM_ROW_15 MEM_EEPROM_SIZE - 105
#define MEM_ROW_16 MEM_EEPROM_SIZE - 104
#define MEM_ROW_17 MEM_EEPROM_SIZE - 103
#define MEM_ROW_18 MEM_EEPROM_SIZE - 102
#define MEM_ROW_19 MEM_EEPROM_SIZE - 101
#define MEM_COL_0 MEM_EEPROM_SIZE - 100
#define MEM_COL_1 MEM_EEPROM_SIZE - 99
#define MEM_COL_2 MEM_EEPROM_SIZE - 98
#define MEM_COL_3 MEM_EEPROM_SIZE - 97
#define MEM_COL_4 MEM_EEPROM_SIZE - 96
#define MEM_COL_5 MEM_EEPROM_SIZE - 95
#define MEM_COL_6 MEM_EEPROM_SIZE - 94
#define MEM_COL_7 MEM_EEPROM_SIZE - 93
#define MEM_COL_8 MEM_EEPROM_SIZE - 92
#define MEM_COL_9 MEM_EEPROM_SIZE - 91
#define MEM_COL_10 MEM_EEPROM_SIZE - 90
#define MEM_COL_11 MEM_EEPROM_SIZE - 89
#define MEM_COL_12 MEM_EEPROM_SIZE - 88
#define MEM_COL_13 MEM_EEPROM_SIZE - 87
#define MEM_COL_14 MEM_EEPROM_SIZE - 86
#define MEM_COL_15 MEM_EEPROM_SIZE - 85
#define MEM_COL_16 MEM_EEPROM_SIZE - 84
#define MEM_COL_17 MEM_EEPROM_SIZE - 83
#define MEM_COL_18 MEM_EEPROM_SIZE - 82
#define MEM_COL_19 MEM_EEPROM_SIZE - 81
#define MEM_NKRO_MODE MEM_EEPROM_SIZE - 80
#define MEM_LAY_COUNT MEM_EEPROM_SIZE - 79
#define MEM_IS_USBHOST MEM_EEPROM_SIZE - 78
#define MEM_DYNAMIC_ADDR MEM_EEPROM_SIZE - 74

#elif defined (ARDUINO_SAMD_ZERO) // this is running on SAMD

// note: because of this bug, the FlashAsEEPROM library is moved to its separate folder
//TODO create in-house builder for platform specific code
#include <FlashAsEEPROM.h> //NOTE: The Atmega32u4 version is not supposed to include this, but the Arduino precompiler sucks and it is included anyway


#define MEM_EEPROM_SIZE EEPROM_EMULATION_SIZE // retrieved from FlashAsEEPROM
#define MEM_BOARD_TYPE MEM_EEPROM_SIZE - 124
#define MEM_REFRESH_RATE MEM_EEPROM_SIZE - 123
#define MEM_ROW_COUNT MEM_EEPROM_SIZE - 122
#define MEM_COL_COUNT MEM_EEPROM_SIZE - 121
#define MEM_ROW_0 MEM_EEPROM_SIZE - 120
#define MEM_ROW_1 MEM_EEPROM_SIZE - 119
#define MEM_ROW_2 MEM_EEPROM_SIZE - 118
#define MEM_ROW_3 MEM_EEPROM_SIZE - 117
#define MEM_ROW_4 MEM_EEPROM_SIZE - 116
#define MEM_ROW_5 MEM_EEPROM_SIZE - 115
#define MEM_ROW_6 MEM_EEPROM_SIZE - 114
#define MEM_ROW_7 MEM_EEPROM_SIZE - 113
#define MEM_ROW_8 MEM_EEPROM_SIZE - 112
#define MEM_ROW_9 MEM_EEPROM_SIZE - 111
#define MEM_ROW_10 MEM_EEPROM_SIZE - 110
#define MEM_ROW_11 MEM_EEPROM_SIZE - 109
#define MEM_ROW_12 MEM_EEPROM_SIZE - 108
#define MEM_ROW_13 MEM_EEPROM_SIZE - 107
#define MEM_ROW_14 MEM_EEPROM_SIZE - 106
#define MEM_ROW_15 MEM_EEPROM_SIZE - 105
#define MEM_ROW_16 MEM_EEPROM_SIZE - 104
#define MEM_ROW_17 MEM_EEPROM_SIZE - 103
#define MEM_ROW_18 MEM_EEPROM_SIZE - 102
#define MEM_ROW_19 MEM_EEPROM_SIZE - 101
#define MEM_COL_0 MEM_EEPROM_SIZE - 100
#define MEM_COL_1 MEM_EEPROM_SIZE - 99
#define MEM_COL_2 MEM_EEPROM_SIZE - 98
#define MEM_COL_3 MEM_EEPROM_SIZE - 97
#define MEM_COL_4 MEM_EEPROM_SIZE - 96
#define MEM_COL_5 MEM_EEPROM_SIZE - 95
#define MEM_COL_6 MEM_EEPROM_SIZE - 94
#define MEM_COL_7 MEM_EEPROM_SIZE - 93
#define MEM_COL_8 MEM_EEPROM_SIZE - 92
#define MEM_COL_9 MEM_EEPROM_SIZE - 91
#define MEM_COL_10 MEM_EEPROM_SIZE - 90
#define MEM_COL_11 MEM_EEPROM_SIZE - 89
#define MEM_COL_12 MEM_EEPROM_SIZE - 88
#define MEM_COL_13 MEM_EEPROM_SIZE - 87
#define MEM_COL_14 MEM_EEPROM_SIZE - 86
#define MEM_COL_15 MEM_EEPROM_SIZE - 85
#define MEM_COL_16 MEM_EEPROM_SIZE - 84
#define MEM_COL_17 MEM_EEPROM_SIZE - 83
#define MEM_COL_18 MEM_EEPROM_SIZE - 82
#define MEM_COL_19 MEM_EEPROM_SIZE - 81
#define MEM_NKRO_MODE MEM_EEPROM_SIZE - 80
#define MEM_LAY_COUNT MEM_EEPROM_SIZE - 79
#define MEM_IS_USBHOST MEM_EEPROM_SIZE - 78
#define MEM_DYNAMIC_ADDR MEM_EEPROM_SIZE - 74

#else
#error unknown target device
#endif

#include "Global.h"


class CMem
{
private:
  //TODO remove these private methods when it is confirmed that these aren't used elsewhere
  void SetKey(byte x, byte y, byte z, byte inputChar, byte inputType);
  void SetRowCount(byte input);
  void SetColCount(byte input);
  void SetLayCount(byte input);
  void SetRowPin(byte pinNo, byte rowNo);
  void SetColPin(byte pinNo, byte colNo);
  void SetBoardType(byte input);
  void SetNKROType(byte input);
  void SetUSBHostType(byte input);
  void SetRefreshRate(byte input);
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
  byte GetRowCount();
  byte GetColCount();
  byte GetLayCount();
  byte GetRowPin(byte rowNo);
  byte GetColPin(byte colNo);
  byte GetBoardType();
  byte GetNKROType();
  byte GetUSBHostType();
  byte GetRefreshRate();

  byte GetModData(short addr, byte modNo);

  void Serial(String input);
  void End(void);
};
extern CMem PersMem;

#endif
