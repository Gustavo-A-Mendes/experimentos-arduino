
int state = 0;

void indicacaoTrilha (int n, int nBit[4]) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(nBit[i], bitRead(n, i));
  }
}
