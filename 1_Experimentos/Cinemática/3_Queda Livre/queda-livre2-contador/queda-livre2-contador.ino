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

#include <Servo.h>

Servo meuServo;
// int pos = 0;
bool servoAtivo = false;

const int servoBotao = 5; // Botão que ativa o servo
const int ledVerde = 7; // o LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6; // o LED vermelho deverá ser ligado no pino digital 6

const int nSensor = 3; // quantidade de sensores que estamos usando
const int sensores[3] = {2, 3, 4};
//const int sensorUM = 2; // configura o pino digital 2 para o PRIMEIRO SENSOR
//const int sensorDOIS = 3; // configura o pino digital 3 para o SEGUNDO SENSOR
//const int sensorTRES = 4; // configura o pino digital 4 para o TERCEIRO SENSOR

int estados[3];
//int estadoUM, estadoDOIS, estadoTRES; // variáveis que guardam os estados dos sensores
long instantes[3];
//long instanteUM, instanteDOIS, instanteTRES; // tempo decorrido pelo programa até o respectivo sensor

long instanteInicial; // tempo decorrido antes de ativar o servomotor

long interTempos[3];
//long interTempoUM; // tempo decorrido no primeiro intervalo do início ao sensor 1
//long interTempoDOIS ; // tempo decorrido no primeiro intervalo do sensor 1 ao 2
//long interTempoTRES ; // tempo decorrido no segundo intervalo do sensor 2 ao 3

float deslocamentos[3] = {100.0, 400.0, 400.0};
//float deslocamentoUM = 100.0; // distância sugerida, em milimetros, entre a bola até o primeiro sensor
//float deslocamentoDOIS = 400.0; // distância sugerida, em milimetros, entre sensor 1 e 2
//float deslocamenteTRES = 400.0; // distância sugerida, em milimetros, entre sensor 2 e 3

float velocidades[3];
//float velocidadeUM, velocidadeDOIS, velocidadeTRES; // variáveis que guardam a velocidade em cada instante

float g; // aceleração gravitacional


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
  digitalWrite(ledVermelho, LOW); // desliga LED vermelho 
  digitalWrite(ledVerde, LOW); // desliga LED verde

  meuServo.attach(9);
  Serial.println(".....................................................");
  Serial.println("PREPARANDO...");
  delay(3000);
  Serial.println("LIBERANDO O OBJETO");
  // meuServo.write();
  delay(350);
  instanteInicial = millis();
}

void loop() {
  servoAtivo = digitalRead(servoBotao); 
  
  while(servoAtivo){
    int cont = 0;
    while (cont < nSensor) {
      calculaVelocidade(cont)
      cont++;
    }
  }

  // g = (pow(velocidade[2], 2) - pow(velocidades[1],2))/(2*deslocamentos[2]); // eq. De Torricelli

  mostraDados()
}


/* ====== AREA DAS FUNÇÕES ====== */

void calculaVelocidade(n){
  estados[n] = digitalRead(sensores[n]);
  if(estados[n] == LOW) {
    
    instantes[n] = millis();
    
    if(n == 0) {
      interTempos[n] = instantes[n] - instanteInicial;
      velocidades[n] = (2 * deslocamentos[n]) / interTempos[n];
    }
    else {
      interTempos[n] = instantes[n] + instante[n-1] - (2 * instanteInicial);
      velocidades[n] = velocidade[n-1] + ((2 * deslocamentos[n]) / interTempos[n]);
    }

    // controle do LED verde
    if(n != 1) {
      digitalWrite(ledVerde, HIGH); // Liga o LED VERDE
    }
    // controle do LED vermelho
    if(n != 0) {
      digitalWrite(ledVermelho, HIGH); // liga LED vermelho
    }
  }
  else {
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, LOW); // desliga LED verde e Vermelho
  }
}


void mostraDados() {
  if (instante[2] != 0) {
    
    Serial.println(".................................................................");
    Serial.print("s1 = ");
    Serial.println(deslocamentos[0]);
    Serial.print("t1 = ");
    Serial.println(interTempos[0]);
    Serial.print("v1 = ");
    Serial.println(velocidades[0]);
    Serial.println(".................................................................");
    Serial.print("s2 = ");
    Serial.println(deslocamentos[1]);
    Serial.print("t2 = ");
    Serial.println(interTempos[1]);
    Serial.print("v2 = ");
    Serial.println(velocidades[1]);
    Serial.println(".................................................................");
    Serial.print("s3 = ");
    Serial.println(deslocamentos[2]);
    Serial.print("t3 = ");
    Serial.println(interTempos[2]);
    Serial.print("v3 = ");
    Serial.println(velocidades[2]);

    g = (pow(velocidade[2], 2) - pow(velocidades[1],2))/(2*deslocamentos[2]); // eq. De Torricelli
    
    Serial.println(".................................................................");
    Serial.print(" |||| Aceleracao Gravitacional (em m/s^2) |||| g= ");
    Serial.println(g); // imprime no monitor serial o valor aproximado da aceleração gravitacional
    Serial.println(".................................................................");
    Serial.println(".................................................................");
    
    // limpa as variáveis
    for (int i = 0; i < nSensor; i++)
    {
      instantes[i] = 0;
    }
    
    delay(3000); //tempo de espera para efetuar nova leitura
    instanteInicial = 0;
    // meuServo.write();
    servoAtivo = false;
  }
}
