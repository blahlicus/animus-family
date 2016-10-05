
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
boolean readyMillis = false;
void MillisLoop()
{
  currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= RefreshDelay)
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
