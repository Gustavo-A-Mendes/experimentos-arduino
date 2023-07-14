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
#include <Servo.h>
#include <LiquidCrystal.h>

// inicializa a biblioteca com os números dos pinos de interface
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo meuServo;
bool servoAtivo = false;

// configuracao dos botoes de selecao
const int btnMenu = 7;
const int btnSeletor = 8;
bool menu_estado = false;
bool menu_estadoAnt;
bool seletor_estado = false;
bool seletor_estadoAnt;
int contador = 0;
int contador2 = 0;

// configuracao da inclinacao
const int sinalTransf = A0;
int transferidor;
int grau;

// configuracao dos sensores
const int servoBotao = 9;                           // o botão deverá ser ligado no pino digital 12
const int sensorUM = A4;                              // configura o pino digital 2 para o PRIMEIRO SENSOR
const int sensorDOIS = A5;                            // configura o pino digital 3 para o SEGUNDO SENSOR
int estadoUM, estadoDOIS;                            // variáveis que guardam os estados dos sensores
long instanteInicial;                                // tempo decorrido antes de ativar o servomotor
long instanteUM, instanteDOIS;                       // tempo decorrido pelo programa até os sensores
long interTempoUM, interTempoDOIS;                   // intervalo decorrido do início até os sensores
float deslocamentoUM = 400.0;                        // distância sugerida, em milimetros, até o sensorUM.
// Mude se for conveniente
float deslocamentoDOIS = 400.0;                      // distância sugerida, em milimetros, até o sensorDOIS.
// Mude se for conveniente
float velUM, velDOIS;                                // variáveis que guardam a velocidade em cada instante
float aceleracao;
float gravidadeUM, gravidadeDOIS;                    // variáveis que guardam a gravidade em cada instante
float gravidadeMedia;

void setup() {
  // configura o número de linhas e colunas do LCD:
  lcd.begin(16, 2);
  meuServo.attach(9);                                // configura o pino 9 como saída do servomotor

  pinMode(btnMenu, INPUT);
  pinMode(btnSeletor, INPUT);
  pinMode(sinalTransf, INPUT);
  pinMode(sensorUM, INPUT);                          // configura o pino 3 como entrada
  pinMode(sensorDOIS, INPUT);                        // configura o pino 4 como entrada
  pinMode(servoBotao, INPUT);                        // configura o pino 12 como entrada
  meuServo.write(175);                               // posição em que o servomotor inicia
}

void loop() {
  menu();
  switch (contador) {
    case 0:
      lcd.clear();
      lcd.print("   Escolha um");
      lcd.setCursor(0, 1);
      lcd.print("   Experimento");
      while (contador == 0) {
        menu();
      }
      break;
    case 1:
      lcd.clear();
      lcd.print("  Mov. Uniforme");
      contador2 = 0;
      while (contador == 1) {
        menu();
        movimento_uniforme();
      }
      break;
    case 2:
      lcd.clear();
      lcd.print("  Mov. Variado");
      contador2 = 0;
      while (contador == 2) {
        menu();
        movimento_variado();
      }
      break;
    case 3:
      lcd.clear();
      lcd.print("  Queda Livre");
      contador2 = 0;
      while (contador == 3) {
        menu();
        queda_livre();
      }
      break;
    default:
      contador = 1;
      break;
  }
}

// ===== AREA DAS FUNCOES =====

void menu() {
  menu_estado = digitalRead(btnMenu);
  if (menu_estado != menu_estadoAnt) {
    if (menu_estado == HIGH) {
      contador++;
      delay(500);
    }
  }
  menu_estadoAnt = menu_estado;
}


void selecao() {
  seletor_estado = digitalRead(btnSeletor);
  switch (contador2) {
    case 0:
      if (seletor_estado != seletor_estadoAnt) {
        if (seletor_estado == HIGH) {
          contador2++;
          delay(500);
        }
      }
      seletor_estadoAnt = seletor_estado;
      break;
    case 1:
      lcd.clear();
      angulo();
      seletor_estado = digitalRead(btnSeletor);
      if (contador == 1) {
        while (seletor_estado == 0 || transferidor > grau + 1) {
          seletor_estado = digitalRead(btnSeletor);
          angulo();
        }
      }
      else if (contador == 2) {
        while (seletor_estado == 0 || (transferidor < 29 || transferidor > 31) && (transferidor < 44 || transferidor > 46)) {
          seletor_estado = digitalRead(btnSeletor);
          angulo();
        }
      }
      else {
        while (seletor_estado == 0 || transferidor < grau - 1) {
          seletor_estado = digitalRead(btnSeletor);
          angulo();
        }
      }
      contador2++;
      break;
    case 2:
      contador2++;
      break;
    default:
      testeContinuar();
      break;
  }
    
}


void angulo() {
  const int resMIN = 0;
  const int resMAX = 1023;
  transferidor = map(analogRead(sinalTransf), resMIN, resMAX, 0, 180);

  lcd.print("<Angulo: ");
  lcd.print(transferidor);
  lcd.print(">");
  lcd.setCursor(0, 1);
  lcd.print("Incline em ");
  if (contador == 2) {
    lcd.print("30/45");
  }
  else {
    lcd.print(grau);
  }

  delay(250);
  lcd.clear();
}


