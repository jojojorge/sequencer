int Interruptor = 0;          // El interruptor a utilizar sera el 0 es decir el pin digital 2
int ledSalida = 11;        // Aqui pondremos un led para ver como funcionan las interrupciones
int estado = LOW;       // El estado del led
 
void setup() 
{
 // ponemos en modo output el led 
  pinMode(ledSalida, OUTPUT);
  digitalWrite(ledSalida, estado);    //Lo encendemos
 
  //Adjuntamos al interruptor 0 ( pin 2 ) la funcion cambios, cuando suceda un CHANGE
  attachInterrupt(Interruptor, cambios, RISING);
}  
 
void loop() 
{
  //Simulamos un proceso complicado o largo
  for (int i = 0; i < 100; i++)
  {
    // "hacemos algo dificil y repetitivo" :P
    delay(10);
  }
}
//Esta seria nuestra funcion critica.
void cambios()
{
  estado = !estado;
  digitalWrite(ledSalida, estado);
}
