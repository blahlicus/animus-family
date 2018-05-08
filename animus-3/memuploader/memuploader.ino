#include "Comms.h"
void setup()
{
  Comms.Begin(19200);
}

void loop()
{
  Comms.Loop();

}
