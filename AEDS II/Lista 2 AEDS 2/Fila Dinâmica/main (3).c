#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
  int valor;
  struct elemento *proximo;
} Elemento;

typedef struct fila {
  Elemento *inicio;
  Elemento *fim;
} Fila;

Elemento *criaElemento(int valor) {
  Elemento *E = (Elemento *)malloc(sizeof(Elemento));
  if (E == NULL) {
    printf("Erro ao criar elemento.\n");
    exit(1); 
  } else {
    E->valor = valor;
    E->proximo = NULL;
    return E;
  }
}

Fila *criaFila() {
  Fila *f = (Fila *)malloc(sizeof(Fila));
  if (f == NULL) {
    printf("Erro ao criar fila.\n");
    exit(4); 
  } else {
    f->inicio = NULL;
    f->fim = NULL;
    return f;
  }
}

int estahFVazia(Fila *f) { return ((f->inicio == NULL) && (f->fim == NULL)); }

void enFila(Fila *f, int valor) {
  Elemento *E = criaElemento(valor);
  if (estahFVazia(f)) {
    f->inicio = E;
    f->fim = E;
  } else {
    f->fim->proximo = E;
    f->fim = E;
  }
}

void deFila(Fila *f, int *valor) {
  if (estahFVazia(f)) {
    printf("Erro: fila vazia.\n");
    exit(3);
  } else {
    Elemento *aux = f->inicio;
    *valor = aux->valor;
    f->inicio = aux->proximo;
    if (f->inicio == NULL) {
      f->fim = NULL; 
    }
    free(aux);
  }
}

void liberaFila(Fila *f) {
  int valor;
  while (!estahFVazia(f)) {
    deFila(f, &valor);
  }
  free(f);
}
void enfilera(Fila *f1, Fila *f2, Fila *f3) {
  Elemento *aux1 = f1->inicio;
  Elemento *aux2 = f2->inicio;

  while (aux1 != NULL && aux2 != NULL) {
    if (aux1->valor < aux2->valor) {
      enFila(f3, aux1->valor);
      aux1 = aux1->proximo;
    } else {
      enFila(f3, aux2->valor);
      aux2 = aux2->proximo;
    }
  }
  while (aux1 != NULL) {
    enFila(f3, aux1->valor);
    aux1 = aux1->proximo;
  }
  while (aux2 != NULL) {
    enFila(f3, aux2->valor);
    aux2 = aux2->proximo;
  }
}


void imprimeFila(Fila *p) {
  Elemento *aux = p->inicio;
  printf("\n[ ");
  while (aux != NULL) {
    printf("%d ", aux->valor);
    aux = aux->proximo;
  }
  printf("]\n");
}

int main() {
  Fila *f1 = criaFila();
  enFila(f1, 10);
  enFila(f1, 20);
  enFila(f1, 30);
  enFila(f1, 40);
  enFila(f1, 50);
  imprimeFila(f1);
  Fila *f2 = criaFila();
  enFila(f2, 11);
  enFila(f2, 14);
  enFila(f2, 36);
  enFila(f2, 56);
  enFila(f2, 60);
  imprimeFila(f2);
  Fila *f3 = criaFila();
  enfilera(f1, f2, f3);
  imprimeFila(f3);
  liberaFila(f1);
  liberaFila(f2);
  liberaFila(f3);
  return 0;
}