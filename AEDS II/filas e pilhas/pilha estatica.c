#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
  int vetor[MAX];
  int topo;
} Pilha;

Pilha *criaPilha();
void liberaPilha(Pilha *p);
int estahVazia(Pilha *p);
int estahCheia(Pilha *p);
int empilha(Pilha *p, int x);
int desempilha(Pilha *p, int *x);
int mostraTopo(Pilha *p);

int main(void) {
  Pilha *p = NULL;
  int s, x;

  while (1) {
    printf("\n1)Cria pilha\n"
           "2)Adiciona elemento a pilha\n"
           "3)Remove elemento da pilha\n"
           "4)Exibe pilha\n"
           "5)Apaga pilha\n"
           "6)Mostra topo da pilha\n"
           "0)Sair\n");
    scanf("%d", &s);

    switch (s) {
    case 1:
      if (p != NULL) {
        printf("Pilha já foi criada!\n");
      } else {
        p = criaPilha();
        printf("Pilha criada!\n");
      }
      break;

    case 2:
      if (p == NULL) {
        printf("ERRO. Pilha não foi criada\n");
      } else {
        printf("Insira elemento: ");
        scanf("%d", &x);
        if (empilha(p, x)) {
          printf("Elemento adicionado\n");
        } else {
          printf("ERRO. Pilha cheia\n");
        }
      }
      break;

    case 3:
      if (desempilha(p, &x)) {
        printf("Elemento %d removido da pilha\n", x);
      } else {
        printf("ERRO. Pilha Vazia\n");
      }
      break;

    case 4:
      if (p == NULL) {
        printf("ERRO. Pilha não foi criada\n");
      } else {
        printf("Pilha:\n[ ");
        for (int i = 0; i < p->topo; i++) {
          printf("%d ", p->vetor[i]);
        }
        printf("]\n");
      }
      break;

    case 5:
      if (p == NULL) {
        printf("ERRO. Pilha não foi criada\n");
      } else {
        liberaPilha(p);
        p = NULL;
        printf("Pilha apagada\n");
      }
      break;

    case 6:
      if (p == NULL) {
        printf("ERRO. Pilha não foi criada\n");
      } else {
        printf("Topo: %d\n", mostraTopo(p));
      }
      break;

    case 0:
      printf("TCHAU!\n");
      return 0;
    }
  }
}

Pilha *criaPilha() {
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  p->topo = 0;
  return p;
}

int estahVazia(Pilha *p) {
  if (p->topo == 0) {
    return 1;
  } else {
    return 0;
  }
}

int estahCheia(Pilha *p) {
  if (p->topo == MAX) {
    return 1;
  } else {
    return 0;
  }
}

int empilha(Pilha *p, int x) {
  if (!estahCheia(p)) {
    p->vetor[p->topo] = x;
    p->topo++;
    return 1;
  } else {
    return 0;
  }
}

int desempilha(Pilha *p, int *x) {
  if (!estahVazia(p)) {
    p->topo--;
    *x = p->vetor[p->topo];
    return 1;
  } else {
    return 0;
  }
}

void liberaPilha(Pilha *p) { free(p); }

int mostraTopo(Pilha *p) { return p->vetor[p->topo-1]; }