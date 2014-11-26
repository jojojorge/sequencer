#include "Timer.h"                     //http://github.com/JChristensen/Timer


//TODO: gestionar interrupciones externas
// asignarles un estado

const int LED1 = 10;                    //connect one LED to this pin (with appropriate current-limiting resistor of course)
const int LED2 = 11; 
const int LED3 = 12;                    //connect one LED to this pin (with appropriate current-limiting resistor of course)
const int LED4 = 13;          //connect another LED to this pin (don't forget the resistor)
const int LEDint = 9;
const int BUTTON_PIN = 2;
Timer t; 

//Global variables for interruptions
int intState = LOW;

//Global definitions
int numberSteps = 4; //Numero de estados del sequencer
int actualState = 0; //Define el numero del "tiempo" donde nos encontramos
int actualMode = 0; //Define el modo: 1: play 2:record 3:stop 
boolean LEDintState = LOW;

//REGISTROS  DE NOTAS


int nota1 = 0x40;
int nota2 = 0x40;
int nota3 = 0x40;
int nota4 = 0x40;
//instantiate the timer object

void setup(void)
{ 
    Serial.begin(115200);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);
    pinMode(LEDint, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    digitalWrite(BUTTON_PIN, HIGH);
    t.every(500,changeState);
    attachInterrupt(0, somethingIsHappening, RISING);
}

void loop(void)
{
    t.update();
    
    if(actualState==1)
    {
      digitalWrite(LED4, LOW);
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
      digitalWrite(LED3, HIGH);
    }
    else if (actualState==4)
    {
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
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
  LEDintState = !LEDintState;
  digitalWrite(LEDint, LEDintState);
 
  
}

void noteOn(int cmd, int pitch, int velocity) {
Serial.write(cmd);
Serial.write(pitch);
Serial.write(velocity);
}
