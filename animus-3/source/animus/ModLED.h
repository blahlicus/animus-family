#ifndef ANIMUS_MOD_MODLED
#define ANIMUS_MOD_MODLED
#define LED_PIN_MEM 0
#define LED_COUNT_MEM 1
#define LED_MAX_BRIGHTNESS 180
#include "ModTemplate.h"
#include "Animus.h"
#define FASTLED_FORCE_SOFTWARE_SPI
#include <FastLED.h>

class CModLED : public CModTemplate
{
private:
  bool Enabled = true;
  CRGB LEDs[255];
  uint8_t LEDCount = 0;
  byte LEDPreviousBrightness = 0;
  short RefreshCounter = 500;
public:
  CModLED(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PressCoords(byte x, byte y);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);

  void InitiateLED(void);
  void RefreshLED(void);

};
extern CModLED ModLED;

#endif
