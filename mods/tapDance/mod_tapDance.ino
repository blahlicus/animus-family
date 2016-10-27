// completed 5/27/2016 blahlicus
// this library helps
// example serial command: uniqueksetmacro(0(4(97(0(0(98(0(0(99(0(0(100(0(0(97(0(1(98(0(1(99(0(1(100(0(1(0

/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
EEPROM(842,982)
Keytype(19)
BUILDER_REQUIREMENT_END
Remeber to change the mod_modname to your mod name
*/


#define mod_modname tapDance

#define modMethod(str) conca(mod_modname, str)

const int modMethod(MAX_ADDR) = 842;
const int modMethod(MIN_ADDR) = 982;
const byte modMethod(MAX_INDEX) = 20;
const byte modMethod(MAX_KEYS) = 3;
const byte modMethod(PADDING) = 2;

int modMethod(PressTimer)[modMethod(MAX_INDEX)];
int modMethod(PressCount)[modMethod(MAX_INDEX)];




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
    if (type == 19)
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
  else if (input.startsWith("uniqueksettapdance"))
  {
    byte key, type, state;

    input = input.substring(input.indexOf('(')+1);
    byte id = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte length = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte delay = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte key0val = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte key0type = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte key1val = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte key1type = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte key2val = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte key2type = input.toInt();

    Serial.print("set tapdance(");
    Serial.print(id);
    Serial.print("(");
    Serial.print(length);
    Serial.print("(");
    Serial.print(delay);
    Serial.print("(");
    Serial.print(key0val);
    Serial.print("(");
    Serial.print(key0type);
    Serial.print("(");
    Serial.print(key1val);
    Serial.print("(");
    Serial.print(key1type);
    Serial.print("(");
    Serial.print(key2val);
    Serial.print("(");
    Serial.println(key2type);
  }

}

// TODO
byte modMethod(GetLength)(int id)
{

    byte output = 0;
    if (id < modMethod(MAX_INDEX))
    {
      int addr = modMethod(GetStartAddr)(id);
      byte main = EEPROM.read(addr);
      output = main & 3;
    }
    return output;
}

void modMethod(SetLength)(int id, byte val)
{

  if (id < modMethod(MAX_INDEX))
  {
    int addr = modMethod(GetStartAddr)(id);
    EEPROM.update(addr, val + (modMethod(GetTimeout)(id) << 2) );
  }
}

byte modMethod(GetTimeout)(int id)
{

      byte output = 0;
      if (id < modMethod(MAX_INDEX))
      {
        int addr = modMethod(GetStartAddr)(id);
        byte main = EEPROM.read(addr);
        output = (main >> 2) & 63;
      }
      return output;
}

void modMethod(SetTimeout)(int id, byte val)
{

  if (id < modMethod(MAX_INDEX))
  {
    int addr = modMethod(GetStartAddr)(id);
    EEPROM.update(addr, modMethod(GetLength)(id) + (val << 2) );
  }
}

// TODO remove later
void modMethod(Send)(int id)
{
  if (id < modMethod(MAX_INDEX))
  {
    byte length = modMethod(GetLength)(id);
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
  if (id < modMethod(MAX_INDEX) && key < modMethod(MAX_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    byte keyStates = EEPROM.read(addr);
    bitWrite(keyStates, key, bitState);
    EEPROM.update(addr, keyStates);
  }
}
// TODO remove later ends



// key LL functions start
char modMethod(GetKeyVal)(int id, byte key)
{
  byte output = 0;
  if (id < modMethod(MAX_INDEX) && key < modMethod(MAX_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    output = EEPROM.read(addr + modMethod(PADDING) + key * 2);
  }
  return output;
}

void modMethod(SetKeyVal)(int id, byte key, byte val)
{
  if (id < modMethod(MAX_INDEX) && key < modMethod(MAX_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    EEPROM.update(addr + modMethod(PADDING) + key * 2, val);
  }
}

byte modMethod(GetKeyType)(int id, byte key)
{
  byte output = 0;
  if (id < modMethod(MAX_INDEX) && key < modMethod(MAX_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    output = EEPROM.read(addr + modMethod(PADDING) + key * 2 + 1);
  }
  return output;
}

void modMethod(SetKeyType)(int id, byte key, byte val)
{
  if (id < modMethod(MAX_INDEX) && key < modMethod(MAX_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    EEPROM.update(addr + modMethod(PADDING) + key * 2 + 1, val);
  }
}

/* not used for this set
byte modMethod(GetLength)(int id)
{
  byte output = 0;
  if (id < modMethod(MAX_INDEX))
  {
    int addr = modMethod(GetStartAddr)(id);
    output = EEPROM.read(addr + 1);
  }
  return output;
}

void modMethod(SetLength)(int id, byte newLength)
{
  if (id < modMethod(MAX_INDEX) && newLength <= modMethod(MAX_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    EEPROM.update(addr + 1, newLength);
  }
}
*/

int modMethod(GetStartAddr)(int id)
{
  int addr = modMethod(MAX_ADDR) + (id * (modMethod(MAX_KEYS) * 2 + modMethod(PADDING)));
  return addr;
}

// key LL functions stop

#undef mod_modname
#undef modMethod
