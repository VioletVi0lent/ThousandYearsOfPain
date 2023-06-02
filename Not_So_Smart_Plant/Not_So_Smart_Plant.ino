/*
Created by Maximilian Throgmorton, AKA Violet#6515
Finalized on 5/24/2023
Feel free to edit whatever is needed. This code is already unoptimized as it is.
Thumbs up to whoever can make this thing speak regularly.
Keep this entire section in for credit. Pls.
*/
//The plant is based off of my cactus.
//Her name is Frisbee.

#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay delay_2s;

float tempF;
int light, lightMap;
int capVal, capMap;
int tempMap; //Still not sure if tempMap should be on the same line as tempF. I say, No.
int switchPin = 7;

volatile bool NightTime = false;

bool switchVal = 0;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  delay_2s.start(2000, AsyncDelay::MILLIS);
  Serial.println("Starting timers"); //Because of the delay between uploading and opening the serial monitor, this message is never seen.
  randomSeed(analogRead(0)); //This is a surprise tool that will help us later.

  pinMode(switchPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(switchPin), onOff, CHANGE);
}

void loop() {
  //Set a "massive" IF statement here for nighttime mode.
  if(NightTime == true)
  {
    delay(5);
    switchVal = digitalRead(switchPin);
    NightTime = false;
    Serial.println("Ahh, something changed!"); //Not only does this tell you when the switch is used, but it also gives the plant a voice.
  }
    if (delay_2s.isExpired())
    {
      tempF = CircuitPlayground.temperatureF();
      light = CircuitPlayground.lightSensor();
      capVal = CircuitPlayground.readCap(6);
      capMap = map(capVal, 230, 1016, 0, 255);
      lightMap = map(light, 0, 1023, 0, 255);
      tempMap = map(tempF, -67, 257, 0, 255);

      if(capMap < 0)
      {
        capMap = 0;
      }
      if(capMap > 255)
      {
        capMap = 255;
      }
      if(lightMap < 0)
      {
        lightMap = 0;
      }
      if(lightMap > 255)
      {
        lightMap = 255;
      }
      if(tempMap < 0)
      {
        tempMap = 0;
      }
      if(tempMap > 255)
      {
        tempMap = 255;
      }

// that whole last section was to prevent overflow and underflow of code.

      for(int i = 0; i < 2; i++)
      {
        CircuitPlayground.setPixelColor(i, 0, capMap, 0);
      }
      
      if(capMap > 220)
      {
        if(!switchVal)
        {
          CircuitPlayground.playTone(293.67, 200);
        }
        for(int k = 0; k < 2; k++)
        {
          CircuitPlayground.setPixelColor(k, 255, 0, 0);
        }
      }
      else if(capMap < 50)
      {
        if(!switchVal)
        {
          CircuitPlayground.playTone(440.00, 200);
        }
        for(int g = 0; g < 2; g++)
        {
          CircuitPlayground.setPixelColor(g, 0, 0, 255);
        }
      }

      if(tempF >= 68 && tempF <= 85)
        {
          for(int j = 2; j < 5; j++)
          {
            CircuitPlayground.setPixelColor(j, 0, 128, 0);
          }
        }
      else if(tempF > 85)
        {
          for(int s = 2; s < 5; s++)
          {
            CircuitPlayground.setPixelColor(s, 128, 0, 0);
          }
        }
      else
        {
          for(int c = 2; c < 5; c++)
          {
            CircuitPlayground.setPixelColor(c, 0, 0, 128);
          }
        }
    Serial.print("Capacitence: ");  
    Serial.println(capVal);
    Serial.print("Temperature: ");
    Serial.println(tempF);

    delay_2s.repeat();
    }

  if(tempMap >= 128)
  {
    for(int r = 0; r > 10; r++)
      {
        Popcorn(200);
      }
  }
  
  if(lightMap > 150) //Because of the placement of the light sensor in the code, this plays twice. I don't know how to stop it.
  {
    Music();
  }
}

void Popcorn(int flashTime) //This code doesn't do much anymore since it got a lot cooler.
{
  int LED_num = random(5, 10);
  CircuitPlayground.setPixelColor(LED_num, 225, 215, 0);
  if(!switchVal)
    {
       CircuitPlayground.playTone(82.407, 100);
    }
  delay(flashTime/2);
  CircuitPlayground.setPixelColor(LED_num, 0, 0, 0);
  delay(flashTime/2);
}

void Music()
{
  if(!switchVal)
  {
    CircuitPlayground.playTone(146.83 , 200);
    delay(1);
    CircuitPlayground.playTone(146.83 , 200);
    delay(1);
    CircuitPlayground.playTone(293.67 , 200);
    delay(1);
    CircuitPlayground.playTone(220.00 , 200);
    delay(1);
  } //I am not sorry.
}

void onOff()
{
  NightTime = 1;
}