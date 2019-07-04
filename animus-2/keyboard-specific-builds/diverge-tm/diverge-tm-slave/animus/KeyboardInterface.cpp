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
  if (KeyboardMode == 1)
  {
    NKROKeyboard.begin();
  }
  else
  {
    BootKeyboard.begin();
  }
}

void KeyboardInterface::end(void)
{
  if (KeyboardMode == 1)
  {
    NKROKeyboard.end();
  }
  else
  {
    BootKeyboard.end();
  }
}


size_t KeyboardInterface::press(uint8_t k)
{
  if (KeyboardMode == 1)
  {
    NKROKeyboard.press((KeyboardKeycode)k);
  }
  else
  {
    BootKeyboard.press((KeyboardKeycode)k);
  }
}

// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t KeyboardInterface::release(uint8_t k)
{
  if (KeyboardMode == 1)
  {
    NKROKeyboard.release((KeyboardKeycode)k);
  }
  else
  {
    BootKeyboard.release((KeyboardKeycode)k);
  }
}

void KeyboardInterface::releaseAll(void)
{
  if (KeyboardMode == 1)
  {
    NKROKeyboard.releaseAll();
  }
  else
  {
    BootKeyboard.releaseAll();
  }
}

void KeyboardInterface::releaseAllExcept(uint8_t k[18]) //TODO modify this to add support to except arg
{
  if (KeyboardMode == 1)
  {
    NKROKeyboard.releaseAll();
  }
  else
  {
    BootKeyboard.releaseAll();
  }
}
void KeyboardInterface::setNKROMode(uint8_t mode)
{
  end();
  KeyboardMode = mode;
  begin();
}


size_t KeyboardInterface::write(uint8_t c)
{
  if (KeyboardMode == 1)
  {
    NKROKeyboard.write((KeyboardKeycode)c);
  }
  else
  {
    BootKeyboard.write((KeyboardKeycode)c);
  }
}

KeyboardInterface AnimusKeyboard;
