const int iniciarBotao = 12;                        // o botão deverá ser ligado no pino digital 12
const int ledVerde = 7;                             // o LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6;                          // o LED vermelho deverá ser ligado no pino digital 6
const int sensorInicial = 2;                        // configura o pino digital 2 para o SENSOR DE LARGADA
const int sensorIR = 3;                             // configura o pino digital 3 para o SENSOR DE CHEGADA
int estadoIR, estadoIRAnt = 1;                      // armazena os estados do SENSOR DE LARGADA
int estadoInicial, estadoInicialAnt = 1;            // armazena os estados do SENSOR DE CHEGADA
float instanteIR, instanteInicial;                  // armazena o tempo decorrido até os sensores
float interTempoIR;                                 // intervalo decorrido entre os sensores
float deslocamentoIR = 1000.0;                      // distância sugerida, em milimetros, até o sensor.
// Mude se for conveniente.
float aceleracao;                                   // armazena a aceleracao
float velocidade;
int tempoTotal = 3000;                              // tempo de espera sugerido até a próxima medida

void setup() {
  Serial.begin(9600);
  digitalWrite(ledVerde, LOW);                      // desliga LED verde
  digitalWrite(ledVermelho, HIGH);                  // liga LED vermelho
}

void loop() {
  estadoInicial = digitalRead(sensorInicial);       // ler o sensorDOIS e armazena em estadoDOIS
  if (estadoInicial != estadoInicialAnt) {
    if (estadoInicial == HIGH) {
      instanteInicial = millis();                   // tempo da largada
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, LOW);
    }
    estadoInicialAnt = estadoInicial;
  }
  estadoIR = digitalRead(sensorIR);               // ler o sensorDOIS e armazena em estadoDOIS
  if (estadoIR != estadoIRAnt) {
    if (estadoIR == HIGH) {
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledVermelho, LOW);
      instanteIR = millis();                          // tempo da chegada
      interTempoIR = instanteIR - instanteInicial;    // intervalo de tempo do percurso
      // a = 2s /(t^2)
      aceleracao = (2 * 0.001 * deslocamentoIR) / sq(0.001 * interTempoIR);
      // v = a*t
      velocidade = 0.001 * interTempoIR * aceleracao;
      Serial.println(".....................................................");
      Serial.print(" distância (m) = "); Serial.println(0.001 * deslocamentoIR);
      Serial.print(" tempo (s) = "); Serial.println(0.001 * interTempoIR);
      Serial.print("\n v (m/s) = "); Serial.println(velocidade);
      Serial.print("\n a(m/s^2) = "); Serial.println(aceleracao);
      delay(tempoTotal);                              // tempo de espera até a próxima leitura
      instanteInicial = 0;                            // limpa a variavel do tempo de largada
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, HIGH);
    }
    estadoIRAnt = estadoIR;
  }
}
