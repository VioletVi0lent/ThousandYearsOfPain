//GEN_RUSH
//Made by Maximilian Throgmorton
//Licenses and stuff goes here.

#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>

AsyncDelay delay_5s;

int Difficulty = 5; //The B button is the difficulty selector.
int Interact = 4; //The A button is the main tool for the game.

int IniZone = 0;
int MinusZone = 0;
int PlusZone = 0;

volatile bool SkillCheck = false;
volatile bool SpeedUp = false;

bool AVal = 0;
bool BVal = 0;
bool GameTimeVal = 0;
int Charge = 0;
int i = 10;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  delay_5s.start(5000, AsyncDelay::MILLIS);
  randomSeed(analogRead(0));

  pinMode(Difficulty,INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Difficulty), Changer, FALLING);

  pinMode(Interact, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Interact), DidItWork, FALLING);

}

void loop() {
  if(SpeedUp == true)
  {
    BVal++;
    if(BVal > 1)
    {
      BVal = 0;
    }
    SpeedUp = false;
    Serial.println("Hurry Up! activated.");
    //I don't know what to put for speed. I'll figure it out soon.
  }

  if(GameTimeVal == false)
  {
    if(delay_5s.isExpired())
    {
      CircuitPlayground.playTone(1480.0 , 300);
      StartEngine();
      CircuitPlayground.setPixelColor(IniZone, 128, 128, 128);
      CircuitPlayground.setPixelColor(MinusZone, 128, 128, 128);
      CircuitPlayground.setPixelColor(PlusZone, 128, 128, 128);
      GameTimeVal = true;
      delay_5s.repeat();
    }
    Serial.println(Charge);
  }
  while(GameTimeVal == true)
  {
    if(SkillCheck == true)
   {
     if(i == IniZone)
     {
       CircuitPlayground.playTone(440.00, 200);
       Charge += 100;
       for(int l = 0; l < 10; l++)
       {
         CircuitPlayground.setPixelColor(l, 0, 255, 0);
       }
       delay(100);
       CircuitPlayground.clearPixels();
       GameTimeVal = false;
     }
     else if(i == MinusZone)
     {
       CircuitPlayground.playTone(440.00, 200);
       Charge += 100;
       for(int l = 0; l < 10; l++)
       {
         CircuitPlayground.setPixelColor(l, 0, 255, 0);
       }
       delay(100);
       CircuitPlayground.clearPixels();
       GameTimeVal = false;
     }
     else if(i == PlusZone)
     {
       CircuitPlayground.playTone(440.00, 200);
       Charge += 100;
       for(int l = 0; l < 10; l++)
       {
         CircuitPlayground.setPixelColor(l, 0, 255, 0);
       }
       delay(100);
       CircuitPlayground.clearPixels();
       GameTimeVal = false;
     }
     else //Fail
     {
       CircuitPlayground.playTone(92.499, 200);
       for(int j = 0; j < 10; j++)
       {
         CircuitPlayground.setPixelColor(j, 255, 0, 0);
       }
       delay(50);
       CircuitPlayground.clearPixels();
       GameTimeVal = false;
     }
     SkillCheck = false;
   }
    CircuitPlayground.setPixelColor(i, 0, 0, 255);
    delay(200);
    CircuitPlayground.setPixelColor(i, 0, 0, 0);
    i--;
    if (i < 0 && GameTimeVal == true)
    {
      CircuitPlayground.playTone(92.499, 200);
      for(int j = 0; j < 10; j++)
      {
        CircuitPlayground.setPixelColor(j, 255, 0, 0);
      }
      delay(50);
      CircuitPlayground.clearPixels();
      GameTimeVal = false;
    }
    else if(GameTimeVal == false)
    {
      break;
    }
  }
}

void DidItWork()
{
  SkillCheck = true;
}

void Changer()
{
  SpeedUp = 1;
}

void StartEngine()
{
  IniZone = random(1, 4);
  MinusZone = IniZone - 1;
  PlusZone = IniZone + 1;
  i = 10;
}