#include <Wire.h>
#include <PrintEx.h>

PrintEx MyPrint = Serial;

int accelerometer_data[3];
// void because this only tells the cip to send data to its output register
// writes data to the slave's buffer
long tempo;
float angle[3] = {};

float x, y, z;
float eixoX, eixoY, eixoZ, modulo, moduloXZ;

// initialise and start everything
void setup() {
  Wire.begin();
  Serial.begin(9600);
  for (int i = 0; i < 3; ++i) {
    accelerometer_data[i]  = 0;
  }
  init_adxl345();
}

void loop() {
  tempo = millis();
  for (int n = 0; n < 300; n++) {
    read_adxl345();

//    tempo = millis();

    x = float(accelerometer_data[0]) * 3.9 / 1000;
    y = float(accelerometer_data[1]) * 3.9 / 1000;
    z = float(accelerometer_data[2]) * 3.9 / 1000;

    eixoX = calibragem(x, -0.94, 0.06, 1.05, -9.81, 9.81);
    eixoY = calibragem(y, -0.96, 0.01, 1.01, 9.81, -9.81);
    eixoZ = calibragem(z, -0.87, 0.12, 1.08, -9.81, 9.81);

    modulo = sqrt(eixoX * eixoX + eixoY * eixoY + eixoZ * eixoZ);
    moduloXZ = sqrt(eixoX * eixoX + eixoZ * eixoZ);

    // verifica o valor de cada eixo enviado pelo sensor
    //  Serial.print(x);//3.9mg/LSB scale factor in 13-bit mode
    //  Serial.print(",\t");
    //  Serial.print(y);
    //  Serial.print(",\t");
    //  Serial.println(z);

    // utiliza a componente dos eixos para definir a orientacao
    //  giroscopio(eixoX, eixoY, eixoZ);

    // imprime o vetor aceleracao da gravidade de cada eixo e o seu modulo
    //  MyPrint.printf("X = %.2f,  Y = %.2f,  Z = %.2f,  modulo = %.2f,  moduloXZ = %.2f\n", eixoX, eixoY, eixoZ, modulo, moduloXZ);
    Serial.print(millis() - tempo);
    MyPrint.printf(",\t%.2f\n", eixoX);
    //  Serial.print(eixoX);
    //  Serial.print(",\t");
    //  Serial.print(eixoY);
    //  Serial.print(",\t");
    //  Serial.print(eixoZ);
    //  Serial.print(",\t");
    //  Serial.println(modulo);
  }
  while (true) {}
}
