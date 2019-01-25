#ifndef ANIMUS_MOD_MODMEDIA
#define ANIMUS_MOD_MODMEDIA
#include "ModTemplate.h"
#include "AnimusMedia.h"
#include "Animus.h"

class CModMedia : public CModTemplate
{
private:
public:
  CModMedia(void);
  void Begin(void);
  void LoadData(void);
  void Loop(void);
  void PrePress(byte val, byte type);
  void PressKey(byte val, byte type);
  void ReleaseKey(byte val, byte type);
  void SerialComms(byte mode);
};
extern CModMedia ModMedia;

#endif
