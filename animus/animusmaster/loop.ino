// layering
int keyLayer = 0;
int tempLayer = 0;

// key states
int keyState[COL][ROW];
int previousState[COL][ROW];

// spacefn keys
boolean pressedKey = false;

void loop()
{
  // main loop starts
  testSerial();
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
          modKeyDown(getValEEPROM(j, i, tempLayer), getTypeEEPROM(j, i, tempLayer));
        }
        else
        {
          releaseKey(getValEEPROM(j, i, tempLayer), getTypeEEPROM(j, i, tempLayer));
          modKeyUp(getValEEPROM(j, i, tempLayer), getTypeEEPROM(j, i, tempLayer));
        }
      }

      previousState[j][i] = keyState[j][i];

    }
  }
  // main loop ends

  modLoop();
  delay(refreshDelay);
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
	else if (type == 4)
	{
    if (val = 0)
    {
  		Remote.increase();
      Remote.clear();
    }
    else if (val == 1)
    {
  		Remote.decrease();
      Remote.clear();
    }
    else if (val == 2)
    {
  		Remote.mute();
      Remote.clear();
    }
    else if (val == 3)
    {
  		Remote.play();
      Remote.clear();
    }
    else if (val == 4)
    {
  		Remote.pause();
      Remote.clear();
    }
    else if (val == 5)
    {
  		Remote.next();
      Remote.clear();
    }
    else if (val == 6)
    {
  		Remote.previous();
      Remote.clear();
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
	if (keyLayer >= LAY)
	{
		keyLayer = 0;
	}
	else if (keyLayer < 0)
	{
		keyLayer = LAY - 1;
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

// serial functions start

void testSerial()
{
  if (Serial.available()>0)
  {
    char inputByte = (char)Serial.read();
    String inputData;

    if (inputByte != ' ')
    {
      inputData += inputByte;
    }
    else
    {
      serialCommand(inputData);
      inputData = "";
    }
  }
}

void serialCommand(String input)
{
  if (input == "uniquekreqinfo")
  {
    Serial.println(KBINFO);
  }
}

// serial functions end
