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

int tamanhoPilha(Pilha *p){
  int tam = 0;
  Elemento *aux = p->topo;
  while(aux != NULL){
    tam++;
    aux = aux->proximo;
  }
  return tam;
}

int main() {
  int x, s;
  
  Pilha *p1 = criaPilha();
  printf("Pilha criada\n");
  while (1) {
    printf("------- PILHA 1 -------\n"
           "1)Adicina elemento\n"
           "2)Remove elemento\n"
           "0)Sair\n-------"
           "\nEscolha: ");
    scanf("%d", &s);

    switch (s) {
    case 1:
      scanf("%d", &x);
      enPilha(p1, x);
      printf("Elemento %d adicionado a pilha\n", x);
      break;

    case 2:
      dePilha(p1, &x);
      printf("Elemento %d removido da pilha\n", x);
      break;

    case 0:
      printf("Saindo da Pilha 1.\n\n");
      break;
    }
    if (s == 0) {
      break;
    }
  }
  
  Pilha *p2 = criaPilha();
  printf("Pilha criada\n");
  while (1) {
    printf("------- PILHA 2 -------\n"
           "1)Adicina elemento\n"
           "2)Remove elemento\n"
           "0)Sair\n-------"
           "\nEscolha: ");
    scanf("%d", &s);

    switch (s) {
    case 1:
      scanf("%d", &x);
      enPilha(p2, x);
      printf("Elemento %d adicionado a pilha\n", x);
      break;

    case 2:
      dePilha(p2, &x);
      printf("Elemento %d removido da pilha\n", x);
      break;

    case 0:
      printf("Saindo da Pilha 2.\n\n");
      break;
    }
    if (s == 0) {
      break;
    }
  }
  
  if(tamanhoPilha(p1) > tamanhoPilha(p2)){
    printf("Pilha 1 tem maior tamanho\n");
  }else if(tamanhoPilha(p1) < tamanhoPilha(p2)){  
    printf("Pilha 2 tem maior tamanho\n");
  }else{
    printf("Pilhas tem o mesmo tamanho\n");
  }
  liberaPilha(p1, &x);
  liberaPilha(p2, &x);
  return 0;
}