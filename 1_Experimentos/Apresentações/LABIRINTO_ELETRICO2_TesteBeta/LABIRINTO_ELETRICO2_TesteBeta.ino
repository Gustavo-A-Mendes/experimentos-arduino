/* Copie 100% deste documento e cole na área de programação do Arduino IDE */
/* *********************** Nervo Teste do Manual do Mundo ***********************
   Criado por: Anderson Harayashiki Moreira
   Rev.: 02
   Data: 25.02.2018
   Guia de conexão:
   LED indicativo: Pino 2
   Labirinto: Pino 3
   Botão: Pino 7
   Buzzer: Pino 9
   Módulo Relé (Sirene): Pino 10
 ***************************************************************************** */
// Declaração dos pinos utilizados do Arduino
const int pinoLabirinto = 11;
const int pinoBuzzer = 5;

// Declaração dos LEDs de aviso.
const int ledVERDE = 2;
const int ledAMARELO = 3;
const int ledVERMELHO = 4;

// Declaração das variáveis auxiliares
int nivel = 0;
int deltaT;
int tomBuzzer;
int estadoBotao = HIGH;
int estadoBuzzer = LOW;

// A função setup é apenas executada uma vez ao se iniciar o Arduino, aqui configuramos nossa placa Arduino
void setup() {
  // Pinos configurados como entrada:
  pinMode(pinoLabirinto, INPUT_PULLUP); // Configurando a entrada como INPUT_PULLUP, utilizamos o resistor interno pull-up do Arduino
  //=======  pinMode(pinoBotao, INPUT);
  // Pinos configurados como saída:
  pinMode(pinoBuzzer, OUTPUT);
  pinMode(ledVERDE, OUTPUT);
  pinMode(ledAMARELO, OUTPUT);
  pinMode(ledVERMELHO, OUTPUT);
  Serial.begin(9600);
}
// A função loop é executada repetitivamente até se desligar o Arduino
void loop() {
  Serial.println(nivel);
  estadoBotao = digitalRead(pinoLabirinto);
  if (estadoBotao == LOW) {
    nivel++;
    // estabelece um comportamento para cada estado de nivel
    switch (nivel) {
      case 0:
        tentativas();
        break;
      case 1:
        deltaT = 150;
        tomBuzzer = 3500;
        tentativas();
        break;
      case 2:
        deltaT = 100;
        tomBuzzer = 4000;
        tentativas();
        break;
      case 3:
        deltaT = 1000;
        tomBuzzer = 500;
        tentativas();
        break;
        /*
          case 4:
          deltaT = 1000;
          tomBuzzer = 500;
          tentativas();
          break;
        */
    }
  }
}

// funcao que contabiliza as tentativas e emite um sinal caracteristico
void tentativas() {
  if (nivel >= 1) {
    if (nivel < 3) {
      for (int i = 0; i < 5; i++) {
        tone(pinoBuzzer, tomBuzzer, deltaT / 2);
        pisca();
        delay(deltaT);
      }
      noTone(pinoBuzzer);
    }
    else {
      tone(pinoBuzzer, tomBuzzer);
      pisca();
      noTone(pinoBuzzer);
      nivel = 0;
    }
  }

  delay(4500);
  tone(pinoBuzzer, 2000, 100);
  delay(100);
  noTone(pinoBuzzer);
}


void pisca() {
  bool estadoPisca = HIGH;
  if (nivel == 1) {
    digitalWrite(ledVERDE, HIGH);
    digitalWrite(ledAMARELO, LOW);
    digitalWrite(ledVERMELHO, LOW);
  }
  else if (nivel == 2) {
    digitalWrite(ledVERDE, HIGH);
    digitalWrite(ledAMARELO, HIGH);
    digitalWrite(ledVERMELHO, LOW);
  }
  else if (nivel == 3) {
    for (int i = 0; i < 10; i++) {
      if (estadoPisca) {
        digitalWrite(ledVERDE, HIGH);
        digitalWrite(ledAMARELO, HIGH);
        digitalWrite(ledVERMELHO, HIGH);
      }
      else {
        digitalWrite(ledVERDE, LOW);
        digitalWrite(ledAMARELO, LOW);
        digitalWrite(ledVERMELHO, LOW);
      }
      estadoPisca = !estadoPisca;
      delay(250);

    }
  }
  else {
    digitalWrite(ledVERDE, LOW);
    digitalWrite(ledAMARELO, LOW);
    digitalWrite(ledVERMELHO, LOW);
  }
}
