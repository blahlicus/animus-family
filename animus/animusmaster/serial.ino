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

    if (inputData.length() > 100)
    {
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
  else if (input.startsWith("uniquekseteeprom"))
  {
    input = input.substring(input.indexOf('(')+1);
    int addr = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte val = input.toInt();
    EEPROM.write(addr, val);
    Serial.print("Wrote to EEPROM: ");
    Serial.print(addr);
    Serial.print(", ");
    Serial.println(val);
  }
  else if (input.startsWith("uniqueksetlay"))
  {
    input = input.substring(input.indexOf('(')+1);
    byte val = input.toInt();

    if (val <= (500  / (ROW * COL)))
    {
      EEPROM.write(1023, val);
      Serial.print("Edited layer count to: ");
      Serial.println(val);
    }
    else
    {
      Serial.println("Layer count edit aborted, insufficient EEPROM");
    }

  }
  else if (input == "uniquekgetlay")
  {
    Serial.println(EEPROM.read(1023));
  }
}

// serial functions end
