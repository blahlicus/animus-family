// serial data
String inputData = "";

// serial functions start

void TestSerial()
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
      SerialCommand(inputData);
      inputData = "";
    }

    if (inputData.length() > 100)
    {
      inputData = "";
    }
  }
}

void SerialCommand(String input)
{
  if (input == "uniquekreqinfo")
  {
    Serial.println("DEPRECIATED");
  }
  if (input == "uniquekreqname")
  {
    Serial.println(builder_kbname);
  }
  if (input == "uniquekreqvariant")
  {
    Serial.println(builder_kbvariant);
  }
  if (input == "uniquekreqdriver")
  {
    Serial.println(builder_kbdriver);
  }
  if (input == "uniquekreqbuild")
  {
    Serial.println(builder_kbdriver_build);
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
    SetEEPROM(x, y, z, val, type);
    Serial.print("set key(");
    Serial.print(x);
    Serial.print("(");
    Serial.print(y);
    Serial.print("(");
    Serial.print(z);
    Serial.print("(");
    Serial.print(val);
    Serial.print("(");
    Serial.println(type);
  }
  else if (input.startsWith("uniquekseteeprom"))
  {
    input = input.substring(input.indexOf('(')+1);
    int addr = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte val = input.toInt();
    EEPROM.update(addr, val);
    Serial.print("set EEPROM(");
    Serial.print(addr);
    Serial.print("(");
    Serial.println(val);
  }
  else if (input.startsWith("uniqueksetlay"))
  {
    input = input.substring(input.indexOf('(')+1);
    byte val = input.toInt();

    if (val <= (600  / (ROW * COL)))
    {
      EEPROM.update(1023, val);
      Serial.print("set layer count(");
      Serial.println(val);
    }
    else
    {
      Serial.println("error: insufficient EEPROM");
    }

  }
  else if (input == "uniquekgetlay")
  {
    Serial.println(EEPROM.read(1023));
  }
  else if (input.startsWith("uniquekgeteeprom"))
  {
    
    input = input.substring(input.indexOf('(')+1);
    byte val = input.toInt();
    Serial.println(EEPROM.read(val));    
  }
  else if (input.startsWith("uniquekgetkey"))
  {
    input = input.substring(input.indexOf('(')+1);
    byte x = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte y = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte z = input.toInt();
    byte outVal = GetValEEPROM(x, y, z);
    byte outType = GetTypeEEPROM(x, y, z);
    Serial.print("return key(");
    Serial.print(outVal);
    Serial.print("(");
    Serial.println(outType);
  }
  else if (input.startsWith("uniquekgetrow"))
  {
    Serial.println(ROW);
  }
  else if (input.startsWith("uniquekgetcol"))
  {
    Serial.println(COL);
  }
  else if (input.startsWith("uniqueksetmaster"))
  {
    input = input.substring(input.indexOf('(')+1);
    byte out = input.toInt();
    if (out == 0)
    {
      IS_MASTER = false;
    }
    else
    {
      IS_MASTER = true;
    }
    Serial.print("set master(");
    Serial.print(IS_MASTER);
  }
  NKROSerial(input);
  ModSerial(input);
}

// serial functions end
