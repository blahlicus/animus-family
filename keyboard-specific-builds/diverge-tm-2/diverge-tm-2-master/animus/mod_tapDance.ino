// completed 5/27/2016 blahlicus
// this library enables a special key called a tap dance key, allowing one physical button to function as a number of keys depending on the number of taps
// example serial command: uniqueksettapdance(0(3(25(4(0(5(0(6(0

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

byte modMethod(PressTimer)[modMethod(MAX_INDEX)];
byte modMethod(PressCount)[modMethod(MAX_INDEX)];
boolean modMethod(KeyIsDown)[modMethod(MAX_INDEX)];



void modMethod(Startup)()
{
  // things to run during hardware startup
  for (int i = 0; i < modMethod(MAX_INDEX); i++)
  {
    modMethod(PressCount)[i] = 0;
    modMethod(PressTimer)[i] = 0;
    modMethod(KeyIsDown)[i] = false;
  }
}

void modMethod(Loop)()
{
  // full speed master loop


  // things inside this if statement is ran every RefreshDelay milliseconds
  if (CheckMillis())
  {
    if (IS_MASTER)
    {
      for (int i = 0; i < modMethod(MAX_INDEX); i++)
      {


        if (modMethod(PressCount)[i] > 0)
        {
          if (modMethod(PressTimer)[i] > 0)
          {
            modMethod(PressTimer)[i]--;
          }
          else
          {
            PressKey(modMethod(GetKeyVal)(i, modMethod(PressCount)[i] - 1), modMethod(GetKeyType)(i, modMethod(PressCount)[i] - 1));
            if (modMethod(KeyIsDown)[i])
            {
              // do nothing
            }
            else
            {
              modMethod(KeyUp)(i, 19);
            }
          }
        }
      }
    }


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
      if (modMethod(PressCount)[val] > modMethod(MAX_KEYS))
      {
        // do nothing
      }
      else
      {

        modMethod(PressCount)[val]++;
        modMethod(PressTimer)[val] = modMethod(GetTimeout)(val) * 2;
        modMethod(KeyIsDown)[val] = true;
      }

    }
  }
}

void modMethod(KeyUp)(char val, byte type)
{
  // ran when a key is pressed up


  // ran if this device's IS_MASTER flag is true
  if (IS_MASTER)
  {
    if (type == 19)
    {
      // sends the macro sequence with id = val
      ReleaseKey(modMethod(GetKeyVal)(val, modMethod(PressCount)[val] - 1), modMethod(GetKeyType)(val, modMethod(PressCount)[val] - 1));

      if (modMethod(KeyIsDown)[val])
      {
        // do nothing
      }
      else
      {

        modMethod(PressCount)[val] = 0;
        modMethod(PressTimer)[val] = 0;
      }
      modMethod(KeyIsDown)[val] = false;

    }
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

    modMethod(SetLength)(id, length);
    modMethod(SetTimeout)(id, delay);
    modMethod(SetKeyVal)(id, 0, key0val);
    modMethod(SetKeyVal)(id, 1, key1val);
    modMethod(SetKeyVal)(id, 2, key2val);
    modMethod(SetKeyType)(id, 0, key0type);
    modMethod(SetKeyType)(id, 1, key1type);
    modMethod(SetKeyType)(id, 2, key2type);



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
