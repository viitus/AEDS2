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

Elemento* criarElemento(int valor) {
  Elemento *novo = (Elemento*) malloc(sizeof(Elemento));
  novo->valor = valor;
  novo->proximo = NULL;
  return novo;
}

Lista* criarLista() {
  Lista *lista = (Lista*) malloc(sizeof(Lista));
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
  Elemento* novo = criarElemento(valor);
  Elemento* atual = lista->topo;
  Elemento* anterior = NULL;
  for(int i=0; i < posicao; i++) {
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
  for(int i=0; i < posicao; i++) {
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
  if(estahVazia(lista)) {
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
  for(int i=0; i < posicao; i++) {
    atual = atual->proximo;
  }
  *valor = atual->valor;
  return 1;
}

int main() {
  Lista *lista = criarLista();
  int opcao, valor, posicao;

  while(1){
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

    switch(opcao){
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
      inserirPosicao(lista, valor, posicao-1);
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
      removerPosicao(lista, &valor, posicao-1);
      printf("Elemento %d da posição %d removido da lista.\n", valor, posicao);
      break;

      case 7:
      printf("Digite a posição a ser recuperada: ");
      scanf("%d", &posicao);
      recuperarElemento(lista, &valor, posicao-1);
      printf("O valor na posição %d é %d\n", posicao, valor);
      break;

      case 8:
      imprimirLista(lista);
      break;

      case 9:
      printf("Digite o valor a ser buscado: ");
      scanf("%d", &valor);
      if(existeElemento(lista, valor)) {
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