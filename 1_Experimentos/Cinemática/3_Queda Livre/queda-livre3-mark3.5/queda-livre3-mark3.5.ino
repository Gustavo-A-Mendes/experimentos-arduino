
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
int atraso = 162;                                   // atraso necessário para a bola ser totalmente liberada
const int servoBotao = 12;                          // o botão deverá ser ligado no pino digital 12
const int ledVerde = 7;                             // o LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6;                          // o LED vermelho deverá ser ligado no pino digital 6
const int sensorUM = 2;                             // configura o pino digital 2 para o PRIMEIRO SENSOR
const int sensorDOIS = 3;                           // configura o pino digital 3 para o SEGUNDO SENSOR
int estadoUM, estadoDOIS;                           // variáveis que guardam os estados dos sensores
long instanteUM, instanteDOIS;                      // tempo decorrido pelo programa até os sensores
long instanteInicial;                               // tempo decorrido antes de ativar o servomotor
long interTempoUM, interTempoDOIS;                  // intervalo decorrido do início até os sensores
float deslocamentoUM = 500.0;                       // distância sugerida, em milimetros, até o sensor 1.
                                                    // Mude se for conveniente.
float deslocamentoDOIS = 900.0;                     // distância sugerida, em milimetros, até o sensor 2.
                                                    // Mude se for conveniente.
float gravidadeUM, gravidadeDOIS;                   // variáveis que guardam a gravidade em cada instante
float gravidadeMedia;

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
  pinMode(sensorUM, INPUT);                         // configura o pino 3 como entrada
  pinMode(sensorDOIS, INPUT);                       // configura o pino 4 como entrada
  pinMode(servoBotao, INPUT);                       // configura o pino 12 como entrada
  digitalWrite(ledVermelho, LOW);                   // desliga LED vermelho
  digitalWrite(ledVerde, LOW);                      // desliga LED verde
  meuServo.attach(9);                               // configura o pino 9 como saída do servomotor
  meuServo.write(175);                              // posição em que o servomotor inicia
}

void loop() {
  servoAtivo = digitalRead(servoBotao);             // ler o botão e armazena em servoAtivo

  // se o botão for ativado, o servo ativa e inicia o código
  while (servoAtivo == HIGH) {
    if (instanteInicial == 0) {
      Serial.println(".....................................................");
      Serial.println("PREPARANDO...");
      delay(3000);
      Serial.println("=== LIBERANDO O OBJETO ===");
      meuServo.write(120);                          // abrir a porta
      delay(atraso);                                // espera até a bola ser totalmente liberada
      instanteInicial = millis();                   // armazenar o tempo quando a bola foi liberada
    }
    
    estadoUM = digitalRead(sensorUM);               // ler o sensorUM e armazena em estadoUM
    if (estadoUM == LOW) {
      digitalWrite(ledVerde, HIGH);                 // desliga LED verde
      digitalWrite(ledVermelho, LOW);               // liga LED vermelho
      instanteUM = millis();                        // armazena o tempo Total decorrido para SensorUM
      interTempoUM = instanteUM - instanteInicial;
      gravidadeUM = (2 * 0.001 * deslocamentoUM) / pow(0.001 * interTempoUM, 2);
    }
    else {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, LOW);               // desliga os LEDs verde e Vermelho
    }

    estadoDOIS = digitalRead(sensorDOIS);           // ler o sensorDOIS e armazena em estadoDOIS
    if (estadoDOIS == LOW) {
      digitalWrite(ledVerde, LOW);                  // liga LED Verde
      digitalWrite(ledVermelho, HIGH);              // liga LED Vermelho
      instanteDOIS = millis();                      // armazena o tempo Total decorrido para SensordOIS
      interTempoDOIS = instanteDOIS - instanteInicial;
      gravidadeDOIS = (2 * 0.001 * deslocamentoDOIS) / pow(0.001 * interTempoDOIS, 2);

      gravidadeMedia = (gravidadeUM + gravidadeDOIS) / 2;
      
      Serial.println(".................................................................");
      Serial.print(" |||| Aceleracao Gravitacional (em m/s^2) |||| g_Média= ");
      Serial.println(gravidadeMedia);               // imprime no monitor serial o valor aproximado da aceleração gravitacional
      Serial.println(".................................................................");
      Serial.println(".................................................................");

      delay(3000);                                  // tempo de espera para efetuar nova leitura
      instanteInicial = 0;                          // a variável do tempo inicial será limpa
      meuServo.write(175);                          // o servomotor volta ao estado inicial
      servoAtivo = LOW;                             // o código sai da estrutura while
    }
    else {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, LOW);               // desliga LED verde e Vermelho
    }
  }
}
