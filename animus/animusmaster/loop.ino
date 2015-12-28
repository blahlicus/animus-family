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
  // put your main code here, to run repeatedly:

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
          pressKey(keyLayout[j][i][tempLayer]);
          modKeyDown(keyLayout[j][i][tempLayer]);
        }
        else
        {
          releaseKey(keyLayout[j][i][tempLayer]);
          modKeyUp(keyLayout[j][i][tempLayer]);
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

void pressKey(key input)
{
  pressedKey = true;

	if (input.type == 0)
	{
		Keyboard.press(input.val);
	}
	else if (input.type == 1)
	{
		tempLayer = input.val;
		releaseAllKey();
	}
  else if (input.type == 2)
  {
    pressedKey = false;
    tempLayer = input.val;
    releaseAllKey();
  }
	else if (input.type == 3)
	{
    if (input.val == 0)
    {
  		switchLayer(true);
    }
    else if (input.val == 1)
    {
    	switchLayer(false);
    }
	}
	else if (input.type == 4)
	{
    if (input.val = 0)
    {
  		Remote.increase();
      Remote.clear();
    }
    else if (input.val == 1)
    {
  		Remote.decrease();
      Remote.clear();
    }
    else if (input.val == 2)
    {
  		Remote.mute();
      Remote.clear();
    }
    else if (input.val == 3)
    {
  		Remote.play();
      Remote.clear();
    }
    else if (input.val == 4)
    {
  		Remote.pause();
      Remote.clear();
    }
    else if (input.val == 5)
    {
  		Remote.next();
      Remote.clear();
    }
    else if (input.val == 6)
    {
  		Remote.previous();
      Remote.clear();
    }
	}
	else if (input.type == 5)
	{
    if (tempLayer == input.val)
    {
      tempLayer = keyLayer;
    }
    else
    {
      tempLayer = input.val;
    }
    releaseAllKey();
	}
}

void releaseKey(key input)
{
  if (input.type == 0)
	{
		Keyboard.release(input.val);
	}
	else if (input.type == 1)
	{
		tempLayer = keyLayer;
		releaseAllKey();
	}
  else if (input.type == 2)
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
