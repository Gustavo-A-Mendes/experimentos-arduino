#include <Servo.h>
Servo meuServo;
bool servoAtivo = false;                            // o servomotor inicia desativado
int fechado = 175;                                  // posicao de inicial do servomotor
int aberto = 120;                                   // posicao de abertura do servomotor
int atraso = 160;                                   // atraso necessário para a bola ser totalmente liberada
const int servoBotao = 12;                          // o botão deverá ser ligado no pino digital 12
const int ledVerde = 7;                             // o LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6;                          // o LED vermelho deverá ser ligado no pino digital 6
const int sensorIR = 3;                             // configura o pino digital 3 para o SENSOR DE CHEGADA
int estadoIR, estadoIRAnt = 1;                      // armazena os estados do SENSOR DE CHEGADA
long instanteIR;                                    // tempo decorrido até o sensor
long instanteInicial;                               // tempo em que a bola foi totalmente liberada
long interTempoIR;                                  // intervalo decorrido pelo percurso
float deslocamentoIR = 900.0;                       // distância sugerida, em milimetros, até o sensor 2.
                                                    // Mude se for conveniente.
float gravidade;                                    // armazena a gravidade
float velocidade;                                   // armazena a velocidade

void setup() {
  Serial.begin(9600);
  digitalWrite(ledVerde, LOW);                      // desliga LED vermelho
  digitalWrite(ledVermelho, HIGH);                  // desliga LED verde
  meuServo.attach(9);                               // configura o pino 9 como saída do servomotor
  meuServo.write(fechado);                          // posição em que o servomotor inicia
}
void loop() {
  servoAtivo = digitalRead(servoBotao);             // verifica se o botão foi apertado
  while (servoAtivo == HIGH) {
    if (instanteInicial == 0) {
      delay(3000);
      meuServo.write(aberto);                       // abre a porta
      delay(atraso);                                // espera até a bola ser totalmente liberada
      instanteInicial = millis();                   // armazenar o tempo quando a bola foi liberada
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, LOW);
    }

    estadoIR = digitalRead(sensorIR);               // verifica o estado do sensorIR
    if (estadoIR != estadoIRAnt) {
      if (estadoIR == LOW) {
        digitalWrite(ledVerde, HIGH);
        digitalWrite(ledVermelho, HIGH);
        instanteIR = millis();                      // armazena o tempo Total decorrido para sensorIR
        interTempoIR = instanteIR - instanteInicial;
        gravidade = (2 * 0.001 * deslocamentoIR) / sq(0.001 * interTempoIR);
        velocidade = 0.001 * interTempoIR * gravidade;
        Serial.println(".....................................................");
        Serial.print("distância (m) = "); Serial.println(0.001 * deslocamentoIR);
        Serial.print("tempo (s) = "); Serial.println(0.001 * interTempoIR);
        Serial.print("v (m/s) = "); Serial.println(velocidade);
        Serial.print("g (m/s^2) = "); Serial.print(gravidade);
        meuServo.write(fechado);                      // o servomotor volta ao estado inicial
        servoAtivo = LOW;                             // o código sai da estrutura while
        delay(3000);                                  // tempo de espera até a próxima leitura
        instanteInicial = 0;                          // limpa a variáveldo tempo de largada
        digitalWrite(ledVerde, LOW);
        digitalWrite(ledVermelho, HIGH);
      }
      estadoIRAnt = estadoIR;
    }
  }
}
