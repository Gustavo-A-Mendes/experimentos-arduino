
/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   BACHARELADO EM CIENCIAS E TECNOLOGIA - BCT
   O programa calcula o intervalo de tempo entre três sensores
   infravermelho,
   e determina se o movimento é uniforme ou uniformemente variado
   Este programa poderá ser usado para se determinar a aceleração
   gravitacional
*/

#include <Servo.h>

Servo meuServo;
bool servoAtivo = false;                            // o servomotor inicia desativado
int fechado = 175;                                  // posicao de inicial do servomotor
int aberto = 120;                                   // posicao de abertura do servomotor
int atraso = 250;                                   // atraso necessário para a bola ser totalmente liberada

const int servoBotao = 12;                          // o botão deverá ser ligado no pino digital 12
const int ledVerde = 7;                             // o LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6;                          // o LED vermelho deverá ser ligado no pino digital 6
const int sensorIR = 3;                             // configura o pino digital 3 para o sensor
int estadoIR;                                       // variável que guarda o estado do sensor
long instanteIR;                                    // tempo decorrido pelo programa até o sensor
long instanteInicial;                               // tempo decorrido antes de ativar o servomotor
long interTempoIR;                                  // intervalo decorrido do início até o sensor
float deslocamentoIR = 900.0;                       // distância sugerida, em milimetros, até o sensor.
// Mude se for conveniente.
float gravidade;                                    // variáveis que guardam a gravidade em cada instante
float gravidadeMedia;
int i = 0;

float velocidade;
long tempoTotal = 3000;                             // tempo de espera para efetuar nova leitura

void setup() {
  Serial.begin(9600);

  Serial.println(".....................................................");
  Serial.println("TESTES DE EXPERIMENTOS FÍSICOS COM ARDUINO");
  Serial.println(".....................................................");
  delay(1000); // pausa de 1 segundos
  Serial.println(".....................................................");
  Serial.println("=== CINEMATICA ===");
  Serial.println(".....................................................");
  delay(1000); // pausa de 1 segundos
  Serial.println(".....................................................");
  Serial.println("Afericao da Aceleracao Gravitacional (g)");
  Serial.println(".....................................................");
  delay(500); // pausa de 0.5 segundos
  Serial.println("=== APERTE O BOTAO PARA INICIAR O EXPERIMENTO ===");
  Serial.println(".....................................................");
  delay(500); // pausa de 0.5 segundos

  pinMode(ledVermelho, OUTPUT);                     // configura o pino 6 como saída
  pinMode(ledVerde, OUTPUT);                        // configura o pino 7 como saída
  pinMode(sensorIR, INPUT);                         // configura o pino 3 como entrada
  pinMode(servoBotao, INPUT);                       // configura o pino 12 como entrada
  digitalWrite(ledVermelho, HIGH);                  // desliga LED vermelho
  digitalWrite(ledVerde, HIGH);                     // desliga LED verde
  meuServo.attach(9);                               // configura o pino 9 como saída do servomotor
  meuServo.write(fechado);                          // posição em que o servomotor inicia
}

void loop() {
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledVermelho, HIGH);                  // desliga LED verde e vermelho
  servoAtivo = digitalRead(servoBotao);             // ler o botão e armazena em servoAtivo

  // se o botão for ativado, o servo ativa e inicia o código
  while (servoAtivo == HIGH) {
    if (instanteInicial == 0) {
      digitalWrite(ledVerde, LOW);                  // desliga o LED verde
      digitalWrite(ledVermelho, LOW);               // desliga os LEDs vermelho
      Serial.println(".....................................................");
      Serial.println("PREPARANDO...");
      delay(3000);
      Serial.println("=== LIBERANDO O OBJETO ===");
      meuServo.write(aberto);                       // abrir a porta
      delay(atraso);                                // espera até a bola ser totalmente liberada
      instanteInicial = millis();                   // armazenar o tempo quando a bola foi liberada
      digitalWrite(ledVerde, LOW);                  // desliga o LED verde
      digitalWrite(ledVermelho, HIGH);              // liga o LED vermelho
    }

    estadoIR = digitalRead(sensorIR);               // ler o sensorIR e armazena em estadoIR
    if (estadoIR == LOW) {
      digitalWrite(ledVerde, HIGH);                 // liga LED Verde
      digitalWrite(ledVermelho, LOW);              // liga LED Vermelho
      instanteIR = millis();                        // armazena o tempo Total decorrido para SensorIR
      interTempoIR = instanteIR - instanteInicial;
      gravidade = (2 * 0.001 * deslocamentoIR) / sq(0.001 * interTempoIR);
      velocidade = 0.001 * interTempoIR * gravidade;

      /*
      gravidadeMedia += gravidade;
      i++;
      Serial.print("Medida ");
      Serial.print(i);
      Serial.println(" aferida");
      if (i == 10) {
        Serial.println(gravidadeMedia / 10);
      }
      
      */
      Serial.println(".....................................................");
      Serial.print(" distância = ");
      Serial.print(0.001 * deslocamentoIR);
      Serial.println(" m");

      Serial.print(" tempo = ");
      Serial.print(0.001 * interTempoIR);
      Serial.println(" s");

      Serial.println(".....................................................");
      Serial.println("|||| Velocidade ||||");
      Serial.print("\n v = ");
      Serial.print(velocidade);
      Serial.println(" m/s");
      Serial.println("\n.....................................................");

      Serial.println(".....................................................");
      Serial.println("|||| Aceleracao no Plano ||||");
      Serial.print("\n g = ");
      Serial.print(gravidade);                      // imprime no monitor serial o valor aproximado da aceleração gravitacional
      Serial.println(" m/s^2");
      Serial.println("\n.....................................................");
      

      delay(tempoTotal);                            // tempo de espera para efetuar nova leitura
      instanteInicial = 0;                          // a variável do tempo inicial será limpa
      meuServo.write(fechado);                      // o servomotor volta ao estado inicial
      servoAtivo = LOW;                             // o código sai da estrutura while

    }
    else {
    }
  }
}
