// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Valores configuráveis
int rodadaMax = 10;
int rodadaAumentaVelocidade = 5; //
long tempoLimite = 3000;



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Define sinais de entrada e saida dos LEDs
#define BOTAO_AZUL 8
#define BOTAO_AMARELO 9
#define BOTAO_VERDE 10
#define BOTAO_VERMELHO 11

#define LED_AZUL 2
#define LED_AMARELO 3
#define LED_VERDE 4
#define LED_VERMELHO 5

int rodada = 0;
int rodadaCount = 0;
long tempoDuracaoCor = 500;
int recomecar = 1;

int cores[50];
int n = 5;

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
  
  while(recomecar) {
    attractMode();  // Pisca luzes enquanto aguarda o usuário apertar um botão
    recomecar = 0;
  }
  
  // Indique o início do jogo
  acendeLEDS(4);  // Ativar todos os LEDs
  delay(1000);
  acendeLEDS(5);  // Desligue os LEDs
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
  delay(2000);
  recomecar = 1;
  
}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// As seguintes funções estão relacionadas a lógica do jogo

// Bloco principal:
// Retorna 0 se o jogador perder ou 1 se o jogador ganhar
int jogo(void) {
  gerarSequencia();
  rodada = 0;

  rodadaCount = 0;
  while (rodada < rodadaMax) {
    if (rodadaCount = rodadaAumentaVelocidade) {
      tempoDuracaoCor -= 100;
      rodadaCount = 0;
    }
    
    mostrarSequencia();
	
    if (!jogador()) {
      return false;
    }
  return true;
}

// Cria uma sequencia de cores aleatoria
void gerarSequencia(void) {
  for (int i = 0; i < rodadaMax; i++) {	
    int novaCor = random(0, 4);

    Serial.print(novaCor);
    cores[i] = novaCor;
  }
  Serial.print("\n");
}

// Reproduz as cores da sequencia, com base na quantidade de rodadas
void mostrarSequencia(void) {
  for (int corAtual = 0; corAtual <= rodada; corAtual++) {
    
    toner(cores[corAtual], tempoDuracaoCor);
    Serial.print(cores[corAtual]);
  }
  Serial.println("\n");
}

// O jogador deve repetir a sequencia de cores corretamente para ganhar
int jogador(void) {
  for (int corAtual = 0; corAtual <= rodada; corAtual++) {
    int escolha = esperaBotao();
	
    if (escolha == 5) return false;
    if (escolha != cores[corAtual]) return false;
  }
  rodada++;
  rodadaCount++;
  delay(1000);
  return true;
}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// As seguintes funções controlam o hardware

// Acende LEDs selecionados
// Recebe um byte composto pelos CHOICE's das 4 cores
void acendeLEDS(int n) {
  switch (n) {
    case 0:
      digitalWrite(LED_AZUL, HIGH);
      digitalWrite(LED_AMARELO, LOW);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, LOW);
      break;
    case 1:
      digitalWrite(LED_AZUL, LOW);
      digitalWrite(LED_AMARELO, HIGH);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, LOW);
      break;
    case 2:
      digitalWrite(LED_AZUL, LOW);
      digitalWrite(LED_AMARELO, LOW);
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, LOW);
      break;
    case 3:
      digitalWrite(LED_AZUL, LOW);
      digitalWrite(LED_AMARELO, LOW);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, HIGH);
      break;
    case 4:
      digitalWrite(LED_AZUL, HIGH);
      digitalWrite(LED_AMARELO, HIGH);
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, HIGH);
      break;
    default:
      digitalWrite(LED_AZUL, LOW);
      digitalWrite(LED_AMARELO, LOW);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, LOW);
      break;
  }
}

// Retorna a cor do botao escolhido se dentro do limite de tempo, 0 se expirar
int esperaBotao(void) {
  // Cria um timer a partir do momento que a funcao e chamada
  long tempoInicial = millis();
  while ((millis() - tempoInicial) < tempoLimite) { 

    int botao = checaBotao();
    if (botao != 5) {
      toner(botao, tempoDuracaoCor);
      
      while (checaBotao() != 5);  // espera até que o jogador solte o botao
      delay(10);

      return botao;
    }
  }
  return 5;
}

// Retorna um bit '1' na posição correspondente a CHOICE_RED, CHOICE_GREEN, etc.
int checaBotao() {
  
  if      (digitalRead(BOTAO_AZUL) == 0)      n = 0;
  else if (digitalRead(BOTAO_AMARELO) == 0)   n = 1;
  else if (digitalRead(BOTAO_VERDE) == 0)     n = 2;
  else if (digitalRead(BOTAO_VERMELHO) == 0)  n = 3;
  else										  n = 5;
  
  return n;
}


void toner(byte opcao, int atraso) {
  
  acendeLEDS(opcao);  // Ligue um dado LED

  // Reproduz o som associado ao LED fornecido
  switch (opcao) {

    case 0:
      delay(atraso);
      // buzz_sound(buzz_length_ms, 1136);
      break;

    case 1:
      delay(atraso);
   	  // buzz_sound(buzz_length_ms, 568);
      break;

    case 2:
      delay(atraso);
      // buzz_sound(buzz_length_ms, 851);
      break;

    case 3:
      delay(atraso);
      // buzz_sound(buzz_length_ms, 638);
      break;
  }
  acendeLEDS(5);  // Desligue todos os LEDs
}

// Mostra uma tela de "modo de atração" enquanto aguarda o usuário pressionar o botão.
void attractMode(void) {

  while (1) {
    acendeLEDS(0);
    delay(100);
    if (checaBotao() != 5) return;

    acendeLEDS(1);
    delay(100);
    if (checaBotao() != 5) return;

    acendeLEDS(2);
    delay(100);
    if (checaBotao() != 5) return;

    acendeLEDS(3);
    delay(100);
    if (checaBotao() != 5) return;
  }
}