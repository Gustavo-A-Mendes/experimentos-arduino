// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Variáveis do Jogo
int rodadaMax = 10;
int rodadaAumentaVelocidade = 5; //
long tempoLimite = 3000;

#define MODE_MEMORY  0
#define MODE_BATTLE  1
// #define MODE_BEEGEES 2
int gameMode = MODE_MEMORY; //Por padrão, vamos jogar o jogo da memória


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Notas usadas
#define buzzerPIN 6
#define NOTE_A4  440
#define NOTE_D5  587
#define NOTE_G5  784
#define NOTE_A5  880

// Define sinais de entrada e saida dos LEDs
#define BOTAO_AZUL 8
#define BOTAO_AMARELO 9
#define BOTAO_VERDE 10
#define BOTAO_VERMELHO 11

#define LED_AZUL 2
#define LED_AMARELO 3
#define LED_VERDE 4
#define LED_VERMELHO 5

// Variáveis de estado do jogo
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

  // Verificação de modo
  gameMode = MODE_MEMORY; // Por padrão, vamos jogar o jogo da memória

  if (checaBotao() == 2) {

    gameMode = MODE_BATTLE; // Coloque o jogo no modo de batalha

    //Ligue o LED superior direito (verde)
    acendeLEDS(2);
    toner(2, tempoDuracaoCor);

    acendeLEDS(4); // Ligue os outros LEDs até você soltar o botão

    while(checaBotao() != 5) ; // Aguarde até que o usuário pare de pressionar o botão

    //Agora não faça nada. O modo de batalha esta ativado
  }
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
  
  if (gameMode == MODE_MEMORY) {
    // Recebe o resultado do jogo
    if (jogo_memoria() == true) {
      Serial.println("venceu!");
      venceu(); // Ganhou
    } 
    else {
      Serial.println("perdeu!");
      perdeu(); // Perdeu
    }
    delay(1000);
    recomecar = 1;
  }

  if (gameMode == MODE_BATTLE) {
    jogo_batalha();
    Serial.println("perdeu!");
    perdeu(); // Perdeu
  }

}


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// As seguintes funções estão relacionadas a lógica do jogo

// Bloco principal:
// Retorna 0 se o jogador perder ou 1 se o jogador ganhar
int jogo_memoria(void) {
  gerarSequencia();
  rodada = 0;

  rodadaCount = 0;
  while (rodada < rodadaMax) {
    if (rodadaCount == rodadaAumentaVelocidade) {
      tempoDuracaoCor -= 100;
      rodadaCount = 0;
    }
    
    mostrarSequencia();
	
    if (!jogador()) {
      return false;
    }
    delay(1000);

  }
  return true;
}

// Jogue o modo de batalha especial de 2 jogadores
// Um jogador começa pressionando um botão e entregando ao outro jogador
// Esse jogador repete o botão e adiciona um, depois passa de volta.
// Esta função retorna quando alguém perde
int jogo_batalha(void) {

  rodada = 0; // Redefinir o quadro do jogo de volta para um quadro

  while (1) { // Loop até alguém falhar
	
    if (!adversario()) {
      return false;
    }
    
    if (!jogador()) {
      return false;
    }

    delay(100); // Dê ao usuário 100ms extras para entregar o jogo ao outro jogador
  }

  return true; // Nós nunca devemos chegar aqui
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
    
    //acendeLEDS(cores[corAtual]);
    //delay(tempoDuracaoCor);
    //acendeLEDS(5);
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
  return true;
}

