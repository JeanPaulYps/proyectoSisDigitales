//Definir variables
int posicionSeleccionada = 0;
int posicionPrevia = 0;

int jugador = 1;
boolean juegoTerminado = false;


int botonSeleccion = 2;
int valorBotonSeleccion = LOW;
int botonMover = 3;
int valorBotonMover = LOW;

//Temporizadores
// Para el jugador
unsigned long temporizadorJugador = 0;
// Para la seleccion
unsigned long temporizadorSeleccion = 0;

int cicloSeleccion = LOW;
int cicloJugador = LOW;

//Led 0 es la esquina superior izquierda
int L0 = 13;
int L1 = 10;
int L2 = 7;
int L3 = 12;
int L4 = 9;
int L5 = 6;
int L6 = 11;
int L7 = 8;
int L8 = 5;

//Arreglo de leds y de tablero
int LEDS [9] = {L0,L1,L2,L3,L4,L5,L6,L7,L8};
int tablero [9] = {0,0,0,0,0,0,0,0,0};

int obtenerPosicionLED (int posicion)
{
  return LEDS[posicion];
}
void cambiarEstadoLED (int posicion, int estado)
{
  digitalWrite(LEDS[posicion], estado);
}

int obtenerValorTablero (int posicion)
{
  return tablero[posicion];
}

void ponerValorTablero (int posicion, int valor)
{
  tablero[posicion] = valor;
}

void cambiarJugador ()
{
  if (jugador == 1) jugador = 2;
  else jugador = 1;
}

void ganar (int led1, int led2, int led3) {
  cambiarJugador();
  for(int led = 0; led <= 8; led++) {
    cambiarEstadoLED(led, LOW);
  }
  ponerValorTablero(led1, jugador);
  ponerValorTablero(led2, jugador);
  ponerValorTablero(led3, jugador);
}
bool puedeCambiarPosicion ()
{
  for (int i = 0; i < 9; i ++)
  {
    if (obtenerValorTablero(i) == 0)
    {
      return true;
    }
  }
  return false;
}
int cambiarPosicion (int actual){
  int posicion = 0;
  for (int i = 1; i <= 9; i ++)
  {
    if (obtenerValorTablero((actual + i)%9) == 0 || obtenerValorTablero((actual + i)%9) == 3)
    {
      posicion = (actual + i)%9;
      break;
    }
  }
  //Quitar despues
  return posicion;
}

void setup()
{
  for(int led = 0; led < 9; led++) {
    pinMode(obtenerPosicionLED(led), OUTPUT);
  }
  pinMode(botonSeleccion, INPUT);
  pinMode(botonMover, INPUT);
  Serial.begin(9600);  
}

void loop()
{
  if((unsigned long)(millis() - temporizadorSeleccion) >= 100) {
      cicloSeleccion = !cicloSeleccion;
      temporizadorSeleccion = millis();
    }
  if((unsigned long)(millis() - temporizadorJugador) >= 350) {
      cicloJugador = !cicloJugador;
      temporizadorJugador = millis();
  }
  for(int led = 0; led <= 8; led++) 
  {
    if (obtenerValorTablero(led) == 0)
    {
      digitalWrite(obtenerPosicionLED(led), LOW);
    }
    else if (obtenerValorTablero(led) == 1)
    {
      digitalWrite(obtenerPosicionLED(led), HIGH);
    }
    else if (obtenerValorTablero(led) == 2)
    {
      digitalWrite(obtenerPosicionLED(led), cicloJugador);
    }
    else if (obtenerValorTablero(led) == 3)
    {
      digitalWrite(obtenerPosicionLED(led), cicloSeleccion);
    }
    
  }
  valorBotonMover = digitalRead(botonMover);
  valorBotonSeleccion = digitalRead(botonSeleccion);
  delay(200);
  posicionPrevia = posicionSeleccionada;
  if (valorBotonMover == HIGH && puedeCambiarPosicion())
  {
    posicionSeleccionada = cambiarPosicion(posicionPrevia);
    Serial.println("Mover");
    Serial.println(posicionSeleccionada);
    Serial.println(posicionPrevia);
    ponerValorTablero(posicionSeleccionada, 3);
    ponerValorTablero(posicionPrevia, 0);
  }
  else if (valorBotonSeleccion == HIGH && puedeCambiarPosicion())
  {
    posicionSeleccionada = cambiarPosicion(posicionPrevia);
    Serial.println("Seleccion");
    Serial.println(posicionSeleccionada);
    Serial.println(posicionPrevia);
    ponerValorTablero(posicionPrevia, jugador);
    cambiarJugador();
  }
  if (obtenerValorTablero(posicionSeleccionada) == 0)
  {
    ponerValorTablero(posicionSeleccionada, 3);
  }
 
}