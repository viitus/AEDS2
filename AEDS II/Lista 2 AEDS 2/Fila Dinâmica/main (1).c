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

typedef struct pilha {
  Elemento *topo;
} Pilha;

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

Pilha *criaPilha() {
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  if (p == NULL) {
    printf("Erro ao criar pilha.\n");
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
    printf("Erro: pilha vazia.\n");
    exit(3); 
  } else {
    Elemento *aux = p->topo;
    *valor = aux->valor;
    p->topo = aux->proximo;
    free(aux);
  }
}

void liberaPilha(Pilha *p) {
  int valor;
  while (!estahVazia(p)) {
    dePilha(p, &valor);
  }
  free(p);
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

void imprimeFila(Fila *p) {
  Elemento *aux = p->inicio;
  printf("\n[ ");
  while (aux != NULL) {
    printf("%d ", aux->valor);
    aux = aux->proximo;
  }
  printf("]\n");
}

int maiorElemento(Fila *f) {
  Elemento *aux = f->inicio;
  int maior = aux->valor;
  while (aux != NULL) {
    if (aux->valor > maior) {
      maior = aux->valor;
    }
    aux = aux->proximo;
  }
  return maior;
}

int menorElemento(Fila *f) {
  Elemento *aux = f->inicio;
  int menor = aux->valor;
  while (aux != NULL) {
    if (aux->valor < menor) {
      menor = aux->valor;
    }
    aux = aux->proximo;
  }
  return menor;
}

float mediaElemento(Fila *f) {
  int soma = 0;
  int qtd = 0;
  Elemento *aux = f->inicio;
  while (aux != NULL) {
    soma += aux->valor;
    qtd++;
    aux = aux->proximo;
  }
  return soma / qtd;
}

int main() {
  Fila *p = criaFila();
  printf("Fila criada\n");
  int x, s;

  while (1) {
    printf("-------\n1)Adicionar elemento\n"
           "2)Remover elemento\n"
           "4)Imprimir fila\n"
           "5)Maior elemento\n"
           "6)Menor elemento\n"
           "7)Media dos elementos na fila\n"
           "0)Sair\n-------"
           "\nEscolha: ");
    scanf("%d", &s);

    switch (s) {
    case 1:
      printf("Elemento: ");
      scanf("%d", &x);
      enFila(p, x);
      printf("Elemento %d adicionado à fila\n", x);
      break;

    case 2:
      if (!estahFVazia(p)) {
        deFila(p, &x);
        printf("Elemento %d removido da fila\n", x);
      } else {
        printf("A fila está vazia!\n");
      }
      break;

    case 4:
      imprimeFila(p);
      break;

    case 5:
      printf("Maior elemento: %d\n", maiorElemento(p));
      break;

    case 6:
      printf("Menor elemento: %d\n", menorElemento(p));
      break;

    case 7:
      printf("Media dos elementos: %f\n", mediaElemento(p));

    case 0:
      liberaFila(p);
      printf("Tchau!\n");
      return 0;
    }
  }
  return 0;
}