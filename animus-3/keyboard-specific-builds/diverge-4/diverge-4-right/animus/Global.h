// constants such as pin counts, the pin array, and the refresh delays will be #defined here
// note to future self: I originally implemented dynamic pin addressing and configuration
// via EEPROM, but really it is not worth the effort for that, don't do it


// Make sure builder_kbfirmware is under the format "Animus [x/v][xx].[xx].[xx]" use x to denote prototype and use v to denote stable release
#define BUILDER_FIRMWARE_HANDLE "Animus x3.1.0"
#define BUILDER_HARDWARE_HANDLE "Diverge 4 Right"
// the test configuration is configured for the Diverge 4 left side
#define BUILDER_ROW 6
#define BUILDER_COL 7
#define BUILDER_VPIN 6, 22, 8, 17, 15, 14
#define BUILDER_HPIN 12, 19, 9, 18, 16, 2, 5

#define BUILDER_PRESS_COOLDOWN 5
#define BUILDER_RELEASE_COOLDOWN 2

#define I2C_HOST_ADDRESS 7
#define I2C_GUEST_ADDRESS 8

// for LED mode, use 0 for no LED, 1 for second generation device LED (solo colour) 2 for RGB LED via WS2811
#define BUILDER_LED_MODE 2


#ifndef ANIMUS_GLOBAL
#define ANIMUS_GLOBAL
#include "Arduino.h"

class CGlobal
{
private:
public:
  byte ModCount = 0; // always starts at 0
  byte KeyDownDelay = BUILDER_PRESS_COOLDOWN; // configured from #define
  byte KeyUpDelay = BUILDER_RELEASE_COOLDOWN; // configured from #define
  byte ROW = BUILDER_ROW; // configured from #define
  byte COL = BUILDER_COL; // configured from #define
  byte LAY = 1; // default value, overriden on EEPROM load

  byte VPins[BUILDER_ROW] = {BUILDER_VPIN}; // configured from #define
  byte HPins[BUILDER_COL] = {BUILDER_HPIN}; // configured from #define


  byte KeyLayer = 0;
  byte TempLayer = 0;


  byte KeyState[BUILDER_COL][BUILDER_ROW];
  byte KeyStateCoolDown[BUILDER_COL][BUILDER_ROW];
  byte PreviousState[BUILDER_COL][BUILDER_ROW];
  byte LayerState[BUILDER_COL][BUILDER_ROW];

  bool HasUSB = false; // default state of USB comms, used to differentiate between the host and guest for split keyboards
  bool RequiresLoadData = false; // I am soo sorry for the spaghetti

  byte NKROMode = 0; // default state as 6KRO, will load from EEPROM
  byte LEDBrightness = 127;


  unsigned long PreviousMillis = 0;
  unsigned long CurrentMillis = 0;
  bool ReadyMillis = false;
  void MillisLoop(void);

  CGlobal(void);
};
extern CGlobal Global;

#endif
