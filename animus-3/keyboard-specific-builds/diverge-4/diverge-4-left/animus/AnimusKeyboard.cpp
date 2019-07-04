#include "AnimusKeyboard.h"

#include "HID-Project.h"
// this is for the modified arduino HID
IKeyboard::IKeyboard(void)
{
  //nothing
}

void IKeyboard::Begin(void)
{
  Keyboard.begin();
  //NKROKeyboard.begin();
}
void IKeyboard::End(void)
{
  Keyboard.end();
  //NKROKeyboard.end();
}
void IKeyboard::Press(byte k)
{
  if (Global.NKROMode == 0)
  {
    Keyboard.press((KeyboardKeycode)k);
  }
  else
  {
    //NKROKeyboard.press((KeyboardKeycode)k);
  }
  KeyState[k] = true;
}
void IKeyboard::Release(byte k)
{
  if (Global.NKROMode == 0)
  {
    Keyboard.release((KeyboardKeycode)k);
  }
  else
  {
    //NKROKeyboard.release((KeyboardKeycode)k);
  }
  KeyState[k] = true;

}
void IKeyboard::Write(byte k)
{
  if (Global.NKROMode == 0)
  {
    Keyboard.press((KeyboardKeycode)k);
    Keyboard.release((KeyboardKeycode)k);
  }
  else
  {
    //NKROKeyboard.press((KeyboardKeycode)k);
    //NKROKeyboard.release((KeyboardKeycode)k);
  }
}
void IKeyboard::ReleaseAll(void)
{
  Keyboard.releaseAll();
  //NKROKeyboard.releaseAll();
  for (short i = 0; i < 256; i++)
  {
    KeyState[i] = false;
  }
}

IKeyboard AnimusKeyboard;
