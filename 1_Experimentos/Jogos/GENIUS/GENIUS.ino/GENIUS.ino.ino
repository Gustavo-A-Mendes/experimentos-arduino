// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Valores configuráveis
int rodadaMax = 10;
int rodadaAumentaVelocidade = 5; //
long tempoLimite = 3000;


// Define sinais de entrada e saida dos LEDs
#define BOTAO_AZUL 8
#define BOTAO_AMARELO 9
#define BOTAO_VERDE 10
#define BOTAO_VERMELHO 11

#define LED_AZUL 2
#define LED_AMARELO 3
#define LED_VERDE 4
#define LED_VERMELHO 5


#define CHOICE_OFF 0  // Usado para controlar LEDs
#define CHOICE_NONE 0  // Usado para verificar botões
#define CHOICE_AZUL (1 << 0)
#define CHOICE_AMARELO (1 << 1)
#define CHOICE_VERDE (1 << 2)
#define CHOICE_VERMELHO (1 << 3)

int rodada = 0;
long tempoDuracaoCor = 500;

int cores[100];

void setup() {
  Serial.begin(9600);
  
  pinMode(BOTAO_AZUL, INPUT_PULLUP);
  pinMode(BOTAO_AMARELO, INPUT_PULLUP);
  pinMode(BOTAO_VERDE, INPUT_PULLUP);
  pinMode(BOTAO_VERMELHO, INPUT_PULLUP);
  
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  
  randomSeed(analogRead(0));
}

void loop() {
  // Serial.print("oi");
  // teste = 1;
  // jogo();
  // delay(100);
  //Serial.println(analogRead(A5));

  attractMode();  // Pisca luzes enquanto aguarda o usuário apertar um botão

  // Indique o início do jogo
  acendeLEDS(CHOICE_AZUL | CHOICE_AMARELO | CHOICE_VERDE | CHOICE_VERMELHO);  // Ativar todos os LEDs
  delay(1000);
  acendeLEDS(CHOICE_OFF);  // Desligue os LEDs
  delay(250);

 
  // Recebe o resultado do jogo
  if (jogo() == true) {
    Serial.println("venceu!");
    //venceu(); // Ganhou
  } 
  else {
    Serial.println("perdeu!");
    //perdeu(); // Perdeu
  }
  while(1);
  
}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// As seguintes funções estão relacionadas a lógica do jogo

// Bloco principal:
// Retorna 0 se o jogador perder ou 1 se o jogador ganhar
int jogo(void) {
  gerarSequencia();
  rodada = 1;

  while (rodada <= rodadaMax) {
    mostrarSequencia();

    if (!jogador()) {
      return false;
    }
  }
  return true;
}

// Cria uma sequencia de cores aleatoria
void gerarSequencia(void) {
  for (int i = 0; i < rodadaMax; i++) {	
    int novaCor = random(0, 4);
	
    // Serial.print(i);
    // Serial.print(" - ");
    
    if (novaCor == 0) novaCor = CHOICE_AZUL;
    else if (novaCor == 1) novaCor = CHOICE_AMARELO;
    else if (novaCor == 2) novaCor = CHOICE_VERDE;
    else if (novaCor == 3) novaCor = CHOICE_VERMELHO;
    Serial.print(novaCor);
    cores[i] = novaCor;
    
    // delay(500);
  }
  Serial.print("\n");
}

// Reproduz as cores da sequencia, com base na quantidade de rodadas
void mostrarSequencia(void) {
  for (byte corAtual = 0; corAtual < rodada; corAtual++) {
    toner(cores[corAtual], tempoDuracaoCor);
    Serial.print(cores[corAtual]);
  }
  Serial.println("\n");
}

// O jogador deve repetir a sequencia de cores corretamente para ganhar
int jogador(void) {
  for (int corAtual = 0; corAtual < rodada; corAtual++) {
    int escolha = esperaBotao();
	
    if (escolha == 0) return false;
    if (escolha != cores[corAtual]) return false;
  }
  rodada++;
  delay(1000);
  return true;
}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// As seguintes funções controlam o hardware

