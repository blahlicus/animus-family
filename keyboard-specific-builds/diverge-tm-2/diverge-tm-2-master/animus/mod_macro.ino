// completed 5/27/2016 blahlicus
// this library helps
// example serial command: uniqueksetmacro(0(4(97(0(0(98(0(0(99(0(0(100(0(0(97(0(1(98(0(1(99(0(1(100(0(1(0

/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
EEPROM(600,800)
Keytype(7)
BUILDER_REQUIREMENT_END
Remeber to change the mod_modname to your mod name
*/


#define mod_modname macro


const int macroMinAddr = 600;
const int macroMaxAddr = 800;
const byte macroMAX_MACROS = 12;
const byte macroMAX_KEYS = 8;
const byte macroSERIES_PADDING = 2;
const byte macroKEY_DOWN = 0;
const byte macroKEY_UP = 1;

int macroDelay = 5;

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
    if (type == 7)
    {
      // sends the macro sequence with id = val
      modMethod(Send)(val);
    }
  }
}

void modMethod(KeyUp)(char val, byte type)
{
  // ran when a key is pressed up


  // ran if this device's IS_MASTER flag is true
  if (IS_MASTER)
  {
  }
}

void modMethod(Serial)(String input)
{
  // ran when serial command of input is sent to device from host

  // do not delete this as this is for the identifier
  if (input.startsWith("uniquekgetmods"))
  {
    Serial.print(tokenToString(mod_modname));
  }
  else if (input.startsWith("uniqueksetmacro"))
  {
    byte key, type, state;

    input = input.substring(input.indexOf('(')+1);
    byte id = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte length = input.substring(0, input.indexOf('(')).toInt();

    modMethod(SetMacroLength)(id, length);

    for (int i = 0; i < macroMAX_KEYS; i++)
    {
      input = input.substring(input.indexOf('(')+1);
      key = input.substring(0, input.indexOf('(')).toInt();
      modMethod(SetKeyVal)(id, i, key);
      input = input.substring(input.indexOf('(')+1);
      type = input.substring(0, input.indexOf('(')).toInt();
      modMethod(SetKeyType)(id, i, type);
      input = input.substring(input.indexOf('(')+1);
      state = input.substring(0, input.indexOf('(')).toInt();
      modMethod(SetKeyDownUp)(id, i, state);
    }

    input = input.substring(input.indexOf('(')+1);
    byte overflow = input.toInt();

    Serial.print("set macro(");
    Serial.print(id);
    Serial.print("(");
    Serial.println(length);
  }

}

void modMethod(Send)(int id)
{
  if (id < macroMAX_MACROS)
  {
    byte length = modMethod(GetMacroLength)(id);
    for (int i = 0; i < length; i++)
    {
      if (modMethod(GetKeyDownUp)(id, i) == macroKEY_DOWN)
      {
        PressKey( modMethod(GetKeyVal)(id, i), modMethod(GetKeyType)(id, i) );
      }
      else if (modMethod(GetKeyDownUp)(id, i) == macroKEY_UP)
      {
        ReleaseKey( modMethod(GetKeyVal)(id, i), modMethod(GetKeyType)(id, i) );
      }
      delay(macroDelay);
    }
    ReleaseAllKey();
  }
}

char modMethod(GetKeyVal)(int id, byte key)
{
  char output = 0;
  if (id < macroMAX_MACROS)
  {
    int addr = modMethod(GetMacroStartAddr)(id);
    output = EEPROM.read(addr + macroSERIES_PADDING + key * 2);
  }
  return output;
}

void modMethod(SetKeyVal)(int id, byte key, byte val)
{
  if (id < macroMAX_MACROS && key < macroMAX_KEYS)
  {
    int addr = modMethod(GetMacroStartAddr)(id);
    EEPROM.update(addr + macroSERIES_PADDING + key * 2, val);
  }
}

byte modMethod(GetKeyType)(int id, byte key)
{
  char output = 0;
  if (id < macroMAX_MACROS && key < macroMAX_KEYS)
  {
    int addr = modMethod(GetMacroStartAddr)(id);
    output = EEPROM.read(addr + macroSERIES_PADDING + key * 2 + 1);
  }
  return output;
}

void modMethod(SetKeyType)(int id, byte key, byte val)
{
  if (id < macroMAX_MACROS && key < macroMAX_KEYS)
  {
    int addr = modMethod(GetMacroStartAddr)(id);
    EEPROM.update(addr + macroSERIES_PADDING + key * 2 + 1, val);
  }
}


byte modMethod(GetKeyDownUp)(int id, byte key)
{
  byte output = 2;
  if (id < macroMAX_MACROS)
  {
    int addr = modMethod(GetMacroStartAddr)(id);
    output = bitRead(EEPROM.read(addr), key);
  }
  return output;
}

void modMethod(SetKeyDownUp)(int id, byte key, byte bitState)
{
  if (id < macroMAX_MACROS && key < macroMAX_KEYS)
  {
    int addr = modMethod(GetMacroStartAddr)(id);
    byte keyStates = EEPROM.read(addr);
    bitWrite(keyStates, key, bitState);
    EEPROM.update(addr, keyStates);
  }
}

byte modMethod(GetMacroLength)(int id)
{
  byte output = 0;
  if (id < macroMAX_MACROS)
  {
    int addr = modMethod(GetMacroStartAddr)(id);
    output = EEPROM.read(addr + 1);
  }
  return output;
}

void modMethod(SetMacroLength)(int id, byte newLength)
{
  if (id < macroMAX_MACROS && newLength <= macroMAX_KEYS)
  {
    int addr = modMethod(GetMacroStartAddr)(id);
    EEPROM.update(addr + 1, newLength);
  }
}

int modMethod(GetMacroStartAddr)(int id)
{
    int addr = macroMinAddr + (id * (macroMAX_KEYS * 2 + macroSERIES_PADDING));
    return addr;
}


#undef mod_modname
#undef modMethod
