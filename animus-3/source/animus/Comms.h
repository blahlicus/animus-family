#ifndef ANIMUS_SERIAL
#define ANIMUS_SERIAL
#include "PersMem.h"
#define COMM_KEY_0 0
#define COMM_KEY_1 1
#define COMM_KEY_2 2
#define COMM_KEY_3 3

#if defined (ARDUINO_SAMD_ZERO) // this is running on SAMD
#define Serial SerialUSB
#else
#error unknown target device
#endif

class CSerial
{
private:
  short loadCounter = 0;
  byte keyMode = 0;

  // used byte mode 8 only
  short startAddress = -2;
  short inputLength = -2;
  byte startByte = 0;
public:
  byte mode;

  CSerial(void);
  void Begin(int baud);
  void Loop(void);
  void End(void);
};
extern CSerial Comms;

#endif