void movimento_uniforme() {
  grau = 2;
  selecao();
  if (contador2 == 2) {
    sensorDados();
    
    interTempoUM = (instanteUM - instanteInicial); // cálculo do primeiro intervalo de tempo
    velUM = (0.001 * deslocamentoUM) / (0.001 * interTempoUM);
    interTempoDOIS = (instanteDOIS - instanteUM);  // cálculo do segundo intervalo de tempo
    velDOIS = (0.001 * deslocamentoDOIS) / (0.001 * interTempoDOIS);

    lcd.clear();
    lcd.print("v1 = ");
    lcd.print(velUM);
    lcd.setCursor(0, 1);
    lcd.print("v2 = ");
    lcd.print(velDOIS);
    delay(500);
    seletor_estado = digitalRead(btnSeletor);
    while (seletor_estado == 0) {
      seletor_estado = digitalRead(btnSeletor);
    }
  }
}


void movimento_variado() {
  selecao();
  if (contador2 == 2) {
    sensorDados();
    
    interTempoUM = (instanteUM - instanteInicial); // cálculo do primeiro intervalo de tempo
    velUM = (0.001 * deslocamentoUM) / (0.001 * interTempoUM);
    interTempoDOIS = (instanteDOIS - instanteUM);  // cálculo do segundo intervalo de tempo
    velDOIS = (0.001 * deslocamentoDOIS) / (0.001 * interTempoDOIS);

    aceleracao = ((velDOIS * velDOIS) - (velUM * velUM)) / (2 * 0.001 * deslocamentoDOIS); // eq. De Torricelli

    lcd.clear();
    lcd.print("a1 = ");
    lcd.print(aceleracao);
    delay(500);
    seletor_estado = digitalRead(btnSeletor);
    while (seletor_estado == 0) {
      seletor_estado = digitalRead(btnSeletor);
    }
  }
}


void queda_livre() {
  grau = 90;
  selecao();
  if (contador2 == 2) {
    sensorDados();
    
    interTempoUM = (instanteUM - instanteInicial); // cálculo do primeiro intervalo de tempo
    gravidadeUM = (2 * 0.001 * deslocamentoUM) / pow(0.001 * interTempoUM, 2);
    interTempoDOIS = (instanteDOIS - instanteInicial);  // cálculo do segundo intervalo de tempo
    gravidadeDOIS = (4 * 0.001 * deslocamentoDOIS) / pow(0.001 * interTempoDOIS, 2);

    gravidadeMedia = (gravidadeUM + gravidadeDOIS) / 2;

    lcd.clear();
    lcd.print("g = ");
    lcd.print(gravidadeMedia);
    delay(500);
    seletor_estado = digitalRead(btnSeletor);
    while (seletor_estado == 0) {
      seletor_estado = digitalRead(btnSeletor);
    }
  }
}


void sensorDados() {
  while (true) {
    lcd.clear();
    lcd.print("APERTE O BOTAO ");
    lcd.setCursor(0, 1);
    lcd.print("PARA COMECAR...");
    delay(500); // pausa de 0.2 segundos

    /*
    servoAtivo = digitalRead(servoBotao);         // ler o botão e armazena em servoAtivo
    if (servoAtivo == HIGH) {
      break;
    }
    */
    
    seletor_estado = digitalRead(btnSeletor);
    if (seletor_estado == HIGH) {
      seletor_estado = LOW;
      break;
    }
  }

  instanteInicial = 100;

  instanteUM = 200;
  deslocamentoUM = 400;
  instanteDOIS = 250;
  deslocamentoDOIS = 400;

  /*
  while (servoAtivo == HIGH) {
    if (instanteInicial == 0) {
      lcd.print("PREPARANDO...");
      delay(3000);
      lcd.print("OBJETO LIBERADO");
      meuServo.write(120);                           // abrir a porta
      delay(atraso);                                 // espera até a bola ser totalmente liberada
      instanteInicial = millis();                    // armazenar o tempo quandoa bola foi liberada
    }

    estadoUM = digitalRead(sensorUM);                // ler o sensor UM e armazena em estadoDOIS
    if (estadoUM == LOW) {
      instanteUM = millis();                         // armazena o tempo Total decorrido para Sensor UM
      interTempoUM = (instanteUM - instanteInicial); // cálculo do primeiro intervalo de tempo
    }

    estadoDOIS = digitalRead(sensorDOIS);            // ler o sensor DOIS e armazena em estadoTRES
    if (estadoDOIS == LOW) {
      instanteDOIS = millis();                       // armazena o tempo Total decorrido para Sensor DOIS
      interTempoDOIS = (instanteDOIS - instanteUM);  // cálculo do segundo intervalo de tempo
    }

    delay(3000);                              // tempo de espera para efetuar nova leitura
    instanteInicial = 0;                      // a variável do tempo inicial será limpa
    meuServo.write(175);                      // o servomotor volta ao estado inicial
    servoAtivo = LOW;                         // o código sai da estrutura while
  }
  */
}


void testeContinuar() {
  lcd.clear();
  lcd.print("Continuar?");
  lcd.setCursor(0, 1);
  lcd.print("[NAO] [SIM]");
  delay(500);

  menu_estado = digitalRead(btnMenu);
  seletor_estado = digitalRead(btnSeletor);
  while (menu_estado == 0 || seletor_estado == 0) {
    menu_estado = digitalRead(btnMenu);
    seletor_estado = digitalRead(btnSeletor);
    if (menu_estado == 1) {
      contador = 0;
      break;
    }
    if (seletor_estado == 1) {
      contador2 = 2;
      break;
    }
  }
  delay(500);
}
