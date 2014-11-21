#include "Timer.h"                     //http://github.com/JChristensen/Timer


//TODO: gestionar interrupciones externas
// asignarles un estado


const int LED1 = 12;                    //connect one LED to this pin (with appropriate current-limiting resistor of course)
const int LED2 = 13;          //connect another LED to this pin (don't forget the resistor)
const int LEDint = 11;
const int BUTTON_PIN = 2;
Timer t; 

//Global variables for interruptions
int volatile intState = LOW;

//Global definitions
int numberSteps = 4; //Numero de estados del sequencer
int actualState = 0; //Define el numero del "tiempo" donde nos encontramos
int actualMode = 0; //Define el modo: 1: play 2:record 3:stop 

//instantiate the timer object

void setup(void)
{
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LEDint, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    digitalWrite(BUTTON_PIN, HIGH);
    t.every(500,changeState);
    attachInterrupt(0, somethingIsHappening, FALLING);
}

void loop(void)
{
    t.update();
    
    if(actualState==1)
    {
      digitalWrite(LED2, LOW);
      digitalWrite(LED1, HIGH);
    }
    else if (actualState==2)
    {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
    }
    else if(actualState==3)
    {
      digitalWrite(LED2, LOW);
      digitalWrite(LED1, HIGH);
    }
    else if (actualState==4)
    {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
    }
      
    
}

void changeState()
{
  if (actualState < numberSteps)
  {
    actualState++;
  }
  else
  {
    actualState = 1;
  }
}
void somethingIsHappening()
{
  if (LEDintState)
  {
    digitalWrite(LEDint, LOW);
  }
  else
  {
    digitalWrite(LEDint, HIGH);
  }
}

