// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

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

const int ledVermelho = 6; // O LED vermelho deverá ser ligado no pino digital 6
const int ledVerde = 7; // O LED verde deverá ser ligado no pino digital 7
const int sensor[] = {8, 9, 10};
const int numeroSensor = 3;
int cont = 0;
int estadoSensor[3];
long interTempo[2]; // tempo decorrido no primeiro intervalo
float vel[2];
int dist[] = {20, 20};
long instante[3]; // tempo total decorrido desde que o programa foi executado
long tempoTotal = 2000;
 
void setup() 
{
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  Serial.println(".....................................................");
  Serial.println("TESTES DE EXPERIMENTOS FÍSICOS COM ARDUINO");
  Serial.println(".....................................................");
  delay(1000); //Pausa de 1 segundos
  Serial.println(".....................................................");
  Serial.println("CINEMATICA");
  Serial.println(".....................................................");
  delay(1000); //Pausa de 1 segundos
  
  Serial.println(".....................................................");
  Serial.println("Analise do tipo de movimento e Calculo da Velocidade");
  Serial.println(".....................................................");
  delay(500); //Pausa de 0.5 segundos
  Serial.println("::INICIE O EXPERIMENTO::");
  Serial.println(".....................................................");
  delay(500); //Pausa de 0.5 segundos
  
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);  
  for (cont = 0; cont < numeroSensor; cont++)
  {
    pinMode(sensor[cont], INPUT);
  }
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledVerde, LOW); 
}

void loop() 
{ 
  
  calculoSensor();

  mostraDados();

  // imprimeLCD();

}

// ---------- AREA DAS DEFINIÇÕES DE CÓDIGOS ----------

void calculoSensor()
{
  int cont = 0; // zerar o índice de contagem
  while (cont < numeroSensor) // repete o código até que a condição seja falseada
  {
    estadoSensor[cont] = digitalRead(sensor[cont]);
    if (estadoSensor[cont] == LOW)
    {
      instante[cont] = millis();
      
      // controle do LED Verde
      if (cont != 1)
      {
        digitalWrite(ledVerde, HIGH); // liga o led Verde quando cont == 0 ou cont == 2
      }
      // controle do LED Vermelho
      if (cont != 0)
      {
        digitalWrite(ledVermelho, HIGH); // liga o led Vermelho quando cont == 1 ou cont == 2
        
        interTempo[cont-1] = (instante[cont] - instante[cont-1]); // cálculo dos intervalos de tempo
        vel[cont-1] = (0.01 * dist[cont-1]) / (0.001 * interTempo[cont-1]);
      }
      delay(100);
    }
    else
    {
      digitalWrite(ledVermelho, LOW);
      digitalWrite(ledVerde, LOW); // desliga LED verde e Vermelho
    }
    cont++; // incrementa o contador
  }
}

void mostraDados()
{
  if (instante[2] != 0)
  {
    Serial.println(".................................................................");
  
    Serial.print(" d1 (m) = ");
    Serial.print(0.001 * dist[0], 3); // imprime no monitor serial a Primeira Distância
    Serial.print("\t | d2 (m) = ");
    Serial.println(0.001 * dist[1], 3); // imprime no monitor serial a Segunda Distância
  
    Serial.print(" t1 (s) = ");
    Serial.print(0.001 * interTempo[0], 3); // imprime no monitor serial o Primeiro Intervalo de Tempo
    Serial.print("\t | t2 (s) = ");
    Serial.println(0.001 * interTempo[1], 3); // imprime no monitor serial o Primeiro Intervalo de Tempo
  
    Serial.println(".................................................................");
    
    Serial.print(" v1 (m/s) = ");
    Serial.print(vel[0], 3); // imprime no monitor serial a Primeira Velocidade
    Serial.print("\t | v2 (m/s) = ");
    Serial.println(vel[1], 3); // imprime no monitor serial a Segunda Velocidade

    delay(tempoTotal); //tempo de espera para efetuar nova leitura
  
    /*
    Serial.println(".................................................................");
  
    Serial.print(" 1o distancia (m) = ");
    Serial.println(0.001 * dist[0], 3); // imprime no monitor serial a Primeira Distância
  
    Serial.print(" 1o intervalo (s) = ");
    Serial.println(0.001 * interTempo[0], 3); // imprime no monitor serial o Primeiro Intervalo de Tempo
    Serial.print(" 1o velocidade (m/s) = ");
    Serial.println(vel[0], 3); // imprime no monitor serial a Primeira Velocidade
    Serial.println(".................................................................");
    Serial.println(".................................................................");
  
    Serial.print(" 2o distancia (m) = ");
    Serial.println(0.001 * dist[1], 3); // imprime no monitor serial a Segunda Distância
  
    Serial.print(" 2o intervalo (s) = ");
    Serial.println(0.001 * interTempo[1], 3); // imprime no monitor serial o Primeiro Intervalo de Tempo
    Serial.print(" 2o velocidade (m/s) = ");
    Serial.println(vel[1], 3); // imprime no monitor serial a Segunda Velocidade
    delay(tempoTotal); //tempo de espera para efetuar nova leitura
    */
    
    Serial.println(".....................................................");
    Serial.println(".....................................................");
    Serial.println("Qual o tipo de movimento descrito pelo objeto?");
    Serial.println(".....................................................");
    
    // limpa as variáveis
    for (int i = 0; i < 3; i++)
    {
      instante[i] = 0;
    }
  }
}

void imprimeLCD() 
{
  
}
