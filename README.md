# Animus
## Introduction
This is an Arduino based firmware for use by devices compatible with the Arduino Leonardo firmware (Leonardo, Mico, Pro Micro, etc). Animus is highly customisable and modular, allowing for additional modifications to be made without needing to edit the base code. Animus is one of the first of its kind where persistent live editing of the keyboard layout is possible via serial commands sent from the host computer. Resource management is important as the hardware (atmega32u4, etc) has limited flash memory and EEPROM, heavy optimisation has been done in order to preserve resources.

## Features
* 6KRO
* live key layout editing (no need to reupload layout)
* persistent key layout (keyboard layout is remembered across computers)
* split keyboard compatible via I2C (works on stuff like ergodox/diverge)
* up to 256 FN layers limited by EEPROM
* up to 256 layers limited by EEPROM
* FN keys, spaceFN, toggleFN
* media keys
* serial communication (for editing layout, layers, name, etc)
* device embedded unique id
* modular modding system (plugins could be added to provide additional functionality)
* low ROM usage (currently uses less than 500 bytes)

## Table of Content (use Ctrl+F)

* 1.00: Quick start guide to using animus for your keyboard project
  * 1.10: Hardware Prerequisites
  * 1.20: Software Prerequisites
  * 1.30: Step 1: Building Animus with Animus Builder
  * 1.40: Step 2: Uploading the firmware
  * 1.60: Step 3: Setting layers and rebinding keys
* 2.00: Animus Builder Documentation
  * 2.10: Overview
  * 2.20: Building your own Animus builder
* 3.00: Main Animus Documentation
  * 3.10: Basic Structure
  * 3.20: Globals
  * 3.30: File: animus_main.ino
  * 3.40: File: animusmaster.ino
  * 3.50: File: EEPROM.ino
  * 3.60: File: millis.ino
  * 3.70: File: mod.ino
  * 3.80: File: seria.ino
* 4.00: Animus Modding Documentation
  * 4.10: Basic Structure
  * 4.20: Togglables
  * 4.30: Function: modStartup()
  * 4.40: Function: modLoop()
  * 4.50: Function: modKeyDown(char val, byte type) and modKeyUp(char val, byte type)
  * 4.60: Function: modSerial(String input)
  * 4.70: Animus mod development language convention
  * 4.80: Getting started on writing Animus mods
* 6.00: Mod List
  * 6.10: Overview
  * 6.20: Mod: I2C
  * 6.30: Mod: I2CSlave
  * 6.40: Mod: media

## Using the driver for a keyboard project (quick and no coding)
### Hardware Prerequisites
* custom keyboard built with an arduino capable device (any teensy/Arduino Leonardo/Arduino Micro/Pro Micro)

### Software Prerequisites
* Arduino IDE

### Getting Started
Using the firmware is extremely easy, every keyboard project is different, to account for hardware differences, the firmware needs to be pre-built with the animus builder, it allows you to specify the number of rows and columns of your matrix keyboard, the pins, as well as any mods/plugins, identifiers, etc.

Simply build your own own customised firmware with animus builder in releases/animusbuilder

Animus builder is fully cross-platform and is currently command-line only (set to change), the builder prepares animus files for precompilation and upload, the command-line arguments list is the following

```
animusbuilder [animus path] [output path] [row] [column] [vertical pins] [horizontal pins]

animusbuilder [animus path] [output path] [row] [column] [vertical pins] [horizontal pins] [refresh rate]

animusbuilder [animus path] [output path] [row] [column] [vertical pins] [horizontal pins] [refresh rate]

animusbuilder [animus path] [output path] [row] [column] [vertical pins] [horizontal pins] [refresh rate] [kb name] [kb variant] [driver build name]

animusbuilder [animus path] [output path] [row] [column] [vertical pins] [horizontal pins] [refresh rate] [kb name] [kb variant] [driver build name] [mods folder path] [list of included mods]
```

* `animus path`: path to the animusmaster directory
* `output path`: output path (creates folder if it does not already exist)
* `row`: number of rows your keyboard matrix has
* `columns`: number of columns your keyboard matrix has
* `vertical pins`: array of arduino `pins` written in quotes separated by commas (like this: "1, 2, 3, 4")
* `horizontal pins`: array of arduino `pins` written in quotes separated by commas (like this: "1, 2, 3, 4")
* `refresh rate`: refresh rate in milliseconds to prevent debouncing
* `kb name`: name of keyboard or keyboard type, used in serial identifier to interact with third-party software
* `kb variant`: data, used in serial identifier to interact with third-party software
* `driver build name`: data, used in serial identifier to interact with third-party software
* `mods folder path`: path to the directory containing animus mods/plugins
* `list of included mods`: list of mod files to be included, filename and extension is needed, this should be written in quotes separated by commas (e.g. "mod_I2C.ino, mod_media.ino")

### Upload Firmware to Hardware
Now launch [modified arduino IDE with media controls](https://github.com/stefanjones/Arduino) and upload animus to your target device, be sure to select "Arduino Leonardo" or other comparable board types when uploading the firmware to your device.
### Remapping The Keyboard Layout
There are currently plans for a GUI software for remapping the keyboard but it is currently unavailable.

To rebind keys, launch any Arduino IDE, then select Tools > Serial Monitor, then select 19200 baud in the lower right corner of the new window

The escape character for animus is the space character ' ', so make sure to include a space to the end of each of your command

The argument separator is the '(' character, phrasing of serial commands goes like this: _"command(arg0(arg1(arg2 "_

enter the following commands for varying uses
* "uniquekreqinfo ": prints KBINFO
* "uniqueksetkey(_x_(_y_(_z_(_val_(_type_ ": sets key binding in location x, y, z with ASCII value val and type (see animus/docs/kedeclarations.ino for default keys and references such as FN and media keys)
* "uniquekseteeprom(_addr_(_value_ ": sets eeprom in address _addr_ as value _value_, use numbers for both arguments (addr: 0-1023, value: 0-255)
* "uniqueksetlay(_val_ ": sets the maximum layer for your key layout (max 500 / ROW * LAY)
* "uniquekgetlay ": returns number of layers

## Authors and Contributors
This firmware is done entirely by blahlicus for the purpose of using it for his [Unique Keyboards](http://uniquekeyboard.com/) (custom mech keyboards).

## Support or Contact
Contact blahlicus at blahlicus@gmail.com

## Licenses
This software is under a variant of the Apache License, see LICENSE.md for more detail
