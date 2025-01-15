// Lista dinamica duplamente encadeada
#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
  int valor;
  struct elemento *proximo;
  struct elemento *anterior;
} Elemento;

typedef struct lista {
  Elemento *inicio;
  Elemento *fim;
  int tamanho;
} Lista;

Elemento *criarElemento(int valor) {
  Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
  novo->valor = valor;
  novo->proximo = NULL;
  novo->anterior = NULL;
  return novo;
}

Lista *criarLista() {
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
  return lista;
}

int estahVazia(Lista *lista) { return (lista->tamanho == 0); }

void inserirFinal(Lista *lista, int valor) {
  Elemento *novo = criarElemento(valor);
  if (estahVazia(lista)) {
    lista->inicio = novo;
    lista->fim = novo;

  } else {
    novo->anterior = lista->fim;
    lista->fim->proximo = novo;
    lista->fim = novo;
  }
  lista->tamanho++;
}

void inserirInicio(Lista *lista, int valor) {
  Elemento *novo = criarElemento(valor);
  if (estahVazia(lista)) {
    lista->inicio = novo;
    lista->fim = novo;
  } else {
    novo->proximo = lista->inicio;
    lista->inicio->anterior = novo;
    lista->inicio = novo;
  }
  lista->tamanho++;
}

void inserirPosicao(Lista *lista, int valor, int posicao) {
  if (posicao < 0 || posicao > lista->tamanho) {
    printf("Posicao invalida!\n");
    return;
  }
  if (posicao == 0) {
    inserirInicio(lista, valor);
  } else if (posicao == lista->tamanho) {
    inserirFinal(lista, valor);
  } else {
    Elemento *novo = criarElemento(valor);
    Elemento *aux = lista->inicio;
    for (int i = 0; i < posicao - 1; i++) {
      aux = aux->proximo;
    }
    novo->proximo = aux->proximo;
    novo->anterior = aux;
    aux->proximo->anterior = novo;
    aux->proximo = novo;
    lista->tamanho++;
  }
}

void removerFinal(Lista *lista, int *valor) {
  if (estahVazia(lista)) {
    printf("Lista vazia!\n");
    return;
  }
  Elemento *aux = lista->fim;
  *valor = aux->valor;
  if (lista->tamanho == 1) {
    lista->inicio = NULL;
    lista->fim = NULL;
  } else {
    lista->fim = aux->anterior;
    lista->fim->proximo = NULL;
  }
  free(aux);
  lista->tamanho--;
}

void removerInicio(Lista *lista, int *valor) {
  if (estahVazia(lista)) {
    printf("Lista vazia!\n");
    return;
  }
  Elemento *aux = lista->inicio;
  *valor = aux->valor;
  if (lista->tamanho == 1) {
    lista->inicio = NULL;
    lista->fim = NULL;
  } else {
    lista->inicio = aux->proximo;
    lista->inicio->anterior = NULL;
  }
  free(aux);
  lista->tamanho--;
}

void removerPosicao(Lista *lista, int *valor, int posicao) {
  if (estahVazia(lista)) {
    printf("Lista vazia!\n");
    return;
  }
  if (posicao < 0 || posicao >= lista->tamanho) {
    printf("Posicao invalida!\n");
    return;
  }
  if (posicao == 0) {
    removerInicio(lista, valor);
  } else if (posicao == lista->tamanho - 1) {
    removerFinal(lista, valor);
  } else {
    Elemento *aux = lista->inicio;
    for (int i = 0; i < posicao; i++) {
      aux = aux->proximo;
      *valor = aux->valor;
      aux->anterior->proximo = aux->proximo;
      aux->proximo->anterior = aux->anterior;
    }
    free(aux);
    lista->tamanho--;
  }
}

void imprimirLista(Lista *lista) {
  Elemento *aux = lista->inicio;
  printf("Lista: [ ");
  while (aux != NULL) {
    printf("%d ", aux->valor);
    aux = aux->proximo;
  }
  printf("]\n");
}

void liberarLista(Lista *lista) {
  Elemento *aux = lista->inicio;
  while (aux != NULL) {
    Elemento *temp = aux;
    aux = aux->proximo;
    free(temp);
  }
  free(lista);
}

//exercicio 19
int existeElemento(Lista *lista, int valor) {
  Elemento *aux = lista->inicio;
  while (aux != NULL) {
    if (aux->valor == valor) {
      return 1;
    }
    aux = aux->proximo;
  }
  return 0;
}

int recuperarElemento(Lista *lista, int *valor, int posicao) {
  if (estahVazia(lista)) {
    printf("Lista vazia!\n");
    return 0;
  }
  if (posicao < 0 || posicao >= lista->tamanho) {
    printf("Posicao invalida!\n");
    return 0;
  }
  Elemento *aux = lista->inicio;
  for (int i = 0; i < posicao; i++) {
    aux = aux->proximo;
  }
  *valor = aux->valor;
  return 1;
}

int main() {
  Lista *lista = criarLista();
  int opcao, valor, posicao;

  while (1) {
    printf("\n----------------------------------------\n"
           "Escolha uma opção:\n"
           "1 - Inserir elemento no início da lista\n"
           "2 - Inserir elemento no final da lista\n"
           "3 - Inserir elemento em uma posição específica da lista\n"
           "4 - Remover elemento do início da lista\n"
           "5 - Remover elemento do final da lista\n"
           "6 - Remover elemento de uma posição específica da lista\n"
           "7 - Recuperar elemento de uma posição específica da lista\n"
           "8 - Imprimir lista\n"
           "9 - Verificar se um elemento existe na lista\n"
           "0 - Sair\n"
           "Opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Digite o valor a ser inserido: ");
      scanf("%d", &valor);
      inserirInicio(lista, valor);
      break;

    case 2:
      printf("Digite o valor a ser inserido: ");
      scanf("%d", &valor);
      inserirFinal(lista, valor);
      break;

    case 3:
      printf("Digite o valor a ser inserido: ");
      scanf("%d", &valor);
      printf("Digite a posição a ser inserida: ");
      scanf("%d", &posicao);
      inserirPosicao(lista, valor, posicao - 1);
      break;

    case 4:
      removerInicio(lista, &valor);
      printf("Elemento %d removido do início da lista.\n", valor);
      break;

    case 5:
      removerFinal(lista, &valor);
      printf("Elemento %d removido do final da lista.\n", valor);
      break;

    case 6:
      printf("Digite a posição a ser removida: ");
      scanf("%d", &posicao);
      removerPosicao(lista, &valor, posicao - 1);
      printf("Elemento %d da posição %d removido da lista.\n", valor, posicao);
      break;

    case 7:
      printf("Digite a posição a ser recuperada: ");
      scanf("%d", &posicao);
      recuperarElemento(lista, &valor, posicao - 1);
      printf("O valor na posição %d é %d\n", posicao, valor);
      break;

    case 8:
      imprimirLista(lista);
      break;

    case 9:
      printf("Digite o valor a ser buscado: ");
      scanf("%d", &valor);
      if (existeElemento(lista, valor)) {
        printf("O valor %d existe na lista.\n", valor);
      } else {
        printf("O valor %d não existe na lista.\n", valor);
      }
      break;

    case 0:
      liberarLista(lista);
      printf("Lista liberada com sucesso.\n");
      return 0;
    }
  }
  return 0;
}