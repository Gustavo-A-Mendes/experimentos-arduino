int pinoPotencia = A0;
float sinal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sinal = analogRead(pinoPotencia);
  Serial.println(sinal);
}
