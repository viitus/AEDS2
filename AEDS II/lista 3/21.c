#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemento {
  char nome[50];
  struct elemento *proximo;
} Elemento;

typedef struct lista {
  Elemento *topo;
  int tamanho;
} Lista;

Elemento *criarElemento(char nome[]) {
  Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
  strcpy(novo->nome, nome);
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

void inserirFinal(Lista *lista, char nome[]) {
  Elemento *novo = criarElemento(nome);
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

void inserirInicio(Lista *lista, char nome[]) {
  Elemento *novo = criarElemento(nome);
  if (estahVazia(lista)) {
    lista->topo = novo;
  } else {
    novo->proximo = lista->topo;
    lista->topo = novo;
  }
  lista->tamanho++;
}

void inserirPosicao(Lista *lista, char nome[], int posicao) {
  if (posicao < 0 || posicao > lista->tamanho) {
    printf("Posição inválida!\n");
    return;
  }
  if (posicao == 0) {
    inserirInicio(lista, nome);
    return;
  }
  Elemento *novo = criarElemento(nome);
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

void removerFinal(Lista *lista, char nome[]) {
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
  strcpy(nome, atual->nome);
  if (anterior == NULL) {
    lista->topo = NULL;
  } else {
    anterior->proximo = NULL;
  }
  free(atual);
  lista->tamanho--;
}

void removerInicio(Lista *lista, char nome[]) {
  if (estahVazia(lista)) {
    printf("Lista vazia!\n");
    return;
  }
  Elemento *atual = lista->topo;
  strcpy(nome, atual->nome);
  lista->topo = atual->proximo;
  free(atual);
  lista->tamanho--;
}

void removerPosicao(Lista *lista, char nome[], int posicao) {
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
  strcpy(nome, atual->nome);
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
  printf("\n------------------\nLista de filmes:\n");
  while (atual != NULL) {
    printf(" - %s\n", atual->nome);
    atual = atual->proximo;
  }
  printf("-------------------\n");
}

void liberarLista(Lista *lista) {
  Elemento *atual = lista->topo;
  while (atual != NULL) {
    Elemento *proximo = atual->proximo;
    free(atual->nome);
    free(atual);
    atual = proximo;
    lista->tamanho--;
  }
  free(lista);
}

int existeElemento(Lista *lista, char nome[]) {
  if (estahVazia(lista)) {
    return 0;
  }
  Elemento *atual = lista->topo;
  while (atual != NULL) {
    if (strcmp(atual->nome, nome) == 0) {
      return 1;
    }
    atual = atual->proximo;
  }
  return 0;
}

int recuperarElementoPorPosicao(Lista *lista, char nome[], int posicao) {
  if (posicao < 0 || posicao >= lista->tamanho) {
    printf("Posição inválida!\n");
    return 0;
  }
  Elemento *atual = lista->topo;
  for (int i = 0; i < posicao; i++) {
    atual = atual->proximo;
  }
  strcpy(nome, atual->nome);
  return 1;
}

int recuperarElementoPorNome(Lista *lista, char nome[]) {
  if (estahVazia(lista)) {
    printf("Lista vazia!\n");
    return 0;
  }
  Elemento *atual = lista->topo;
  int i = 0;
  while (atual != NULL) {
    if (strcmp(atual->nome, nome) == 0) {
      return i;
    }
    atual = atual->proximo;
    i++;
  }
  printf("Elemento não encontrado!\n");
  return 0;
}

void inverterLista(Lista *lista) {
  Elemento *anterior = NULL;
  Elemento *atual = lista->topo;
  Elemento *proximo = NULL;
  while (atual != NULL) {
    proximo = atual->proximo;
    atual->proximo = anterior;
    anterior = atual;
    atual = proximo;
  }
  lista->topo = anterior;
}

void insereNome(char *nome) {
  setbuf(stdin, NULL);
  fgets(nome, 50, stdin);
  nome[strcspn(nome, "\n")] = '\0';
}

int main() {
  Lista *lista = criarLista();
  char nome[50];
  int opcao, posicao;
  while (1) {
    printf("\nEscolha uma opção:\n");
    printf("1 - Inserir um filme no final da lista\n"
           "2 - Inserir um filme em uma posição específica da lista\n"
           "3 - Remover um filme da lista\n"
           "4 - Remover um filme em uma posição específica da lista\n"
           "5 - Pesquisar se um filme consta na lista\n"
           "6 - Listar todos os filmes da lista\n"
           "7 - Inverter a ordem dos filmes presentes na lista\n"
           "8 - Encerrar o programa\n"
           "Opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:
      printf("Digite o nome do filme: ");
      insereNome(nome);
      inserirFinal(lista, nome);
      break;

    case 2:
      printf("Digite o nome do filme: ");
      insereNome(nome);
      printf("Digite a posição em que deseja inserir o filme: ");
      scanf("%d", &posicao);
      inserirPosicao(lista, nome, posicao - 1);
      break;

    case 3:
      printf("Digite o nome do filme que deseja remover: ");
      insereNome(nome);
      posicao = recuperarElementoPorNome(lista, nome);
      removerPosicao(lista, nome, posicao - 1);
      break;

    case 4:
      printf("Digite a posição do filme que deseja remover: ");
      scanf("%d", &posicao);
      removerPosicao(lista, nome, posicao - 1);
      break;

    case 5:
      printf("Digite o nome do filme que deseja pesquisar: ");
      insereNome(nome);
      if (existeElemento(lista, nome)) {
        printf("O filme %s está na lista.\n", nome);
      } else {
        printf("O filme %s não está na lista.\n", nome);
      }
      break;

    case 6:
      imprimirLista(lista);
      break;

    case 7:
      printf("Lista invertida!\n");
      inverterLista(lista);
      break;

    case 8:
      printf("Encerrando o programa...\n");
      return 0;

    default:
      printf("Opção inválida!\n");
      break;
    }
  }

  return 0;
}