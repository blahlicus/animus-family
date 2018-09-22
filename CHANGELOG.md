##Patch Notes
Stable release versions are prefixed by the "v" notation whilst pre-releases are prefixed by the "x" notation.


#### x3.0.0 (2018-06-11) Animus 3 "Nova" (Pre-release)
Animus 3 codename "Nova" is finally completed and is currently in beta, all functions are tested working at least once but it was not tested in a long term use scenario.

Animus 3 is a complete refactor based on Animus 2.3.1 which was the latest stable version until I've updated 2.6 to 2.7. It has vastly improved encapsulation and it is a lot more platform agnostic, which means it will be very easy to port over to other microcontrollers including stuff like SAMD chips and STM32 chips.

There are no major new features but all mods received vast improvements because they are all rewritten from scratch. persistent data management is also dynamic which allows vastly more stuff to be stored in the limited EEPROM of the Atmega32u4.

Serial command speed has been improved by over an order of magnitude.

New features:

* The board layout (including mod settings such as macros) can now be loaded from the device to Arbites
* Pins and other board settings are now saved in EEPROM, this means now all keyboards run the same build of the same version of the firmware instead of previously where keyboards run their own build of the same version of the firmware.
* Macros now don't have length limits (was 8 keys previously)
* Macros could now act with "release keys on release macro" behaviour.
* You could now have up to 256 Macros limited by EEPROM
* Tapdance now don't have length limits ( was 3 keys previously)
* You could now have up to 256 Tapdance keys limited by EEPROM
* CMD + [x] dual roles keys are now available
* CMD + [x] + other modifier sticky keys are now available
* CMD + [x] + other modifier modified keys are now available
* Configurable I2C host/guest relationship, you could now switch between the I2C host/guest on split keyboards by pressing a key on the keyboard instead of requiring a firmware reflash
* Mouse 4 and Mouse 5 buttons added (back and next button)

Enhancements to existing features:

* Dual roles keys now do not cancel each other (if you press shift || 1, then shift || 2, then you will get a "@" as output instead of a "2" previously)
* Serial comms speed is increased by 30 times, this means it means Arbites could now upload layouts 30 times faster, uploading layouts now literally take less than 1 second on a Terminus Mini
* Cooldown based debouncing system prevents debouncing completely without increasing any latency

Please note that this version requires a new version of Arbites because serial comms are changed completely, so this version **will not** work with anything below Arbites 3 and uploading this firmware to your device **will not preserve your previous layout**, do not upgrade to this version until Arbites 3 is ready.

#### v2.7.0 (2018-06-11) Animus 2.7 (Stable)
Animus 2.6 was quite buggy but I neglected to update it because effort was placed in Animus 3 and I did not want to waste development time on a deadend, now that Animus 3 is in beta, I'm porting its debounce handling algorithm to Animus 2 and just some general bugfixing to make sure Animus 2 is super stable going forward.

New Features:

* Cooldown based anti-debounce system ported from Animus 3.0

Bugfix:

* No more debouncing issues!
* Tapdance cooldowns now work properly

QoL improvements:

* Increased 30% gravitas


#### v2.5.0 (2017-08-24) Animus 2.5 (Stable)

Animus 2.5 added tapdance and a new debounce detection algorithm.

#### v2.3.1 (2016-12-19) Animus 2.3.1 (Stable)

Animus 2.3.1 added mouse controls.

#### v2.3.0 (2016-11-16) Animus 2.3 (Stable)

Animus 2.3 contains numerous bugfixes and refinements.

#### v2.0.0 (2016-10-06) Animus 2 (Stable)

Animus 2 codenamed "Innova" is completely refactored. Notably, scancodes are now used instead of ascii codes at the firmware level. New features include customisable macros saved in EEPROM, dual role keys (modifier+X keys) and sticky keys.

New Features:

* Dual roles keys (modifier + x keys)
* Up to 20 macros with each macro able to perform up to 8 actions
* sticky keys for modifiers and FN keyboards

Bugfix:

* Numerous misc bugfixes

#### v1.0.0 (2016-03-06) Animus 1 (Stable)

First stable release of Animus. This version is the successor to the older `keydriver2` (Also written by Blahlicus) firmware that ran on Diverge 1s and Terminus Minis. The previous version was not very modular and it was not feature complete. The v1.0.0 release marks the first stable release of the animus firmware family.

Features:

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
