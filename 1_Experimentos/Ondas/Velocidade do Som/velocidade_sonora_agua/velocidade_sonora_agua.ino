#define pino_trigger 8
#define pino_echo 9 
#define contraste 6

#include <LiquidCrystal.h>
// inicializa a biblioteca com os números dos pinos de interface
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Variaveis
// Velocidade do som (20ºC)
// float velAr = 344.0;          //valor teorico
float velAr = 362.0;          // valor experimental

// frequencia: 40,000 Hz
// comprimento de onda = velocidade do som / frequencia
// p/ v=344, λ=8.6mm      ||    p/ v=362, λ=9.0mm

float alturaAr_CM = 7.0;    // meio comprimento de onda
float alturaAgua_CM = 30.0;
float tempo;
float velAgua;

void setup() {
  // Inicializamos a comunicacao com o display lcd
  lcd.begin(16, 2);
  pinMode(pino_trigger, OUTPUT); //PINO DE TRIGGER
  pinMode(pino_echo, INPUT); // SINAL DE ECO
  analogWrite(contraste, 110);

  lcd.print("  VELOC. DO SOM ");
  lcd.setCursor(0, 1);
  lcd.print("     NA AGUA    ");
  delay(2000);
  lcd.clear();
}

void loop()
{
  digitalWrite(pino_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pino_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pino_trigger, LOW);
  // o tempo sera registrado em microssegundos
  tempo = pulseIn(pino_echo, HIGH);
  velAgua = float (2 * alturaAgua_CM * velAr) / ((velAr * tempo * 0.0001) - (2 * alturaAr_CM));
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("t= ");
  lcd.print(tempo);
  lcd.print(" us");

  lcd.setCursor(0, 1);
  lcd.print("v_w= ");
  lcd.print(velAgua, 1);
  lcd.print(" m/s");
  delay(1000);
}
