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
bool servoAtivo = false; // o servomotor inicia desativado
int atraso = 145; // atraso necessário para a bola ser totalmente liberada

const int servoBotao = 12; // o botão deverá ser ligado no pino digital 12
const int ledVerde = 7; // o LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6; // o LED vermelho deverá ser ligado no pino digital 6
const int sensorUM = 2; // configura o pino digital 2 para o PRIMEIRO SENSOR
const int sensorDOIS = 3; // configura o pino digital 3 para o SEGUNDO SENSOR
const int sensorTRES = 4; // configura o pino digital 4 para o TERCEIRO SENSOR

int estadoUM, estadoDOIS, estadoTRES; // variáveis que guardam os estados dos sensores
long instanteUM, instanteDOIS, instanteTRES; // tempo decorrido pelo programa até o respectivo sensor
long instanteInicial; // tempo decorrido antes de ativar o servomotor

long interTempoUM; // tempo decorrido no primeiro intervalo do início ao sensor 1
long interTempoDOIS ; // tempo decorrido no segundo intervalo do início ao sensor 2
long interTempoTRES ; // tempo decorrido no terceiro intervalo do início ao sensor 3

float deslocamentoUM = 131.0; // distância sugerida, em milimetros, entre o início e o sensor 1
float deslocamentoDOIS = 531.0; // distância sugerida, em milimetros, entre o início e o sensor 2
float deslocamentoTRES = 931.0; // distância sugerida, em milimetros, entre o início e o sensor 3

float gravidadeUM, gravidadeDOIS, gravidadeTRES; // variáveis que guardam a gravidade em cada instante
float gravidadeMedia;

void setup() {
  Serial.begin(9600);

  Serial.println(".....................................................");
  Serial.println("TESTES DE EXPERIMENTOS FÍSICOS COM ARDUINO");
  Serial.println(".....................................................");
  delay(1000); //Pausa de 1 segundos
  Serial.println(".....................................................");
  Serial.println("::CINEMATICA::");
  Serial.println(".....................................................");
  delay(1000); //Pausa de 1 segundos
  Serial.println(".....................................................");
  Serial.println("Afericao da Aceleracao Gravitacional (g)");
  Serial.println(".....................................................");
  delay(500); //Pausa de 0.5 segundos
  Serial.println("::INICIE O EXPERIMENTO::");
  Serial.println(".....................................................");
  delay(500); //Pausa de 0.5 segundos

  pinMode(ledVermelho, OUTPUT); // Configura o pino 6 como saída
  pinMode(ledVerde, OUTPUT); // Configura o pino 7 como saída
  pinMode(sensorUM, INPUT); // Configura o pino 2 como entrada
  pinMode(sensorDOIS, INPUT); // Configura o pino 3 como entrada
  pinMode(sensorTRES, INPUT); // Configura o pino 4 como entrada
  pinMode(servoBotao, INPUT); // Configura o pino 12 como entrada
  digitalWrite(ledVermelho, LOW); // desliga LED vermelho
  digitalWrite(ledVerde, LOW); // desliga LED verde

  meuServo.attach(9); // Configura o pino 9 como saída do servomotor
  meuServo.write(175); // posição em que o servomotor inicia
}

void loop() {
  servoAtivo = digitalRead(servoBotao); // Verifica se o botão foi apertado

  // essa estrutura while irá liberar a bola, dando inicio ao código, quando o botão for ativado
  while (servoAtivo == HIGH) {
    if (instanteInicial == 0) {
      Serial.println(".....................................................");
      Serial.println("PREPARANDO...");
      delay(3000);
      Serial.println("::LIBERANDO O OBJETO::");
      meuServo.write(120); // muda a posição da hélice do servomotor para liberar a bola
      delay(atraso);
      instanteInicial = millis(); // armazena o tempo em que a bola foi liberada
    }

    estadoUM = digitalRead(sensorUM); // Ler o sensor UM e armazena em estadoUM
    if (estadoUM == LOW) {
      digitalWrite(ledVerde, HIGH); // Liga o LED VERDE
      digitalWrite(ledVermelho, LOW); // desliga o LED VERMELHO
      instanteUM = millis(); // armazena o tempo Total decorrido para Sensor UM

      interTempoUM = instanteUM - instanteInicial;
      gravidadeUM = (2 * 0.001 * deslocamentoUM) / pow(0.001 * interTempoUM, 2);
    }
    else {
      digitalWrite(ledVerde, LOW); // desliga os lEDs VERDE e VERMELHO
      digitalWrite(ledVermelho, LOW);
    }

    estadoDOIS = digitalRead(sensorDOIS); // Ler o sensor DOIS e armazena em estadoDOIS
    if (estadoDOIS == LOW) {
      digitalWrite(ledVerde, LOW); // desliga LED verde
      digitalWrite(ledVermelho, HIGH); // liga LED vermelho
      instanteDOIS = millis(); // armazena o tempo Total decorrido para Sensor DOIS

      interTempoDOIS = instanteDOIS - instanteInicial;
      gravidadeDOIS = (2 * 0.001 * deslocamentoDOIS) / pow(0.001 * interTempoDOIS, 2);
    }
    else {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, LOW); //desliga os LED verde e Vermelho
    }

    estadoTRES = digitalRead(sensorTRES); // Ler o sensor TRÊS e armazena em estadoTRES
    if (estadoTRES == LOW) {
      digitalWrite(ledVerde, HIGH); // liga LED Verde
      digitalWrite(ledVermelho, HIGH); // liga LED Vermelho
      instanteTRES = millis(); // armazena o tempo Total decorrido para Sensor TRÊS

      interTempoTRES = instanteTRES - instanteInicial;
      gravidadeTRES = (2 * 0.001 * deslocamentoTRES) / pow(0.001 * interTempoTRES, 2);

      gravidadeMedia = (gravidadeUM + gravidadeDOIS + gravidadeTRES) / 3;

      Serial.println(".................................................................");
      Serial.print(" |||| Aceleracao Gravitacional (em m/s^2) |||| g_Média= ");
      Serial.println(gravidadeMedia); // imprime no monitor serial o valor aproximado da aceleração gravitacional
      Serial.println(".................................................................");
      Serial.println(".................................................................");

      delay(3000); //tempo de espera para efetuar nova leitura

      instanteInicial = 0; // a variável do tempo inicial deverá ser limpa, para o próximo teste
      meuServo.write(175); // o servomotor volta ao estado inicial
      servoAtivo = LOW; // o código sai da estrutura while
    }
    else {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, LOW); // desliga LED verde e Vermelho
    }
  }
}
