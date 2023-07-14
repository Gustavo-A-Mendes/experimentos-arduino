bool i = true;
int x = 0;
int y = 5;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//while(x<y) if(i) x++; Serial.println(x); 
  Serial.println(round(27/4));
}
