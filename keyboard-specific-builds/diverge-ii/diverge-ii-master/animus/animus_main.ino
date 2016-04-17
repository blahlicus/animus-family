#define _tokenToString(str) #str
#define tokenToString(str) _tokenToString(str)

#define _conca(str1, str2) str1##str2
#define conca(str1, str2) _conca(str1, str2)



#define Lay GetLayEEPROM()

// layering
int KeyLayer = 0;
int TempLayer = 0;

// key states
int KeyState[COL][ROW];
int PreviousState[COL][ROW];

// slave states
boolean IS_MASTER = true;

// spacefn keys
boolean PressedKey = false;

// baud: dont change this it messes with the GUI interface
int BaudRate = 19200;


void setup()
{
  Keyboard.begin();
  Serial.begin(BaudRate);
  NKROStartup();
  ModStartup();
  ResetPins();

  // serial delay
  delay(1000);
}

void loop()
{
  // resets millis counter
  MillisLoop();
  // checks serials
  TestSerial();

  if (CheckMillis())
  {
    // main loop starts
    KeyScan();
    for (int i = 0; i < ROW; i++)
    {
      for (int j = 0; j < COL; j++)
      {
        if (PreviousState[j][i] != KeyState[j][i])
        {
          if (KeyState[j][i] == HIGH)
          {
            PressKey(GetValEEPROM(j, i, TempLayer), GetTypeEEPROM(j, i, TempLayer));
          }
          else
          {
            ReleaseKey(GetValEEPROM(j, i, TempLayer), GetTypeEEPROM(j, i, TempLayer));
          }
        }

        PreviousState[j][i] = KeyState[j][i];

      }
    }
    // main loop ends
  }

  ModLoop();
  NKROLoop();
}


// key press functions start

void PressKey(char val, byte type)
{
  PressedKey = true;
  if (IS_MASTER)
  {
    if (type == 0)
    {
      Keyboard.press(val);
    }
    else if (type == 1)
    {
      TempLayer = val;
      ReleaseAllKey();
    }
    else if (type == 2)
    {
      PressedKey = false;
      TempLayer = val;
      ReleaseAllKey();
    }
    else if (type == 3)
    {
      if (val == 0)
      {
        SwitchLayer(true);
      }
      else if (val == 1)
      {
        SwitchLayer(false);
      }
      else
      {
        /* Rotate to the next layer in bitfield within val */
        RotateLayers(val);
      }
    }
    else if (type == 5)
    {
      if (TempLayer == val)
      {
        TempLayer = KeyLayer;
      }
      else
      {
        TempLayer = val;
      }
      ReleaseAllKey();
    }
  }

  NKROKeyDown(val, type);
  ModKeyDown(val, type);
}

void ReleaseKey(char val, byte type)
{
  if (IS_MASTER)
  {
    if (type == 0)
    {
      Keyboard.release(val);
    }
    else if (type == 1)
    {
      TempLayer = KeyLayer;
      ReleaseAllKey();
    }
    else if (type == 2)
    {
      if (PressedKey == false)
      {
        Keyboard.write(' ');
      }
      TempLayer = KeyLayer;
      ReleaseAllKey();
    }
  }
  NKROKeyUp(val, type);
  ModKeyUp(val, type);
}

void ReleaseAllKey()
{
  Keyboard.releaseAll();
}


void SwitchLayer(boolean increment)
{
  if (increment)
  {
    KeyLayer++;
  }
  else
  {
    KeyLayer--;
  }
  if (KeyLayer >= Lay)
  {
    KeyLayer = 0;
  }
  else if (KeyLayer < 0)
  {
    KeyLayer = Lay - 1;
  }
  ReleaseAllKey();
}


/*
  Rotate to the next layer in bitfield within val.
  Examples:
    val=0x3: rotate between layers 0 and 1
    val=0x7: rotate between layers 0, 1, and 2
    val=0xF: rotate between layers 0, 1, 2, and 3
    val=0x11: rotate between layers 0 and 4
*/
void RotateLayers(byte val)
{
  int newLayer = KeyLayer;
  byte mask = 1 << newLayer;

  if (! val)
  {
    /* No layers are allowed. Do nothing. */
    return;
  }

  /*
    Find the next layer within the bitfield.
    Limit iterations to 10, to ensure no infinite loop.
   */
  for (int i = 0; i < 10; i++)
  {
    newLayer++;
    mask <<= 1;
    if ((! mask) || (newLayer >= Lay))
    {
      newLayer = 0;
      mask = 1;
    }

    if (val & mask)
    {
      /* newLayer is an allowed layer within the bitfield. */
      break;
    }
  }

  KeyLayer = newLayer;
  ReleaseAllKey();
}



void ResetPins()
{
  for (int i = 0; i < ROW; i++)
  {
    pinMode(VPins[i], INPUT);
    digitalWrite(VPins[i], HIGH);
  }

  for (int i = 0; i < COL; i++)
  {
    pinMode(HPins[i], INPUT);
    digitalWrite(HPins[i], LOW);
  }

  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < COL; j++)
    {
      KeyState[j][i] = 0;
      PreviousState[j][i] = 0;
    }
  }
}





void KeyScan()
{
  for (int i = 0; i < COL; i++)
  {
    pinMode(HPins[i], OUTPUT);

    for (int j = 0; j < ROW; j++)
    {
      int val = digitalRead(VPins[j]);
      KeyState[i][j] = (val == LOW);
    }

    pinMode(HPins[i], INPUT);
  }
}


// key press functions end
