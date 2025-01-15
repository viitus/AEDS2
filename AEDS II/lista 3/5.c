#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct produto {
  int codProd;       // código do produto
  char nomeProd[10]; // nome do produto
  float valor;       // valor do produto
  int qtdeEstoque;   // quantidade disponível em estoque
} Produto;

typedef struct elemento {
  Produto produto;
  struct elemento *proximo;
} Elemento;

typedef struct lista {
  Elemento *topo;
  int tamanho;
} Lista;

// funçoes de lista
Elemento *criarElemento(Produto p);
Lista *criarLista();
int estahVazia(Lista *lista);
void inserirFinal(Lista *lista, Produto p);
void inserirInicio(Lista *lista, Produto p);
void inserirPosicao(Lista *lista, Produto p, int posicao);
void removerFinal(Lista *lista, Produto *p);
void removerInicio(Lista *lista, Produto *p);
void removerPosicao(Lista *lista, Produto *p, int posicao);
void imprimirLista(Lista *lista);
void liberarLista(Lista *lista);
int existeElemento(Lista *lista, int codigo);
int recuperarElemento(Lista *lista, Produto *p, int posicao);

// exercicio 5
int menorPreco(Lista *lista, Produto *p);

int main() {
  Lista *lista = criarLista();
  
  Produto p1 = {1, "Arroz", 5.55, 5};
  Produto p2 = {2, "Feijao", 4.60, 8};
  Produto p3 = {3, "Macarrao", 3.00, 5};
  Produto p4 = {4, "Carne", 10.00, 5};
  Produto p5 = {5, "Cerveja", 4.50, 12};
  Produto p6 = {6, "Refri", 5.00, 1};
  Produto p7 = {7, "Agua", 2.20, 5};

  inserirFinal(lista, p1);
  inserirFinal(lista, p2);
  inserirFinal(lista, p3);
  inserirFinal(lista, p4);
  inserirFinal(lista, p5);
  inserirFinal(lista, p6);
  inserirFinal(lista, p7);
  
  //exercicio5
  Produto p;
  if(menorPreco(lista, &p)){
    printf("Menor preco: %s, R$%.2f\n", p.nomeProd, p.valor);
  }else{
    printf("Lista vazia!\n");
  }
  
  return 0;
}

// funçoes de lista
Elemento *criarElemento(Produto p) {
  Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
  novo->produto = p;
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

void inserirFinal(Lista *lista, Produto p) {
  Elemento *novo = criarElemento(p);
  if (estahVazia(lista)) {
    lista->topo = novo;
  } else {
    Elemento *atual = lista->topo;
    while (atual->proximo != NULL) {
      atual = atual->proximo;
    }
    atual->proximo = novo;
  }
  lista->tamanho++;
}

void inserirInicio(Lista *lista, Produto p) {
  Elemento *novo = criarElemento(p);
  if (estahVazia(lista)) {
    lista->topo = novo;
  } else {
    novo->proximo = lista->topo;
    lista->topo = novo;
  }
  lista->tamanho++;
}

void inserirPosicao(Lista *lista, Produto p, int posicao) {
  if (posicao < 0 || posicao > lista->tamanho) {
    printf("Posição inválida!\n");
    return;
  }
  Elemento *novo = criarElemento(p);
  Elemento *atual = lista->topo;
  Elemento *anterior = NULL;
  for (int i = 0; i < posicao; i++) {
    anterior = atual;
    atual = atual->proximo;
  }
  novo->proximo = atual;
  anterior->proximo = novo;
  lista->tamanho++;
}

void removerFinal(Lista *lista, Produto *p) {
  if (estahVazia(lista)) {
    printf("Lista vazia!\n");
    return;
  }
  Elemento *atual = lista->topo;
  Elemento *anterior = NULL;
  while (atual->proximo != NULL) {
    anterior = atual;
    atual = atual->proximo;
  }
  *p = atual->produto;
  if (anterior == NULL) {
    lista->topo = NULL;
  } else {
    anterior->proximo = NULL;
  }
  free(atual);
  lista->tamanho--;
}

void removerInicio(Lista *lista, Produto *p) {
  if (estahVazia(lista)) {
    printf("Lista vazia!\n");
    return;
  }
  Elemento *atual = lista->topo;
  *p = atual->produto;
  lista->topo = atual->proximo;
  free(atual);
  lista->tamanho--;
}

void removerPosicao(Lista *lista, Produto *p, int posicao) {
  if (posicao < 0 || posicao >= lista->tamanho) {
    printf("Posição inválida!\n");
    return;
  }
  Elemento *atual = lista->topo;
  Elemento *anterior = NULL;
  for (int i = 0; i < posicao; i++) {
    anterior = atual;
    atual = atual->proximo;
  }
  *p = atual->produto;
  if (anterior == NULL) {
    lista->topo = atual->proximo;
  } else {
    anterior->proximo = atual->proximo;
  }
  free(atual);
  lista->tamanho--;
}

void imprimirLista(Lista *lista) {
  Elemento *atual = lista->topo;
  printf("Lista:\n-------\n");
  while (atual != NULL) {
    printf("Codigo: %d\n", atual->produto.codProd);
    printf("Nome: %s\n", atual->produto.nomeProd);
    printf("Preco: R$%.2f\n", atual->produto.valor);
    printf("Quantidade: %d\n", atual->produto.qtdeEstoque);
    printf("--------\n");
    atual = atual->proximo;
  }
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

int existeElemento(Lista *lista, int codigo) {
  if (estahVazia(lista)) {
    return 0;
  }
  Elemento *atual = lista->topo;
  while (atual != NULL) {
    if (atual->produto.codProd == codigo) {
      return 1;
    }
    atual = atual->proximo;
  }
  return 0;
}

int recuperarElemento(Lista *lista, Produto *p, int posicao) {
  if (posicao < 0 || posicao >= lista->tamanho) {
    printf("Posição inválida!\n");
    return 0;
  }
  Elemento *atual = lista->topo;
  for (int i = 0; i < posicao; i++) {
    atual = atual->proximo;
  }
  *p = atual->produto;
  return 1;
}

int menorPreco(Lista *lista, Produto *p) {
  if (estahVazia(lista)) {
    return 0;
  }
  Elemento *atual = lista->topo;
  float menor = atual->produto.valor;
  while (atual != NULL) {
    if (atual->produto.valor < menor) {
      menor = atual->produto.valor;
      *p = atual->produto;
    }
    atual = atual->proximo;
  }
  return 1;
}