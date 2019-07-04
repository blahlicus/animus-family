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


const byte modMethod(TIMER_MULTIPLIER) = 50;
const int modMethod(MAX_ADDR) = 842;
const int modMethod(MIN_ADDR) = 982;
const byte modMethod(MAX_INDEX) = 20;
const byte modMethod(MAX_KEYS) = 3;
const byte modMethod(PADDING) = 2;

int16_t modMethod(PressTimer)[modMethod(MAX_INDEX)];
byte modMethod(PressCount)[modMethod(MAX_INDEX)];
boolean modMethod(KeyIsDown)[modMethod(MAX_INDEX)];



void modMethod(Startup)()
{
  // things to run during hardware startup
  for (byte i = 0; i < modMethod(MAX_INDEX); i++)
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
      for (byte i = 0; i < modMethod(MAX_INDEX); i++)
      {


        if (modMethod(PressCount)[i] > 0)
        {
          if (modMethod(PressTimer)[i] > 0)
          {
            modMethod(PressTimer)[i]--;
          }
          else if (modMethod(PressTimer)[i] == 0)
          {
            modMethod(FireTapDance)(i);
            if (!modMethod(KeyIsDown)[i])
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
      if (modMethod(PressCount)[val] < modMethod(MAX_KEYS))
      {
        byte count = ++modMethod(PressCount)[val]; // count gets the *new* count value
        modMethod(PressTimer)[val] = modMethod(GetTimeout)(val) * modMethod(TIMER_MULTIPLIER);
        modMethod(KeyIsDown)[val] = true;

        if (count == modMethod(MAX_KEYS))
        {
          // no more tap dance keys; fire immediately
          modMethod(FireTapDance)(val);
        }
        else
        {
          // check the key that would come after this one
          char tdVal = modMethod(GetKeyVal)(val, count);
          byte tdType = modMethod(GetKeyType)(val, count);

          if (tdVal == 0 && tdType == 0)
          {
            // no more tap dance keys; fire immediately
            modMethod(FireTapDance)(val);
          }
        }
      }
    }
  }
}

void modMethod(PrePress)(char val, byte type)
{
  if (IS_MASTER)
  {
    for (byte i = 0; i < modMethod(MAX_INDEX); i++)
    {
      if ((type != 19 || val != i) && modMethod(PressTimer)[i] > 0)
      {
        modMethod(FireTapDance)(i);
        if (!modMethod(KeyIsDown)[i])
        {
          modMethod(KeyUp)(i, 19);
        }
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
      // if key has been fired
      if (modMethod(PressTimer)[val] < 0)
      {
        byte count = modMethod(PressCount)[val] - 1;
        char tdVal = modMethod(GetKeyVal)(val, count);
        byte tdType = modMethod(GetKeyType)(val, count);

        ReleaseKey(tdVal, tdType);
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

void modMethod(FireTapDance)(byte id)
{
  byte count = modMethod(PressCount)[id] - 1;
  char val = modMethod(GetKeyVal)(id, count);
  byte type = modMethod(GetKeyType)(id, count);
  modMethod(PressTimer)[id] = -1; // signal that the key has fired
  PressKey(val, type);
}

byte modMethod(GetLength)(byte id)
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

void modMethod(SetLength)(byte id, byte val)
{

  if (id < modMethod(MAX_INDEX))
  {
    int addr = modMethod(GetStartAddr)(id);
    EEPROM.update(addr, val + (modMethod(GetTimeout)(id) << 2) );
  }
}

byte modMethod(GetTimeout)(byte id)
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

void modMethod(SetTimeout)(byte id, byte val)
{

  if (id < modMethod(MAX_INDEX))
  {
    int addr = modMethod(GetStartAddr)(id);
    EEPROM.update(addr, modMethod(GetLength)(id) + (val << 2) );
  }
}


// key LL functions start
char modMethod(GetKeyVal)(byte id, byte key)
{
  byte output = 0;
  if (id < modMethod(MAX_INDEX) && key < modMethod(MAX_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    output = EEPROM.read(addr + modMethod(PADDING) + key * 2);
  }
  return output;
}

void modMethod(SetKeyVal)(byte id, byte key, byte val)
{
  if (id < modMethod(MAX_INDEX) && key < modMethod(MAX_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    EEPROM.update(addr + modMethod(PADDING) + key * 2, val);
  }
}

byte modMethod(GetKeyType)(byte id, byte key)
{
  byte output = 0;
  if (id < modMethod(MAX_INDEX) && key < modMethod(MAX_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    output = EEPROM.read(addr + modMethod(PADDING) + key * 2 + 1);
  }
  return output;
}

void modMethod(SetKeyType)(byte id, byte key, byte val)
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

int modMethod(GetStartAddr)(byte id)
{
  int addr = modMethod(MAX_ADDR) + (id * (modMethod(MAX_KEYS) * 2 + modMethod(PADDING)));
  return addr;
}

// key LL functions stop

void modMethod(PressCoord)(byte x, byte y) { }
#undef mod_modname
#undef modMethod
