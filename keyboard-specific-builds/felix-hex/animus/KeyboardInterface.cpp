/*
This contains an "adapter" that allows animus to use multiple HID libraries/HID APIs/HID HALs, this is useful for targetting different platforms and microcontrollers
*/


#include "KeyboardInterface.h"

KeyboardInterface::KeyboardInterface(void)
{
  // put init code here if necessary

}



void KeyboardInterface::begin(void)
{
  ArduinoKeyboard.begin();
}

void KeyboardInterface::end(void)
{
  ArduinoKeyboard.end();
}


size_t KeyboardInterface::press(uint8_t k)
{
  return ArduinoKeyboard.press(k);

}

// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t KeyboardInterface::release(uint8_t k)
{
  return ArduinoKeyboard.release(k);
}

void KeyboardInterface::releaseAll(void)
{
  ArduinoKeyboard.releaseAll();
}

void KeyboardInterface::releaseAllExcept(uint8_t k[18])
{
  ArduinoKeyboard.releaseAllExcept(k);
}
void KeyboardInterface::setNKROMode(uint8_t mode)
{
  ArduinoKeyboard.setNKROMode(mode);
}

uint8_t KeyboardInterface::getNKROMode(void)
{
  return ArduinoKeyboard.getNKROMode();
}

size_t KeyboardInterface::write(uint8_t c)
{
  return ArduinoKeyboard.write(c);
}

KeyboardInterface AnimusKeyboard;
