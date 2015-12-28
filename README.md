# Animus
## Introduction
This is an Arduino based firmware for use by devices compatible with the Arduino Leonardo firmware (Leonardo, Mico, Pro Micro, etc). Animus is highly customisable and modular, allowing for additional modifications to be made without needing to edit the base code. Animus is one of the first of its kind where persistent live editing of the keyboard layout is possible via serial commands sent from the host computer. Resource management is important as the hardware (atmega32u4, etc) has limited flash memory and EEPROM, heavy optimisation has been done in order to preserve resources.

## Features
* 6KRO
* live key layout editing (no need to reupload layout)
* persistent key layout (keyboard layout is remembered across computers)
* up to 256 FN layers limited by EEPROM
* up to 256 layers limited by EEPROM
* FN keys, spaceFN, toggleFN
* media keys
* serial communication (for editing layout, layers, name, etc)
* device embedded unique id
* modular modding system (plugins could be added to provide additional functionality)
*low ROM usage (currently uses less than 500 bytes)

## Using the driver for a keyboard project
### Hardware Prerequisites 
* custom keyboard built with an arduino capable device (any teensy/Arduino Leonardo/Arduino Micro/Pro Micro)

### Software Prerequisites
* [modified arduino IDE with media controls](https://github.com/stefanjones/Arduino)

### Getting Started
Using the firmware is extremely easy, first, open animus/animusmaster.ino and edit the code within, animusmaster.ino functions like a config file of sorts, everything you need to edit is within.

    const int ROW = 4;
    const int COL = 6;
    String KBINFO = "DivergeTM,Diverge TM,Animus,Diverge TM QWERTY";
    int vPins[ROW] = { A3, A2, 9, 16};
    int hPins[COL] = { 10, 8, 7, 6, 5, 4};
    int refreshDelay = 10;

* const int ROW: number of rows your keyboard matrix has
* const int COL: number of columns your keyboard matrix has
* **DEPRECIATED** string KNINFO: serial identifier in the format of "[device name],[devicetype],[driver name],[layout name]"
* int vPins[ROW]: array containing the vertical pins in your keyboard matrix, top left corner first
* int hPins[COL]: array containing the horizontal pins in your keyboard matrix, top left corner first
* int refreshDelay: delay in ms between each scan check used for preventing debounce.

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
This firmware is done entirely by @blahlicus for the purpose of using it for his [Unique Keyboards](http://uniquekeyboard.com/) (custom mech keyboards).

## Support or Contact
Contact @blahlicus at blahlicus@gmail.com

## Licenses
This software is under a variant of the Apache License, see LICENSE.md for more detail
