// Exemplo por Jeff Gray (originalmente em Inglês)
// Arduino Mega usando todas suas quatro portas seriais
// (Serial, Serial1, Serial2, Serial3),
// com baud rates diferentes:

void setup() {
  Serial.begin(9600);
  Serial1.begin(38400);
  Serial2.begin(19200);
  Serial3.begin(4800);

  Serial.println("Hello Computer");
  Serial1.println("Hello Serial 1");
  Serial2.println("Hello Serial 2");
  Serial3.println("Hello Serial 3");
}
void loop() {
}
