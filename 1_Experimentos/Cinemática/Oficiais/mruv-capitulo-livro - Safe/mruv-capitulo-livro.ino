/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   BACHARELADO EM CIENCIAS E TECNOLOGIA - BCT
   O programa calcula o intervalo de tempo entre três sensores
   infravermelho,
   e determina se o movimento é uniforme ou uniformemente variado
   Este programa poderá ser usado para se determinar a aceleração
   gravitacional
*/

const int sensorBotao = 12;                         // o botão deverá ser ligado no pino digital 12
const int ledVerde = 7;                             // o LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6;                          // o LED vermelho deverá ser ligado no pino digital 6
const int sensorInicial = 2;                        // configura o pino digital 2 para o PRIMEIRO SENSOR
const int sensorIR = 3;                             // configura o pino digital 3 para o SEGUNDO SENSOR

bool inicioAtivo = false;                           // os inicia desativado
int iniciar = 0;

int estadoInicial, estadoIR;                        // variável que guarda o estado do sensor
long instanteInicial, instanteIR;                   // tempo decorrido pelo programa até o sensor
long interTempoInicial, interTempoIR;               // intervalo decorrido do início até o sensor
float deslocamentoIR = 600.0;                      // distância sugerida, em milimetros, até o sensor.
                                                    // Mude se for conveniente.
float aceleracao;                                   // variável que guarda a gravidade no instanteIR
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
  Serial.println("Analise do tipo de movimento e Calculo da Aceleracao");
  Serial.println(".....................................................");
  delay(500); // pausa de 0.5 segundos
  Serial.println("=== APERTE O BOTAO PARA INICIAR O EXPERIMENTO ===");
  Serial.println(".....................................................");
  delay(500); // pausa de 0.5 segundos

  pinMode(ledVermelho, OUTPUT);                     // configura o pino 6 como saída
  pinMode(ledVerde, OUTPUT);                        // configura o pino 7 como saída
  pinMode(sensorInicial, INPUT);                         // configura o pino 3 como entrada
  pinMode(sensorIR, INPUT);                         // configura o pino 3 como entrada
  pinMode(sensorBotao, INPUT);                       // configura o pino 12 como entrada
  digitalWrite(ledVermelho, HIGH);                  // desliga LED vermelho
  digitalWrite(ledVerde, HIGH);                     // desliga LED verde
}

void loop() {
  digitalWrite(ledVerde, HIGH);                     // liga o LED verde
  digitalWrite(ledVermelho, HIGH);                  // Liga o LED Vermelho
  inicioAtivo = digitalRead(sensorBotao);             // ler o botão e armazena em servoAtivo

  // se o botão for ativado, o servo ativa e inicia o código
  while (inicioAtivo == HIGH) {
    if (iniciar == 0) {
      iniciar = 1;
      digitalWrite(ledVerde, LOW);                 // desliga o LED verde
      digitalWrite(ledVermelho, LOW);              // desliga o LED vermelho
      Serial.println(".....................................................");
      Serial.println("PREPARANDO...");
      delay(3000);
      Serial.println("=== LIBERE O OBJETO ===");
      
      digitalWrite(ledVerde, HIGH);                // pisca os dois LEDs
      digitalWrite(ledVermelho, HIGH);
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledVermelho, HIGH);
    }

    estadoInicial = digitalRead(sensorInicial);               // ler o sensorDOIS e armazena em estadoDOIS
    if (estadoInicial == LOW) {
      digitalWrite(ledVerde, LOW);                 // liga o LED verde
      digitalWrite(ledVermelho, HIGH);               // desliga o LED Vermelho
      instanteInicial = millis();                        // armazena o tempo Total decorrido para SensordOIS
    }

    estadoIR = digitalRead(sensorIR);               // ler o sensorDOIS e armazena em estadoDOIS
    if (estadoIR == LOW) {
      digitalWrite(ledVerde, HIGH);                 // liga o LED verde
      digitalWrite(ledVermelho, LOW);               // desliga o LED Vermelho
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
      Serial.print(velocidade, 3);
      Serial.println(" m/s");
      Serial.println("\n.....................................................");

      Serial.println("|||| Aceleracao no Plano ||||");
      Serial.print("\n a = ");
      Serial.print(aceleracao, 3);                   // imprime no monitor serial o valor aproximado da aceleração no plano
      Serial.println(" m/s^2");
      Serial.println("\n.....................................................");


      delay(tempoTotal);
      iniciar = 0;                          // a variável do tempo inicial será limpa
      inicioAtivo = LOW;                             // o código sai da estrutura while
    }
    else {
    }
  }
}
