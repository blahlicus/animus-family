#include "AnimusKeyboard.h"
#include "ArduinoKeyboard.h"
// this is for the modified arduino HID
IKeyboard::IKeyboard(void)
{
  //nothing
}

void IKeyboard::Begin(void)
{
  Keyboard.begin();
}
void IKeyboard::End(void)
{
  Keyboard.end();
}
void IKeyboard::Press(byte k)
{
  Keyboard.press(k);
  KeyState[k] = true;
}
void IKeyboard::Release(byte k)
{
  KeyState[k] = false;
  Keyboard.release(k);

}
void IKeyboard::Write(byte k)
{
  Keyboard.press(k);
  Keyboard.release(k);

}
void IKeyboard::SetNKRO(byte mode)
{
  Keyboard.setNKROMode(mode);
}
uint8_t IKeyboard::GetNKRO(void)
{
  return Keyboard.getNKROMode();
}
void IKeyboard::ReleaseAll(void)
{
  Keyboard.releaseAll();
  for (short i = 0; i < 256; i++)
  {
    KeyState[i] = false;
  }
}

IKeyboard AnimusKeyboard;
