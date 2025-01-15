#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

typedef struct contato {
  char nome[MAX];
  char telefone[MAX];
  char email[MAX];
  struct contato *prox;
} Contato;

typedef struct lista {
  Contato *topo;
  int tamanho;
} Lista;

Contato *criarContato(char *nome, char *telefone, char *email) {
  Contato *novoContato = (Contato *)malloc(sizeof(Contato));
  strcpy(novoContato->nome, nome);
  strcpy(novoContato->telefone, telefone);
  strcpy(novoContato->email, email);
  novoContato->prox = NULL;
  return novoContato;
}

Lista *criarLista() {
  Lista *lista = (Lista *)malloc(sizeof(Lista));
  lista->topo = NULL;
  lista->tamanho = 0;
  return lista;
}

int estahVazia(Lista *lista) { return (lista->topo == NULL); }

void adicionarContato(Lista *lista, Contato *novoContato) {
  if (estahVazia(lista) || strcmp(novoContato->nome, lista->topo->nome) < 0) {
    novoContato->prox = lista->topo;
    lista->topo = novoContato;
  } else {
    Contato *atual = lista->topo;
    while (atual->prox != NULL &&
           strcmp(novoContato->nome, atual->prox->nome) > 0) {
      atual = atual->prox;
    }
    novoContato->prox = atual->prox;
    atual->prox = novoContato;
  }
  lista->tamanho++;
}

void removerContato(Lista *lista, char *nome) {
  Contato *atual = lista->topo;
  Contato *anterior = NULL;
  while (atual != NULL && strcmp(atual->nome, nome) != 0) {
    anterior = atual;
    atual = atual->prox;
  }
  if (atual != NULL) {
    if (anterior == NULL) {
      lista->topo = atual->prox;
    } else {
      anterior->prox = atual->prox;
    }
    free(atual);
    lista->tamanho--;
  }
}

void exibirLista(Lista *lista) {
  Contato *atual = lista->topo;
  printf("Lista de contatos:\n-----\n");
  while (atual != NULL) {
    printf("Nome: %s\n", atual->nome);
    printf("Telefone: %s\n", atual->telefone);
    printf("Email: %s\n", atual->email);
    printf("-----\n");
    atual = atual->prox;
  }
}

void atualizarContato(Lista *lista, char *nome, char *nNome, char *nTelefone,
                      char *nEmail) {
  Contato *atual = lista->topo;
  while (atual != NULL && strcmp(atual->nome, nome) != 0) {
    atual = atual->prox;
  }
  if (atual != NULL) {
    strcpy(atual->nome, nNome);
    strcpy(atual->telefone, nTelefone);
    strcpy(atual->email, nEmail);
  }
}

void liberarMemoria(Lista *lista) {
  Contato *atual = lista->topo;
  Contato *proximo;
  while (atual != NULL) {
    proximo = atual->prox;
    free(atual);
    atual = proximo;
  }
  lista->topo = NULL;
  lista->tamanho = 0;
}

void insereDado(char *dado) {
  setbuf(stdin, NULL);
  fgets(dado, MAX, stdin);
  dado[strcspn(dado, "\n")] = '\0';
}

int main() {
  int opcao;
  char novoNome[MAX];
  char nome[MAX];
  char telefone[MAX];
  char email[MAX];
  Lista *lista = criarLista();
  Contato *contato1 =
      criarContato("Geraldo", "(11) 1111-1111", "geras@hotmail.com");
  adicionarContato(lista, contato1);
  Contato *contato2 =
      criarContato("Andresa", "(22) 2222-2222", "dresa@gmail.com");
  adicionarContato(lista, contato2);
  Contato *contato3 =
      criarContato("Pedrinho", "(33) 3333-3333", "pedre@yahoo.com.br");
  adicionarContato(lista, contato3);

  while (1) {
    printf("1 - Adicionar contato\n"
           "2 - Excluir contato\n"
           "3 - Atualizar contato\n"
           "4 - Exibir lista de contatos\n"
           "5 - Sair\n"
           "Opção: ");
    scanf("%d", &opcao);
    switch (opcao) {
      case 1: 
      printf("Digite o nome do contato: ");
      insereDado(nome);
      printf("Digite o telefone do contato: ");
      insereDado(telefone);
      printf("Digite o email do contato: ");
      insereDado(email);
      Contato *contato = criarContato(nome, telefone, email);
      adicionarContato(lista, contato);
      break;

      case 2:
      printf("Digite o nome do contato a ser excluído: ");
      insereDado(nome);
      removerContato(lista, nome);
      break;

      case 3:
      printf("Digite o nome do contato a ser atualizado: ");
      insereDado(nome);
      printf("Digite o novo nome do contato: ");
      insereDado(novoNome);
      printf("Digite o novo telefone do contato: ");
      insereDado(telefone);
      printf("Digite o novo email do contato: ");
      insereDado(email);
      atualizarContato(lista, nome, novoNome, telefone, email);
      break;

      case 4:
      exibirLista(lista);
      break;

      case 5:
      printf("Encerrando o programa...\n");
      liberarMemoria(lista);
      return 0;

      default:
      printf("Opção inválida!\n");
      break;
    }
  }
  return 0;
}