int adversario() {
  Serial.println("nova cor");
  int novaCor = esperaBotao(); // Aguarde até que o usuário insira o próximo passo
  cores[rodada] = novaCor; // Adicionar este novo botão ao array do jogo
  Serial.print("nova cor inserida - ");
  Serial.println(novaCor);
  if (novaCor == 5) return false;
  if (novaCor != cores[rodada]) return false;
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
int checaBotao(void) {
  
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
      tocaSom(NOTE_D5, atraso);
      // buzz_sound(buzz_length_ms, 1136);
      break;

    case 1:
      delay(atraso);
      tocaSom(NOTE_G5, atraso);
   	  // buzz_sound(buzz_length_ms, 568);
      break;

    case 2:
      delay(atraso);
      tocaSom(NOTE_A5, atraso);
      // buzz_sound(buzz_length_ms, 851);
      break;

    case 3:
      delay(atraso);
      tocaSom(NOTE_A4, atraso);
      // buzz_sound(buzz_length_ms, 638);
      break;
  }
  acendeLEDS(5);  // Desligue todos os LEDs
}

void tocaSom(int nota, int duracao) {
  tone(buzzerPIN, nota, duracao-50);
  delay(duracao);
  noTone(buzzerPIN);
}

void venceu(void) {
  musicaVitoria();
}

void musicaVitoria() {
  int c4 = 262, gS3 = 208, aS3 = 233;

  int notas = 10;
  // COMPASSO: 4/4
  float andamento = 150;
  // tempo do compasso(s) = 240 / andamento
  float tempo = (240 / andamento) * 1000;
  // notas na melodia:
  int melodia[10] = {
    c4, c4, c4, c4, gS3,/*|*/aS3, c4, 0, aS3, c4
  };

  // duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
  float duracaoNotas[10] = {
    8.0, 8.0, 8.0, 4.0, 4.0, /*|*/4.0, 8.0, 8.0,/*|*/8.0, 2.0
  };

  for (int nota = 0; nota < 10; nota++) {
    changeLED();
    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. tempo = 1000:
    // quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    float duracaoNota = tempo / (duracaoNotas[nota]);
    tone(buzzerPIN, melodia[nota]*2, duracaoNota - 50);
    
    // para distinguir as notas, reduziremos o tempo de nota tocado,
    // porem o tempo até o próxima nota se manterá.
    float pausaEntreNotas = duracaoNota;
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(buzzerPIN);
  }
}

void perdeu(void) {
  musicaDerrota();
}

void musicaDerrota(void) {
  int c5 = 523, d5 = 587, e5 = 659,  f7 = 2794, fS7 = 2960, g7 = 3136;

  int notas = 11;
  // COMPASSO: 4/4
  float andamento = 150;
  // tempo do compasso(s) = 240 / andamento
  float tempo = (240 / andamento) * 1000;
  // notas na melodia:
  int melodia[11] = {
    f7, fS7, g7, 0, e5, e5, 0, d5, d5, c5, 0
  };

  // duracoes das notas: 4 = quarto de tempo, 8 = oitavo de tempo, etc.:
  float duracaoNotas[11] = {
    16.0, 16.0, 8.0, 4.0, 4.0, 8.0, 4.0, 8.0, 4.0, 2.0, 2.0
  };

  for (int nota = 0; nota < 11; nota++) {
    changeLED();

    // para calcular a duracao da nota, utilizaremos um segundo
    // dividido pelo tipo da nota.
    // ex. tempo = 1000:
    // quarto de tempo = 1000 / 4, oitavo de tempo = 1000/8, etc.
    float duracaoNota = tempo / (duracaoNotas[nota]);
    tone(buzzerPIN, melodia[nota]*2, duracaoNota - 50);
    
    // para distinguir as notas, reduziremos o tempo de nota tocado,
    // porem o tempo até o próxima nota se manterá.
    float pausaEntreNotas = duracaoNota;
    delay(pausaEntreNotas);
    // parar a funcao tone:
    noTone(buzzerPIN);
  }
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

// Cada vez que esta função é chamada, a placa se move para o próximo LED
void changeLED(void) {
  static int LEDnumber = 0;
  acendeLEDS(0 + LEDnumber); // Mude o LED

  LEDnumber++; // Ir para o próximo LED
  if(LEDnumber > 3) LEDnumber = 0; // Enrole o balcão, se necessário
}