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

Servo meuServoUM;
Servo meuServoDOIS;
bool servoAtivo = false;                            // os servomotores inicia desativado
int fechadoUM = 145;                                // posicao de inicial do servomotorUM
int fechadoDOIS = 90;                               // posicao de inicial do servomotorDOIS
int abertoUM = 90;                                  // posicao de abertura do servomotorUM
int abertoDOIS = 155;                               // posicao de abertura do servomotorDOIS
int atraso = 435;                                   // atraso necessário para a bola ser totalmente liberada

const int servoBotao = 12;                          // o botão deverá ser ligado no pino digital 12
const int ledVerde = 7;                             // o LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6;                          // o LED vermelho deverá ser ligado no pino digital 6
const int sensorIR = 3;                             // configura o pino digital 3 para o PRIMEIRO SENSOR
int estadoIR;                                       // variável que guarda o estado do sensor
long instanteIR;                                    // tempo decorrido pelo programa até o sensor
long instanteInicial;                               // tempo decorrido antes de ativar o servomotor
long interTempoIR;                                  // intervalo decorrido do início até o sensor
float deslocamentoIR = 1000.0;                      // distância sugerida, em milimetros, até o sensor.
                                                    // Mude se for conveniente.
float aceleracao;                                   // variável que guarda a gravidade no instanteIR
float velocidade;

int tempoTotal = 3000;

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
  Serial.println("Analise do tipo de movimento e Calculo da Aceleracao");
  Serial.println(".....................................................");
  delay(500); // pausa de 0.5 segundos
  Serial.println("=== APERTE O BOTAO PARA INICIAR O EXPERIMENTO ===");
  Serial.println(".....................................................");
  delay(500); // pausa de 0.5 segundos

  pinMode(ledVermelho, OUTPUT);                     // configura o pino 6 como saída
  pinMode(ledVerde, OUTPUT);                        // configura o pino 7 como saída
  pinMode(sensorIR, INPUT);                         // configura o pino 3 como entrada
  pinMode(servoBotao, INPUT);                       // configura o pino 12 como entrada
  digitalWrite(ledVermelho, LOW);                   // desliga LED vermelho
  digitalWrite(ledVerde, LOW);                      // desliga LED verde
  meuServoUM.attach(9);                             // configura o pino 9 como saída do servomotorUM
  meuServoDOIS.attach(10);                          // configura o pino 10 como saída do servomotorDOIS
  meuServoUM.write(fechadoUM);                      // posição em que o servomotorUM inicial
  meuServoDOIS.write(fechadoDOIS);                  // posição em que o servomotorDOIS inicial
}

void loop() {
  digitalWrite(ledVerde, HIGH);                     // liga o LED verde
  digitalWrite(ledVermelho, LOW);                   // desliga o LED Vermelho
  servoAtivo = digitalRead(servoBotao);             // ler o botão e armazena em servoAtivo

  // se o botão for ativado, o servo ativa e inicia o código
  while (servoAtivo == HIGH) {
    if (instanteInicial == 0) {
      Serial.println(".....................................................");
      Serial.println("PREPARANDO...");
      delay(3000);
      Serial.println("=== LIBERANDO O OBJETO ===");
      meuServoUM.write(abertoUM);                   // libera o objeto
      meuServoDOIS.write(abertoDOIS);
      delay(atraso);                                // espera até ser totalmente liberada
      instanteInicial = millis();                   // armazenar o tempo quando o objeto foi liberada
      digitalWrite(ledVerde, LOW);                  // desliga o LED verde
      digitalWrite(ledVermelho, LOW);              // desliga o LED Vermelho
    }

    estadoIR = digitalRead(sensorIR);               // ler o sensorDOIS e armazena em estadoDOIS
    if (estadoIR == LOW) {
      digitalWrite(ledVerde, LOW);                  // desliga o LED verde
      digitalWrite(ledVermelho, HIGH);              // liga o LED Vermelho
      instanteIR = millis();                        // armazena o tempo Total decorrido para SensordOIS
      interTempoIR = instanteIR - instanteInicial;

      aceleracao = (2 * 0.001 * deslocamentoIR) / sq(0.001 * interTempoIR);
      velocidade = 0.001 * interTempoIR * aceleracao;

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

      Serial.println("|||| Aceleracao no Plano ||||");
      Serial.print("\n a = ");
      Serial.print(aceleracao);                   // imprime no monitor serial o valor aproximado da aceleração no plano
      Serial.println(" m/s^2");
      Serial.println("\n.....................................................");

      instanteInicial = 0;                          // a variável do tempo inicial será limpa
      meuServoUM.write(fechadoUM);                  // o servomotor volta ao estado inicial
      meuServoDOIS.write(fechadoDOIS);              // o servomotor volta ao estado inicial
      servoAtivo = LOW;                             // o código sai da estrutura while

      delay(tempoTotal);                            // tempo de espera para efetuar nova leitura
    }
    else {
      digitalWrite(ledVermelho, LOW);               // desliga LED vermelho
      digitalWrite(ledVerde, LOW);                  // desliga o LED verde
    }
  }
}
