/*  TESTE RGB
    Componentes:
    - 1 Módulo LED RBG;
    - 1 Resistor 220 ohm;
    - 4 fios link.

    Montagem:
    - Conectar com um fio em cada terminal de cor do RGB nos seus respectivos pinos do Arduino;
    - Conectar o resistor no GND.
*/

const int pinoRed = 9;
const int pinoGrn = 10;
const int pinoBlu = 11;

void setup()
{
  pinMode(pinoGrn, OUTPUT);
  pinMode(pinoBlu, OUTPUT);
  pinMode(pinoRed, OUTPUT);

  digitalWrite(pinoGrn, LOW);
  digitalWrite(pinoBlu, LOW);
  digitalWrite(pinoRed, HIGH);
}

void loop() {
  for (int i = 0; i < 255; i++) {
    analogWrite(pinoRed, (255-i));
    analogWrite(pinoGrn, (i));
    delay(3); // Wait for 10 millisecond(s)
  }
  for (int i = 0; i < 255; i++) {
    analogWrite(pinoGrn, (255-i));
    analogWrite(pinoBlu, (i));
    delay(3); // Wait for 10 millisecond(s)
  }
  for (int i = 0; i < 255; i++) {
    analogWrite(pinoBlu, (255-i));
    analogWrite(pinoRed, (i));
    delay(3); // Wait for 10 millisecond(s)
  }
}