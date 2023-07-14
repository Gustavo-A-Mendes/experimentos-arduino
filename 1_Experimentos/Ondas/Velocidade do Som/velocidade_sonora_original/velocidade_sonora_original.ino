//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
//Variaveis
float SEP_CM = 50.0;
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define pino_trigger 6
#define pino_echo 7

void setup()
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  // Inicializamos a comunicacao serial a
  // 9600 baud rate

  Serial.begin(9600);
  pinMode(pino_trigger, OUTPUT); //PINO DE TRIGGER
  pinMode(pino_echo, INPUT); // SINAL DE ECO

}

void loop()
{
  digitalWrite(pino_trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pino_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pino_trigger, LOW);
  float Tempo = pulseIn(pino_echo, HIGH);
  float Vel = float((SEP_CM * 10000.0) / Tempo);

  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Tempo:");
  lcd.print(Tempo);
  lcd.print("us");
  lcd.setCursor(0, 1);
  lcd.print("Vel.som:");
  lcd.print(Vel);
  lcd.print("m/s");
  delay(700);
