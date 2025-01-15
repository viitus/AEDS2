#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
  int valor;
  struct elemento *proximo;
} Elemento;

typedef struct fila{
  Elemento* inicio;
  Elemento* fim;
}Fila;

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

Fila *criaFila() {
  Fila *f = (Fila *)malloc(sizeof(Fila));
  if (f == NULL) {
    exit(2);
  } else {
    f->inicio = NULL;
    f->fim = NULL;
    return f;
  }
}

int estahVazia(Fila *f) { return ((f->inicio == NULL)&&(f->fim == NULL)); }

void enFila(Fila *f, int valor) {
  Elemento* E = criaElemento(valor);
  if(estahVazia(f)){
    f->inicio = E;
    f->fim = E;
  }else{
    f->fim->proximo = E;
    f->fim = E;
  }
}

void deFila(Fila* f, int *valor){
  if(estahVazia(f)){
    exit(3);
  }
  Elemento * aux = f->inicio;
  *valor = aux->valor;
  f->inicio = aux->proximo;
  free(aux);
}

void liberaFila(Fila *p, int *valor) {
  while (!estahVazia(p)) {
    deFila(p, valor);
  }
  free(p);
}


int main() {
  Fila *p = criaFila();
  printf("Fila criada\n");
  int x, s;

  while (1) {
    printf("-------\n1)Adicina elemento\n"
           "2)Remove elemento\n"
           "3)Topo da fila\n"
           "4)Emprime fila\n"
           "0)Sair\n-------"
           "\nEscolha: ");
    scanf("%d", &s);

    switch (s) {
    case 1:
      scanf("%d", &x);
      enFila(p, x);
      printf("Elemento %d adicionado a fila\n", x);
      break;

    case 2:
      deFila(p, &x);
      printf("Elemento %d removido da fila\n", x);
      break;



      
    case 0:
      liberaFila(p,&x);
      printf("tchau!\n");
      return 0;
    }
  }
  return 0;
}