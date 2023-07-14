int sinal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(analogRead(A0));
  sinal = analogRead(A0);
  if (sinal > 800) {
    Serial.println("frente");
  }
  else if (sinal < 250) {
    Serial.println("trás");
  }
  else {
    Serial.println("parado");
  }
}
