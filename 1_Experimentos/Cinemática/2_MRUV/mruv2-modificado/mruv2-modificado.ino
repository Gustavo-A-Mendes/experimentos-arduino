/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   BACHARELADO EM CIENCIAS E TECNOLOGIA - BCT
   O programa calcula o intervalo de tempo entre três sensores
   infravermelho,
   e determina se o movimento é uniforme ou uniformemente variado
   Este programa poderá ser usado para se determinar a aceleração
   gravitacional
*/

const int ledVerde = 7;                             // o LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6;                          // o LED vermelho deverá ser ligado no pino digital 6
const int sensorUM = 2;                             // configura o pino digital 2 para o PRIMEIRO SENSOR
const int sensorDOIS = 3;                           // configura o pino digital 3 para o SEGUNDO SENSOR
const int sensorTRES = 4;                           // configura o pino digital 4 para o TERCEIRO SENSOR
int estadoUM, estadoDOIS, estadoTRES;               // variáveis que guardam os estados dos sensores
long instanteUM, instanteDOIS, instanteTRES;        // tempo decorrido pelo programa até os sensores
long interTempoUM;                                  // tempo decorrido no primeiro intervalo
long interTempoDOIS;                                // tempo decorrido no segundo intervalo
float velUM, velDOIS;
int deslocamentoUM = 200;                           // distancia sugerida em milimetro entre sensor 1 e 2.
// Mude a medida se for conveniente
int deslocamentoDOIS = 200;                         // distancia sugerida em milimetro entre sensor 2 e 3.
// Mude a medida se for conveniente
long tempoTotal = 2000;
float aceleracao;                                   // aceleração do sistema

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
  estadoUM = digitalRead(sensorUM);                 // ler o sensorUM e armazena em estadoUM
  if (estadoUM == LOW) {
    digitalWrite(ledVerde, HIGH);                   // liga o LED verda
    digitalWrite(ledVermelho, LOW);                 // desliga o LED vermelho
    instanteUM = millis();                          // armazena o tempo Total decorrido para SensorUM
  }
  else {
    digitalWrite(ledVerde, LOW);                    // desliga os LEDs VERDE e VERMELHO
    digitalWrite(ledVermelho, LOW);
  }

  estadoDOIS = digitalRead(sensorDOIS);             // ler o sensorDOIS e armazena em estadoDOIS
  if (estadoDOIS == LOW) {
    digitalWrite(ledVerde, LOW);                    // desliga LED verde
    digitalWrite(ledVermelho, HIGH);                // liga LED vermelho
    instanteDOIS = millis();                        // armazena o tempo Total decorrido para SensorDOIS
    interTempoUM = (instanteDOIS - instanteUM);     // cálculo do primeiro intervalo de tempo
    velUM = (0.001 * deslocamentoUM) / (0.001 * interTempoUM);
  }
  else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, LOW);                 // desliga os LED verde e Vermelho
  }

  estadoTRES = digitalRead(sensorTRES);             // ler o sensorTRES e armazena em estadoTRES
  if (estadoTRES == LOW) {
    digitalWrite(ledVerde, HIGH);                   // liga LED Verde
    digitalWrite(ledVermelho, HIGH);                // liga LED Vermelho
    instanteTRES = millis();                        // armazena o tempo Total decorrido para SensorTRES
    interTempoDOIS = (instanteTRES - instanteDOIS); // cálculo do segundo intervalo de tempo
    velDOIS = (0.001 * deslocamentoDOIS) / (0.001 * interTempoDOIS);

    aceleracao = ((velDOIS * velDOIS) - (velUM * velUM)) / (2 * 0.001 * deslocamentoDOIS); // eq. De Torricelli

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
    Serial.println(".................................................................");
    Serial.print(" a (m/s^2) = ");
    Serial.println(aceleracao, 3);
    delay(tempoTotal);                              // tempo de espera para efetuar nova leitura
  }
  else {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, LOW);                 // desliga LED verde e Vermelho
  }
}