// Acende LEDs selecionados
// Recebe um byte composto pelos CHOICE's das 4 cores
void acendeLEDS(byte leds) {

  // faz um teste bit a bit na entrada "leds"
  
  // xxx[b0] & 000[1] = 000[b0]
  if ((leds & CHOICE_AZUL) != 0) digitalWrite(LED_AZUL, HIGH);
  else digitalWrite(LED_AZUL, LOW);
  
  // xx[b1]x & 00[1]0 = 00[b1]0
  if ((leds & CHOICE_AMARELO) != 0) digitalWrite(LED_AMARELO, HIGH);
  else digitalWrite(LED_AMARELO, LOW);
  
  // x[b2]xx & 0[1]00 = 0[b2]00
  if ((leds & CHOICE_VERDE) != 0) digitalWrite(LED_VERDE, HIGH);
  else digitalWrite(LED_VERDE, LOW);
  
  // [b3]xxx & [1]000 = [b3]000
  if ((leds & CHOICE_VERMELHO) != 0) digitalWrite(LED_VERMELHO, HIGH);
  else digitalWrite(LED_VERMELHO, LOW);
}

// Aguarda até que um botão seja pressionado
// Retorna a cor do botao escolhido se dentro do limite de tempo, 0 se expirar
int esperaBotao(void) {
  
  // Cria um timer a partir do momento que a funcao e chamada
  long tempoInicial = millis();
  while ((millis() - tempoInicial) < tempoLimite) { 

    int botao = checaBotao();
    if (botao != CHOICE_NONE) {
      // toner(botao, 150);
      toner(botao, tempoDuracaoCor);
      while (checaBotao() != CHOICE_NONE);  // espera até que o jogador solte o botao
      
      delay(10);

      return botao;
    }
  }

  return CHOICE_NONE;
}

// Retorna um bit '1' na posição correspondente a CHOICE_RED, CHOICE_GREEN, etc.
int checaBotao(void) {
  
  if      (digitalRead(BOTAO_AZUL) == 0)      return (CHOICE_AZUL);
  else if (digitalRead(BOTAO_AMARELO) == 0)   return (CHOICE_AMARELO);
  else if (digitalRead(BOTAO_VERDE) == 0)     return (CHOICE_VERDE);
  else if (digitalRead(BOTAO_VERMELHO) == 0)  return (CHOICE_VERMELHO);

  return (CHOICE_NONE);  // Se nenhum botão for pressionado, não retorne nenhum
}


void toner(byte opcao, int atraso) {

  acendeLEDS(opcao);  // Ligue um dado LED

  // Reproduz o som associado ao LED fornecido
  switch (opcao) {

    case CHOICE_AZUL:
      delay(atraso);
      // buzz_sound(buzz_length_ms, 1136);
      break;

    case CHOICE_AMARELO:
      delay(atraso);
   	  // buzz_sound(buzz_length_ms, 568);
      break;

    case CHOICE_VERDE:
      delay(atraso);
      // buzz_sound(buzz_length_ms, 851);
      break;

    case CHOICE_VERMELHO:
      delay(atraso);
      // buzz_sound(buzz_length_ms, 638);
      break;
  }

  acendeLEDS(CHOICE_OFF);  // Desligue todos os LEDs
}

// Mostra uma tela de "modo de atração" enquanto aguarda o usuário pressionar o botão.
void attractMode(void) {

  while (1) {
    acendeLEDS(CHOICE_AZUL);
    delay(100);
    if (checaBotao() != CHOICE_NONE) return;

    acendeLEDS(CHOICE_AMARELO);
    delay(100);
    if (checaBotao() != CHOICE_NONE) return;

    acendeLEDS(CHOICE_VERDE);
    delay(100);
    if (checaBotao() != CHOICE_NONE) return;

    acendeLEDS(CHOICE_VERMELHO);
    delay(100);
    if (checaBotao() != CHOICE_NONE) return;
  }
}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Lixo

// void jogo() {
//   for (int i = 0; i <= prox_cor; i++) {
//     Serial.println(cores[i]);
//     switch (cores[i]) {    
//       case 1:
// 		digitalWrite(LED_AZUL, HIGH); 
//     	digitalWrite(LED_AMARELO, LOW); 
//     	digitalWrite(LED_VERDE, LOW); 
//     	digitalWrite(LED_VERMELHO, LOW);
//       	delay(500);	
//       	break;
      
