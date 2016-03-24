## Instructions to writing animus mods

Animus mods must follow strict naming rules for animus builder to work properly
First, name your mod_template file in the following format:

mod_[modname]

Then, replace `uktemplate` in `#define mod_modname` with your own mod name.

Also make sure to rename this directory to [modname].
--------------------------------------------------------------------------------
## How to declare more methods and functions

If more methods or functions are needed, declare them with the following syntax:

```
[return type] modMethod([function name])([arguments])
{

}
```

An example with the method name: `blah` with return type void and 1 int argument

```
void modMethod(blah)(int input)
{

}
```

--------------------------------------------------------------------------------
## How to call methods and functions declared within the mod

If you wish to call any methods or functions declared within the mod, you should
also use modMethod.

To call the function from above with the argument value of 5, do the following:

`modMethod(blah)(5);`

If you wish to call functions from the main animus files, then you could just
call them regularly, example:

`int layer = getLayEEPROM();`
--------------------------------------------------------------------------------
## Using EEPROM

EEPROM addresses 601-999 (inclusive) are reserved for mods, you may get and set
EEPROM values with the following functions:

```
void EEPROM.update(address, valueByte);
byte EEPROM.read(address);
```

--------------------------------------------------------------------------------
# Creating multiple file mods

If your mod contains multiple files, make sure to place them in the same folder,
this allows you to include multiple .ino files, .cpp files and .h files.
