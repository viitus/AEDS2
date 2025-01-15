#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
  int valor;
  struct elemento *proximo;
} Elemento;

typedef struct pilha {
  Elemento *topo;
} Pilha;

Elemento *criaElemento(int valor) {
  Elemento *E = (Elemento *)malloc(sizeof(Elemento));
  if (E == NULL) {
    exit(1);
  } else {
    E->valor = valor;
    E->proximo = NULL;
    return E;
  }
}

Pilha *criaPilha() {
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  if (p == NULL) {
    exit(2);
  } else {
    p->topo = NULL;
    return p;
  }
}

int estahVazia(Pilha *p) { return (p->topo == NULL); }

void enPilha(Pilha *p, int valor) {
  Elemento *E = criaElemento(valor);
  E->proximo = p->topo;
  p->topo = E;
}

void dePilha(Pilha *p, int *valor) {
  if (estahVazia(p)) {
    exit(3);
  } else {
    Elemento *aux = p->topo;
    *valor = aux->valor;
    p->topo = aux->proximo;
    free(aux);
  }
}

void liberaPilha(Pilha *p, int *valor) {
  while (!estahVazia(p)) {
    dePilha(p, valor);
  }
  free(p);
}

void imprimePilha(Pilha *p) {
  Elemento *aux = p->topo;
  printf("\n[ ");
  while (aux != NULL) {
    printf("%d ", aux->valor);
    aux = aux->proximo;
  }
  printf("]\n");
}

int contaImpar(Pilha *p) {
  Elemento *aux = p->topo;
  int cont = 0;
  while (aux != NULL) {
    if (aux->valor % 2 != 0) {
      cont++;
    }
    aux = aux->proximo; 
  }
  return cont;
}

int main() {
  Pilha *p = criaPilha();
  printf("Pilha criada\n");
  int x, s;

  while (1) {
    printf("-------\n1)Adicina elemento\n"
           "2)Remove elemento\n"
           "3)Topo da pilha\n"
           "4)Imprime pilha\n"
           "5)Conta impares\n"
           "0)Sair\n-------"
           "\nEscolha: ");
    scanf("%d", &s);

    switch (s) {
    case 1:
      scanf("%d", &x);
      enPilha(p, x);
      printf("Elemento %d adicionado a pilha\n", x);
      break;

    case 2:
      dePilha(p, &x);
      printf("Elemento %d removido da pilha\n", x);
      break;

    case 3:
      printf("Elemento do topo: %d\n", p->topo->valor);
      break;

    case 4:
      imprimePilha(p);
      break;

    case 5:
      printf("Impares: %d\n", contaImpar(p));
      break;

    case 0:
      liberaPilha(p, &x);
      printf("tchau!\n");
      return 0;
    }
  }
  return 0;
}