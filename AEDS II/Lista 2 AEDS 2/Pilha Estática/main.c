#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct{
  int top;
  char *vetor;
}Pilha;

Pilha *criaPilha(int tamanho) {
  Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
  pilha->top = -1;
  pilha->vetor = (char *)malloc(tamanho * sizeof(char));
  return pilha;
}

int isEmpty(Pilha *pilha) { 
  if (pilha->top == -1)
    return 1;
  return 0; 
}

//push = empilha
void push(Pilha *pilha, char item) { 
  pilha->top++;
  pilha->vetor[pilha->top] = item;
}

//pop = desempilha
void pop(Pilha *pilha, char *c) {
  if (!isEmpty(pilha)){
    *c = pilha->vetor[pilha->top--];
  }
}

void invertePalavra(char *texto) {
  int tamanho = strlen(texto);
  Pilha *pilha = criaPilha(tamanho);
  char c;
  for (int i = 0; i < tamanho; i++) {
    if (texto[i] != ' ' && texto[i] != '.') {
      push(pilha, texto[i]);
    } else {
      while (!isEmpty(pilha)) {
        pop(pilha, &c);
        printf("%c", c);
      }
      if (texto[i] == ' ') {
        printf(" ");
      } else if (texto[i] == '.') {
        printf(".");
      }
    }
  }
}

int main() {
  char texto[MAX];

  printf("Digite um texto terminado por ponto:\n");
  setbuf(stdin, NULL);
  fgets(texto, MAX, stdin);

  printf("\nTexto invertido:\n");
  invertePalavra(texto);

  return 0;
}