// ROUBA MONTES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// structs
typedef struct carta { // cada carta possui um numero e um naipe
  int numero;
  char naipe;
} Carta;

typedef struct monte { // cada monte possui uma quantidade de cartas
  Carta cartas[52];
  int tamanho;
} Monte;

typedef struct jogador { // cada jogador possui:
  char nome[50];         // um nome
  Monte mao;             // uma mao de cartas
  Monte pontos;          // um monte para ser roubado
} Jogador;

// funcoes de carta
Monte *criarMonte() {
  Monte *monte = malloc(sizeof(Monte));
  monte->tamanho = 0;
  return monte;
}
// ♤ ♡ ♢ ♧
void inicializarCartas(Monte *monte) {
  int index = 0;
  for (int i = 1; i <= 13; i++) {
    for (int j = 0; j < 4; j++) {
      monte->cartas[index].numero = i;
      if (j == 0)  monte->cartas[index].naipe = '♡'; // Copas
      else if (j == 1)  monte->cartas[index].naipe = '♢'; // Ouros
      else if (j == 2)  monte->cartas[index].naipe = '♧'; // Paus
      else  monte->cartas[index].naipe = '♤'; // Espadas
      index++;
    }
  }
  monte->tamanho = 52;
}

void embaralharCartas(Monte *monte) { // embaralha as cartas aleatoriamente
  srand(time(NULL));
  for (int i = monte->tamanho - 1; i >= 0; i--) {
    int j = rand() % (i + 1);
    Carta temp = monte->cartas[i];
    monte->cartas[i] = monte->cartas[j];
    monte->cartas[j] = temp;
  }
}

void imprimirCarta(Carta carta) {
  if (carta.numero == 1)  printf("[A-%c] ", carta.naipe);
  else if (carta.numero == 11)  printf("[J-%c] ", carta.naipe);
  else if (carta.numero == 12)  printf("[Q-%c] ", carta.naipe);
  else if (carta.numero == 13)  printf("[K-%c] ", carta.naipe);
  else  printf("[%d-%c] ", carta.numero, carta.naipe);
}

void imprimirMonte(Monte *monte) {
  for (int i = 0; i < monte->tamanho; i++)  imprimirCarta(monte->cartas[i]);
  printf("\n");
}

// funcoes de jogador
int escolherQuantidadeJogadores() { // retorna quantos jogadores irao jogar
  int qtdJ;
  do {
    printf("Quantidade de jogadores: ");
    scanf("%d", &qtdJ);
  } while (qtdJ < 2 || qtdJ > 4);
  return qtdJ;
}
// cria os dados iniciais de cada jogador
void criarJogadores(Jogador jogadores[], int qtd) {
  for (int i = 0; i < qtd; i++) {
    printf("Nome do jogador %d: ", i + 1);
    setbuf(stdin, NULL);
    fgets(jogadores[i].nome, 50, stdin);
    jogadores[i].nome[strcspn(jogadores[i].nome, "\n")] = '\0';
    jogadores[i].mao = *criarMonte();
    jogadores[i].pontos = *criarMonte();
  }
}

void compraCarta(Monte *monte1, Monte *monte2) {
  monte1->cartas[monte1->tamanho] = monte2->cartas[monte2->tamanho - 1];
  monte1->tamanho++;
  monte2->tamanho--;
}

void jogadoresCompram(Jogador jogadores[], int qtd, Monte *compras) {
  if (compras->tamanho == 0) {
    printf("Monte de compras vazio.\n");
    return;
  }
  for (int i = 0; i < qtd; i++) {
    for (int j = 0; j < 4 && j < compras->tamanho; j++) {
      compraCarta(&jogadores[i].mao, compras);
    }
  }
}

void inicializarDescarte(Monte *descarte, Monte *compras) {
  for (int i = 0; i < 4; i++) {
    compraCarta(descarte, compras);
  }
}

int podeRoubar(Carta carta, Monte pontos) {
  if (carta.numero == pontos.cartas[pontos.tamanho - 1].numero) {
    return 1;
  } else {
    return 0;
  }
}

int buscarCarta(Carta carta, Monte *descarte) {
  for (int i = 0; i < descarte->tamanho; i++) {
    if (carta.numero == descarte->cartas[i].numero) return descarte->cartas[i].numero;
  }
  return 0;
}

void roubarDoDescarte(Carta carta, Jogador *jogador, Monte *descarte) {
  int indice = -1;
  // Procura a carta no descarte
  for (int i = 0; i < descarte->tamanho; i++) {
    if (carta.numero == descarte->cartas[i].numero) {
      indice = i;
      break;
    }
  }
  if (indice != -1) {
    // Move a carta da mão do jogador para o monte de pontos
    jogador->pontos.cartas[jogador->pontos.tamanho] = jogador->mao.cartas[indice];
    jogador->pontos.tamanho++;
    // Move a carta do descarte para o monte de pontos
    jogador->pontos.cartas[jogador->pontos.tamanho] = descarte->cartas[indice];
    jogador->pontos.tamanho++;
    // Remove a carta da mão do jogador
    for (int i = indice; i < jogador->mao.tamanho - 1; i++) {
      jogador->mao.cartas[i] = jogador->mao.cartas[i + 1];
    }
    jogador->mao.tamanho--;
    // Remove a carta do descarte
    for (int i = indice; i < descarte->tamanho - 1; i++) {
      descarte->cartas[i] = descarte->cartas[i + 1];
    }
    descarte->tamanho--;
  } else {
    // coloca a carta no monte de descarte
    return;
  }
}

