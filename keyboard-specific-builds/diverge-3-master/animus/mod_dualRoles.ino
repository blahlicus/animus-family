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


#define mod_modname dualRoles

const int dualRolesMinAddr = 801;
const int dualRolesMaxAddr = 841;
const byte dualRolesMAX = 10;
const byte dualRolesSLOT_SIZE = 4;

boolean dualRolesState[10] = {false, false, false, false, false, false, false, false, false, false};


int dualRolesDelay = 5;

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
    for (int i = 0; i < dualRolesMAX; i++)
    {
      dualRolesState[i] = true;
    }
    if (type == 8)
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
    if (type == 8)
    {
      modMethod(FinishHold)(val);
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
  else if (input.startsWith("uniqueksetdualroles"))
  {

    input = input.substring(input.indexOf('(')+1);
    byte id = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte key1val = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte key1type = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte key2val = input.substring(0, input.indexOf('(')).toInt();
    input = input.substring(input.indexOf('(')+1);
    byte key2type = input.substring(0, input.indexOf('(')).toInt();
    input = input.toInt();

    modMethod(SetKeyVal)(id, 0, key1val);
    modMethod(SetKeyType)(id, 0, key1type);
    modMethod(SetKeyVal)(id, 1, key2val);
    modMethod(SetKeyType)(id, 1, key2type);
    Serial.print("set dual-roles(");
    Serial.println(id);
  }

}

void modMethod(HoldKey)(int id)
{
  if (id < dualRolesMAX)
  {
    PressKey( modMethod(GetKeyVal)(id, 0), modMethod(GetKeyType)(id, 0) );
    dualRolesState[id] = false;
  }
}
void modMethod(FinishHold)(int id)
{
  if (id < dualRolesMAX)
  {
    ReleaseKey( modMethod(GetKeyVal)(id, 0), modMethod(GetKeyType)(id, 0) );
    if (dualRolesState[id] == false)
    {
      PressKey( modMethod(GetKeyVal)(id, 1), modMethod(GetKeyType)(id, 1) );
      delay(dualRolesDelay);
      ReleaseKey( modMethod(GetKeyVal)(id, 1), modMethod(GetKeyType)(id, 1) );
    }
  }
}

byte modMethod(GetKeyVal)(int id, byte key)
{
  char output = 0;
  if (id < dualRolesMAX && key < 2)
  {
    int addr = modMethod(GetStartAddr)(id);
    output = EEPROM.read(addr + key * 2);
  }
  return output;
}

void modMethod(SetKeyVal)(int id, byte key, byte val)
{
  if (id < dualRolesMAX && key < 2)
  {
    int addr = modMethod(GetStartAddr)(id);
    EEPROM.update(addr + key * 2, val);
  }
}

byte modMethod(GetKeyType)(int id, byte key)
{
  char output = 0;
  if (id < dualRolesMAX && key < 2)
  {
    int addr = modMethod(GetStartAddr)(id);
    output = EEPROM.read(addr + key * 2 + 1);
  }
  return output;
}

void modMethod(SetKeyType)(int id, byte key, byte val)
{
  if (id < dualRolesMAX && key < 2)
  {
    int addr = modMethod(GetStartAddr)(id);
    EEPROM.update(addr + key * 2 + 1, val);
  }
}


int modMethod(GetStartAddr)(int id)
{
    int addr = dualRolesMinAddr + (id * dualRolesSLOT_SIZE);
    return addr;
}


#undef mod_modname
#undef modMethod
