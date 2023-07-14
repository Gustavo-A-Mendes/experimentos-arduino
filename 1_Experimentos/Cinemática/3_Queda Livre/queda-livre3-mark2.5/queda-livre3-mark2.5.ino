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
int atraso = 145;

const int servoBotao = 12; // Botão que ativa o servo
const int ledVerde = 7; // o LED verde deverá ser ligado no pino digital 7
const int ledVermelho = 6; // o LED vermelho deverá ser ligado no pino digital 6
const int sensorUM = 2; // configura o pino digital 2 para o PRIMEIRO SENSOR
const int sensorDOIS = 3; // configura o pino digital 3 para o SEGUNDO SENSOR
const int sensorTRES = 4; // configura o pino digital 4 para o TERCEIRO SENSOR

int estadoUM, estadoDOIS, estadoTRES; // variáveis que guardam os estados dos sensores
long instanteUM, instanteDOIS, instanteTRES; // tempo decorrido pelo programa até o respectivo sensor
long instanteInicial; // tempo decorrido antes de ativar o servomotor

long interTempoUM; // tempo decorrido no primeiro intervalo do início ao sensor 1
long interTempoDOIS ; // tempo decorrido no primeiro intervalo do sensor 1 ao 2
long interTempoTRES ; // tempo decorrido no segundo intervalo do sensor 2 ao 3

float deslocamentoUM = 131.0; // distância sugerida, em milimetros, entre a bola até o primeiro sensor
float deslocamentoDOIS = 531.0; // distância sugerida, em milimetros, entre sensor 1 e 2
float deslocamentoTRES = 931.0; // distância sugerida, em milimetros, entre sensor 2 e 3

float gravidadeUM, gravidadeDOIS, gravidadeTRES; // variáveis que guardam a velocidade em cada instante
float gMedia;

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
  pinMode(servoBotao, INPUT);
  digitalWrite(ledVermelho, LOW); // desliga LED vermelho 
  digitalWrite(ledVerde, LOW); // desliga LED verde

  meuServo.attach(9);
  meuServo.write(175);
}

void loop() {
  servoAtivo = digitalRead(servoBotao); 
  
  while(servoAtivo){
    if (instanteInicial == 0){
      Serial.println(".....................................................");
      Serial.println("PREPARANDO...");
      delay(3000);
      Serial.println("::LIBERANDO O OBJETO::");
      meuServo.write(120);
      // delay(192); para a precisão do primeiro
      delay(atraso);
      instanteInicial = millis();
    }

    estadoUM = digitalRead(sensorUM); // Ler o sensor UM e armazena em estadoUM
    if(estadoUM == LOW) {
      digitalWrite(ledVerde, HIGH); // Liga o LED VERDE
      digitalWrite(ledVermelho, LOW); // desliga o LED VERMELHO
      instanteUM = millis(); // armazena o tempo Total decorrido para Sensor UM
      
      interTempoUM = instanteUM - instanteInicial;
      gravidadeUM = (2*0.001*deslocamentoUM)/ pow(0.001*interTempoUM, 2);
    }
    else {
      digitalWrite(ledVerde, LOW); // desliga os lEDs VERDE e VERMELHO
      digitalWrite(ledVermelho, LOW);
    }
    
    estadoDOIS = digitalRead(sensorDOIS); // Ler o sensor DOIS e armazena em estadoDOIS
    if(estadoDOIS == LOW) {
      digitalWrite(ledVerde, LOW); // desliga LED verde
      digitalWrite(ledVermelho, HIGH); // liga LED vermelho
      instanteDOIS = millis(); // armazena o tempo Total decorrido para Sensor DOIS
       
      interTempoDOIS = instanteDOIS - instanteInicial; // cálculo do primeiro intervalo de tempo
      gravidadeDOIS = (2*0.001*deslocamentoDOIS)/pow(0.001*interTempoDOIS, 2); // calculo da velocidade média entre 1 e 2 sensor 
    }
    else {
      digitalWrite(ledVerde, LOW); 
      digitalWrite(ledVermelho, LOW); //desliga os LED verde e Vermelho 
    }
  
    estadoTRES = digitalRead(sensorTRES); // Ler o sensor TRÊS e armazena em estadoTRES
    if(estadoTRES == LOW) {
      digitalWrite(ledVerde, HIGH); // liga LED Verde
      digitalWrite(ledVermelho, HIGH); // liga LED Vermelho
      instanteTRES = millis(); // armazena o tempo Total decorrido para Sensor TRÊS
      
      interTempoTRES = instanteTRES - instanteInicial;
      gravidadeTRES = (2*0.001*deslocamentoTRES)/pow(0.001*interTempoTRES, 2); // calculo da velocidade média entre 1 e 2 sensor
  
      // Serial.println(instanteInicial);
      // Serial.println(instanteUM);
      // Serial.println(instanteDOIS);
      // Serial.println(instanteTRES);

      Serial.print("delay: ");
      Serial.println(atraso);
      
      Serial.println(".................................................................");
      // Serial.print("s1 = ");
      // Serial.println(deslocamentoUM);
      // Serial.print("t1 = ");
      // Serial.println(interTempoUM);
      Serial.print("g1 = ");
      Serial.println(gravidadeUM);
      Serial.println(".................................................................");
      // Serial.print("s2 = ");
      // Serial.println(deslocamentoDOIS);
      // Serial.print("t2 = ");
      // Serial.println(interTempoDOIS);
      Serial.print("g2 = ");
      Serial.println(gravidadeDOIS);
      Serial.println(".................................................................");
      // Serial.print("s3 = ");
      // Serial.println(deslocamentoTRES);
      // Serial.print("t3 = ");
      // Serial.println(interTempoTRES);
      Serial.print("g3 = ");
      Serial.println(gravidadeTRES);
      
      gMedia = (gravidadeUM + gravidadeDOIS + gravidadeTRES)/3;
  
      Serial.println(".................................................................");
      Serial.print(" |||| Aceleracao Gravitacional (em m/s^2) |||| g_Média= ");
      Serial.println(gMedia); // imprime no monitor serial o valor aproximado da aceleração gravitacional
      Serial.println(".................................................................");
      Serial.println(".................................................................");
      
      delay(3000); //tempo de espera para efetuar nova leitura
      instanteInicial = 0;
      meuServo.write(175);
      servoAtivo = false;
    }
    else {
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledVermelho, LOW); // desliga LED verde e Vermelho
    }
  }
}

// ------ AREA DAS FUNÇÕES ------