//       case 2:
//       	digitalWrite(LED_AZUL, LOW); 
//     	digitalWrite(LED_AMARELO, HIGH); 
//     	digitalWrite(LED_VERDE, LOW); 
//     	digitalWrite(LED_VERMELHO, LOW);  	
//       	delay(500);
//       	break;
      
//       case 3:
//       	digitalWrite(LED_AZUL, LOW); 
//     	digitalWrite(LED_AMARELO, LOW); 
//     	digitalWrite(LED_VERDE, HIGH); 
//     	digitalWrite(LED_VERMELHO, LOW);
//       	delay(500);
//       	break;
      
//       case 4:
//     	digitalWrite(LED_AZUL, LOW); 
//     	digitalWrite(LED_AMARELO, LOW); 
//     	digitalWrite(LED_VERDE, LOW); 
//     	digitalWrite(LED_VERMELHO, HIGH);	
//       	delay(500);	
//       	break;
      
//       default:
//       	digitalWrite(LED_AZUL, LOW); 
//     	digitalWrite(LED_AMARELO, LOW); 
//     	digitalWrite(LED_VERDE, LOW); 
//     	digitalWrite(LED_VERMELHO, LOW);
//       	delay(500);
//       	break;
//     }
//     delay(100);
//   }  
  
//   digitalWrite(LED_AZUL, LOW); 
//   digitalWrite(LED_AMARELO, LOW); 
//   digitalWrite(LED_VERDE, LOW); 
//   digitalWrite(LED_VERMELHO, LOW);
  
//   while (teste) {
//     //Serial.println("oi");
//     //Serial.println(prox_cor);
    
//     /*
//     azul = digitalRead(8);
//     amarelo = digitalRead(9);
//     verde = digitalRead(10);
//     vermelho = digitalRead(11);
//     */
//     acendeCor();
//     Serial.println(n);
    
//     if (apertouBotao()) {
//     } else {
//       n = 0;
//     }
    
    
//     /*
//     if (n != 0) {
// 	  checarCor();  
//     }
//     */
//    	// cor = analogRead(A5); 
//     delay(500);
//   }
//   /*
//   if(analogRead(A5) > 800) {
//       prox_cor++; 
//   }
//   */
// }
/*
bool apertouBotao() {
  
  static bool estado_Atu = 1, estado_Ant = 1;
  bool saida = 0;
  if (!(azul && amarelo && verde && vermelho)) {
    estado_Atu = 0;
  } else {
    estado_Atu = 1;
  }
  
  if (estado_Atu != estado_Ant) {
    if (estado_Atu == LOW) {
      //Serial.println("to aqui");
      saida = 1;
      
    }
    estado_Ant = estado_Atu;
  }
  //Serial.println(saida);
  return saida;
}

void acendeCor() {
  
  azul = digitalRead(8);
  amarelo = digitalRead(9);
  verde = digitalRead(10);
  vermelho = digitalRead(11);
  
  if (azul == LOW) {
    n = 1;
    digitalWrite(LED_AZUL, HIGH); 
  } else {
    digitalWrite(LED_AZUL, LOW); 
  }
  if (amarelo == LOW) {
    n = 2;
    digitalWrite(LED_AMARELO, HIGH); 
  } else {
    digitalWrite(LED_AMARELO, LOW); 
  }
  if (verde == LOW) {
    n = 3;
    digitalWrite(LED_VERDE, HIGH); 
  } else {
    digitalWrite(LED_VERDE, LOW); 
  }
  if (vermelho == LOW) {
    n = 4;
    digitalWrite(LED_VERMELHO, HIGH); 
  } else {
    digitalWrite(LED_VERMELHO, LOW); 
  }
}

void checarCor() {
  // prox_cor = 0;

  for (int i = 0; i <= prox_cor;) {
    acendeCor();
  	//if (n != 0) {
    if (apertouBotao()) {
      Serial.println("oi");
      if (cores[i] == n) {
        i++;
      } else {
        perdeu();
      }
    }      
  }
  prox_cor++;
  teste = 0;
}


void perdeu() {
  while (true) {
    Serial.println("Perdeu Playboy!");
  }
}
*/