#define _tokenToString(str) #str
#define tokenToString(str) _tokenToString(str)

#define _conca(str1, str2) str1##str2
#define conca(str1, str2) _conca(str1, str2)



#define lay getLayEEPROM()

// layering
int keyLayer = 0;
int tempLayer = 0;

// key states
int keyState[COL][ROW];
int previousState[COL][ROW];
int LayerState[COL][ROW];

// slave states
boolean IS_MASTER = true;

// spacefn keys
boolean pressedKey = false;

// baud: dont change this it messes with the GUI interface
int baudRate = 19200;


void setup()
{
  Keyboard.begin();
  Serial.begin(baudRate);
  modStartup();
  resetPins();

  // serial delay
  delay(2000);
}

void loop()
{
  // resets millis counter
  millisLoop();
  // checks serials
  testSerial();

  if (checkMillis())
  {
    // main loop starts
    keyScan();
    for (int i = 0; i < ROW; i++)
    {
      for (int j = 0; j < COL; j++)
      {
        if (previousState[j][i] != keyState[j][i])
        {
          if (keyState[j][i] == HIGH)
          {
            LayerState[j][i] = TempLayer;
            pressKey(getValEEPROM(j, i, tempLayer), getTypeEEPROM(j, i, tempLayer));
          }
          else
          {
            releaseKey(getValEEPROM(j, i, LayerState[j][i]), getTypeEEPROM(j, i, LayerState[j][i]));
          }
        }

        previousState[j][i] = keyState[j][i];

      }
    }
    // main loop ends
  }


  modLoop();
}


// key press functions start

void pressKey(char val, byte type)
{
  pressedKey = true;
  if (IS_MASTER)
  {
    if (type == 0)
    {
      Keyboard.press(val);
    }
    else if (type == 1)
    {
      tempLayer = val;
      //releaseAllKey();
    }
    else if (type == 2)
    {
      pressedKey = false;
      tempLayer = val;
      //releaseAllKey();
    }
    else if (type == 3)
    {
      if (val == 0)
      {
        switchLayer(true);
      }
      else if (val == 1)
      {
        switchLayer(false);
      }
      else
      {
        /* Rotate to the next layer in bitfield within val */
        rotateLayers(val);
      }
    }
    else if (type == 5)
    {
      if (tempLayer == val)
      {
        tempLayer = keyLayer;
      }
      else
      {
        tempLayer = val;
      }
      //releaseAllKey();
    }
  }

  modKeyDown(val, type);
}

void releaseKey(char val, byte type)
{
  if (IS_MASTER)
  {
    if (type == 0)
    {
      Keyboard.release(val);
    }
    else if (type == 1)
    {
      tempLayer = keyLayer;
      //releaseAllKey();
    }
    else if (type == 2)
    {
      if (pressedKey == false)
      {
        Keyboard.write(' ');
      }
      tempLayer = keyLayer;
      //releaseAllKey();
    }
  }

  modKeyUp(val, type);
}

void releaseAllKey()
{
  Keyboard.releaseAll();
}


void switchLayer(boolean increment)
{
  if (increment)
  {
    keyLayer++;
  }
  else
  {
    keyLayer--;
  }
  if (keyLayer >= lay)
  {
    keyLayer = 0;
  }
  else if (keyLayer < 0)
  {
    keyLayer = lay - 1;
  }
  //releaseAllKey();
}


/*
  Rotate to the next layer in bitfield within val.
  Examples:
    val=0x3: rotate between layers 0 and 1
    val=0x7: rotate between layers 0, 1, and 2
    val=0xF: rotate between layers 0, 1, 2, and 3
    val=0x11: rotate between layers 0 and 4
*/
void rotateLayers(byte val)
{
  int newLayer = keyLayer;
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
    if ((! mask) || (newLayer >= lay))
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

  keyLayer = newLayer;
  //releaseAllKey();
}



void resetPins()
{
  for (int i = 0; i < ROW; i++)
  {
    pinMode(vPins[i], INPUT);
    digitalWrite(vPins[i], HIGH);
  }

  for (int i = 0; i < COL; i++)
  {
    pinMode(hPins[i], INPUT);
    digitalWrite(hPins[i], LOW);
  }

  for (int i = 0; i < ROW; i++)
  {
    for (int j = 0; j < COL; j++)
    {
      keyState[j][i] = 0;
      previousState[j][i] = 0;
    }
  }
}





void keyScan()
{
  for (int i = 0; i < COL; i++)
  {
    pinMode(hPins[i], OUTPUT);

    for (int j = 0; j < ROW; j++)
    {
      int val = digitalRead(vPins[j]);
      keyState[i][j] = (val == LOW);
    }

    pinMode(hPins[i], INPUT);
  }
}


// key press functions end
