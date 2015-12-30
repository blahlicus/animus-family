#define lay getLayEEPROM()

// layering
int keyLayer = 0;
int tempLayer = 0;


// key states
int keyState[COL][ROW];
int previousState[COL][ROW];

// spacefn keys
boolean pressedKey = false;

// slave data
byte slaveArray[30];
byte slaveCount = 0;
const byte MAX_SLAVE_COUNT = 30;

// millis clock

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
  }


  modLoop();
}


// key press functions start

void pressKey(char val, byte type)
{
  if (slaveCount < MAX_SLAVE_COUNT)
  {
    slaveArray[slaveCount] = val;
    slaveCount++;
    slaveArray[slaveCount] = type;
    slaveCount++;
    slaveArray[slaveCount] = true;
    slaveCount++;
  }
}

void releaseKey(char val, byte type)
{
  if (slaveCount < MAX_SLAVE_COUNT)
  {
    slaveArray[slaveCount] = val;
    slaveCount++;
    slaveArray[slaveCount] = type;
    slaveCount++;
    slaveArray[slaveCount] = false;
    slaveCount++;
  }
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
