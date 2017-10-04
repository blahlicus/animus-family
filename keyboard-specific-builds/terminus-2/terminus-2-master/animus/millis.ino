
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
boolean readyMillis = false;
#define MILLIS_TICK 1
void MillisLoop()
{
  currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= MILLIS_TICK)
  {
    previousMillis = currentMillis;
    readyMillis = true;
  }
  else
  {
    readyMillis = false;
  }
}

boolean CheckMillis()
{
  return readyMillis;
}
