#include "AnimusKeyboard.h"

#define HID_CUSTOM_LAYOUT
#define LAYOUT_HID_SCANCODE
#include "HID.h"
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
    BootKeyboard.press(k);
  }
  else
  {
    NKROKeyboard.press(k);
  }
  KeyState[k] = true;
}
void IKeyboard::Release(byte k)
{
  if (Global.NKROMode == 0)
  {
    BootKeyboard.release(k);
  }
  else
  {
    NKROKeyboard.release(k);
  }
  KeyState[k] = true;

}
void IKeyboard::Write(byte k)
{
  if (Global.NKROMode == 0)
  {
    BootKeyboard.press(k);
    BootKeyboard.release(k);
  }
  else
  {
    NKROKeyboard.press(k);
    NKROKeyboard.release(k);
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
