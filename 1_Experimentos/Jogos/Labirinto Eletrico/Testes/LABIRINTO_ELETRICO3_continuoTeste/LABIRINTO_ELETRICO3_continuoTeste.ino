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
int pinoLabirinto = 3;
int pinoBuzzer = 9;
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
  Serial.begin(9600);
}
// A função loop é executada repetitivamente até se desligar o Arduino
void loop() {
  Serial.println(nivel);
  estadoBotao = digitalRead(pinoLabirinto);
  if (estadoBotao == LOW) {  
    nivel++;
  }
    // estabelece um comportamento para cada estado de nivel
  switch (nivel) {
    case 0:
      tentativas();
      break;
    case 1:
      deltaT = 300;
      tomBuzzer = 3000;
      tentativas();
      break;
    case 2:
      deltaT = 150;
      tomBuzzer = 3500;
      tentativas();
      break;
    case 3:
      deltaT = 100;
      tomBuzzer = 4000;
      tentativas();
      break;
    case 4:
      deltaT = 1000;
      tomBuzzer = 500;
      tentativas();
      break;
  }
}
// funcao que contabiliza as tentativas e emite um sinal caracteristico
void tentativas() {
  if (nivel >= 1) {
    if (nivel < 4) {
      
      if(estadoBuzzer){
        tone(pinoBuzzer, tomBuzzer, deltaT);
      }
      else {
        noTone(pinoBuzzer);
        
      }
      estadoBuzzer = !estadoBuzzer;
      delay(deltaT/2);
      /*
      for (int i = 0; i < 5; i++) {  
        tone(pinoBuzzer, tomBuzzer, deltaT/2);
        delay(deltaT);
        noTone(pinoBuzzer);
      }
      */
    }
    else {
      tone(pinoBuzzer, tomBuzzer, deltaT);
      delay(1000);
      // nivel = 0;
      while (true) {
        Serial.println("");
      }
    }
  }
}
