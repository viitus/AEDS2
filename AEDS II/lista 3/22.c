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

int somaElementos(Lista *lista) {
  if (estahVazia(lista)) {
    return 0;
  }
  Elemento *atual = lista->topo;
  int soma = 0;
  while (atual != NULL) {
    soma += atual->valor;
    atual = atual->proximo;
  }
  return soma;
}

int maiorElemento(Lista *lista) {
  if (estahVazia(lista)) {
    printf("Lista vazia!\n");
    return 0;
  }
  Elemento *atual = lista->topo;
  int maior = atual->valor;
  while (atual != NULL) {
    if (atual->valor > maior) {
      maior = atual->valor;
    }
    atual = atual->proximo;
  }
  return maior;
}

int menorElemento(Lista *lista) {
  if (estahVazia(lista)) {
    printf("Lista vazia!\n");
    return 0;
  }
  Elemento *atual = lista->topo;
  int menor = atual->valor;
  while (atual != NULL) {
    if (atual->valor < menor) {
      menor = atual->valor;
    }
    atual = atual->proximo;
  }
  return menor;
}

void removerPares(Lista *lista) {
  Elemento *atual = lista->topo;
  Elemento *anterior = NULL;
  while (atual != NULL) {
    if (atual->valor % 2 == 0) {
      if (anterior == NULL) {
        lista->topo = atual->proximo;
      } else {
        anterior->proximo = atual->proximo;
      }
      Elemento *temp = atual;
      atual = atual->proximo;
      free(temp);
      lista->tamanho--;
    } else {
      anterior = atual;
      atual = atual->proximo;
    }
  }
}

void inverteLista(Lista *lista) {
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

int main() {
  Lista *lista = criarLista();
  int opcao, valor, posicao;
  while (1) {
    printf("1- Insira um número na lista\n"
           "2 - Verifica se um número se encontra na lista\n"
           "3 - Exiba a soma de todos os números na lista\n"
           "4 - Exiba o maior número na lista\n"
           "5 - Exiba o menor número na lista\n"
           "6 - Remova todos os números pares da lista\n"
           "7 - Exiba os números que estão na lista\n"
           "8 - Inverta os elementos da lista\n"
           "9 - Encerre o programa\nOpção: ");
    scanf("%d",&opcao);
    switch(opcao){
      case 1:
      printf("Digite o valor a ser inserido: ");
      scanf("%d", &valor);
      inserirFinal(lista, valor);
      break;

      case 2:
      printf("Digite o valor a ser buscado: ");
      scanf("%d", &valor);
      if (existeElemento(lista, valor)) {
        printf("O valor %d existe na lista.\n", valor);
      } else {
        printf("O valor %d não existe na lista.\n", valor);
      }
      break;

      case 3:
      printf("A soma dos valores na lista é: %d\n", somaElementos(lista));
      break;

      case 4:
      printf("O maior valor na lista é: %d\n", maiorElemento(lista));
      break;

      case 5:
      printf("O menor valor na lista é: %d\n", menorElemento(lista));
      break;

      case 6:
      printf("Remova todos os números pares da lista.\n");
      removerPares(lista);
      break;

      case 7:
      imprimirLista(lista);
      break;

      case 8:
      inverteLista(lista);
      break;

      case 9:
      printf("Encerrando o programa...\n");
      liberarLista(lista);
      return 0;

      default:
      printf("Opção inválida.\n");
      break;
    }
  }
  return 0;
}