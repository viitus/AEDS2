#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct elemento {
  char valor;
  struct elemento *proximo;
} Elemento;

typedef struct pilha {
  Elemento *topo;
} Pilha;

Elemento *criaElemento(char valor) {
  Elemento *E = (Elemento *)malloc(sizeof(Elemento));
  if (E == NULL) {
    exit(1);
  } else {
    E->valor = valor;
    E->proximo = NULL;
    return E;
  }
}

Pilha *criaPilha() {
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  if (p == NULL) {
    exit(2);
  } else {
    p->topo = NULL;
    return p;
  }
}

int estahVazia(Pilha *p) { return (p->topo == NULL); }

void enPilha(Pilha *p, char valor) {
  Elemento *E = criaElemento(valor);
  E->proximo = p->topo;
  p->topo = E;
}

void dePilha(Pilha *p, char *valor) {
  if (estahVazia(p)) {
    exit(3);
  } else {
    Elemento *aux = p->topo;
    *valor = aux->valor;
    p->topo = aux->proximo;
    free(aux);
  }
}

void liberaPilha(Pilha *p, char *valor) {
  while (!estahVazia(p)) {
    dePilha(p, valor);
  }
  free(p);
}
char* invertePalavra(char *texto) {
  int tamanho = strlen(texto);
  Pilha *pilha = criaPilha();
  char c;
  char *novaString = (char *)malloc(tamanho * sizeof(char));
  int j=-1;
  for (int i = 0; i < tamanho; i++) {
    if (texto[i] != '\n') {
      enPilha(pilha, texto[i]);
    } else {
      while (!estahVazia(pilha)) {
        dePilha(pilha, &c);
        novaString[++j] = c;
      }
    }
  }
  novaString[++j] = '\n';
  return novaString;
}

int isPalindromo(char* texto1, char* texto2){
  if(strcmp(texto1, texto2) == 0)
    return 1;
  return 0;
}

int main() {
  char texto[MAX];

  printf("Digite uma palavra: ");
  setbuf(stdin, NULL);
  fgets(texto, MAX, stdin);

  char *texto2 = invertePalavra(texto);
  printf("\nPalavra invertida: %s\n",texto2);

  if(isPalindromo(texto, texto2)){
    printf("É um palindromo");
  }else{
    printf("Não é um palindromo");
  }

  return 0;
}