#include "AnimusKeyboard.h"

#include "HID-Project.h"
// this is for the modified arduino HID
IKeyboard::IKeyboard(void)
{
  //nothing
}

void IKeyboard::Begin(void)
{
  BootKeyboard.begin();
  NKROKeyboard.begin();
}
void IKeyboard::End(void)
{
  BootKeyboard.end();
  NKROKeyboard.end();
}
void IKeyboard::Press(byte k)
{
  if (Global.NKROMode == 0)
  {
    BootKeyboard.press((KeyboardKeycode)k);
  }
  else
  {
    NKROKeyboard.press((KeyboardKeycode)k);
  }
  KeyState[k] = true;
}
void IKeyboard::Release(byte k)
{
  if (Global.NKROMode == 0)
  {
    BootKeyboard.release((KeyboardKeycode)k);
  }
  else
  {
    NKROKeyboard.release((KeyboardKeycode)k);
  }
  KeyState[k] = true;

}
void IKeyboard::Write(byte k)
{
  if (Global.NKROMode == 0)
  {
    BootKeyboard.press((KeyboardKeycode)k);
    BootKeyboard.release((KeyboardKeycode)k);
  }
  else
  {
    NKROKeyboard.press((KeyboardKeycode)k);
    NKROKeyboard.release((KeyboardKeycode)k);
  }
}
void IKeyboard::ReleaseAll(void)
{
  BootKeyboard.releaseAll();
  NKROKeyboard.releaseAll();
  for (short i = 0; i < 256; i++)
  {
    KeyState[i] = false;
  }
}

IKeyboard AnimusKeyboard;
