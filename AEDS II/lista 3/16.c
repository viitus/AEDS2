#include <stdio.h>
#include <stdlib.h>

// Estrutura da Lista estática
#define MAX 100
typedef struct {
  int vetor[MAX];
  int fim;
} ListaEstatica;

// Estrutura da Lista simples
typedef struct elementoSimples {
  int valor;
  struct elementoSimples *proximo;
} ElementoSimples;

typedef struct listaSimples {
  ElementoSimples *topo;
  int tamanho;
} ListaSimples;

//  Estrutura da Lista dupla
typedef struct elementoDuplo {
  int valor;
  struct elementoDuplo *proximo;
  struct elementoDuplo *anterior;
} ElementoDuplo;

typedef struct listaDupla {
  ElementoDuplo *inicio;
  ElementoDuplo *fim;
  int tamanho;
} ListaDupla;

// inicialização das listas
ListaEstatica *inicializarListaEstatica() {
  ListaEstatica *lista = (ListaEstatica *)malloc(sizeof(ListaEstatica));
  lista->fim = -1;
  return lista;
}

ListaSimples *inicializarListaSimples() {
  ListaSimples *lista = (ListaSimples *)malloc(sizeof(ListaSimples));
  lista->topo = NULL;
  lista->tamanho = 0;
  return lista;
}

ListaDupla *inicializarListaDupla() {
  ListaDupla *lista = (ListaDupla *)malloc(sizeof(ListaDupla));
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
  return lista;
}

// craição dos elementos
ElementoSimples *criarElementoSimples(int valor) {
  ElementoSimples *novoElemento = (ElementoSimples *)malloc(sizeof(ElementoSimples));
  novoElemento->valor = valor;
  novoElemento->proximo = NULL;
  return novoElemento;
}

ElementoDuplo *criarElementoDuplo(int valor) {
  ElementoDuplo *novoElemento = (ElementoDuplo *)malloc(sizeof(ElementoDuplo));
  novoElemento->valor = valor;
  novoElemento->proximo = NULL;
  novoElemento->anterior = NULL;
  return novoElemento;
}

// inserir elementos
void inserirElementoEstatico(ListaEstatica *lista, int elemento) {
  if (lista->fim < MAX - 1) {
    lista->fim++;
    lista->vetor[lista->fim] = elemento;
  }
}
void inserirElementoSimples(ListaSimples *lista, int elemento) {
  ElementoSimples *novoElemento = criarElementoSimples(elemento);
  novoElemento->proximo = lista->topo;
  lista->topo = novoElemento;
  lista->tamanho++;
}
void inserirElementoDuplo(ListaDupla *lista, int elemento) {
  ElementoDuplo *novoElemento = criarElementoDuplo(elemento);
  if (lista->tamanho == 0) {
    lista->inicio = lista->fim = novoElemento;
  } else {
    novoElemento->proximo = lista->inicio;
    lista->inicio->anterior = novoElemento;
    lista->inicio = novoElemento;
  }
  lista->tamanho++;
}

// exercicio 16
ListaDupla *inserirOrdenado(ListaSimples *lista1, ListaEstatica *lista2) {
  ListaDupla *listaResultado = inicializarListaDupla();

  for (ElementoSimples *atualLista1 = lista1->topo; atualLista1 != NULL; atualLista1 = atualLista1->proximo) {
    inserirElementoDuplo(listaResultado, atualLista1->valor);
  }
  for (int i = 0; i <= lista2->fim; i++) {
    inserirElementoDuplo(listaResultado, lista2->vetor[i]);
  }

  ElementoDuplo *atual = listaResultado->inicio;
  ElementoDuplo *indice = NULL;
  int temp;

  while (atual != NULL) {
    indice = atual->proximo;
    while (indice != NULL) {
      if (atual->valor > indice->valor) {
        temp = atual->valor;
        atual->valor = indice->valor;
        indice->valor = temp;
      }
      indice = indice->proximo;
    }
    atual = atual->proximo;
  }

  return listaResultado;
}

int main() {
  ListaSimples *lista1 = inicializarListaSimples();
  ListaEstatica *lista2 = inicializarListaEstatica();

  inserirElementoSimples(lista1, 10);
  inserirElementoSimples(lista1, 255);
  inserirElementoSimples(lista1, 93);
  inserirElementoSimples(lista1, 44);

  inserirElementoEstatico(lista2, 11);
  inserirElementoEstatico(lista2, 26);
  inserirElementoEstatico(lista2, 39);
  inserirElementoEstatico(lista2, 45);
  inserirElementoEstatico(lista2, 58);

  ListaDupla *lista3 = inserirOrdenado(lista1, lista2);

  // imprimir lista 3
  ElementoDuplo *atual = lista3->inicio;
  while (atual != NULL) {
    printf("%d ", atual->valor);
    atual = atual->proximo;
  }

  return 0;
}