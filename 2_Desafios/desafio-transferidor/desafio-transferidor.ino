const int sinal = A0;
int leitura = 0;
int l_Ant = 0;
int l_Atu = 0;
int angulo = 0;
float resMax = 817.0;
float resMin = 257.0;

int resDif = 0;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sinal, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  leitura = analogRead(sinal);
  
  
  /*if (leitura < 390) {
    angulo = map(leitura, resMin, 363, 0, 90); // de 257 a 363 == 0° a 90° (1° para cada 1.18 de sinal)
  }
  else {
    angulo = map(leitura, 363, resMax, 90, 180); // de 363 a 1023 == 90° a 180° (1° para cada 5.04 de sinal)
  }*/

  // resDif = resMax - resMin;
  // angulo = 180 * (leitura - resMin) / (resDif);

  Serial.print("Leitura pino: ");
  Serial.println(leitura);
  // Serial.print("Diferença: ");
  // Serial.println(resDif);
  // Serial.print("angulo: ");
  // Serial.println(angulo);
  delay(25);
}
