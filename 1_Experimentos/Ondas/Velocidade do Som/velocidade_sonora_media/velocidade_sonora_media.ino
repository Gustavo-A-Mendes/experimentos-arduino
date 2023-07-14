#define pino_trigger 8
#define pino_echo 9
#define contraste  6

#include <LiquidCrystal.h>
// inicializa a biblioteca com os números dos pinos de interface
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Variaveis
float distancia_CM = 16.0;
float tempo, velAr;
float tempoMedia, velMedia;

void setup() {
  // Inicializamos a comunicacao com o display lcd
  lcd.begin(16, 2);
  pinMode(pino_trigger, OUTPUT); //PINO DE TRIGGER
  pinMode(pino_echo, INPUT); // SINAL DE ECO
  analogWrite(contraste, 110);

  lcd.print("  VELOC. DO SOM ");
  lcd.setCursor(0, 1);
  lcd.print("      NO AR     ");
  delay(2000);
}

void loop() {
  for (int i = 0; i < 20; i++) {
    digitalWrite(pino_trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(pino_trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(pino_trigger, LOW);
    // o tempo sera registrado em microssegundos
    tempo = pulseIn(pino_echo, HIGH);
    velAr = float((2 * distancia_CM * 10000.0) / tempo);

    tempoMedia = tempoMedia + tempo;
    velMedia = velMedia + velAr;
    delay(500);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("t = ");
  lcd.print(tempo);
  lcd.print("us");

  lcd.setCursor(0, 1);
  lcd.print("v_a = ");
  lcd.print(velAr, 1);
  lcd.print(" m/s");

  tempoMedia = 0;
  velMedia = 0;
}