void jogarNoDescarte(Carta carta, Jogador *jogador, Monte *descarte) {
  descarte->cartas[descarte->tamanho] = carta;
  descarte->tamanho++;
  for (int i = 0; i < jogador->mao.tamanho; i++) {
    if (carta.numero == jogador->mao.cartas[i].numero) {
      jogador->mao.cartas[i] = jogador->mao.cartas[jogador->mao.tamanho - 1];
    }
  }
  jogador->mao.tamanho--;
}

void roubarPontos(Carta carta, Jogador *jogador1, Jogador *jogador2) {
  // Transfere todas as cartas do monte de pontos do jogador2 para o jogador1
  for (int i = 0; i < jogador2->pontos.tamanho; i++) {
    jogador1->pontos.cartas[jogador1->pontos.tamanho] = jogador2->pontos.cartas[i];
    jogador1->pontos.tamanho++;
  }
  // Limpa o monte de pontos do jogador2
  jogador2->pontos.tamanho = 0;
}

int main() {
  // cria o monte de compras
  Monte *compras = criarMonte();
  inicializarCartas(compras);
  embaralharCartas(compras);
  Monte *descarte = criarMonte();
  inicializarDescarte(descarte, compras);
  
  // cria jogadores
  int qtdJ = escolherQuantidadeJogadores();
  Jogador jogadores[4];
  criarJogadores(jogadores, qtdJ);
  int i = 0;
  int opcao;
  int j;
  
  //loop do jogo
  while (1) {
    if (jogadores[i].mao.tamanho == 0) {
      printf("Distribuindo cartas...\n");
      jogadoresCompram(jogadores, qtdJ, compras);
    }
    // system("cls || clear");
    printf("------------------------------\n");
    printf("Pilha de Compras: %d\n", compras->tamanho);
    printf("Pilha de Descarte: \n");
    imprimirMonte(descarte);
    
    for (j = 0; j < qtdJ; j++) {
      if (jogadores[j].pontos.tamanho > 0) {
        printf("Pontos de %s: %d", jogadores[j].nome, jogadores[j].pontos.tamanho);
        imprimirCarta(jogadores[i].pontos.cartas[jogadores[j].pontos.tamanho]);
      }
    }

    // jogador escolhe qual carta jogar
    printf("\nVez de %s\n", jogadores[i].nome);
    printf("Escolha uma carta para jogar: \n");
    imprimirMonte(&jogadores[i].mao);

    while (1) {
      // verifica se a carta escolhida eh valida
      if (scanf("%d", &opcao) != 1 || opcao < 1 || opcao > jogadores[i].mao.tamanho) {
        printf("Carta invalida. Tente novamente.\n");
        getchar();
        continue;
      } else {
        opcao--;
        break; // so sai se escolher uma carta valida
      }
    }
    
    Carta cartaEscolhida = jogadores[i].mao.cartas[opcao];
    printf("Escolha onde jogar a carta: \n");
    printf("1 - Descarte\n");
    for (j = 0; j < qtdJ; j++) {
      if (jogadores[j].pontos.tamanho > 0) {
        printf("%d - Roubar %s\n", j + 2, jogadores[j].nome);
      }
    }
    int s;
    while (1) {
      scanf("%d", &s);
      if (s == 1) {
        // jogador joga na pilha de descarte
        if (buscarCarta(cartaEscolhida, descarte) != 0) {
          // roubar carta do descarte
          roubarDoDescarte(cartaEscolhida, &jogadores[i], descarte);
        } else {
          // colocar carta na descarte
          jogarNoDescarte(cartaEscolhida, &jogadores[i], descarte);
        }
        break; // sair do loop ao escolher a opção 1
      } else if (s >= 2 && s <= qtdJ + 1) {
        if (s - 2 == i) {
          // Jogador tentou roubar de si mesmo, colocar a carta no topo do monte de pontos
          jogadores[i].pontos.cartas[jogadores[i].pontos.tamanho] = cartaEscolhida;
          jogadores[i].pontos.tamanho++;
          // Remover a carta da mão do jogador
          for (int k = opcao; k < jogadores[i].mao.tamanho - 1; k++) {
            jogadores[i].mao.cartas[k] = jogadores[i].mao.cartas[k + 1];
          }
          jogadores[i].mao.tamanho--;
          break; // sair do loop ao escolher uma opção válida
        } else if (podeRoubar(cartaEscolhida, jogadores[s - 2].pontos)) {
          // Jogador rouba carta do monte de pontos
          roubarPontos(cartaEscolhida, &jogadores[i], &jogadores[s - 2]);
          break; // sair do loop ao escolher uma opção válida
        } else {
          printf("Não pode roubar %s. Tente novamente.\n", jogadores[s - 2].nome);
        }
      } else {
        printf("Opção inválida. Tente novamente.\n");
      }
      getchar(); // limpar o buffer do teclado
    }

    if (compras->tamanho == 0) {
      break;
    }
    i++;
    i %= qtdJ;
  }
  //sai do loop do jogo

  int maior = 0;
  int ganhador;
  for (int i = 0; i < qtdJ; i++) {
    if (jogadores[i].pontos.tamanho > maior) {
      maior = jogadores[i].pontos.tamanho;
      ganhador = i;
    }
  }
  printf("O ganhador é %s", jogadores[ganhador].nome);

  return 0;
}