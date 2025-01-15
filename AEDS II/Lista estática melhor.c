#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
  int vetor[MAX];
  int fim;
} Lista;

Lista *criaLista() {
  Lista *p = (Lista *)malloc(sizeof(Lista));
  p->fim = 0;
  return p;
}

void liberaLista(Lista *p) { free(p); }
int mostraPosicao(Lista *p, int k) { return p->vetor[k]; }
int estahVazia(Lista *p) { return (p->fim == 0); }
int estahCheia(Lista *p) { return (p->fim == MAX); }
void movePesqueda(Lista *p, int i) { p->vetor[i] = p->vetor[i - 1]; }
void movePdireita(Lista *p, int i) { p->vetor[i] = p->vetor[i + 1]; }

int enListaNaPosicao(Lista *p, int x, int k) {
  if (!estahCheia(p)) {
    p->fim++;
    for (int i = p->fim; i > k; i--) {
      movePesqueda(p, i);
    }
    p->vetor[k] = x;
    return 1;
  }
  return 0;
}
int deListaDaPosicao(Lista *p, int *x, int k) {
  if (!estahVazia(p)) {
    *x = p->vetor[k];
    p->fim--;
    for (int i = k; i < p->fim; i++) {
      movePdireita(p, i);
    }
    return 1;
  }
  return 0;
}

int main(void) {
  Lista *p = NULL;
  int s, x, k;

  while (1) {
    printf("\n1)Cria lista\n"
           "2)Adiciona elemento a lista\n"
           "3)Remove elemento da lista\n"
           "4)Exibe lista\n"
           "5)Apaga lista\n"
           "6)Mostrar elemento da lista\n"
           "7)Tamanho da lista\n"
           "0)Sair\n");
    scanf("%d", &s);

    switch (s) {
    case 1:
      if (p != NULL) {
        printf("Lista já foi criada!\n");
      } else {
        p = criaLista();
        printf("Lista criada!\n");
      }
      break;

    case 2:
      printf("\n1)Adicina no inicio\n"
             "2)Adiciona no final\n"
             "3)Escolher posição\n");
      scanf("%d", &s);
      switch (s) {
      case 1:
        printf("Digite o valor a ser adicionado: ");
        scanf("%d", &x);
        if (enListaNaPosicao(p, x, 0)) {
          printf("Elemento adicionado com sucesso!\n");
        } else {
          printf("Erro, lista cheia\n");
        }
        break;

      case 2:
        printf("Digite o valor a ser adicionado: ");
        scanf("%d", &x);
        if (enListaNaPosicao(p, x, p->fim-1)) {
          printf("Elemento adicionado com sucesso!\n");
        } else {
          printf("Erro, lista cheia\n");
        }
        break;

      case 3:
        printf("Digite o valor a ser adicionado: ");
        scanf("%d", &x);
        printf("Digite a posição: ");
        scanf("%d", &k);
        if (enListaNaPosicao(p, x, k-1)) {
          printf("Elemento adicionado com sucesso!\n");
        } else {
          printf("Erro, lista cheia\n");
        }
        break;
      }
      break;

    case 3:
      printf("1)Remover do inicio\n"
             "2)Remover do final\n"
             "3)Escolher posição\n");
      scanf("%d", &s);
      switch (s) {
      case 1:
        if (deListaDaPosicao(p, &x, 0)) {
          printf("Elemento %d removido com sucesso!\n", x);
        } else {
          printf("Erro, lista vazia\n");
        }
        break;

      case 2:
        if (deListaDaPosicao(p, &x, p->fim)) {
          printf("Elemento %d removido com sucesso!\n", x);
        } else {
          printf("Erro, lista vazia\n");
        }
        break;

      case 3:
        printf("Digite a posição: ");
        scanf("%d", &k);
        if (deListaDaPosicao(p, &x, k - 1)) {
          printf("Elemento %d removido com sucesso!\n", x);
        } else {
          printf("Erro, lista vazia\n");
        }
        break;
      }
      break;

    case 4:
      if (p == NULL) {
        printf("ERRO. Lista não foi criada\n");
      } else {
        printf("Lista:\n[ ");
        for (int i = 0; i < p->fim; i++) {
          printf("%d ", p->vetor[i]);
        }
        printf("]\n");
      }
      break;

    case 5:
      if (p == NULL) {
        printf("ERRO. Lista não foi criada\n");
      } else {
        liberaLista(p);
        p = NULL;
        printf("Lista apagada\n");
      }
      break;

    case 6:
      printf("1)Mostrar elemento do inicio\n"
             "2)Mostrar elemento do final\n"
             "3)Escolher posição\n");
      scanf("%d", &s);
      switch (s) {
      case 1:
        if (p == NULL) {
          printf("ERRO. Lista não foi criada\n");
        } else {
          printf("Elemento do inicio: %d\n", mostraPosicao(p, 0));
        }
        break;

      case 2:
        if (p == NULL) {
          printf("ERRO. Lista não foi criada\n");
        } else {
          printf("Elemento do final: %d\n", mostraPosicao(p, p->fim - 1));
        }
        break;

      case 3:
        if (p == NULL) {
          printf("ERRO. Lista não foi criada\n");
        } else {
          printf("Digite a posição: ");
          scanf("%d", &k);
          printf("Elemento da posição %d: %d\n", k, mostraPosicao(p, k - 1));
        }
        break;
      }
      break;

    case 7:
      if (p == NULL) {
        printf("ERRO. Lista não foi criada\n");
      } else {
        printf("Tamanho da Lista: %d\n", p->fim);
      }
      break;

    case 0:
      printf("TCHAU!\n");
      return 0;
    }
  }
}