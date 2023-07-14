/* UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
   CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
   BACHARELADO EM CIENCIAS E TECNOLOGIA - BCT
   O programa calcula o intervalo de tempo entre três sensores
   infravermelho,
   e determina se o movimento é uniforme ou uniformemente variado
   Este programa poderá ser usado para se determinar a aceleração
   gravitacional
*/

// inclui as bibliotecas de código:
#include <LiquidCrystal.h>

// inicializa a biblioteca com os números dos pinos de interface
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define contraste 6
#define btnIniciar 7
// configuracao dos sensores
#define servoBotao 9                            // o botão deverá ser ligado no pino digital 9
#define sensorUM A4                             // configura o pino digital 2 para o PRIMEIRO SENSOR
#define sensorDOIS A5                           // configura o pino digital 3 para o SEGUNDO SENSOR

// configuracao do botao de selecao
bool iniciar_estado = false;

// configuracao dos sensores
int estadoUM, estadoDOIS;                            // variáveis que guardam os estados dos sensores
int temporizadorUM = HIGH;
int temporizadorDOIS = HIGH;
long tempoInicial;
float deslocamento = 50.0;
float tempoUM, tempoDOIS;
float velocidadeUM, velocidadeDOIS;

void setup() {
  Serial.begin(9600);
  // configura o número de linhas e colunas do LCD:
  lcd.begin(16, 2);
  // configuracao do contraste
  analogWrite(contraste, 110);

  pinMode(btnIniciar, INPUT);
  pinMode(sensorUM, INPUT);                          // configura o pino 3 como entrada
  pinMode(sensorDOIS, INPUT);                        // configura o pino 4 como entrada                        // configura o pino 12 como entrada

  // Introducao
  lcd.setCursor(0, 0);
  lcd.print("UFERSA APRESENTA");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   CORRIDA DE   ");
  lcd.setCursor(0, 1);
  lcd.print("    BOLINHAS    ");
  delay(1500);
}

void loop() {
  iniciar_estado = digitalRead(btnIniciar);
  if (iniciar_estado == HIGH) {
    lcd.clear();
    // contando a largada
    lcd.print("  PREPARADOS?");
    lcd.setCursor(0, 1);
    for (int i = 1; i < 4; i++) {
      lcd.print(i);
      lcd.print("...");
      delay(1000);
    }
    lcd.print("JA!");
    lcd.clear();
    // COMEEEEEEEECA A CORRIDA
    tempoInicial = millis();
    delay(200);           // tempo para a liberacao total
    while (true) {
      estadoUM = digitalRead(sensorUM);
      estadoDOIS = digitalRead(sensorDOIS);
      Serial.println(estadoUM);
      Serial.println(estadoDOIS);

      corridaUM();
      corridaDOIS();
      if ((temporizadorUM || temporizadorDOIS) == LOW) {
        break;
      }

    }
    while (true) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" Bolinha 1: ");
      lcd.print(velocidadeUM, 1);
      lcd.setCursor(0, 1);
      lcd.print(" Bolinha 2: ");
      lcd.print(velocidadeDOIS, 1);
      delay(1000);
    }
  }

}

// ===== AREA DAS FUNCOES =====

// funcao para controlar o temporizador da primeira bolinha
void corridaUM() {
  if (temporizadorUM == HIGH) {
    tempoUM = (millis() - tempoInicial) * 0.001;
    //lcd.print("Bolinha 1: ");
    //lcd.print(tempoUM);

    estadoUM = digitalRead(sensorUM);
    if (estadoUM == LOW) {
      velocidadeUM = (0.02 * deslocamento) / tempoUM;
      temporizadorUM = LOW;
    }
  }
}

// funcao para controlar o temporizador da primeira bolinha
void corridaDOIS() {
  if (temporizadorDOIS == HIGH) {
    tempoDOIS = (millis() - tempoInicial) * 0.001;
    //lcd.print("Bolinha 2: ");
    //lcd.print(tempoDOIS);

    estadoDOIS = digitalRead(sensorDOIS);
    if (estadoDOIS == LOW) {
      velocidadeDOIS = (0.02 * deslocamento) / tempoDOIS;
      temporizadorDOIS = LOW;
    }
  }
}
