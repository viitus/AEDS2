#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
  int vetor[MAX];
  int fim;
} Lista;

Lista *criaLista();
void liberaLista(Lista *p);
int estahVazia(Lista *p);
int estahCheia(Lista *p);
int removeDaPosicao(Lista *p, int *x, int k);
int insereNaOrdem(Lista *p, int x);
void imprimeLista(Lista *p);

int main(void) { 
  Lista* p = criaLista();
  
  while(1){
    printf("1-Insere\n2-Remove\n3-Imprime\n4-Sair\n");
    int s,x,k;
    scanf("%d", &s);
    switch(s){
      case 1:
      printf("Digite o valor a ser inserido: ");
     
      scanf("%d", &x);
      insereNaOrdem(p, x);
      break;

      case 2:
      printf("Digite a posição a ser removida: ");
      scanf("%d", &k);
        if(removeDaPosicao(p, &x, k)){
          printf("Elemento removido: %d\n", x);
        }else{
          printf("Posição inválida\n");
        }
      break;

      case 3:
      printf("Imprimindo lista...\n");
      imprimeLista(p);
      break;

      case 4:
      printf("Saindo...\n");
      liberaLista(p);
      exit(0);
    }
  }
  
  return 0; 
}

Lista *criaLista() {
  Lista *p = (Lista *)malloc(sizeof(Lista));
  p->fim = 0;
  return p;
}
void liberaLista(Lista *p) { free(p); }
int estahVazia(Lista *p) { return (p->fim == 0); }
int estahCheia(Lista *p) { return (p->fim == MAX); }

// Adicionar elementos
int insereNaOrdem(Lista *p, int x) {
  if(estahCheia(p)) {
    return 0;
  }
  if (estahVazia(p)) {
    p->vetor[0] = x;
    p->fim++;
  } else {
    int i;
    for (i = p->fim - 1; i >= 0 && p->vetor[i] > x; i--) {
      p->vetor[i + 1] = p->vetor[i];
    }
    p->vetor[i+1] = x;
    p->fim++;
  }
  return 1;
}

// Remover Elementos
int removeDaPosicao(Lista *p, int *x, int k) {
  if (!estahVazia(p)) {
    *x = p->vetor[k];
    p->fim--;
    for (int i = k; i < p->fim; i++) {
      p->vetor[i] = p->vetor[i + 1];
    }
    return 1;
  }
  return 0;
}

void imprimeLista(Lista *p) {
  for (int i = 0; i < p->fim; i++) {
    printf("%d ", p->vetor[i]);
  }
  printf("\n");
}