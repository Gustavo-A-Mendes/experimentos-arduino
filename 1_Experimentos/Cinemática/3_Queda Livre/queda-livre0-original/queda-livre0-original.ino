/* MESTRADO NACIONAL PROFISSIONAL EM ENSINO DE FÍSICA-SBF
 * INSTITUTO FEDERAL DE CIÊNCIA E TECNOLOGIA DO CEARÁ-IFCE
 * UNIVERSIDADE ESTADUAL VALE DO ACARAÚ-UVA
 * PRODUTO DESENVOLVIDO POR: OSÉIAS DE SOUSA MOURÃO
 *
 * Programa destinado para estudo de Cinemática.
 * O programa calcula o intervalo de tempo entre três sensores
 infravermelho,
 * e determina se o movimento é uniforme ou uniformemente variado
 * Este programa poderá ser usado para se determinar a aceleração
 gravitacional
*/
const int ledVerde = 7; // O LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6; // O LED vermelho deverá ser ligado no pino digital 6
const int sensorUM = 2; // Configura o pino digital 2 para o PRIMEIRO SENSOR
const int sensorDOIS = 3; // Configura o pino digital 3 para o SEGUNDO SENSOR
const int sensorTRES = 4; // Configura o pino digital 4 para o TERCEIRO SENSOR
int estadoUM; // variável que guarda estado do primeiro sensor
int estadoDOIS; // variável que guarda estado do segundo sensor
int estadoTRES; // variável que guarda estado do terceiro sensor
long interTempoUM; // tempo decorrido no primeiro intervalo
long interTempoDOIS; // tempo decorrido no segundo intervalo
long instanteUM = 0; // tempo total decorrido desde que o programa foi executado
long instanteDOIS = 0; // tempo total decorrido desde que o programa foi executado
long instanteTRES= 0; // tempo total decorrido desde que o programa foi executado
float velocidadeUM;
float velocidadeDOIS;
long deslocamentoUM = 400; // distancia sugerida em milimetro entre sensor 1 e 2. Mude a medida se for conveniente
long deslocamentoDOIS = 400; // distancia sugerida em milimetro entre sensor 2 e 3. Mude a medida se for conveniente
long tempoTotal;
float g; // aceleração gravitacional

void setup()
{
  Serial.begin(9600);
  
  Serial.println(".....................................................");
  Serial.println("MESTRADO NACIONAL PROFISSIONAL EM ENSINO DE FISICA - MNPEF");
  Serial.println("PRODUTO DESENVOLVIDO POR: OSEIAS MOURAO");
  Serial.println(".....................................................");
  delay(2000); //Pausa de 2 segundos
  Serial.println(".....................................................");
  Serial.println("CINEMATICA");
  Serial.println(".....................................................");
  delay(2000); //Pausa de 2 segundos
  Serial.println(".....................................................");
  Serial.println("Afericao da Aceleracao Gravitacional (g)");
  Serial.println(".....................................................");
  delay(1000); //Pausa de 1 segundos
  Serial.println("::INICIE O EXPERIMENTO::");
  Serial.println(".....................................................");
  delay(1000); //Pausa de 1 segundos
  
  pinMode(ledVermelho, OUTPUT); // Configura o pino 6 como saída
  pinMode(ledVerde, OUTPUT); // Configura o pino 7 como saída
  pinMode(sensorUM, INPUT); // Configura o pino 2 como entrada
  pinMode(sensorDOIS, INPUT); // Configura o pino 3 como entrada
  pinMode(sensorTRES, INPUT); // Configura o pino 4 como entrada
  digitalWrite(ledVermelho, LOW); // desliga LED vermelho digitalWrite(ledVerde, LOW); // desliga LED verde
}

void loop()
{
  estadoUM = digitalRead(sensorUM); // Ler o sensor UM e armazena em estadoUM
  if(estadoUM == HIGH)
  {
    digitalWrite(ledVerde, HIGH); // Liga o LED VERDE
    digitalWrite(ledVermelho, LOW); // desliga o LED VERMELHO
    instanteUM = millis(); // armazena o tempo Total decorrido para Sensor UM
  }
  else
  {
    digitalWrite(ledVerde, LOW); // desliga os lEDs VERDE e VERMELHO
    digitalWrite(ledVermelho, LOW);
  }
  
  estadoDOIS = digitalRead(sensorDOIS); // Ler o sensor DOIS e armazena em estadoDOIS
  if(estadoDOIS == HIGH)
  {
    digitalWrite(ledVerde, LOW); // desliga LED verde
    digitalWrite(ledVermelho, HIGH); // liga LED vermelho
    instanteDOIS = millis(); // armazena o tempo Total decorrido para Sensor DOIS
     
    interTempoUM = (instanteDOIS - instanteUM); // cálculo do primeiro intervalo de tempo
    velocidadeUM = deslocamentoUM/interTempoUM; // calculo da velocidade média entre 1 e 2 sensor 
  }
  else
  {
    digitalWrite(ledVerde, LOW); 
    digitalWrite(ledVermelho, LOW); //desliga os LED verde e Vermelho 
  }
  
  estadoTRES = digitalRead(sensorTRES); // Ler o sensor TRÊS e armazena em estadoTRES
  if(estadoTRES == HIGH) {
    digitalWrite(ledVerde, HIGH); // liga LED Verde
    digitalWrite(ledVermelho, HIGH); // liga LED Vermelho
    instanteTRES = millis(); // armazena o tempo Total decorrido para Sensor TRÊS
    
    interTempoDOIS = (instanteTRES - instanteDOIS);
    velocidadeDOIS = deslocamentoDOIS/interTempoDOIS; // calculo da velocidade média entre 1 e 2 sensor
    g=((velocidadeUM*velocidadeUM)*(velocidadeDOIS*velocidadeDOIS))/deslocamentoDOIS; // eq. De Torricelli
    
    Serial.println(".................................................................");
    Serial.print(" |||| Aceleracao Gravitacional (em m/s^2) |||| g= ");
    Serial.println(g); // imprime no monitor serial o valor aproximado da aceleração gravitacional
    Serial.println(".................................................................");
    Serial.println(".................................................................");
    delay(tempoTotal); //tempo de espera para efetuar nova leitura
  }
  else
  {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, LOW); // desliga LED verde e Vermelho
  }
}
