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

int umMaiorQueDois(Pilha *p1, Pilha *p2){
  if(p1->topo > p2->topo){
    return 1;
  }else{
    return 0;
  }
}

int main(void) {
  Pilha *p1 = criaPilha();
  Pilha *p2 = criaPilha();
  int x;
  printf("(0 para sair)\n");
  while(1){
    printf("Insira valor na pilha1: ");
    scanf("%d",&x);
    if(x==0) {
      break;
    }else{
      push(p1, x);
    }
  }

  printf("(0 para sair)\n");
  while(1){
    printf("Insira valor na pilha2: ");
    scanf("%d",&x);
    if(x==0) {
      break;
    }else{
      push(p2, x);
    }
  }

  if(umMaiorQueDois(p1, p2)){
    printf("a pilha1 tem mais elementos que a pilha2\n");
  }else{
    printf("a pilha1 não tem mais elementos que a pilha2\n");
  }
  
  return 0;
}