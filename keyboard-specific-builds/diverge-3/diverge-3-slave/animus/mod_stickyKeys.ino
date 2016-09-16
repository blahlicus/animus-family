// completed 5/28/2016 blahlicus
// example serial command: uniqueksetdualroles(0(129(0(97(0

/*
Do not remove this comment, this comment is used by animus builder for the
build process
BUILDER_REQUIREMENT_START
EEPROM(801,841)
BUILDER_REQUIREMENT_END
Remeber to change the mod_modname to your mod name
*/


#define mod_modname stickyKeys

#define modMethod(str) conca(mod_modname, str)

const int modMethod(MinAddr) = 842;
const int modMethod(MaxAddr) = 862;
const byte modMethod(MAX) = 10;
const byte modMethod(SLOT_SIZE) = 2;
const byte modMethod(SLOT_KEYS) = 1;

boolean modMethod(State)[10] = {false, false, false, false, false, false, false, false, false, false};

boolean modMethod(Lifted)[10] = {false, false, false, false, false, false, false, false, false, false};


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
    for (int i = 0; i < modMethod(MAX); i++)
    {
      if (modMethod(Lifted)[i])
      {
        modMethod(CheckLift)(i);
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
    for (int i = 0; i < modMethod(MAX); i++)
    {
      if (type !=9)
      {
        modMethod(State)[i] = true;
      }
    }
    if (type == 9)
    {
      modMethod(HoldKey)(val);
    }
  }
}

void modMethod(KeyUp)(char val, byte type)
{
  // ran when a key is pressed up


  // ran if this device's IS_MASTER flag is true
  if (IS_MASTER)
  {
    if (type == 9)
    {
      modMethod(LiftKey)(val);
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
  else if (input.startsWith("uniqueksetstickykeys"))
  {

    input = input.substring(input.indexOf('(')+1);
    byte id = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte key1val = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte key1type = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);

    modMethod(SetKeyVal)(id, 0, key1val);
    modMethod(SetKeyType)(id, 0, key1type);
    Serial.print("set sticky-keys(");
    Serial.println(id);
  }

}

void modMethod(HoldKey)(int id)
{
  if (id < modMethod(MAX))
  {
    PressKey( modMethod(GetKeyVal)(id, 0), modMethod(GetKeyType)(id, 0) );
    modMethod(State)[id] = false;
    modMethod(Lifted)[id] = false;
  }
}
void modMethod(LiftKey)(int id)
{
  if (id < modMethod(MAX))
  {
    modMethod(Lifted)[id] = true;
  }
}

void modMethod(CheckLift)(int id)
{
  if (id < modMethod(MAX))
  {
    if (modMethod(State)[id] == true)
    {
        ReleaseKey( modMethod(GetKeyVal)(id, 0), modMethod(GetKeyType)(id, 0) );
    }
    modMethod(Lifted)[id] == false;
  }
}

byte modMethod(GetKeyVal)(int id, byte key)
{
  char output = 0;
  if (id < modMethod(MAX) && key < modMethod(SLOT_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    output = EEPROM.read(addr + key * 2);
  }
  return output;
}

void modMethod(SetKeyVal)(int id, byte key, byte val)
{
  if (id < modMethod(MAX) && key < modMethod(SLOT_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    EEPROM.update(addr + key * 2, val);
  }
}

byte modMethod(GetKeyType)(int id, byte key)
{
  char output = 0;
  if (id < modMethod(MAX) && key < modMethod(SLOT_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    output = EEPROM.read(addr + key * 2 + 1);
  }
  return output;
}

void modMethod(SetKeyType)(int id, byte key, byte val)
{
  if (id < modMethod(MAX) && key < modMethod(SLOT_KEYS))
  {
    int addr = modMethod(GetStartAddr)(id);
    EEPROM.update(addr + key * 2 + 1, val);
  }
}


int modMethod(GetStartAddr)(int id)
{
    int addr = modMethod(MinAddr) + (id * modMethod(SLOT_SIZE));
    return addr;
}


#undef mod_modname
#undef modMethod
