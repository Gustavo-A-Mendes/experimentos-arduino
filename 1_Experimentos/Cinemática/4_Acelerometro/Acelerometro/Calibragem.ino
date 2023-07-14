// redistribuicao generica de uma faixa de entrada para uma faixa de saida
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// alinha os valores de entrada minimos e maximos com a variação de -1 a 1
// o valor de origem corresponde ao acelerometro em paralelo com o eixo
float alinhamento(float x, float in_min, float origem, float in_max) {
  if (x < origem) {
    return floatMap(x, in_min, origem, -1.00, 0.00);
  }
  else {
    return floatMap(x, origem, in_max, 0.00, 1.00);
  }
}

// distribuicao dos valores alinhados com o valor da gravidade
float calibragem(float x, float in_min, float origem, float in_max, float out_min, float out_max) {
  float xCalibrado = alinhamento(x, in_min, origem, in_max);
  return floatMap(xCalibrado, -1.00, 1.00, out_min, out_max);
}

// define uma orientacao com base na aceleracao percebida no eixo
float inclinacao(float n) {
  if (n >= 6.93) {
    return 0;
  }
  else if (n >= -6.93) {
    return 1;
  }
  else {
    return 2;
  }
}
