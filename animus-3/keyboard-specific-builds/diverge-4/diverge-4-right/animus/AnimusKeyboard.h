#ifndef ANIMUS_KEYBOARD
#define ANIMUS_KEYBOARD
#include "Global.h"

class IKeyboard
{
private:
  //nothing
public:
  bool KeyState[256];
  IKeyboard(void);
  void Begin();
  void End(void);
  void Press(uint8_t k);
  void Release(uint8_t k);
  void Write(uint8_t k);
  void ReleaseAll(void);
};
extern IKeyboard AnimusKeyboard;

#endif
