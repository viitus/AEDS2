#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Fila {
  int vetor[MAX];
  int inicio;
  int fim;
} Fila;

Fila *createFila() {
  Fila *f = (Fila *)malloc(sizeof(Fila));
  if (f == NULL) {
    printf("Erro na alocação de memória.\n");
    exit(1);
  }
  f->inicio = 0;
  f->fim = 0;
  return f;
}

int isEmpty(Fila *f) { return (f->inicio == f->fim); }
int isFull(Fila *f) { return (f->fim == MAX); }

void enFila(Fila *f, int item) {
  if (isFull(f)) {
    printf("A fila está cheia. Não é possível adicionar mais elementos.\n");
    exit(2);
  }
  f->vetor[f->fim] = item;
  f->fim++;
}

int deFila(Fila *f) {
  int item;
  if (isEmpty(f)) {
    printf("A fila está vazia. Não é possível remover elementos.\n");
    exit(3);
  }
  item = f->vetor[f->inicio];
  f->inicio++;
  return item;
}

void liberaFila(Fila *f) { free(f); }

void imprimeFila(Fila *f) {
  printf("\n[ ");
  for (int i = f->inicio; i < f->fim; i++) {
    printf("%d ", f->vetor[i]);
  }
  printf("]\n\n");
}

void enfilera(Fila *f1, Fila *f2, Fila *f3) {
  while (!isEmpty(f1) && !isEmpty(f2)) {
    if (f1->vetor[f1->inicio] < f2->vetor[f2->inicio]) {
      enFila(f3, deFila(f1));
    } else {
      enFila(f3, deFila(f2));
    }
  }
  while (!isEmpty(f1)) {
    enFila(f3, deFila(f1));
  }
  while (!isEmpty(f2)) {
    enFila(f3, deFila(f2));
  }
}

int main() {
  Fila *f1 = createFila();
  enFila(f1, 10);
  enFila(f1, 20);
  enFila(f1, 30);
  enFila(f1, 40);
  enFila(f1, 50);
  imprimeFila(f1);

  Fila *f2 = createFila();
  enFila(f2, 11);
  enFila(f2, 15);
  enFila(f2, 36);
  enFila(f2, 59);
  imprimeFila(f2);

  Fila *f3 = createFila();
  enfilera(f1, f2, f3);
  imprimeFila(f3);

  liberaFila(f1);
  liberaFila(f2);
  liberaFila(f3);

  return 0;
}
