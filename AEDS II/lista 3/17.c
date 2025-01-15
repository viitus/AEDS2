#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
  int valor;
  struct elemento *proximo;
} Elemento;

typedef struct lista {
  Elemento *topo;
  int tamanho;
} Lista;

Elemento *criarElemento(int valor) {
  Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
  novo->valor = valor;
  novo->proximo = NULL;
  return novo;
}

Lista *criarLista() {
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  lista->topo = NULL;
  lista->tamanho = 0;
  return lista;
}

int estahVazia(Lista *lista) { return (lista->topo == NULL); }

//exercicio 15
void inserirCrescente(Lista *lista, int valor) {
  Elemento *novo = criarElemento(valor);
  if (estahVazia(lista) || lista->topo->valor > valor) {
    novo->proximo = lista->topo;
    lista->topo = novo;
    lista->tamanho++;
  } else {
    Elemento *atual = lista->topo;
    while (atual->proximo != NULL && atual->proximo->valor <= valor) {
      atual = atual->proximo;
    }
    novo->proximo = atual->proximo;
    atual->proximo = novo;
    lista->tamanho++;
  }
}
int removerElemento(Lista *lista, int valor) {
  Elemento *atual = lista->topo;
  Elemento *anterior = NULL;
  while (atual != NULL && atual->valor != valor) {
    anterior = atual;
    atual = atual->proximo;
  }
  if (atual != NULL) {
    if (anterior == NULL) {
      lista->topo = atual->proximo;
    } else {
      anterior->proximo = atual->proximo;
    }
    free(atual);
    lista->tamanho--;
    return 1;
  } else {
    return 0;
  }
}
void imprimirLista(Lista *lista) {
  Elemento *atual = lista->topo;
  printf("Lista: [ ");
  while (atual != NULL) {
    printf("%d ", atual->valor);
    atual = atual->proximo;
  }
  printf("]\n");
}
void liberarLista(Lista *lista) {
  Elemento *atual = lista->topo;
  while (atual != NULL) {
    Elemento *proximo = atual->proximo;
    free(atual);
    atual = proximo;
    lista->tamanho--;
  }
  free(lista);
}

int main(void) { 
  Lista* p = criarLista();
  inserirCrescente(p, 100);
  inserirCrescente(p, 56);
  inserirCrescente(p, 29);
  inserirCrescente(p, 75);
  inserirCrescente(p, 32);
  imprimirLista(p);
  printf("Digite o elemento que deseja remover: ");
  int x;
  scanf("%d",&x);
  if(removerElemento(p, x)){
    printf("Elemento removido\n");
  }else{
    printf("Elemento nao existe\n");
  }
  imprimirLista(p);
  

  return 0; 
}