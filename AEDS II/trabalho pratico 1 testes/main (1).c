#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 52
#define PRETO "\x1b[30m"
#define VERME "\x1b[31m"
#define RESET "\x1b[0m"

// carta
typedef struct carta {
  int numero;
  char naipe;
} Carta;

// pilha de cartas
typedef struct {
  Carta vetor[MAX];
  int topo;
} Pilha;

// jogador
typedef struct jogogador {
  char nome[50];
  Pilha roubo;
} Jogador;

//------------------------------------------------------------------
// funcoes de pilha
Pilha *criaPilha() {
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  if (p == NULL) {
    // Verifica se a alocação de memória foi bem-sucedida
    printf("Erro na alocação de memória.\n");
    return 0;
  }
  p->topo = 0;
  return p;
}
int estahVazia(Pilha *p) { return (p->topo == 0); }
int estahCheia(Pilha *p) { return (p->topo == MAX); }
int enPilha(Pilha *p, Carta x) {
  if (!estahCheia(p)) {
    p->vetor[p->topo] = x;
    p->topo++;
    return 1;
  } else {
    return 0;
  }
}
int dePilha(Pilha *p, Carta *x) {
  if (!estahVazia(p)) {
    p->topo--;
    *x = p->vetor[p->topo];
    return 1;
  } else {
    return 0;
  }
}
int dePilhaPosicao(Pilha *p, Carta *x, int pos) {
  if (!estahVazia(p)) {
    if (pos == p->topo) {
      p->topo--;
      *x = p->vetor[p->topo];
    } else {
      *x = p->vetor[pos];
      for (int i = pos; i < p->topo; i++) {
        p->vetor[i] = p->vetor[i + 1];
      }
      p->topo--;
    }
    return 1;
  } else {
    return 0;
  }
}
int encontraPosicao(Pilha *p, Carta x) {
  for (int i = 0; i < p->topo; i++) {
    if (p->vetor[i].numero == x.numero) {
      return i;
    }
  }
  return -1;
}
void liberaPilha(Pilha *p) { free(p); }
//---------------------------------------------------------------------
// funcoes de inicio
void inicializarCartas(Pilha *monte) {
  int k = 0;
  for (int i = 1; i <= 13; i++) {
    for (int j = 0; j < 4; j++) {
      monte->vetor[k].numero = i;
      if (j == 0) {
        monte->vetor[k].naipe = 'C'; // Copas
      } else if (j == 1) {
        monte->vetor[k].naipe = 'O'; // Ouros
      } else if (j == 2) {
        monte->vetor[k].naipe = 'P'; // Paus
      } else {
        monte->vetor[k].naipe = 'E'; // Espadas
      }
      k++;
    }
  }
  monte->topo = k;
}
// embaralha as cartas aleatoriamente
void embaralharCartas(Pilha *monte) {
  srand(time(NULL));
  for (int i = monte->topo - 1; i >= 0; i--) {
    int j = rand() % (i + 1);
    Carta temp = monte->vetor[i];
    monte->vetor[i] = monte->vetor[j];
    monte->vetor[j] = temp;
  }
}
//------------------------------------------------------------------------
void imprimirCarta(Carta carta) {
  if (carta.numero == 1) {
    printf("[A-");
  } else if (carta.numero == 11) {
    printf("[J-");
  } else if (carta.numero == 12) {
    printf("[Q-");
  } else if (carta.numero == 13) {
    printf("[K-");
  } else {
    printf("[%d-", carta.numero);
  }
  if (carta.naipe == 'C' || carta.naipe == 'O') {
    printf(VERME "%c" RESET "] ", carta.naipe);
  } else {
    printf(PRETO "%c" RESET "] ", carta.naipe);
  }
}
void imprimirPilha(Pilha *monte) {
  for (int i = 0; i < monte->topo; i++) {
    imprimirCarta(monte->vetor[i]);
  }
  printf("\n");
}
//-------------------------------------------------------------------------
Jogador *criaJogador(int qtdJ) {
  Jogador *jogadores = (Jogador *)malloc(qtdJ * sizeof(Jogador));
  if (jogadores == NULL) {
    // Verifica se a alocação de memória foi bem-sucedida
    printf("Erro na alocação de memória.\n");
    return 0;
  }
  for (int i = 0; i < qtdJ; i++) {
    printf("Nome do jogador %d: ", i + 1);
    fgets(jogadores[i].nome, sizeof(jogadores[i].nome), stdin);
    jogadores[i].nome[strcspn(jogadores[i].nome, "\n")] = '\0';
    jogadores[i].roubo = *criaPilha();
  }
  return jogadores;
}
void liberaJogador(Jogador *jogador) { free(jogador); }
//-------------------------------------------------------------------------
// carta existe no descarte
int cartaExiste(Pilha *monte, Carta carta) {
  for (int i = 0; i < monte->topo; i++) {
    if (monte->vetor[i].numero == carta.numero) {
      return 1;
    }
  }
  return 0;
}
int podeRoubar(Carta carta, Pilha *monte) {
  if(carta.numero == monte->vetor[monte->topo-1].numero){
    return 1;
  }else{
    return 0;
  }
}

