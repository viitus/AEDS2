#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
  int vetor[MAX];
  int topo;
} Pilha;

Pilha *criaPilha() {
  Pilha *p = (Pilha *)malloc(sizeof(Pilha));
  p->topo = 0;
  return p;
}

void push(Pilha *p, int x) {
  p->vetor[p->topo] = x;
  p->topo++;
}

int pop(Pilha *p) {
  p->topo--;
  return p->vetor[p->topo];
}

void inverte(Pilha *p){
  int size = p->topo;
  int aux[size];
  for(int i=0; i<size; i++){
    aux[i] = pop(p); 
  }
  for(int i = 0; i< size; i++){
    push(p, aux[i]); 
  }
}

int main(void) {
  Pilha *p = criaPilha();
  int x;
  printf("(0 para sair)\n");
  while(1){
    printf("Insira valor na pilha: ");
    scanf("%d",&x);
    if(x==0) {
      break;
    }else{
      push(p, x);
    }
  }
  printf("\nPilha original:\n");
  for(int i=0; i<p->topo; i++){
    printf("%d ",p->vetor[i]);
  }
  inverte(p);
  printf("\nPilha invertida:\n");
  for(int i=0; i<p->topo; i++){
    printf("%d ",p->vetor[i]);
  }
  
  return 0;
}