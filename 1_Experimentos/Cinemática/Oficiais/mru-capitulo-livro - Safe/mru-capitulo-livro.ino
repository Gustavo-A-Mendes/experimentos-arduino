/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   BACHARELADO EM CIENCIAS E TECNOLOGIA - BCT
   O programa calcula o intervalo de tempo entre três sensores
   infravermelho,
   e determina se o movimento é uniforme ou uniformemente variado
   Este programa poderá ser usado para se determinar a aceleração
   gravitacional
*/

const int sensorBotao = 12;                          // o botão deverá ser ligado no pino digital 12
const int ledVerde = 7;                             // o LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6;                          // o LED vermelho deverá ser ligado no pino digital 6
const int sensorInicial = 2;                        // configura o pino digital 2 para o PRIMEIRO SENSOR
const int sensorUM = 3;                           // configura o pino digital 3 para o SEGUNDO SENSOR
const int sensorDOIS = 4;                           // configura o pino digital 4 para o TERCEIRO SENSOR

bool inicioAtivo = false;                           // os inicia desativado
int iniciar = 0;

int estadoInicial, estadoUM, estadoDOIS;            // variáveis que guardam os estados dos sensores
long instanteInicial, instanteUM, instanteDOIS;     // tempo decorrido pelo programa até os sensores
long interTempoInicial, interTempoUM, interTempoDOIS;                  // tempo decorrido nos intervalos
float deslocamentoUM = 300.0;                       // distancia sugerida em milimetro até o sensor 1.
// Mude a medida se for conveniente
float deslocamentoDOIS = 600.0;                     // distancia sugerida em milimetro até o sensor 2.
// Mude a medida se for conveniente
float velocidadeUM, velocidadeDOIS;
long tempoTotal = 3000;                             // tempo de espera para efetuar nova leitura

long interTempoMedio;
float velocidadeMedia;
int sensores = 0;

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
  pinMode(sensorInicial, INPUT);                    // configura o pino 2 como entrada
  pinMode(sensorUM, INPUT);                         // configura o pino 3 como entrada
  pinMode(sensorDOIS, INPUT);                       // configura o pino 4 como entrada
  pinMode(sensorBotao, INPUT);                      // configura o pino 12 como entrada
  digitalWrite(ledVermelho, HIGH);                  // desliga LED vermelho
  digitalWrite(ledVerde, HIGH);                     // desliga LED verde
}

void loop() {
  digitalWrite(ledVerde, HIGH);                     // liga o LED verde
  digitalWrite(ledVermelho, HIGH);                   // desliga o LED Vermelho
  inicioAtivo = digitalRead(sensorBotao);             // ler o botão e armazena em servoAtivo

  // se o botão for ativado, o servo ativa e inicia o código
  while (inicioAtivo == HIGH) {
    if (iniciar == 0) {
      iniciar = 1;
      digitalWrite(ledVerde, LOW);                 // desliga o LED verde
      digitalWrite(ledVermelho, LOW);              // desliga o LED Vermelho
      Serial.println(".....................................................");
      Serial.println("PREPARANDO...");
      delay(3000);
      Serial.println("=== LIBERE O OBJETO ===");

      digitalWrite(ledVerde, HIGH);                // pisca os dois LEDs
      digitalWrite(ledVermelho, HIGH);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledVermelho, HIGH);
    }

    switch (sensores) {
      case 0:
        estadoInicial = digitalRead(sensorInicial);               // ler o sensorDOIS e armazena em estadoDOIS
        if (estadoInicial == LOW) {
          digitalWrite(ledVerde, LOW);                 // liga o LED verde
          digitalWrite(ledVermelho, HIGH);               // desliga o LED Vermelho
          instanteInicial = millis();                        // armazena o tempo Total decorrido para SensordOIS

          sensores++;
        }
        else {
          digitalWrite(ledVerde, LOW);                    // desliga os LEDs verde e vermelho
          digitalWrite(ledVermelho, LOW);
        }
        break;

      case 1:
        estadoUM = digitalRead(sensorUM);                 // ler o sensorUM e armazena em estadoUM
        if (estadoUM == LOW) {
          digitalWrite(ledVerde, LOW);                   // liga o LED verde
          digitalWrite(ledVermelho, HIGH);                 // desliga o LED vermelho
          instanteUM = millis();                          // armazena o tempo Total decorrido para SensorUM
          interTempoUM = instanteUM - instanteInicial;

          velocidadeUM = (0.001 * deslocamentoUM) / (0.001 * interTempoUM);

          sensores++;
        }
        else {
          digitalWrite(ledVerde, LOW);                    // desliga os LEDs verde e vermelho
          digitalWrite(ledVermelho, LOW);
        }
        break;

      case 2:
        estadoDOIS = digitalRead(sensorDOIS);             // ler o sensorDOIS e armazena em estadoDOIS
        if (estadoDOIS == LOW) {
          digitalWrite(ledVerde, HIGH);                    // desliga LED verde
          digitalWrite(ledVermelho, HIGH);                // liga LED vermelho
          instanteDOIS = millis();                        // armazena o tempo Total decorrido para sensorDOIS
          interTempoDOIS = instanteDOIS - instanteInicial;     // cálculo do primeiro intervalo de tempo

          velocidadeDOIS = (0.001 * deslocamentoDOIS) / (0.001 * interTempoDOIS);

          Serial.println(".................................................................");
          Serial.print(" d1 (m) = ");
          Serial.print(0.001 * deslocamentoUM, 3);
          Serial.print("\t\t |\t\t d2 (m) = ");
          Serial.println(0.001 * deslocamentoDOIS, 3);
          Serial.print(" t1 (s) = ");
          Serial.print(0.001 * interTempoUM, 3);          // imprime no monitor serial o Primeiro Intervalo de Tempo
          Serial.print("\t\t |\t\t t2 (s) = ");
          Serial.println(0.001 * interTempoDOIS, 3);      // imprime no monitor serial o Segundo Intervalo de Tempo
          Serial.println(".................................................................");
          Serial.print(" v1 (m/s) = ");
          Serial.print(velocidadeUM, 3);
          Serial.print("\t |\t\t v2 (m/s) = ");
          Serial.println(velocidadeDOIS, 3);
          Serial.println(".....................................................");
          Serial.println(".....................................................");
          Serial.println("Qual o tipo de movimento descrito pelo objeto?");
          Serial.println(".....................................................");


          delay(tempoTotal);
          sensores = 0;
          iniciar = 0;                          // a variável do tempo inicial será limpa
          inicioAtivo = LOW;                             // o código sai da estrutura while

        }
        else {
        }
        break;
    }
  }
}
