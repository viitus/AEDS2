#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Fila {
  int vetor[MAX];
  int inicio;
  int fim;
} Fila;

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
    exit(1);
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
    exit(2);
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

int maiorElemento(Fila *f) {
  int maior = f->vetor[f->inicio];
  for (int i = f->inicio; i <= f->fim; i++) {
    if (f->vetor[i] > maior) {
      maior = f->vetor[i];
    }
  }
  return maior;
}

int menorElemento(Fila *f) {
  int menor = f->vetor[f->inicio];
  for (int i = f->inicio; i <= f->fim; i++) {
    if (f->vetor[i] < menor) {
      menor = f->vetor[i];
    }
  }
  return menor;
}

float mediaElementos(Fila *f) {
  float soma = 0;
  for (int i = f->inicio; i <= f->fim; i++) {
    soma += f->vetor[i];
  }
  return soma / (f->fim - f->inicio + 1);
}

int main() {
  int s, x;
  Fila *f = createFila();

  while (1) {
    printf("\n1-Insere item na fila\n"
           "2-Remove item da fila\n"
           "3-Media dos elementos da fila\n"
           "4-Imprime fila\n"
           "5-Maior elemento\n"
           "6-Menor elemento\n"
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
      printf("Media dos Elementos: %.2f\n", mediaElementos(f));
      break;

    case 4:
      printf("\n[ ");
      for (int i = f->inicio; i <= f->fim; i++) {
        printf("%d ", f->vetor[i]);
      }
      printf("]\n\n");
      break;

    case 5:
      printf("Maior Elemento: %d\n", maiorElemento(f));
      break;

    case 6:
      printf("Menor Elemento: %d\n", menorElemento(f));
      break;

    case 0:
      liberaFila(f);
      printf("Tcahu!");
      return 0;
    }
  }
  return 0;
}