/* 
UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
BACHARELADO EM CIENCIAS E TECNOLOGIA - BCT
=====:Ohmimetro:=====
  
  Utilizando o Arduino, é possível medir o valor de uma
  resistência, a partir de uma relação de resistores, com um
  dos valores conhecidos. 

  O valor da RESISTÊNCIA é medido sobre o resistor conectado
  no 0V (R2), a partir da medição da tensão sobre esse resistor.
  É necessário definir o valor de R1 e a tensão de entrada, que
  será os 5V do Arduino. O cálculo é feito então, usando a
  seguinte equação: R2 = R1 * V_out / V_in - V_out
  Onde V_out é a tensão sobre R2 (tensão máxima do Arduino).
*/

// pinos de entrada
const int tenPIN1 = A0;
const int tenPIN2 = A1;

// armazena valores utilizados
float nivel = 0.0;
float Vin = 5.0;
float Vout = 0.0;
float R1 = 10000.0;
float R2 = 0.0;

float fator = 0.0;

void setup() {
  Serial.begin(9600);
  pinMode(tenPIN1, INPUT);
}

void loop() {
  // voltímetro (converter nivel analógico para valor de tensão);
  // Serial.println(analogRead(tenPIN1) * (5.0 / 1023));
  nivel = analogRead(tenPIN1);
  Vout = nivel * (Vin / 1023.0);

  // ohmímetro
  fator = (Vin/Vout) - 1;
  R2 = R1 / fator;
  
  Serial.println("");
  Serial.print(Vout, 3);
  Serial.print(" V | ");
  Serial.print(R2, 3);
  Serial.print(" Ohm | ");
  // Serial.print(tensao2 * 101.0, 3);  	  Serial.print(" V | ");
  // Serial.print(corrente1 * 1000.0, 3);   Serial.print(" mA |");
  // Serial.print(corrente2 * 1000.0, 3);   Serial.println(" mA");
}