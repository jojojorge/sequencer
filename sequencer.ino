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
int nota2 = 0x42;
int nota3 = 0x44;
int nota4 = 0x46;
int flag1 = 1;
int flag2= 0;
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
    
    t.every(500,changeState);
    attachInterrupt(0, cambiarNota, RISING);
}

void loop(void)
{
    t.update();
    
    if(actualState==1)
    {
      
      digitalWrite(LED4, LOW);
      digitalWrite(LED1, HIGH);
      while (flag1>0)
      {
        noteOn(0x90, nota4, 0x00);
        noteOn(0x90, nota1, 0x50);
        flag1--;
        flag2++;
      }
      
      
    }
    else if (actualState==2)
    {
      
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      while(flag2>0){
        noteOn(0x90, nota1, 0x00);
        noteOn(0x90, nota2, 0x50);
        flag2--;
        flag1++;
      }
      
    }
    else if(actualState==3)
    {
      
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, HIGH);
      
      while (flag1>0)
      {
        noteOn(0x90, nota2, 0x00);
        noteOn(0x90, nota3, 0x50);
        flag1--;
        flag2++;
      }
      
    }
    else if (actualState==4)
    {
      
      digitalWrite(LED3, LOW);
      digitalWrite(LED4, HIGH);
      while(flag2>0){
        noteOn(0x90, nota3, 0x00);
        noteOn(0x90, nota4, 0x50);
        flag2--;
        flag1++;
      }
           
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
void cambiarNota()
{
  LEDintState = !LEDintState;
  digitalWrite(LEDint, LEDintState);
   switch (actualState) {
    case 1:
      //si estamos en el estado 1, cambiamos la variable nota1
      nota1 += 2;
      break;
    case 2:
      //si estamos en el estado 1, cambiamos la variable nota1
      nota2 += 2;
      break;
    case 3:
      //si estamos en el estado 1, cambiamos la variable nota1
      nota3 += 2;
      break;
    case 4:
      //si estamos en el estado 1, cambiamos la variable nota1
      nota4 += 2;
      break;
  }
 
  
}

void noteOn(int cmd, int pitch, int velocity) {
Serial.write(cmd);
Serial.write(pitch);
Serial.write(velocity);
}
