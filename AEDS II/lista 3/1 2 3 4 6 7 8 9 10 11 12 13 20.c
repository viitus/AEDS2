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

// funçoes de lista
Elemento *criarElemento(int valor);
Lista *criarLista();
int estahVazia(Lista *lista);
void inserirFinal(Lista *lista, int valor);
void inserirInicio(Lista *lista, int valor);
void inserirPosicao(Lista *lista, int valor, int posicao);
void removerFinal(Lista *lista, int *valor);
void removerInicio(Lista *lista, int *valor);
void removerPosicao(Lista *lista, int *valor, int posicao);
void imprimirLista(Lista *lista);
void liberarLista(Lista *lista);
int existeElemento(Lista *lista, int valor);
int recuperarElemento(Lista *lista, int *valor, int posicao);

// exercicio 1
Lista *concatenarListas(Lista *lista1, Lista *lista2);
// exercicio 2
int removerNprimeiros(Lista *lista, int n);
// exercicio 3
int maiorValor(Lista *lista, int *valor, int *posicao);
// exercicio 4
int trocarDePosicao(Lista *lista, int posicao1, int posicao2);
// exercicio 6
int qtdePares(Lista *lista);
// exercicio 7
Lista *listaDePares(Lista *lista);
// exercicio 8
int estahOrdenada(Lista *lista);
// exercicio 9
Lista *copiaLista(Lista *lista);
// exercicio 10
Lista *semRepetidos(Lista *lista);
// exercicio 11
Lista *inverteLista(Lista *lista);
// exercicio 12
Lista *encadeiaVetor(int *vetor, int tamanho);
// exercicio 13
void inverteOrdem(Lista *lista);
// exercicio 20
int tamanhoDaListaRecursivo(Elemento *atual);


