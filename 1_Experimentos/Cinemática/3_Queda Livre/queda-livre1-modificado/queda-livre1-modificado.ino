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
const int ledVerde = 7; // O LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6; // O LED vermelho deverá ser ligado no pino digital 6
const int sensorUM = 2; // Configura o pino digital 2 para o PRIMEIRO SENSOR
const int sensorDOIS = 3; // Configura o pino digital 3 para o SEGUNDO SENSOR
const int sensorTRES = 4; // Configura o pino digital 4 para o TERCEIRO SENSOR
int estadoUM; // variável que guarda estado do primeiro sensor
int estadoDOIS; // variável que guarda estado do segundo sensor
int estadoTRES; // variável que guarda estado do terceiro sensor
long interTempoUM ; // tempo decorrido no primeiro intervalo
long interTempoDOIS ; // tempo decorrido no segundo intervalo
long instanteUM = 0; // tempo total decorrido desde que o programa foi executado
long instanteDOIS = 0; // tempo total decorrido desde que o programa foi executado
long instanteTRES= 0; // tempo total decorrido desde que o programa foi executado
float velocidadeUM;
float velocidadeDOIS;
long deslocamentoUM = 500; // distancia sugerida em milimetro entre sensor 1 e 2. Mude a medida se for conveniente
long deslocamentoDOIS = 500; // distancia sugerida em milimetro entre sensor 2 e 3. Mude a medida se for conveniente
long tempoTotal = 2000;
float g; // aceleração gravitacional

void setup()
{
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
  digitalWrite(ledVermelho, LOW); // desliga LED vermelho 
  digitalWrite(ledVerde, LOW); // desliga LED verde
}

void loop()
{
  estadoUM = digitalRead(sensorUM); // Ler o sensor UM e armazena em estadoUM
  if(estadoUM == LOW)
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
  if(estadoDOIS == LOW)
  {
    digitalWrite(ledVerde, LOW); // desliga LED verde
    digitalWrite(ledVermelho, HIGH); // liga LED vermelho
    instanteDOIS = millis(); // armazena o tempo Total decorrido para Sensor DOIS
     
    interTempoUM = (instanteDOIS - instanteUM); // cálculo do primeiro intervalo de tempo
    velocidadeUM = (0.001 * deslocamentoUM)/(0.001 * interTempoUM); // calculo da velocidade média entre 1 e 2 sensor 
  }
  else
  {
    digitalWrite(ledVerde, LOW); 
    digitalWrite(ledVermelho, LOW); //desliga os LED verde e Vermelho 
  }
  
  estadoTRES = digitalRead(sensorTRES); // Ler o sensor TRÊS e armazena em estadoTRES
  if(estadoTRES == LOW) {
    digitalWrite(ledVerde, HIGH); // liga LED Verde
    digitalWrite(ledVermelho, HIGH); // liga LED Vermelho
    instanteTRES = millis(); // armazena o tempo Total decorrido para Sensor TRÊS
    
    interTempoDOIS = (instanteTRES - instanteDOIS);
    velocidadeDOIS = (0.001 * deslocamentoDOIS)/(0.001 * interTempoDOIS); // calculo da velocidade média entre 1 e 2 sensor

    g = ((velocidadeDOIS*velocidadeDOIS) - (velocidadeUM*velocidadeUM))/(2 * 0.001 * deslocamentoDOIS); // eq. De Torricelli
    
    //g = (pow(velDOIS, 2) - pow(velUM, 2)) / (2 * distDOIS); // eq. De Torricelli
    
    //Gustavo: Essa parte, foi adicionada por mim, para que eu pudesse ver quais
    //valores que estavam entrando em cada uma das variáveis usadas nas contas.    
     
    Serial.print("d1: ");
    Serial.println(deslocamentoUM);
    Serial.print("t1: ");
    Serial.println(interTempoUM);
    Serial.print("v1: ");
    Serial.println(velocidadeUM);
    Serial.println(".................................................................");
    Serial.println(".................................................................");
    Serial.print("d2: ");
    Serial.println(deslocamentoDOIS);
    Serial.print("t2: ");
    Serial.println(interTempoDOIS);
    Serial.print("v2: ");
    Serial.println(velocidadeDOIS);
    
    
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
