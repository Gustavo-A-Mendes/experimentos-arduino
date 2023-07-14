/* 
UNIVERSIDADE FEDERAL RURAL DO SEMI-ARIDO
CENTRO DE CIENCIAS EXATAS E NATURAIS - CCEN
BACHARELADO EM CIENCIAS E TECNOLOGIA - BCT
=====:Multimetro:=====
  
  Utilizando o Arduino, é possível medir qualquer tensão, a
  partir de uma relação de resistores. 

  O valor da TENSÃO é medido sobre o resistor conectado no 0V.
  Devido a limitação do dispositivo em receber no máximo 5V, é 
  necessário garantir que essa seja a tensão máxima sobre o
  resistor medido. A proporção deve ser calculada previamente,
  através da equação: V_out = V_in * R2/(R1+R2)
  Onde V_out não pode passar de 5V (tensão máxima do Arduino).

  O valor da CORRENTE será feito através da dedução, através da
  lei de Ohm. Recomenda-se que o resistor sob teste tenha um
  valor bem menor, proporcionalmente, que o outro resistor 
  associado, para não interferir na corrente do sistema.

*/

// pinos de entrada
const int tenPIN1 = A0;
const int tenPIN2 = A1;

// armazena valores utilizados
float tensao1, tensao2;
float corrente1, corrente2;

void setup() {
  Serial.begin(9600);
  pinMode(tenPIN1, INPUT);
  pinMode(tenPIN2, INPUT);
}

void loop() {
  // voltímetro (converter nivel analógico para valor de tensão);
  // Serial.println(analogRead(tenPIN1) * (5.0 / 1023));
  tensao1 = analogRead(tenPIN1) * (5.0 / 1023);
  tensao2 = analogRead(tenPIN2) * (5.0 / 1023);

  // amperímetro
  corrente1 = tensao1 / 1000.0;
  corrente2 = tensao2 / 10.0;
  //Serial.println(tensao2);

  Serial.println("");
  Serial.print(tensao1 * 6, 3);
  Serial.print(" V | ");
  Serial.print(tensao1, 3);
  Serial.print(" V | ");
  // Serial.print(tensao2 * 101.0, 3);  	  Serial.print(" V | ");
  // Serial.print(corrente1 * 1000.0, 3);   Serial.print(" mA |");
  // Serial.print(corrente2 * 1000.0, 3);   Serial.println(" mA");
}