int main(void) {
  // cria objetos do jogo
  Pilha *compras = criaPilha();
  inicializarCartas(compras);
  embaralharCartas(compras);
  Pilha *descarte = criaPilha();
  Carta cartaDaVez;

  // escolher quantidade de jogadores
  int qtdJ = 0;
  while (1) {
    printf("Quantidade de jogadores: ");
    scanf("%d", &qtdJ);
    getchar();
    if (qtdJ > 1 && qtdJ <= 10) {
      break;
    } else {
      printf("Quantidade de jogadores invalida\n");
    }
  }

  // cria os jogadores
  Jogador *jogador = criaJogador(qtdJ);
  int indice = 0; //jogador da vez

  
  while (1) {// loop base do jogo, sai quando o monte de compras esta vazio
    
    while (1) {//loop do jogador, sai se colocar carta no descarte
      int perdeVez = 0;
      system("clear");
      printf("Monte de Compras: %d\n\n", compras->topo);
      printf("Descarte: \n");
      if (descarte->topo > 0) {
        imprimirPilha(descarte);
      }
      for (int i = 0; i < qtdJ; i++) {
        if (jogador[i].roubo.topo > 0) {
          imprimirCarta(jogador[i].roubo.vetor[jogador[i].roubo.topo - 1]);
          printf("%dpts %s", jogador[i].roubo.topo, jogador[i].nome);
          printf("\n");
        }
      }
      // jogador compra carta
      printf("\nVez de %s \n\n", jogador[indice].nome);
      if (dePilha(compras, &cartaDaVez)) {
        printf("Carta comprada: ");
        imprimirCarta(cartaDaVez);
      } else {
        printf("Monte de compras vazio, FIM DE JOGO\n");
        break;
      }
      // onde jogar carta
      int k = 2;
      printf("\n1 - Jogar no descarte\n");
      for (int i = 0; i < qtdJ; i++) {
        if (indice == i && jogador[i].roubo.topo > 0) {
          printf("%d - Colocar na sua pilha\n", k);
          k++;
        } else if (jogador[i].roubo.topo > 0) {
          printf("%d - Roubar de %s\n", k, jogador[i].nome);
          k++;
        }
      }
      
      // jogador joga carta-----------------------------------------------------------------
      while(1){// loop de jogada, sai se jogada for possivel 
        int escolha = 0;
        while (1) { // loop de escolha, sai se escolha for valida
          printf("Escolha uma opcao: ");
          scanf("%d", &escolha);
          getchar();
          if (escolha >= 1 && escolha <= k) {
            break;
          } else {
            printf("Opcao invalida\n");
          }
        }
        if (escolha == 1) { // escolhe jogar no descarte
          if (cartaExiste(descarte, cartaDaVez)) {
            enPilha(&jogador[indice].roubo, cartaDaVez);
            dePilhaPosicao(descarte, &cartaDaVez,encontraPosicao(descarte, cartaDaVez));
            enPilha(&jogador[indice].roubo, cartaDaVez);
          } else {
            enPilha(descarte, cartaDaVez); // perde a vez
            perdeVez = 1;
          }
          break;
        }else if(escolha >= 2){//pretende roubar de alguem
          int escolhaRoubo = escolha - 2;
          if(indice != escolhaRoubo && podeRoubar(cartaDaVez, &jogador[escolhaRoubo].roubo)){
            //roubar de outro
            for(int i = 0; i < jogador[escolhaRoubo].roubo.topo;i++){
              enPilha(&jogador[indice].roubo, jogador[escolhaRoubo].roubo.vetor[i]);
            }
            enPilha(&jogador[indice].roubo, cartaDaVez);
            jogador[escolhaRoubo].roubo.topo = 0;
            break;
          }else if(podeRoubar(cartaDaVez, &jogador[indice].roubo)){
            //roubar de si mesmo
            enPilha(&jogador[indice].roubo, cartaDaVez);
            break;
          }else{
            printf("Escolha inválida, tente novamente.\n");
          }
        }
      }

      if(perdeVez){
        break;
      }
    }// fim do while jogador compra carta
    if(compras->topo==0){
      break;
    }
    // proximo jogador
    indice++;
    indice %= qtdJ;
  }

  // jogador vencedor
  int maisPontos = 0;
  for (int i = 0; i < qtdJ; i++) {
    if (jogador[i].roubo.topo > maisPontos) {
      indice = i;
      maisPontos = jogador[i].roubo.topo;
    }
  }
  printf("Jogador %s venceu com %d pontos\n", jogador[indice].nome, maisPontos);

  // libera memorias usadas
  liberaPilha(compras);
  liberaPilha(descarte);
  liberaJogador(jogador);
  return 0;
}