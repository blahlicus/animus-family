# Animus
## Introduction
This is an Arduino based firmware for use by devices compatible with the Arduino Leonardo firmware (Leonardo, Mico, Pro Micro, etc). Animus is highly customisable and modular, allowing for additional modifications to be made without needing to edit the base code. Animus is one of the first of its kind where persistent live editing of the keyboard layout is possible via serial commands sent from the host computer. Resource management is important as the hardware (atmega32u4, etc) has limited flash memory and EEPROM, heavy optimisation has been done in order to preserve resources.

## Features
* NKRO
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
* 7.00: Authors and Contributors
* 8:00: Support or Contact
* 9.00: Licenses

## 1.00: Using the driver for a keyboard project (quick and no coding)
### 1.10: Hardware Prerequisites
* custom keyboard built with an arduino capable device (any teensy/Arduino Leonardo/Arduino Micro/Pro Micro)

### 1.20: Software Prerequisites
* Arduino IDE

### 1.30: Step 1: Building Animus with Animus Builder
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

to build a firmware for animus, run animusbuilder in a command line with the appropriate arguments

example:

`animusbuilder "/home/docs/animusmaster" "/home/docs/diverge-ii" 5 8 "5, 6, 7, 8, 9" "A3, A2, A1, A0, 15, 14, 16, 10" 10 "Diverge II" "Diverge II Dash" "Animus OEM" "/home/docs/animusmod" "mod_I2C.ino, mod_media.ino"`

the above command would build animus with 5 rows, 8 columns, and loaded with the mods I2C and media, the output folder is set to "/home/docs/diverge-ii"

### 1.40: Step 2: Uploading the firmware
After a customized firmware is built for animus, upload it to your hardware using the Arduino IDE.

Simply open animusmaster.ino, select your device and press upload in the Arduino IDE with the board set as Arduino Leonardo.

### 1.60: Step 3: Setting layers and rebinding keys
There are currently plans for a GUI software for remapping the keyboard but it is currently unavailable.

To rebind keys, launch any Arduino IDE, then select Tools > Serial Monitor, then select 19200 baud in the lower right corner of the new window, alternatively, use any method of your liking to send serial commands to the device with baud set to 19200.

The escape character for animus is the space character ` `, so make sure to include a space to the end of each of your command

The argument separator is the `(` character, phrasing of serial commands goes like this: `"command(arg0(arg1(arg2 "`

the following commands are available with native animus
* `uniquekreqinfo `: prints keyboard info, including keyboard name, keyboard variant, driver name and variant
* `uniquekgetrow `: get number of rows
* `uniquekgetcol `: get number of cols
* `uniqueksetkey(x(y(z(val(type `: sets key binding in location `x`, `y`, `z` with ASCII value `val` and `type`, typically you will use `type = 0` to represent regular keyboard keys, `type` is used for special functions such as FN, layer switching, macros, etc
* `uniquekseteeprom(addr(value `: sets eeprom in address `addr` as value `value`, use numbers for both arguments (addr: 0-1023, value: 0-255) note that use of this function is not really recommended and that addresses 0-1000 are reserved for layers
* `uniqueksetlay(val `: sets the maximum layer for your key layout (max 500 / ROW * LAY)
* `uniquekgetlay `: returns number of layers

To bind your keyboard properly, you will first have to set your number of layers, so run the following command:

`uniqueksetlay(3 `

To set the number of layers in your keyboard to 3 layers, the default layer is layer 0, so, to bind your key in the 0, 0 position of your keyboard matrix, you could run the following command:

`uniqueksetkey(0(0(0(97(0`

The above command sets your 0, 0, 0 key to ASCII char 97, which is 'a'.

You could repeat the above steps or write a program to do it for you to fully bind your keyboard.

## 2.00: Animus Builder Documentation
### 2.10: Overview

Animusbuilder is written in C++, it is a simple file and word parser and minor editor for animusmaster.

Animusbuilder is created for the purpose of making animus fully compatible with any arduino based matrix keyboards and to streamline development and deployment.

To understand why the builder is necessary, we must look at animusmaster and understand what is going on, animusmaster itself is designed to be very portable and editable, only animusmaster.ino and mod.ino need to be edited for different keyboard designs

There are a bunch of precompiler directives at the top of animusmaster.ino and mod.ino, editing them is all that is needed.

Here are the `#define` directives from animusmaster.ino with example input and comment

```
#define builder_row 5    // number of rows
#define builder_col 8    // number of columns
#define builder_kbname "Diverge II"     // keyboard name
#define builder_kbvariant "Diverge II"     // keyboard variant
#define builder_kbdriver "Animus Renascentia 2"     // driver name
#define builder_kbdriver_build "Diverge II OEM"     // driver build
#define builder_vpins 5, 6, 7, 8, 9     // pins
#define builder_hpins A3, A2, A1, A0, 15, 14, 16, 10     // pins
#define builder_refresh 10     // refresh rate
```

And here are the `#define` directives from mod.ino with example input

```
#define builder_mstartup I2CStartup(); mediaStartup();
#define builder_mloop I2CLoop(); mediaLoop();
#define builder_mkeydown I2CKeyDown(val, type); mediaKeyDown(val, type);
#define builder_mkeyup I2CKeyUp(val, type); mediaKeyUp(val, type);
#define builder_mserial I2CSerial(input); mediaSerial(input);
```

In order to be fully compliant, animus mods have strict method naming conventions for the builder's sake, in the above example, the mods I2C and media are installed.

Animusbuilder simply copies all necessary files and edit the precompiler directives in a quick and efficient way, mods are also auto copied.

### 2.20: Building your own Animus builder

TODO

## 3.00: Main Animus Documentation
### 3.10: Overview

Animus is designed to be robust, customisable, modular, and lightweight. The code is properly separated into several files, with non-essential functions set as "mods" (AKA plugins), this allows native animus to be extremely lightweight whilst allowing for plugins to be installed that to make it feature reach (stuff like media keys, dual keyboards, I2C, macros, etc could be done with mods)

### 3.20 3.30 3.40 3.50 3.60 3.70 3.80

TODO


## 7.00: Authors and Contributors
This firmware is done entirely by blahlicus for the purpose of using it for his [Unique Keyboards](http://uniquekeyboard.com/) (custom mech keyboards).

## 8:00: Support or Contact
Contact blahlicus at blahlicus@gmail.com

## 9.00: Licenses
This software is under a variant of the Apache License, see LICENSE.md for more detail
