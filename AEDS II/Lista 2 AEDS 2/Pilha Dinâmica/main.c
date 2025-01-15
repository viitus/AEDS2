#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct elemento {
  char valor;
  struct elemento *proximo;
} Elemento;

typedef struct pilha {
  Elemento *topo;
} Pilha;

Elemento *criaElemento(char valor) {
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

void enPilha(Pilha *p, char valor) {
  Elemento *E = criaElemento(valor);
  E->proximo = p->topo;
  p->topo = E;
}

void dePilha(Pilha *p, char *valor) {
  if (estahVazia(p)) {
    exit(3);
  } else {
    Elemento *aux = p->topo;
    *valor = aux->valor;
    p->topo = aux->proximo;
    free(aux);
  }
}

void liberaPilha(Pilha *p, char *valor) {
  while (!estahVazia(p)) {
    dePilha(p, valor);
  }
  free(p);
}

void invertePalavra(char *texto) {
  int tamanho = strlen(texto);
  Pilha *pilha = criaPilha();
  char c;
  for (int i = 0; i < tamanho; i++) {
    if (texto[i] != ' ' && texto[i] != '.') {
      enPilha(pilha, texto[i]);
    } else {
      while (!estahVazia(pilha)) {
        dePilha(pilha, &c);
        printf("%c", c);
      }
      if (texto[i] == ' ') {
        printf(" ");
      } else if (texto[i] == '.') {
        printf(".");
      }
    }
  }
}

int main() {
  char texto[MAX];

  printf("Digite um texto terminado por ponto:\n");
  setbuf(stdin, NULL);
  fgets(texto, MAX, stdin);

  printf("\nTexto invertido:\n");
  invertePalavra(texto);
  
  return 0;
}