#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
  int vetor[MAX];
  int topo;
} Pilha;

Pilha *criaPilha() {
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  p->topo = 0;
  return p;
}

int isVazia(Pilha *p) { return (p->topo == 0); }
int isCheia(Pilha *p) { return (p->topo == MAX); }

int enPilha(Pilha *p, int x) {
  if (!isCheia(p)) {
    p->vetor[p->topo] = x;
    p->topo++;
    return 1;
  } else {
    return 0;
  }
}

int dePilha(Pilha *p, int *x) {
  if (!isVazia(p)) {
    p->topo--;
    *x = p->vetor[p->topo];
    return 1;
  } else {
    return 0;
  }
}

void liberaPilha(Pilha *p) { free(p); }

int imparPilha(Pilha *p) {
  int impar = 0;
  for (int i = 0; i < p->topo; i++) {
    if (p->vetor[i] % 2 != 0) {
      impar++;
    }
  }
  return impar;
}

int main() {
  Pilha *p = criaPilha();
  printf("Pilha criada\n");
  int x, s;
 
  while (1) {
    printf("-------\n1)Adicina elemento\n"
           "2)Remove elemento\n"
           "3)Topo da pilha\n"
           "4)Conta impares\n"
           "0)Sair\n-------"
           "\nEscolha: ");
    scanf("%d", &s);
    
    switch (s) {
    case 1:
      scanf("%d", &x);
      if (enPilha(p, x)) {
        printf("Elemento %d adicionado a pilha\n", x);
      } else {
        printf("ERRO\n");
      }
      break;

    case 2:
      if (dePilha(p, &x)) {
        printf("Elemento %d removido da pilha\n", x);
      } else {
        printf("ERRO\n");
      }
      break;

    case 3:
      printf("Elemento do topo: %d\n", p->topo - 1);
      break;

    case 4:
      printf("Existem %d impares na pilha\n", imparPilha(p));
      break;

    case 0:
      liberaPilha(p);
      printf("tchau!\n");
      return 0;
    }
  }
}