int main() {
  // exercicio1
  printf("\nEXERCICIO 1 - concatenar\n");
  Lista *lista1 = criarLista();
  inserirInicio(lista1, 90);
  inserirInicio(lista1, 22);
  inserirInicio(lista1, 40);
  imprimirLista(lista1);
  Lista *lista2 = criarLista();
  inserirInicio(lista2, 40);
  inserirInicio(lista2, 55);
  inserirInicio(lista2, 55);
  inserirInicio(lista2, 66);
  inserirInicio(lista2, 77);
  imprimirLista(lista2);
  Lista *lista3 = concatenarListas(lista1, lista2);
  imprimirLista(lista3);

  // exercicio2
  printf("\nEXERCICIO 2 - remover n primeiros\n");
  int n;
  printf("Deseja remover quantos elementos? ");
  scanf("%d", &n);
  if (removerNprimeiros(lista3, n)) {
    imprimirLista(lista3);
  } else {
    printf("Operação não possivel\n");
  }

  // exercicio3
  printf("\nEXERCICIO 3 - encontra maior\n");
  int valor, posicao;
  if (maiorValor(lista3, &valor, &posicao)) {
    printf("Maior valor: %d\n", valor);
    printf("Posição: %d\n", posicao + 1);
  } else {
    printf("Lista vazia\n");
  }

  // exercicio4
  printf("\nEXERCICIO 4 - trocar de posicao\n");
  printf("Trocar de posição\n");
  int posicao1, posicao2;
  printf("Digite a posição 1: ");
  scanf("%d", &posicao1);
  printf("Digite a posição 2: ");
  scanf("%d", &posicao2);
  if (trocarDePosicao(lista3, posicao1 - 1, posicao2 - 1)) {
    imprimirLista(lista3);
  } else {
    printf("Posição inválida!\n");
  }

  // exercicio6
  printf("\nEXERCICIO 6 - qtd de pares\n");
  printf("Quantidade de pares na lista: %d\n", qtdePares(lista3));

  // exercicio7
  printf("\nEXERCICIO 7 - lista de pares\n");
  Lista *listaPar = listaDePares(lista3);
  imprimirLista(listaPar);

  // exercicio8
  printf("\nEXERCICIO 8 - ordenada?\n");
  if (estahOrdenada(lista3)) {
    printf("Lista estah ordenada\n");
  } else {
    printf("Lista não estah ordenada\n");
  }

  // exercicio9
  printf("\nEXERCICIO 9 - copia\n");
  Lista *listaCopia = copiaLista(lista3);
  imprimirLista(listaCopia);

  // exercicio10
  printf("\nEXERCICIO 10 - nao repete\n");
  Lista *listaSemRepetidos = semRepetidos(lista3);
  imprimirLista(listaSemRepetidos);

  // exercicio11
  printf("\nEXERCICIO 11 - inverte\n");
  Lista *listaInvertida = inverteLista(lista3);
  imprimirLista(listaInvertida);

  // exercicio12
  printf("\nEXERCICIO 12 - ancadeira vetor\n");
  int vetor[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Lista *listaVetor = encadeiaVetor(vetor, 10);
  imprimirLista(listaVetor);

  // exercicio13
  printf("\nEXERCICIO 13 - inverte ponteiros \n");
  inverteOrdem(listaVetor);
  imprimirLista(listaVetor);

  // exercicio20
  printf("\nEXERCICIO 20 - conta tamanho\n");
  int tam = tamanhoDaListaRecursivo(listaVetor->topo);
  printf("Tamanho da lista: %d\n", tam);

  
  liberarLista(lista1);
  liberarLista(lista2);
  liberarLista(lista3);
  liberarLista(listaPar);
  liberarLista(listaSemRepetidos);
  liberarLista(listaInvertida);
  liberarLista(listaVetor);
  return 0;
}

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

void inserirFinal(Lista *lista, int valor) {
  Elemento *novo = criarElemento(valor);
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

void inserirInicio(Lista *lista, int valor) {
  Elemento *novo = criarElemento(valor);
  if (estahVazia(lista)) {
    lista->topo = novo;
  } else {
    novo->proximo = lista->topo;
    lista->topo = novo;
  }
  lista->tamanho++;
}

void inserirPosicao(Lista *lista, int valor, int posicao) {
  if (posicao < 0 || posicao > lista->tamanho) {
    printf("Posição inválida!\n");
    return;
  }
  Elemento *novo = criarElemento(valor);
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

void removerFinal(Lista *lista, int *valor) {
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
  *valor = atual->valor;
  if (anterior == NULL) {
    lista->topo = NULL;
  } else {
    anterior->proximo = NULL;
  }
  free(atual);
  lista->tamanho--;
}

void removerInicio(Lista *lista, int *valor) {
  if (estahVazia(lista)) {
    printf("Lista vazia!\n");
    return;
  }
  Elemento *atual = lista->topo;
  *valor = atual->valor;
  lista->topo = atual->proximo;
  free(atual);
  lista->tamanho--;
}

void removerPosicao(Lista *lista, int *valor, int posicao) {
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
  *valor = atual->valor;
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

int existeElemento(Lista *lista, int valor) {
  if (estahVazia(lista)) {
    return 0;
  }
  Elemento *atual = lista->topo;
  while (atual != NULL) {
    if (atual->valor == valor) {
      return 1;
    }
    atual = atual->proximo;
  }
  return 0;
}

int recuperarElemento(Lista *lista, int *valor, int posicao) {
  if (posicao < 0 || posicao >= lista->tamanho) {
    printf("Posição inválida!\n");
    return 0;
  }
  Elemento *atual = lista->topo;
  for (int i = 0; i < posicao; i++) {
    atual = atual->proximo;
  }
  *valor = atual->valor;
  return 1;
}

Lista *concatenarListas(Lista *lista1, Lista *lista2) {
  if (lista1 == NULL) {
    return lista2;
  }
  if (lista2 == NULL) {
    return lista1;
  }
  Lista *lista3 = criarLista();
  Elemento *atual1 = lista1->topo;
  Elemento *atual2 = lista2->topo;
  while (!(atual1 == NULL && atual2 == NULL)) {
    if (atual1 != NULL) {
      inserirFinal(lista3, atual1->valor);
      atual1 = atual1->proximo;
    }
    if (atual2 != NULL) {
      inserirFinal(lista3, atual2->valor);
      atual2 = atual2->proximo;
    }
  }
  return lista3;
}

int removerNprimeiros(Lista *lista, int n) {
  if (n < 0 || n > lista->tamanho) {
    printf("Erro, número inválido!\n");
    return 0;
  }
  for (int i = 0; i < n; i++) {
    int valor;
    removerInicio(lista, &valor);
    printf("Removido: %d\n", valor);
  }
  return 1;
}

int maiorValor(Lista *lista, int *valor, int *posicao) {
  if (estahVazia(lista)) {
    return 0;
  }
  Elemento *atual = lista->topo;
  *valor = atual->valor;
  for (int i = 0; i < lista->tamanho; i++) {
    if (atual->valor > *valor) {
      *valor = atual->valor;
      *posicao = i;
    }
    atual = atual->proximo;
  }

  return 1;
}

int trocarDePosicao(Lista *lista, int posicao1, int posicao2) {
  if (posicao1 < 0 || posicao1 >= lista->tamanho || posicao2 < 0 ||
      posicao2 >= lista->tamanho) {
    return 0;
  }
  Elemento *atual1 = lista->topo;
  Elemento *atual2 = lista->topo;
  for (int i = 0; i < posicao1; i++) {
    atual1 = atual1->proximo;
  }
  for (int i = 0; i < posicao2; i++) {
    atual2 = atual2->proximo;
  }
  int aux = atual1->valor;
  atual1->valor = atual2->valor;
  atual2->valor = aux;
  return 1;
}

int qtdePares(Lista *lista) {
  if (estahVazia(lista)) {
    return -1;
  }
  Elemento *atual = lista->topo;
  int cont = 0;
  while (atual != NULL) {
    if (atual->valor % 2 == 0) {
      cont++;
    }
    atual = atual->proximo;
  }
  return cont;
}

Lista *listaDePares(Lista *lista) {
  if (estahVazia(lista)) {
    return NULL;
  }
  Lista *listaPares = criarLista();
  Elemento *atual = lista->topo;
  while (atual != NULL) {
    if (atual->valor % 2 == 0) {
      int valor;
      inserirFinal(listaPares, atual->valor);
    }
    atual = atual->proximo;
  }
  return listaPares;
}

int estahOrdenada(Lista *lista) {
  if (estahVazia(lista)) {
    return 0;
  }
  Elemento *atual = lista->topo;
  int contador1 = 0;
  int contador2 = 0;
  while (atual->proximo != NULL) {
    if (atual->valor > atual->proximo->valor) {
      contador1++;
    }
    if (atual->valor < atual->proximo->valor) {
      contador2++;
    }
    atual = atual->proximo;
  }
  if (contador1 == 0 || contador2 == 0) {
    return 1;
  }
  return 0;
}

Lista *copiaLista(Lista *l1) {
  if (estahVazia(l1)) {
    return NULL;
  }
  Lista *l2 = criarLista();
  Elemento *atual = l1->topo;
  int valor;
  for (int i = 0; i < l1->tamanho; i++) {
    recuperarElemento(l1, &valor, i);
    inserirFinal(l2, valor);
  }
  return l2;
}

Lista *semRepetidos(Lista *l1) {
  if (estahVazia(l1)) {
    return NULL;
  }
  Lista *l2 = criarLista();
  Elemento *atual = l1->topo;
  int valor;
  for (int i = 0; i < l1->tamanho; i++) {
    recuperarElemento(l1, &valor, i);
    if (existeElemento(l2, valor) == 0) {
      inserirFinal(l2, valor);
    }
    atual = atual->proximo;
  }
  return l2;
}

Lista *inverteLista(Lista *l1) {
  if (estahVazia(l1)) {
    return NULL;
  }
  Lista *l2 = criarLista();
  Elemento *atual = l1->topo;
  int valor;
  for (int i = 0; i < l1->tamanho; i++) {
    recuperarElemento(l1, &valor, i);
    if (i == 0) {
      l2->topo = criarElemento(valor);

    } else {
      Elemento *novo = criarElemento(valor);
      novo->proximo = l2->topo;
      l2->topo = novo;
    }
    atual = atual->proximo;
  }
  return l2;
}

Lista* encadeiaVetor(int *vetor, int tamanho){
  Lista *l = criarLista();
  for(int i = 0; i < tamanho; i++){
    inserirFinal(l, vetor[i]); 
  }
  return l;
}

void inverteOrdem(Lista *lista){
  Elemento *anterior = NULL;
  Elemento *atual = lista->topo;
  Elemento *proximo = NULL;
  while(atual != NULL){
    proximo = atual->proximo;
    atual->proximo = anterior;
    anterior = atual;
    atual = proximo;
  }
  lista->topo = anterior;
}

int tamanhoDaListaRecursivo(Elemento *atual) {
  if (atual == NULL) {
    return 0;
  } else {
    return 1 + tamanhoDaListaRecursivo(atual->proximo);
  }
}