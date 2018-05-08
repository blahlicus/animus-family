#ifndef ANIMUS_SERIAL
#define ANIMUS_SERIAL
#include "PersMem.h"
#define COMM_KEY_0 0
#define COMM_KEY_1 1
#define COMM_KEY_2 2
#define COMM_KEY_3 3



class CSerial
{
private:
  int loadCounter;
  byte preloadCounter;
  byte buffer[5];
public:
  byte mode;

  CSerial(void);
  void Begin(int baud);
  void Loop(void);
  void End(void);
};
extern CSerial Comms;

#endif
