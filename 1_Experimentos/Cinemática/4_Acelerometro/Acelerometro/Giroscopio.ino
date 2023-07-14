int estados[6][3] = {
  {"1 1 0"},
  {"1 1 2"},
  {"1 0 1"},
  {"0 1 1"},
  {"0 2 1"},
  {"2 0 1"}
};

String orientacao[] = {
  "cima",
  "baixo",
  "retrato",
  "retrato invertido",
  "paisagem",
  "paisagem invertida"
};

float angulos[3] = {};
String angRef = "";

void giroscopio(float x, float y, float z) {
  angulos[0] = inclinacao(x);
  angulos[1] = inclinacao(y);
  angulos[2] = inclinacao(z);

  //  Serial.print(angulos[0]);
  //  Serial.print(",\t");
  //  Serial.print(angulos[1]);
  //  Serial.print(",\t");
  //  Serial.println(angulos[2]);

  if (angulos[2] == 0) {
    Serial.println(orientacao[0]);
  }
  else if (angulos[2] == 2) {
    Serial.println(orientacao[1]);
  }
  else {
    if (angulos[1] == 0) {
      Serial.println(orientacao[2]);
    }
    else if (angulos[1] == 2) {
      Serial.println(orientacao[3]);
    }
    else {
      if (angulos[0] == 0) {
        Serial.println(orientacao[4]);
      }
      else if (angulos[0] == 2) {
        Serial.println(orientacao[5]);
      }
    }
  }
}
