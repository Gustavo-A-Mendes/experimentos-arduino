const int redPin = 9, grnPin = 10, bluPin = 11;
long redSignal, grnSignal, bluSignal;
long rndNum;

int incRed = 1, incGrn = 1, incBlu = 1;

void setup() {
  // inicia a comunicacao serial
  Serial.begin(9600);
  // semente para geracao de numero aleatoria
  randomSeed(analogRead(0));

  pinMode(redPin, OUTPUT);
  pinMode(grnPin, OUTPUT);
  pinMode(bluPin, OUTPUT);
  
  // a cor do LED comeca vermelha
  redSignal = 255;
  grnSignal = 0;
  bluSignal = 0;
}

void loop() {
/*
  rndNum -> |  RED  | GREEN |  BLUE  |
            |   0   |   1   |   2    |
*/
  rndNum = random(3);
  switch (rndNum) {
    case 0:
      if (redSignal == 0) {
        incRed = abs(incRed);
      }
      else if (redSignal == 255) {
        incRed = (-1) * abs(incRed);
      }
      redSignal += incRed;
      break;
    case 1:
      if (grnSignal == 0) {
        incGrn = abs(incGrn);
      }
      else if (grnSignal == 255) {
        incGrn = (-1) * abs(incGrn);
      }
      grnSignal += incGrn;
      break;
    case 2:
      if (bluSignal == 0) {
        incBlu = abs(incBlu);
      }
      else if (bluSignal == 255) {
        incBlu = (-1) * abs(incBlu);
      }
      bluSignal += incBlu;
      break;
    default:
      break;
  }

  Serial.print(redSignal);
  Serial.print("\t");
  Serial.print(grnSignal);
  Serial.print("\t");
  Serial.println(bluSignal);
  
  analogWrite(redPin, redSignal);
  analogWrite(grnPin, grnSignal);
  analogWrite(bluPin, bluSignal);

  // delay(1);
}