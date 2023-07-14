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
const int sensorUM = 3;                             // configura o pino digital 3 para o PRIMEIRO SENSOR
const int sensorDOIS = 4;                           // configura o pino digital 3 para o SEGUNDO SENSOR
int estadoUM, estadoDOIS;                           // variáveis que guardam os estados dos sensores
long instanteUM, instanteDOIS;                      // tempo decorrido pelo programa até os sensores
long instanteInicial;                               // tempo decorrido antes de ativar o servomotor
long interTempoUM;                                  // tempo decorrido no primeiro intervalo
long interTempoDOIS;                                // tempo decorrido no segundo intervalo
float deslocamentoUM = 500.0;                       // distância sugerida, em milimetros, até o sensor.
// Mude se for conveniente.
float deslocamentoDOIS = 500.0;                     // distância sugerida, em milimetros, até o sensor.
// Mude se for conveniente.
// float aceleracao;                                   // variável que guarda a gravidade no instanteIR
// float velocidade;




float velUM, velDOIS;

long tempoTotal = 3000;

void setup() {
  Serial.begin(9600);

  Serial.println(".....................................................");
  Serial.println("TESTES DE EXPERIMENTOS FÍSICOS COM ARDUINO");
  Serial.println(".....................................................");
  delay(1000); // pausa de 1 segundos
  Serial.println(".....................................................");
  Serial.println("CINEMATICA");
  Serial.println(".....................................................");
  delay(1000); // pausa de 1 segundos
  Serial.println(".....................................................");
  Serial.println("Analise do tipo de movimento e Calculo da Velocidade");
  Serial.println(".....................................................");
  delay(500); // pausa de 0.5 segundos
  Serial.println("::INICIE O EXPERIMENTO::");
  Serial.println(".....................................................");
  delay(500); // pausa de 0.5 segundos

  pinMode(ledVermelho, OUTPUT);                     // configura o pino 6 como saída
  pinMode(ledVerde, OUTPUT);                        // configura o pino 7 como saída
  pinMode(sensorUM, INPUT);                         // configura o pino 2 como entrada
  pinMode(sensorDOIS, INPUT);                       // configura o pino 3 como entrada
  pinMode(sensorTRES, INPUT);                       // configura o pino 4 como entrada
  digitalWrite(ledVermelho, LOW);                   // desliga LED vermelho
  digitalWrite(ledVerde, LOW);                      // desliga LED verde
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

    estadoUM = digitalRead(sensorUM);                 // ler o sensorUM e armazena em estadoUM
    if (estadoUM == LOW) {
      digitalWrite(ledVerde, LOW);                   // liga o LED verde
      digitalWrite(ledVermelho, HIGH);                 // desliga o LED vermelho
      interTempoUM = instanteUM - instanteInicial;    // armazena o tempo Total decorrido para SensorUM
      velUM = (0.001 * deslocamentoUM) / (0.001 * interTempoUM);
    }
    else {
      digitalWrite(ledVerde, LOW);                    // desliga os LEDs verde e vermelho
      digitalWrite(ledVermelho, LOW);
    }

    estadoDOIS = digitalRead(sensorDOIS);             // ler o sensorDOIS e armazena em estadoDOIS
    if (estadoDOIS == LOW) {
      digitalWrite(ledVerde, HIGH);                    // desliga LED verde
      digitalWrite(ledVermelho, HIGH);                // liga LED vermelho
      instanteDOIS = millis();                        // armazena o tempo Total decorrido para sensorDOIS
      interTempoDOIS = (instanteDOIS - instanteUM);     // cálculo do primeiro intervalo de tempo
      velDOIS = (0.001 * deslocamentoDOIS) / (0.001 * interTempoDOIS);


      Serial.println(".................................................................");
      Serial.print(" d1 (m) = ");
      Serial.print(0.001 * deslocamentoUM, 3);
      Serial.print("\t | d2 (m) = ");
      Serial.println(0.001 * deslocamentoDOIS, 3);
      Serial.print(" t1 (s) = ");
      Serial.print(0.001 * interTempoUM, 3);          // imprime no monitor serial o Primeiro Intervalo de Tempo
      Serial.print("\t | t2 (s) = ");
      Serial.println(0.001 * interTempoDOIS, 3);      // imprime no monitor serial o Segundo Intervalo de Tempo
      Serial.println(".................................................................");
      Serial.print(" v1 (m/s) = ");
      Serial.print(velUM, 3);
      Serial.print("\t | v2 (m/s) = ");
      Serial.println(velDOIS, 3);
      Serial.println(".....................................................");
      Serial.println(".....................................................");
      Serial.println("Qual o tipo de movimento descrito pelo objeto?");
      Serial.println(".....................................................");

      instanteInicial = 0;                          // a variável do tempo inicial será limpa
      meuServoUM.write(fechadoUM);                  // o servomotor volta ao estado inicial
      meuServoDOIS.write(fechadoDOIS);              // o servomotor volta ao estado inicial
      servoAtivo = LOW;                             // o código sai da estrutura while

      delay(tempoTotal);                            // tempo de espera para efetuar nova leitura

    }
    else {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, LOW);                 // desliga os LED verde e Vermelho
    }
  }
