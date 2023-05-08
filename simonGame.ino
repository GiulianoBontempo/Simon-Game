// variáveis de estado
int listaDeLeds[30];
int tamanhoAtualDaLista = 0;
bool perdeu = false;
// pinos
int saidaAmarelo = 32;
int saidaVermelho = 33;
int saidaVerde = 25;
int saidaAzul = 26;
int inputAmarelo = 34;
int inputVermelho = 35;
int inputVerde = 27;
int inputAzul = 14;
int resetButton = 15;

void adicionaSequencia(int *lista, int &tamanho){
  // Sorteia um número randômico de 1 a 4
  int proximoNumero = random(1, 5);
  // Converte o número de 1 a 4 para os valores dos pinos
  switch (proximoNumero){
    case 1:
      lista[tamanho] = saidaAmarelo;
      break;
    case 2:
      lista[tamanho] = saidaVermelho;
      break;
    case 3:
      lista[tamanho] = saidaVerde;
      break;
    case 4:
      lista[tamanho] = saidaAzul;
      break;
  }
  // Adiciona 1 ao contador de quantidade de elementos na lista
  (tamanho)++;
}

void exibePadrao(){
  // Exibe a sequência
  for(int i = 0; i < tamanhoAtualDaLista; i++){
    if(listaDeLeds[i]){
      digitalWrite(listaDeLeds[i], HIGH);
      delay(750);
      digitalWrite(listaDeLeds[i], LOW);
      delay(250);
    }
  }
}

void verificaInput(){
  // Variável para guardar quantos inputs já foram enviados nessa rodada
  int numeroDeInputs = 0;
  while (numeroDeInputs < tamanhoAtualDaLista){
    // Os ifs a seguir começam com a lógica de chamar o game over caso o input seja incorreto, e a seguir lidam com o input correto, acendendo o Led
    if (digitalRead(inputAmarelo)){
      if (!(listaDeLeds[numeroDeInputs] == saidaAmarelo)){
        perdeu = true;
        break;
      }
      digitalWrite(saidaAmarelo, HIGH);
      delay(250);
      digitalWrite(saidaAmarelo, LOW);
      numeroDeInputs++;
    }
    if (digitalRead(inputVermelho)){
      if (!(listaDeLeds[numeroDeInputs] == saidaVermelho)){
        perdeu = true;
        break;
      }
      digitalWrite(saidaVermelho, HIGH);
      delay(250);
      digitalWrite(saidaVermelho, LOW);
      numeroDeInputs++;
    }
    if (digitalRead(inputVerde)){
      if (!(listaDeLeds[numeroDeInputs] == saidaVerde)){
        perdeu = true;
        break;
      }
      digitalWrite(saidaVerde, HIGH);
      delay(250);
      digitalWrite(saidaVerde, LOW);
      numeroDeInputs++;
    }
    if (digitalRead(inputAzul)){
      if (!(listaDeLeds[numeroDeInputs] == saidaAzul)){
        perdeu = true;
        break;
      }
      digitalWrite(saidaAzul, HIGH);
      delay(250);
      digitalWrite(saidaAzul, LOW);
      numeroDeInputs++;
    }
  }
  delay(1000);
}

// Caso o botão de reset seja pressionado, reinicia o contador de tamanho da lista de leds, apaga todos os leds e atualiza a variavel perdeu para verdadeira
void checkResetButton(){
  if (digitalRead(resetButton)){
    tamanhoAtualDaLista = 0;
    digitalWrite(saidaAmarelo, LOW);
    digitalWrite(saidaVermelho, LOW);
    digitalWrite(saidaVerde, LOW);
    digitalWrite(saidaAzul, LOW);
    delay(500);
    perdeu = false;
  }
}

void setup() {
  // Configura o serial:
  Serial.begin(9600);
  // Garante que o random seja de fato randômico
  randomSeed(analogRead(0));
  // Configura os pinos de saída
  pinMode(saidaAmarelo, OUTPUT);
  pinMode(saidaVermelho, OUTPUT);
  pinMode(saidaVerde, OUTPUT);
  pinMode(saidaAzul, OUTPUT);
  // Configura os pinos de input
  pinMode(inputAmarelo, INPUT);
  pinMode(inputVermelho, INPUT);
  pinMode(inputVerde, INPUT);
  pinMode(inputAzul, INPUT);
  pinMode(resetButton, INPUT);
}

void loop() {
  if(perdeu){
    // Acende todos os leds para indicar a derrota e fica checando se o resetButton foi apertado, para reiniciar
    digitalWrite(saidaAmarelo, HIGH);
    digitalWrite(saidaVermelho, HIGH);
    digitalWrite(saidaVerde, HIGH);
    digitalWrite(saidaAzul, HIGH);
    checkResetButton();
  } else{
    /*
  Lógica:
  Sorteia o próximo LED
  Exibe a sequência
  Verifica input do jogador
  */
    adicionaSequencia(listaDeLeds, tamanhoAtualDaLista);
    exibePadrao();
    verificaInput();
  }
}
