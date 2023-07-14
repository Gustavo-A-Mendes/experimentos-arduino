//Programa: Conectando Sensor Ultrassonico HC-SR04 ao Arduino
//Autor: FILIPEFLOP

//Define os pinos para o trigger e echo
#define pino_trigger 8
#define pino_echo 9
#define contraste  6

//Carrega a biblioteca do sensor ultrassonico e do display lcd
#include <Ultrasonic.h>

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);


#include <LiquidCrystal.h>

// inicializa a biblioteca com os números dos pinos de interface
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{ 
  // Inicializamos a comunicacao com o display lcd
  lcd.begin(16, 2);

   /*
  Serial.begin(9600);
  Serial.println("Lendo dados do sensor...");
  */
  
  pinMode(pino_trigger, OUTPUT); //PINO DE TRIGGER
  pinMode(pino_echo, INPUT); // SINAL DE ECO
  
  analogWrite(contraste, 110);

  lcd.print("    DISTANCIA   ");
  lcd.setCursor(0, 1);
  lcd.print("    ULTRASSOM   ");
  delay(2000);
  lcd.clear();
  
}

void loop()
{
  
  //Le as informacoes do sensor, em cm e pol
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  //inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dist.: ");
  lcd.print(cmMsec);
  lcd.print("cm");

  delay(1000);

  /*
  //Exibe informacoes no serial monitor
  Serial.print("Distancia em cm: ");
  Serial.println(cmMsec);
  // Serial.print(" - Distancia em polegadas: ");
  // Serial.println(inMsec);
  delay(1000);
  */
}
