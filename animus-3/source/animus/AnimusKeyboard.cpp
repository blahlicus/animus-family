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
}
void IKeyboard::Release(byte k)
{
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
}

IKeyboard AnimusKeyboard;
