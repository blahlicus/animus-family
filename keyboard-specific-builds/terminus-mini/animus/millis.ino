
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
boolean readyMillis = false;
void millisLoop()
{
  currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= refreshDelay)
  {
    previousMillis = currentMillis;
    readyMillis = true;
  }
  else
  {
    readyMillis = false;
  }
}

boolean checkMillis()
{
  return readyMillis;
}
