//*********************MEDINDO A VELOCIDADE DO SOM COM O SONAR HC SR04**********************
//******************************************************************************************
//***********************INTERFACE ENTRE O ARDUINO E O PYTHON*******************************
//******************************************************************************************
//******************************************************************************************
#define Pin_trigger 8
#define Pin_echo 9
#define LED 13
int opcao;
void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(Pin_trigger,OUTPUT);
  pinMode(Pin_echo,INPUT);
  digitalWrite(LED,LOW);

}

void loop() {
  if(Serial.available()>0){
    opcao = Serial.read();
  }
  switch(opcao){
    case 'A':
      digitalWrite(LED,HIGH);
      digitalWrite(Pin_trigger,LOW);
      delayMicroseconds(2);
      digitalWrite(Pin_trigger,HIGH);
      delayMicroseconds(10);
      digitalWrite(Pin_trigger,LOW);
  
      float Tempo = pulseIn(Pin_echo,HIGH);
      digitalWrite(LED,LOW);
      Serial.println(Tempo);
      opcao = 100;
      break;
  }

}
