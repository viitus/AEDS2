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

char* invertePalavra(char *texto) {
  int tamanho = strlen(texto);
  Pilha *pilha = criaPilha(tamanho);
  char c;
  char *novaString = (char *)malloc(tamanho * sizeof(char));
  int j=-1;
  for (int i = 0; i < tamanho; i++) {
    if (texto[i] != '\n') {
      push(pilha, texto[i]);
    } else {
      while (!isEmpty(pilha)) {
        pop(pilha, &c);
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