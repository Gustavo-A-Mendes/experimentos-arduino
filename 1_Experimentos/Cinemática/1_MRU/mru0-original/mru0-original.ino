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
int UltEstSenUM; // variável a guardar o último estado do primeiro sensor
int UltEstSenDOIS; // variável a guardar o último estado do segundo sensor
int UltEstSenTRES; // variável a guardar o último estado do terceiro sensor
long interTempoUM; // tempo decorrido no primeiro intervalo
long interTempoDOIS; // tempo decorrido no segundo intervalo
long instanteUM = 0; // tempo total decorrido desde que o programa foi executado
long instanteDOIS = 0; // tempo total decorrido desde que o programa foi executado
long instanteTRES= 0; // tempo total decorrido desde que o programa foi executado
long tempoTotal;
 
void setup() 
{
  Serial.begin(9600);
   
  Serial.println(".....................................................");
  Serial.println("MESTRADO NACIONAL PROFISSIONAL EM ENSINO DE FISICA -  MNPEF");
  Serial.println("PRODUTO DESENVOLVIDO POR: OSEIAS MOURAO");
  Serial.println(".....................................................");
  delay(2000);//Pausa de 2 segundos
  Serial.println(".....................................................");
  Serial.println("CINEMATICA");
  Serial.println(".....................................................");
  delay(2000); //Pausa de 2 segundos
  
  Serial.println(".....................................................");
  Serial.println("Analise do tipo de movimento e Calculo da Velocidade");
  Serial.println(".....................................................");
  delay(1000); //Pausa de 2 segundos
  Serial.println("::INICIE O EXPERIMENTO::");
  Serial.println(".....................................................");
  delay(1000); //Pausa de 1 segundos
  
  pinMode(ledVermelho, OUTPUT); // Configura o pino 6 como saída
  pinMode(ledVerde, OUTPUT); // Configura o pino 7 como saída
  pinMode(sensorUM, INPUT); // Configura o pino 2 como entrada
  pinMode(sensorDOIS, INPUT); // Configura o pino 3 como entrada
  pinMode(sensorTRES, INPUT); // Configura o pino 4 como entrada
  digitalWrite(ledVermelho, LOW); // desliga LED vermelho
  digitalWrite(ledVerde, LOW); // desliga LED verde  
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
  }
  else
  {
    digitalWrite(ledVerde, LOW); 
    digitalWrite(ledVermelho, LOW); //desliga os LED verde e Vermelho 
  }
  
  estadoTRES = digitalRead(sensorTRES); // Ler o sensor TRÊS e armazena em estadoTRES
  if(estadoTRES == HIGH)
  {
    digitalWrite(ledVerde, HIGH); // liga LED Verde
    digitalWrite(ledVermelho, HIGH); // liga LED Vermelho 
    instanteTRES = millis(); // armazena o tempo Total decorrido para Sensor TRÊS
    interTempoDOIS = (instanteTRES - instanteDOIS);
    tempoTotal = interTempoDOIS;
    
    Serial.println(".................................................................");
    Serial.print(" 1o intervalo (ms) = ");
    Serial.println(interTempoUM); // imprime no monitor serial o Primeiro Intervalo de Tempo
    Serial.println(".................................................................");
    Serial.println(".................................................................");
    Serial.print(" 2o intervalo (ms) = ");
    Serial.println(interTempoDOIS); // imprime no monitor serial o Primeiro Intervalo de Tempo
    Serial.println(".................................................................");
    Serial.println(".....................................................");
    Serial.println("Anote a distancia entre os Sensores.");
    Serial.println(".....................................................");
    Serial.println(".....................................................");
    Serial.println("calcule as velocidades para o primeiro intervalo e para o segundo.");
    Serial.println(".....................................................");
    Serial.println(".....................................................");
    Serial.println("Qual o tipo de movimento descrito pelo objeto?");
    Serial.println(".....................................................");
    delay(tempoTotal); //tempo de espera para efetuar nova leitura
  }
  else
  {
    digitalWrite(ledVerde, LOW); 
    digitalWrite(ledVermelho, LOW); // desliga LED verde e Vermelho
  } 
}
