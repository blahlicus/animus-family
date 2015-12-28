// serial data
String inputData = "";

// serial functions start

void testSerial()
{
  if (Serial.available()>0)
  {
    char inputByte = (char)Serial.read();

    if (inputByte != ' ')
    {
      inputData += inputByte;
    }
    else
    {
      serialCommand(inputData);
      inputData = "";
    }
  }
}

void serialCommand(String input)
{
  if (input == "uniquekreqinfo")
  {
    Serial.println(KBINFO);
  }
}

// serial functions end
