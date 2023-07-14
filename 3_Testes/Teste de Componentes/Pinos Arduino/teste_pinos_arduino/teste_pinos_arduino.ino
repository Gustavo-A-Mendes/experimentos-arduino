// TESTE PORTAS DO ARDUINO

const int pinos[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2, A3, A4, A5};
String pinoNome[20] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", 
                       "A0", "A1", "A2", "A3", "A4", "A5"};
int sinais[20];
int arrLen;
bool comeco = false;
bool msgEscrita = false;

void setup() {
  Serial.begin(9600);
  arrLen = sizeof(pinos) / sizeof(pinos[0]);
  for (int i = 0; i < arrLen; i++) {
    pinMode(pinos[i], OUTPUT);
  }
}

void loop() {
COMECO:
  delay(500);
  Serial.println("Esperando Leitura...");
  comeco = false;

PROCESSO:
  for (int i = 0; i < arrLen; i++) {
    sinais[i] = digitalRead(pinos[i]);
    if (i > 1) {
      if (sinais[i] == 1) {
        testeMsg(i);
        break;
      }
      else if (i == arrLen - 1) {
        msgEscrita = false;
        if (comeco) {
          goto COMECO;
        }
      }
    }
  }
  goto PROCESSO;

  //  for (int i = 0; i < arrLen; i++) {
  //    Serial.print(digitalRead(pinos[i]));
  //  }
  //  Serial.println("");
}

void testeMsg(int n) {
  if (!msgEscrita) {
    Serial.print("Pino ");
    Serial.print(pinoNome[n]);
    Serial.println("");
    msgEscrita = true;
    comeco = true;
  }
}
