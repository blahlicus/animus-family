/*
This contains an "adapter" that allows animus to use multiple HID libraries/HID APIs/HID HALs, this is useful for targetting different platforms and microcontrollers
*/


#include "KeyboardInterface.h"

KeyboardInterface::KeyboardInterface(void)
{
  // insert code for constructor here

}



void KeyboardInterface::begin(void)
{
  BootKeyboard.begin();
}

void KeyboardInterface::end(void)
{
  BootKeyboard.end();
}


size_t KeyboardInterface::press(uint8_t k)
{
  return BootKeyboard.press(k);
}

// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t KeyboardInterface::release(uint8_t k)
{
  return BootKeyboard.release(k);
}

void KeyboardInterface::releaseAll(void)
{
  BootKeyboard.releaseAll();
}

void KeyboardInterface::releaseAllExcept(uint8_t k[18])
{
  BootKeyboard.releaseAll(); //TODO
}
void KeyboardInterface::setNKROMode(uint8_t mode)
{
  //TODO
}

uint8_t KeyboardInterface::getNKROMode(void)
{
  //TODO
  return 0;
}

size_t KeyboardInterface::write(uint8_t c)
{
  return BootKeyboard.write(c);
}

KeyboardInterface AnimusKeyboard;
