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
  else if (input.startsWith("uniqueksetkey"))
  {
    input = input.substring(input.indexOf('(')+1);
    byte x = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte y = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte z = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte val = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte type = input.toInt();
    setEEPROM(x, y, z, val, type);
    Serial.print("key set: ");
    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.print(", ");
    Serial.print(z);
    Serial.print(", ");
    Serial.print(val);
    Serial.print(", ");
    Serial.println(type);
  }
}

// serial functions end
