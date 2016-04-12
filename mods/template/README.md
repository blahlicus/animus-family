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

`int layer = GetLayEEPROM();`
--------------------------------------------------------------------------------
## Declaring dependancies and reserving resources

If your mod requires use of special functions or pins, you should declare it in
the comment on top of mod_[modname] in between BUILDER_REQUIREMENT_START and
BUILDER_REQUIREMENT_END, the list of special functions available:

* I2C: used by Arduino's Wire library for I2C communication
* EEPROM([addr1],[addr2],[addr3]...): declare to claim ownership of EEPROM
* Pin([pin],[pin],[pin]...): declare to claim ownership of pins
--------------------------------------------------------------------------------
## Using EEPROM

EEPROM addresses 601-999 (inclusive) are reserved for mods, you may get and set
EEPROM values with the following functions:

```
void EEPROM.update(address, valueByte);
byte EEPROM.read(address);
```
Remember to declare the EEPROM addresses used as per the previous section
--------------------------------------------------------------------------------
# Creating multiple file mods

If your mod contains multiple files, make sure to place them in the same folder,
this allows you to include multiple .ino files, .cpp files and .h files.
