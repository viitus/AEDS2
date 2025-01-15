#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 52
#define PRETO "\x1b[30m"
#define VERMELHO "\x1b[31m"
#define RESET "\x1b[0m"

// carta
typedef struct carta
{
  int numero;
  char naipe;
} Carta;

// pilha de cartas
typedef struct
{
  Carta vetor[MAX];
  int topo;
} Pilha;

// jogador
typedef struct jogogador
{
  char nome[50];
  Pilha roubo;
} Jogador;

//------------------------------------------------------------------
// funcoes de pilha
Pilha *criaPilha()
{
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  if (p == NULL)
  {
    // Verifica se a alocação de memória foi bem-sucedida
    printf("Erro na alocação de memória.\n");
    return 0;
  }
  p->topo = 0;
  return p;
}
int estahVazia(Pilha *p) { return (p->topo == 0); }
int estahCheia(Pilha *p) { return (p->topo == MAX); }
int enPilha(Pilha *p, Carta x)
{
  if (!estahCheia(p))
  {
    p->vetor[p->topo] = x;
    p->topo++;
    return 1;
  }
  else
  {
    return 0;
  }
}
int dePilha(Pilha *p, Carta *x)
{
  if (!estahVazia(p))
  {
    p->topo--;
    *x = p->vetor[p->topo];
    return 1;
  }
  else
  {
    return 0;
  }
}
int dePilhaPosicao(Pilha *p, Carta *x, int pos)
{
  if (!estahVazia(p))
  {
    if (pos == p->topo)
    {
      p->topo--;
      *x = p->vetor[p->topo];
    }
    else
    {
      *x = p->vetor[pos];
      for (int i = pos; i < p->topo; i++)
      {
        p->vetor[i] = p->vetor[i + 1];
      }
    }
    return 1;
  }
  else
  {
    return 0;
  }
}
int encontraPosicao(Pilha *p, Carta x)
{
  for (int i = 0; i < p->topo; i++)
  {
    if (p->vetor[i].numero == x.numero)
    {
      return i;
    }
  }
  return -1;
}
void liberaPilha(Pilha *p) { free(p); }
//---------------------------------------------------------------------
// funcoes de inicio
void inicializarCartas(Pilha *monte)
{
  int k = 0;
  for (int i = 1; i <= 13; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      monte->vetor[k].numero = i;
      if (j == 0)
      {
        monte->vetor[k].naipe = 'C'; // Copas
      }
      else if (j == 1)
      {
        monte->vetor[k].naipe = 'O'; // Ouros
      }
      else if (j == 2)
      {
        monte->vetor[k].naipe = 'P'; // Paus
      }
      else
      {
        monte->vetor[k].naipe = 'E'; // Espadas
      }
      k++;
    }
  }
  monte->topo = k;
}
// embaralha as cartas aleatoriamente
void embaralharCartas(Pilha *monte)
{
  srand(time(NULL));
  for (int i = monte->topo - 1; i >= 0; i--)
  {
    int j = rand() % (i + 1);
    Carta temp = monte->vetor[i];
    monte->vetor[i] = monte->vetor[j];
    monte->vetor[j] = temp;
  }
}
//------------------------------------------------------------------------
void imprimirCarta(Carta carta)
{
  if (carta.numero == 1)
  {
    printf("[A-");
  }
  else if (carta.numero == 11)
  {
    printf("[J-");
  }
  else if (carta.numero == 12)
  {
    printf("[Q-");
  }
  else if (carta.numero == 13)
  {
    printf("[K-");
  }
  else
  {
    printf("[%d-", carta.numero);
  }
  if (carta.naipe == 'C' || carta.naipe == 'O')
  {
    printf(VERMELHO "%c" RESET "] ", carta.naipe);
  }
  else
  {
    printf(PRETO "%c" RESET "] ", carta.naipe);
  }
}
void imprimirPilha(Pilha *monte)
{
  for (int i = 0; i < monte->topo; i++)
  {
    imprimirCarta(monte->vetor[i]);
  }
  printf("\n");
}
//-------------------------------------------------------------------------
Jogador *criaJogador(int qtdJ)
{
  Jogador *jogadores = (Jogador *)malloc(qtdJ * sizeof(Jogador));
  if (jogadores == NULL)
  {
    // Verifica se a alocação de memória foi bem-sucedida
    printf("Erro na alocação de memória.\n");
    return 0;
  }
  for (int i = 0; i < qtdJ; i++)
  {
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
int cartaExiste(Pilha *monte, Carta carta)
{
  for (int i = 0; i < monte->topo; i++)
  {
    if (monte->vetor[i].numero == carta.numero)
    {
      return 1;
    }
  }
  return 0;
}

int main(void)
{
  Pilha *compras = criaPilha();
  inicializarCartas(compras);
  embaralharCartas(compras);
  Pilha *descarte = criaPilha();
  Carta cartaDaVez;

  // escolher quantidade de jogadores
  int qtdJ = 0;
  while (1)
  {
    printf("Quantidade de jogadores: ");
    scanf("%d", &qtdJ);
    getchar();
    if (qtdJ > 1 && qtdJ <= 10)
    {
      break;
    }
    else
    {
      printf("Quantidade de jogadores invalida\n");
    }
  }

  // cria os jogadores
  Jogador *jogador = criaJogador(qtdJ);
  int indice = 0;

  // loop do jogo
  while (1)
  {

    while (1)
    {
      system("clear");
      printf("Descarte: \n");
      if (descarte->topo > 0)
      {
        imprimirPilha(descarte);
      }
      for (int i = 0; i < qtdJ; i++)
      {
        if (jogador[i].roubo.topo > 0)
        {
          printf("%s: %dpontos", jogador[i].nome, jogador[i].roubo.topo);
          imprimirCarta(jogador[i].roubo.vetor[jogador[i].roubo.topo - 1]);
          printf("\n");
        }
      }
      // jogador compra carta
      printf("\nVez de %s \n\n", jogador[indice].nome);
      if (dePilha(compras, &cartaDaVez))
      {
        printf("Carta comprada: ");
        imprimirCarta(cartaDaVez);
      }
      else
      {
        printf("Monte de compras vazio, FIM DE JOGO\n");
        break;
      }
      // onde jogar carta
      int k = 2;
      printf("\n1 - Jogar no descarte\n");
      for (int i = 0; i < qtdJ; i++)
      {
        if (indice == i && jogador[i].roubo.topo > 0)
        {
          printf("%d - Colocar na sua pilha\n", k);
          k++;
        }
        else if (jogador[i].roubo.topo > 0)
        {
          printf("%d - Roubar de %s\n", k, jogador[i].nome);
          k++;
        }
      }
      // escolha
      int escolha = 0;
      while (1)
      {
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        getchar();
        if (escolha >= 1 && escolha <= k)
        {
          break;
        }
        else
        {
          printf("Opcao invalida\n");
        }
      }
      // jogador joga carta
      if (escolha == 1)
      { // escolhe jogar no descarte
        if (cartaExiste(descarte, cartaDaVez))
        {
          enPilha(&jogador[indice].roubo, cartaDaVez);
          dePilhaPosicao(descarte, &cartaDaVez,                         encontraPosicao(descarte, cartaDaVez));
          enPilha(&jogador[indice].roubo, cartaDaVez);
        }
        else
        {
          enPilha(descarte, cartaDaVez);
          break; // perde a vez
        }
      }
      else if (escolha == 2 && !cartaExiste(descarte, cartaDaVez))
      {
        // escolhe jogar na pilha do jogador
        enPilha(&jogador[indice].roubo, cartaDaVez);
      }
      else if (escolha > 2)
      {
        // escolhe roubar de outro jogador
        int jogadorRoubo = escolha - 2;
        // Verifica se o jogador escolhido tem cartas para serem roubadas
        if (jogador[jogadorRoubo].roubo.topo > 0)
        {
          // Transfere toda a pilha
          for (int i = 0; i < jogador[jogadorRoubo].roubo.topo; i++)
          {
            enPilha(&jogador[indice].roubo,                    jogador[jogadorRoubo].roubo.vetor[i]);
          }
          jogador[jogadorRoubo].roubo.topo =              0; // Zera a pilha do jogador que teve as cartas roubadas
          enPilha(&jogador[indice].roubo,                  cartaDaVez); // coloca a carta da vez no topo
        }
        else
        {
          printf("%s nao tem cartas para serem roubadas.\n",
                 jogador[jogadorRoubo].nome);
          break;
        }
      }
      else
      {
        break;
      }
    }
    // proximo jogador
    indice++;
    indice %= qtdJ;
  }

  // jogador vencedor
  int maisPontos = 0;
  for (int i = 0; i < qtdJ; i++)
  {
    if (jogador[i].roubo.topo > maisPontos)
    {
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