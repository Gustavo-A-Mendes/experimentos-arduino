/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
 * CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
 * BACHARELADO EM CIENCIAS E TECNOLOGIA - BCT
 * 
 * O programa calcula o intervalo de tempo entre três sensores 
 infravermelho,
 * e determina se o movimento é uniforme ou uniformemente variado
 * Este programa poderá ser usado para se determinar a aceleração 
 gravitacional
 */

const int ledVermelho = 6; // o LED vermelho deverá ser ligado no pino digital 6
const int ledVerde = 7; // o LED verde deverá ser ligado no pino digital 7
const int sensor = A0;
int sinal = 1023; // sinal recebido pelo pino A0. Inicia com o sinal máximo

int distUM = 200; // distancia sugerida em milimetro entre sensor 1 e 2. Mude a medida se for conveniente
int distDOIS = 200; // distancia sugerida em milimetro entre sensor 2 e 3. Mude a medida se for conveniente
float velUM;
float velDOIS;
long interTempoUM; // tempo decorrido no primeiro intervalo
long interTempoDOIS; // tempo decorrido no segundo intervalo
long instanteUM = 0; // tempo total decorrido desde que o programa foi executado
long instanteDOIS = 0; // tempo total decorrido desde que o programa foi executado
long instanteTRES = 0; // tempo total decorrido desde que o programa foi executado
long tempoTotal = 2000; // tempo de espera entre uma mediação e outra
 
void setup() 
{
  Serial.begin(9600);
   
  Serial.println(".....................................................");
  Serial.println("TESTES DE EXPERIMENTOS FÍSICOS COM ARDUINO");
  Serial.println(".....................................................");
  delay(1000); //Pausa de 2 segundos
  Serial.println(".....................................................");
  Serial.println("CINEMATICA");
  Serial.println(".....................................................");
  delay(1000); //Pausa de 2 segundos
  
  Serial.println(".....................................................");
  Serial.println("Analise do tipo de movimento e Calculo da Velocidade");
  Serial.println(".....................................................");
  delay(500); //Pausa de 2 segundos
  Serial.println("::INICIE O EXPERIMENTO::");
  Serial.println(".....................................................");
  delay(500); //Pausa de 1 segundos
  
  pinMode(ledVermelho, OUTPUT); // configura o pino 6 como saída
  pinMode(ledVerde, OUTPUT); // configura o pino 7 como saída
  pinMode(sensor, INPUT); // configura o pino 2 como entrada
  digitalWrite(ledVermelho, LOW); // desliga o LED vermelho
  digitalWrite(ledVerde, LOW); // desliga o LED verde
}

void loop() 
{ 
  sinal = analogRead(sensor); // lê o sensor e armazena seu valor em sinal
  if(sinal < 700) // sinal < 700
  {
    digitalWrite(ledVermelho, LOW); // desliga o LED vermelho
    digitalWrite(ledVerde, HIGH); // liga o LED verde
    instanteUM = millis(); // armazena o tempo Total decorrido para Sensor UM
  }
  else if(sinal < 900) // 700 <= sinal < 900
  {
    digitalWrite(ledVermelho, HIGH); // liga LED verde
    digitalWrite(ledVerde, LOW); // desliga LED verde
    instanteDOIS = millis(); // armazena o tempo Total decorrido para Sensor DOIS
    interTempoUM = (instanteDOIS - instanteUM); // cálculo do primeiro intervalo de tempo
    velUM = (0.001 * distUM) / (0.001 * interTempoUM); // calcula a velocidade do primeito intervalo
  }
  else if(sinal < 1000) // 900 <= sinal < 1000
  {
    digitalWrite(ledVermelho, HIGH); // liga LED vermelho
    digitalWrite(ledVerde, HIGH); // liga LED verde
    instanteTRES = millis(); // armazena o tempo Total decorrido para Sensor TRES
    interTempoDOIS = (instanteTRES - instanteDOIS); // cálculo do segundo intervalo de tempo
    velDOIS = (0.001 * distDOIS) / (0.001 * interTempoDOIS); // calcula a velocidade do segundo intervalo
    
    
    
    /*
    Serial.println(".................................................................");
    
    Serial.print(" 1o distancia (m) = ");
    Serial.println(0.001 * distUM, 3);
    
    Serial.print(" 1o intervalo (s) = ");
    Serial.println(0.001 * interTempoUM, 3); // imprime no monitor serial o Primeiro Intervalo de Tempo
    Serial.print(" 1o velocidade (m/s) = ");
    Serial.println(velUM, 3);
    Serial.println(".................................................................");
    Serial.println(".................................................................");
    
    Serial.print(" 2o distancia (m) = ");
    Serial.println(0.001 * distDOIS, 3);
    
    Serial.print(" 2o intervalo (s) = ");
    Serial.println(0.001 * interTempoDOIS, 3); // imprime no monitor serial o Primeiro Intervalo de Tempo
    Serial.print(" 2o velocidade (m/s) = ");
    Serial.println(velDOIS, 3);
    delay(tempoTotal); //tempo de espera para efetuar nova leitura
    */

    Serial.println(".....................................................");
    Serial.println(".....................................................");
    Serial.println("Qual o tipo de movimento descrito pelo objeto?");
    Serial.println(".....................................................");
  }
  else // sinal >= 1000
  {
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, LOW); //desliga os LED verde e Vermelho
  }
}
