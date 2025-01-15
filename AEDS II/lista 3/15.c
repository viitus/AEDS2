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
void inserirDecrescente(Lista *lista, int valor) {
  Elemento *novo = criarElemento(valor);
  if (estahVazia(lista) || lista->topo->valor < valor) {
    novo->proximo = lista->topo;
    lista->topo = novo;
    lista->tamanho++;
  } else {
    Elemento *atual = lista->topo;
    while (atual->proximo != NULL && atual->proximo->valor >= valor) {
      atual = atual->proximo;
    }
    novo->proximo = atual->proximo;
    atual->proximo = novo;
    lista->tamanho++;
  }
}

int removerPosicao(Lista *lista, int *valor, int posicao) {
  if (posicao < 0 || posicao >= lista->tamanho) {
    printf("Posição inválida!\n");
    return 0;
  }
  if(estahVazia(lista)){
    printf("Lista vazia!\n");
    return 0;
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
  return 1;
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

  while(1){
    printf("1-Insere\n2-Remove\n3-Imprime\n4-Sair\n");
    int s,x,k;
    scanf("%d", &s);
    switch(s){
      case 1:
      printf("Digite o valor a ser inserido: ");

      scanf("%d", &x);
      inserirDecrescente(p, x);
      break;

      case 2:
      printf("Digite a posição a ser removida: ");
      scanf("%d", &k);
        k--;
        if(removerPosicao(p, &x, k)){
          printf("Elemento removido: %d\n", x);
        }else{
          printf("Posição inválida\n");
        }
      break;

      case 3:
      printf("Imprimindo lista...\n");
      imprimirLista(p);
      break;

      case 4:
      printf("Saindo...\n");
      liberarLista(p);
      exit(0);
    }
  }

  return 0; 
}