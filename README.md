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
* "dual-keys" functionality (commaShift, etc)
* media keys
* serial communication (for editing layout, layers, name, etc)
* device embedded unique id
* modular modding system (plugins could be added to provide additional functionality)
* low ROM usage (currently uses less than 500 bytes)

This wiki contains information for both non-programmers and developers alike, check out the side bar for more information.
