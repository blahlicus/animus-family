// WORK IN PROGRESS

/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
EEPROM(801-820)
keytype(8)
BUILDER_REQUIREMENT_END
Remeber to change the mod_modname to your mod name
*/



#define mod_modname AdaptiveMod


const int AdaptiveModMinAddr = 801;
const int MaxAdaptiveMod = 18;

#define modMethod(str) conca(mod_modname, str)

void modMethod(Startup)()
{
  // things to run during hardware startup
}

void modMethod(Loop)()
{
  // full speed master loop


  // things inside this if statement is ran every RefreshDelay milliseconds
  if (CheckMillis())
  {

  }
}

void modMethod(KeyDown)(char val, byte type)
{
  // ran when a key is pressed down


  // ran if this device's IS_MASTER flag is true
  if (IS_MASTER)
  {
    if (type == 8)
    {
      byte switchLay = val & 0xf; // splits byte and get first 4 bits as number

      PressedKey = false;
      TempLayer = switchLay; // switches layer when key is held
      ReleaseAllKey();

    }
  }
}

void modMethod(KeyUp)(char val, byte type)
{
  // ran when a key is pressed up


  // ran if this device's IS_MASTER flag is true
  if (IS_MASTER)
  {
    if (type == 8)
    {

      byte AdapterID = (val > 4) & 0xf; // splits byte and get last 4 bits
      if (PressedKey == false)
      {
        Keyboard.write(modMethod(GetEEPROM)(AdapterID)); // outputs key from EEPROM
      }
      TempLayer = KeyLayer; // resets layer back to default
      ReleaseAllKey(); // DEPRECIATED END
    }
  }
}

void modMethod(Serial)(String input)
{
  // ran when serial command of input is sent to device from host

  if (input.startsWith("uniquekgetmods")) // do not delete this as this is for the identifier
  {
    Serial.print(tokenToString(mod_modname));
  }
  else if (input.startsWith("uniqueksetadaptivekey"))
  {

    input = input.substring(input.indexOf('(')+1);
    byte x = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte y = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte z = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte lay = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte id = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte type = input.toInt();

    byte val = (lay << 4) | id;

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
  else if (input.startsWith("uniquekgetadaptivechar"))
  {

    input = input.substring(input.indexOf('(')+1);
    byte id = input.toInt();

    Serial.print("get adaptive char(");
    Serial.println(modMethod(GetEEPROM)(id));


  }
  else if (input.startsWith("uniqueksetadaptivechar"))
  {

    input = input.substring(input.indexOf('(')+1);
    byte id = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte val = input.toInt();

    if (id < MaxAdaptiveMod)
    {
      modMethod(SetEEPROM)(id, val);

      Serial.print("set adaptive char(");
      Serial.print(id);
      Serial.print("(");
      Serial.println(val);
    }
    else
    {
      Serial.print("fail adaptive char(");
      Serial.print(id);
      Serial.print("(");
      Serial.println(val);
    }
  }

}

int modMethod(GetEEPROM)(int id)
{
  int addr = AdaptiveModMinAddr + id;
  return EEPROM.read(addr);
}

int modMethod(SetEEPROM)(int id, int input)
{
  int addr = AdaptiveModMinAddr + id;
  EEPROM.update(addr, input);
}


#undef mod_modname
#undef modMethod
