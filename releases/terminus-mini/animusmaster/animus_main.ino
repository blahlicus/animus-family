#define lay getLayEEPROM()


// layering
int keyLayer = 0;
int tempLayer = 0;


// key states
int keyState[COL][ROW];
int previousState[COL][ROW];


// spacefn keys
boolean pressedKey = false;


// baud: dont change this it messes with the c#
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
            pressKey(getValEEPROM(j, i, tempLayer), getTypeEEPROM(j, i, tempLayer));
          }
          else
          {
            releaseKey(getValEEPROM(j, i, tempLayer), getTypeEEPROM(j, i, tempLayer));
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
	if (type == 0)
	{
		Keyboard.press(val);
	}
	else if (type == 1)
	{
		tempLayer = val;
		releaseAllKey();
	}
  else if (type == 2)
  {
    pressedKey = false;
    tempLayer = val;
    releaseAllKey();
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
    releaseAllKey();
	}
  modKeyDown(val, type);
}

void releaseKey(char val, byte type)
{
  if (type == 0)
	{
		Keyboard.release(val);
	}
	else if (type == 1)
	{
		tempLayer = keyLayer;
		releaseAllKey();
	}
  else if (type == 2)
  {
    if (pressedKey == false)
    {
      Keyboard.write(' ');
    }
  	tempLayer = keyLayer;
    releaseAllKey();
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
	releaseAllKey();
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
