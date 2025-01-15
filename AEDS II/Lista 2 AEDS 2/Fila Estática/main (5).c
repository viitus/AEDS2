#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Pilha {
  int vetor[MAX];
  int topo;
} Pilha;

typedef struct Fila {
  int vetor[MAX];
  int inicio;
  int fim;
} Fila;

// Funçoes de Pilha
Pilha *createPilha() {
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  p->topo = -1;
  return p;
}

int isPVazia(Pilha *p) { return (p->topo == -1); }
int isPCheia(Pilha *p) { return (p->topo == MAX - 1); }

void enPilha(Pilha *p, int item) {
  if (isPCheia(p)) {
    printf("A pilha está cheia. Não é possível adicionar mais elementos.\n");
  } else {
    p->topo++;
    p->vetor[p->topo] = item;
    printf("Item %d adicionado à pilha.\n", item);
  }
}

int dePilha(Pilha *p) {
  int item;
  if (isPVazia(p)) {
    printf("A pilha está vazia. Não é possível remover elementos.\n");
    return -1;
  } else {
    item = p->vetor[p->topo];
    p->topo--;
    printf("Item %d removido da pilha.\n", item);
    return item;
  }
}
void liberaPilha(Pilha *p) { free(p); }

// Funçoes de Fila
Fila *createFila() {
  Fila *f = (Fila *)malloc(sizeof(Fila));
  f->inicio = -1;
  f->fim = -1;
  return f;
}

int isEmpty(Fila *f) { return (f->inicio == -1 && f->fim == -1); }
int isFull(Fila *f) { return (f->fim == MAX - 1); }

void enFila(Fila *f, int item) {
  if (isFull(f)) {
    printf("A fila está cheia. Não é possível adicionar mais elementos.\n");
  } else {
    if (isEmpty(f)) {
      f->inicio = 0;
    }
    f->fim++;
    f->vetor[f->fim] = item;
  }
}

int deFila(Fila *f) {
  int item;
  if (isEmpty(f)) {
    printf("A fila está vazia. Não é possível remover elementos.\n");
    return -1;
  } else {
    item = f->vetor[f->inicio];
    if (f->inicio >= f->fim) {
      f->inicio = -1;
      f->fim = -1;
    } else {
      f->inicio++;
    }
    return item;
  }
}
void liberaFila(Fila *f) { free(f); }

void inverteFila(Fila *f) {
  Pilha *p = createPilha();
  int inicio = f->inicio;
  int fim = f->fim;
  for (int i = inicio; i <= fim; i++) {
    enPilha(p, deFila(f));
  }
  int topo = p->topo;
  for (int i = 0; i <= topo; i++) {
    enFila(f, dePilha(p));
  }
  liberaPilha(p);
}

int main() {
  int s, x;
  Fila *f = createFila();

  while (1) {
    printf("\n1-Insere item na fila\n"
           "2-Remove item da fila\n"
           "3-Inverte fila\n"
           "4-Imprime fila\n"
           "O-Sai do programa\n");
    scanf("%d", &s);

    switch (s) {
    case 1:
      printf("Item: ");
      scanf("%d", &x);
      enFila(f, x);
      printf("Item %d adicionado à fila.\n", x);
      break;

    case 2:
      x = deFila(f);
      printf("Item %d removido da fila.\n", x);
      break;

    case 3:
      inverteFila(f);
      break;

    case 4:
      printf("\n[ ");
      for (int i = f->inicio; i <= f->fim; i++) {
        printf("%d ",f->vetor[i]);
      }
      printf("]\n\n");
      break;

    case 0:
      liberaFila(f);
      return 0;
    }
  }
}