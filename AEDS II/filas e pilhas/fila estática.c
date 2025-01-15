#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
  int vetor[MAX];
  int inicio;
  int fim;
} Fila;

Fila *criaFila();
void liberaFila(Fila *p);
int estahVazia(Fila *p);
int estahCheia(Fila *p);
int emfila(Fila *p, int x);
int desfila(Fila *p, int *x);
int mostraInicio(Fila *p);
int mostraFim(Fila *p);

int main(void) {
  Fila *p = NULL;
  int s, x;

  while (1) {
    printf("\n1)Cria fila\n"
           "2)Adiciona elemento a fila\n"
           "3)Remove elemento da fila\n"
           "4)Exibe fila\n"
           "5)Apaga fila\n"
           "6)Mostra inicio da fila\n"
           "7)Mostra fim da fila\n"
           "0)Sair\n");
    scanf("%d", &s);

    switch (s) {
    case 1:
      if (p != NULL) {
        printf("Fila já foi criada!\n");
      } else {
        p = criaFila();
        printf("Fila criada!\n");
      }
      break;

    case 2:
      if (p == NULL) {
        printf("ERRO. Fila não foi criada\n");
      } else {
        printf("Insira elemento: ");
        scanf("%d", &x);
        if (emfila(p, x)) {
          printf("Elemento adicionado\n");
        } else {
          printf("ERRO. Fila cheia\n");
        }
      }
      break;

    case 3:
      if (desfila(p, &x)) {
        printf("Elemento %d removido da fila\n", x);
      } else {
        printf("ERRO. Fila Vazia\n");
      }
      break;

    case 4:
      if (p == NULL) {
        printf("ERRO. Fila não foi criada\n");
      } else {
        printf("Fila:\n[ ");
        for (int i = p->inicio; i < p->fim; i++) {
          printf("%d ", p->vetor[i]);
        }
        printf("]\n");
      }
      break;

    case 5:
      if (p == NULL) {
        printf("ERRO. Fila não foi criada\n");
      } else {
        liberaFila(p);
        p = NULL;
        printf("Fila apagada\n");
      }
      break;

    case 6:
      if (p == NULL) {
        printf("ERRO. Fila não foi criada\n");
      } else {
        printf("Inicio: %d\n", mostraInicio(p));
      }
      break;

    case 7:
      if (p == NULL) {
        printf("ERRO. Fila não foi criada\n");
      } else {
        printf("Fim: %d\n", mostraFim(p));
      }
      break;

    case 0:
      printf("TCHAU!\n");
      return 0;
    }
  }
  return 0;
}

Fila *criaFila() {
  Fila *p = (Fila *)malloc(sizeof(Fila));
  p->inicio = 0;
  p->fim = 0;
  return p;
}

int estahVazia(Fila *p) {
  if (p->inicio == p->fim) {
    return 1;
  } else {
    return 0;
  }
}

int estahCheia(Fila *p) {
  if (p->fim == MAX) {
    return 1;
  } else {
    return 0;
  }
}

int emfila(Fila *p, int x) {
  if (!estahCheia(p)) {
    p->vetor[p->fim] = x;
    p->fim++;
    return 1;
  } else {
    return 0;
  }
}

int desfila(Fila *p, int *x) {
  if (!estahVazia(p)) {
    *x = p->vetor[p->inicio];
    p->inicio++;
    return 1;
  } else {
    return 0;
  }
}

void liberaFila(Fila *p) { free(p); }

int mostraInicio(Fila *p) { return p->vetor[p->inicio]; }

int mostraFim(Fila *p) { return p->vetor[p->fim-1]; }