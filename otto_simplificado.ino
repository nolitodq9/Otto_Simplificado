
/* Programa que imita o comportamento dun robot Otto simplificado.

As conexións aos servos son as que se indican a seguir.
         --------------- 
        |     O   O     |
        |---------------|
LR 3==> |               | <== LL 2
         --------------- 
            ||     ||
            ||     ||
FR 5==>   -----   ------  <== FL 4
         |-----   ------|
         
O zumbador vai conectado no pin 13 e o sensor de distancia HC-SR04 
nos pins 9 (echo) e 8 (trigger).

A función loop() vai facendo chamadas a funcións definidas aparte. NON inclúe máis
código que chamdas a función externas.

Autor: Manuel Dominguez
Data: 28/03/2021
*/



#include <Servo.h>		//añadimos a biblioteca servo

// Definicións do sensor HC-SR04
#define ECHO           9	// Pin 9 = o sensor emite ultrasóns
#define TRIGGER        8	// Pin 8 = o sensor "escoita" os ultrasóns emitidos
#define DIST_MAX       200	// Defínese o alcance máximo do sensor
#define UMBRAL_DIST    12	// 12 cm definimos a distancia que sexa umbral

NewPing sonar(TRIGGER, ECHO, DIST_MAX); //Obxeto sensor de distancia para <NewPing.h>
#define calcDist(t) t*0.017  //Fórmula para calcular distancia en cm

// Buzzer
#define BUZZER   13			// Indicamos que o Buzzer está no pin 13

// Definicións dos servos, asociadondo o control de cada un dos 4 servos a un pin
#define FR       5  // Pé dereito (Right Foot) = pin 5
#define LR       3  // Perna esquerda (Right Leg) = pin 3
#define FL       4  // Pé esquerdo (Left Foot) = pin 4
#define LL       2  // Perna esquerda (Left Leg) = pin 2

Servo peDer, pernaDer, peIzq, pernaIzq;  // Asociamos as seguintes nomenclaturas a que sn Servos.

void setup() {			// 
  Serial.begin(9600);			// Velocidade comunicacións = 9600 baudios
  pinMode(TRIGGER, OUTPUT);		// TRIGGER = SAÍDA
  pinMode(ECHO, INPUT);			// ECHO = ENTRADA
  pinMode(BUZZER, OUTPUT);		// BUZZER = SAÍDA
  peDer.attach(FR);				// Asignamos un pin dixital (5) a "peDer.attach (FR)" que é un obxeto motor
  pernaDer.attach(LR);			// Asignamos un pin dixital (3) a "pernaDer.attach (FR)", que é un obxeto motor
  peIzq.attach(FL);				// Asignamos un pin dixital (4) a "peIzq.attach (FR)", que é un obxeto motor
  pernaIzq.attach(LL);			// Asignamos un pin dixital (2) a "pernaIzq.attach (FR)", que é un obxeto motor
}

void loop() {					// Estructura do programa que se executa de forma constante
  demasiadoProximo();			// Función que se encarga de dicir se hai algo próximo ao sensor
}

// Funciones externas

// Función que indica si el objeto está demasiado cerca (true) o no (false)
bool demasiadoProximo() {   							// Empregamos termino booleano (true or false), e a función para calcular a distancia
  bool zumbar = false;									// Partimos da base que zumbar sexa falso
  if (calcDist(sonar.ping_cm()) < UMBRAL_DIST) {		// condición na que a función calCdist si a medición do sensor é menor ca o umbral, zumbar = true
    zumbar = true;
    zumbarBuzzer(BUZZER, HIGH);							// Activar o zumbador
  } else {												// Se non sucede o anterior fai isto
    zumbarBuzzer(BUZZER, LOW);							// Non activar o zumbador
  }
  return zumbar;										// Devolve o resultado de zumbar
}

// Función que calcula la distancia al objeto en cm
// Incluye una espera de 50 ms
float distanciaObjeto() {					// Añadimos un float na función distanciObjeto para te un resultado con decimais
  digitalWrite(TRIGGER, LOW);				// Dicimos que o TRIGGER se apague para asegurar que comeza a funcionar acto seguido
  delayMicroseconds(5);						// Espera 5 us
  digitalWrite(TRIGGER, HIGH);				// Activa o TRIGGER
  delayMicroseconds(10);					// Agarda 10 us
  digitalWrite(TRIGGER, LOW);				// Desactiva o TRIGGER
  unsigned int duration = pulseIn(ECHO, HIGH); // Declara a variable duración coma un enteiro sen signo (so valores positivos), e emprega a función pulseIn para medir a duración dun pulso no pin Echo
  float distance = calcDist(duration); 			// Declara que distancia é igual ao resultado da duración da función calcDist
  return distance;								// Devolve o valor de distancia
}

// Función que hace sonar el zumbador durante 200 ms
void zumbarBuzzer(int pin, int level) {
  digitalWrite(pin, level);
  delay(200);
}

