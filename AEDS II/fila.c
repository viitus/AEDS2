#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
  int vetor[MAX];
  int tamanho;
  int inicio;
  int fim;
} Fila;

Fila *criaFila();
void liberaFila(Fila *p);
int estahVazia(Fila *p);
int estahCheia(Fila *p);
int enFila(Fila *p, int x);
int deFila(Fila *p, int *x);
int mostraInicio(Fila *p);
int mostraFim(Fila *p);

int main(void) {
  Fila *p = NULL;
  int s, x;

  while (1) {
    printf("\n1)Cria fila\n"
           "2)Adiciona elemento a fila\n"
           "3)Remove elemento da fila\n"
           "4)Apaga fila\n"
           "5)Mostra inicio da fila\n"
           "6)Mostra fim da fila\n"
           "0)Sair\n");
    scanf("%d", &s);

    switch (s) {
    case 1:
      if (p != NULL) {
        printf("Fila já foi criada!\n");
      } else {
        p = criaFila();
        printf("Fila criada!\n");
      }
      break;

    case 2:
      if (p == NULL) {
        printf("ERRO. Fila não foi criada\n");
      } else {
        printf("Insira elemento: ");
        scanf("%d", &x);
        if (enFila(p, x)) {
          printf("Elemento adicionado\n");
        } else {
          printf("ERRO. Fila cheia\n");
        }
      }
      break;

    case 3:
      if (deFila(p, &x)) {
        printf("Elemento %d removido da fila\n", x);
      } else {
        printf("ERRO. Fila Vazia\n");
      }
      break;

    case 4:
      if (p == NULL) {
        printf("ERRO. Fila não foi criada\n");
      } else {
        liberaFila(p);
        p = NULL;
        printf("Fila apagada\n");
      }
      break;

    case 5:
      if (p == NULL) {
        printf("ERRO. Fila não foi criada\n");
      } else {
        printf("Inicio: %d\n", mostraInicio(p));
      }
      break;

    case 6:
      if (p == NULL) {
        printf("ERRO. Fila não foi criada\n");
      } else {
        printf("Fim: %d\n", mostraFim(p));
      }
      break;

    case 0:
      printf("TCHAU!\n");
      return 0;

    default:
      printf("OPÇÃO INVALIDA\n");
      break;
    }
  }
  return 0;
}

Fila *criaFila() {
  Fila *p = (Fila *)malloc(sizeof(Fila));
  p->inicio = 0;
  p->fim = 0;
  p->tamanho = 0;
  return p;
}
void liberaFila(Fila *p) { free(p); }
int estahVazia(Fila *p) { return (p->tamanho == 0); }
int estahCheia(Fila *p) { return (p->tamanho == MAX); }
int mostraInicio(Fila *p) { return p->vetor[p->inicio]; }
int mostraFim(Fila *p) { return p->vetor[p->fim - 1]; }

int enFila(Fila *p, int x) {
  if (!estahCheia(p)) {
    p->vetor[p->fim] = x;
    p->fim++;
    p->fim = p->fim % MAX;
    p->tamanho++;
    return 1;
  }
  return 0;
}

int deFila(Fila *p, int *x) {
  if (!estahVazia(p)) {
    *x = p->vetor[p->inicio];
    p->inicio++;
    p->inicio = p->inicio % MAX;
    p->tamanho--;
    return 1;
  }
  return 0;
}