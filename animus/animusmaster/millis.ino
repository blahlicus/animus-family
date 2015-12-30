
unsigned long previousMillis = 0;

void millisLoop()
{
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= refreshDelay)
  {
    previousMillis = currentMillis;
  }
}

boolean checkMillis()
{
  unsigned long currentMillis = millis();
  boolean output = ((unsigned long)(currentMillis - previousMillis) >= refreshDelay);
  return output;
}
