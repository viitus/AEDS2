#include <stdio.h>
#include <stdlib.h>

typedef struct ConjuntoInteiros {
  int elementos[100];
  int tamanho;
} ConInt;

ConInt criarConj() {
  ConInt x;
  printf("Quantos elementos ? ");
  scanf("%d", &x.tamanho);
  fflush(stdin);
  if (x.tamanho != 0) {
    printf("insira os elementos:\n");
    for (int i = 0; i < x.tamanho; i++) {
      scanf("%d", &x.elementos[i]);
      fflush(stdin);
    }
  } 
  return x;
}

void criaVazio(ConInt *v) {
  v->tamanho = 0;
}

void exibeConjunto(ConInt x) {
  printf("[ ");
  for (int i = 0; i < x.tamanho; i++) {
    printf("%d ", x.elementos[i]);
  }
  printf("]\n");
}

void insereElemento(ConInt *conjunto, int elemento) {
  conjunto->elementos[conjunto->tamanho] = elemento;
  conjunto->tamanho++;
}

void removeElemento(ConInt *conjunto, int elemento) {
  int remover = -1;
  for (int i = 0; i < conjunto->tamanho; i++) {
    if (conjunto->elementos[i] == elemento) {
      remover = i;
      conjunto->tamanho--;
    }
  }
  if (remover == -1) {
    printf("elemento nao pertence ao conjunto\n");
  }
  for (int i = remover; i < conjunto->tamanho; i++) {
    conjunto->elementos[remover] = conjunto->elementos[remover + 1];
  }
}

int pertence(int x, ConInt a) {
  for (int i = 0; i < a.tamanho; i++) {
    if (x == a.elementos[i]) {
      return 1;
    }
  }
  return 0;
}

void criaUniao(ConInt *resultado, ConInt a, ConInt b) {
  resultado->tamanho = 0;
  for (int i = 0; i < a.tamanho; i++) {
    insereElemento(resultado, a.elementos[i]);
  }
  for (int i = 0; i < b.tamanho; i++) {
    if (!pertence(b.elementos[i], *resultado)) {
      insereElemento(resultado, b.elementos[i]);
    }
  }
}

void criaInter(ConInt *resultado, ConInt a, ConInt b){
  resultado->tamanho = 0;
  for(int i=0,j=0; i<a.tamanho; i++){
    if(pertence(a.elementos[i], b)){
      resultado->elementos[j] = a.elementos[i];
      resultado->tamanho++;
      j++;
    }
  }
}

void criaDiferenca(ConInt *diferenca, ConInt a, ConInt b){
  int j=0;
  for(int i=0; i<a.tamanho; i++){
    if(!pertence(a.elementos[i], b)){
      diferenca->elementos[j] = a.elementos[i];
      j++;
    }
  }
  diferenca->tamanho = j;
}

int tamanhoConj(ConInt conjunto){
  return conjunto.tamanho;
}

int mesmoTamanho(ConInt a, ConInt b){
  if(tamanhoConj(a) == tamanhoConj(b)){
    return 1;
  }else{
    return 0;
  }
}

int mesmoConjunto(ConInt a, ConInt b){
  int x=0;
  if(mesmoTamanho(a, b)){
    for(int i=0; i<a.tamanho; i++){
      if(pertence(a.elementos[i], b)){
        x++;
      }
    }
    if(x == a.tamanho){
      return 1;
    }
  }
  return 0;
}

int testeVazio(ConInt conjunto) {
  if (conjunto.tamanho == 0) {
    return 1;
  } else {
    return 0;
  }
}

int maiorElemento(ConInt x){
  int maior = x.elementos[0];
  for(int i=0; i<x.tamanho; i++){
    if(x.elementos[i] > maior){
      maior = x.elementos[i];
    }
  }
  return maior;
}

int menorElemento(ConInt x){
  int menor = x.elementos[0];
  for(int i=0; i<x.tamanho; i++){
    if(x.elementos[i] < menor){
      menor = x.elementos[i];
    }
  }
  return menor;
}

int main(void) {
  printf("CRIAR CONJUNTO A:\n");
  ConInt a = criarConj();
  getchar();
  printf("CRIAR CONJUNTO B:\n");
  ConInt b = criarConj();
  getchar();
  ConInt v, u, i, r;
  char s, c;
  int d;
  while (1) {
    printf("A: ");
    exibeConjunto(a);
    printf("B: ");
    exibeConjunto(b);

    printf("\n---MENU---\n"
           "a) Cria um conjunto União\n"
           "b) Cria um conjunto Vazio\n"
           "c) Insere elemento a um conjunto\n"
           "d) Remove elemento de um conjunto\n"
           "e) Cria o conjunto Intersecção\n"
           "f) Cria o conjunto Diferença\n"
           "g) Testa se um número pertence ao conjunto\n"
           "h) Encontra o Menor valor de um conjunto\n"
           "i) Encontra o Maior valor de um conjunto\n"
           "j) Testa se os conjuntos são iguais\n"
           "k) Verifica o tamanho do conjunto\n"
           "l) Testa se o conjunto é vazio\n"
           "m) Sair\n");
    scanf(" %c", &s);
    getchar();

    switch (s) {

    case 'a':
      criaUniao(&u, a, b);
      printf("U: ");
      exibeConjunto(u);
      break;

    case 'b':
      criaVazio(&i);
      printf("V: ");
      exibeConjunto(v);
      break;

    case 'c':
      printf("escolha um conjunto (A/B): ");
      scanf(" %c", &c);
      getchar();
      if (c == 'A' || c == 'a') {
        printf("Insira o elemento a ser inserido: ");
        scanf("%d", &d);
        insereElemento(&a, d);
        getchar();
      } else if (c == 'B' || c == 'b') {
        printf("Insira o elemento a ser inserido: ");
        scanf("%d", &d);
        insereElemento(&b, d);
        getchar();
      } else {
        printf("Opção inválida\n");
      }
      break;

    case 'd':
      printf("escolha um conjunto (A/B): ");
      scanf(" %c", &c);
      getchar();
      if (c == 'A' || c == 'a') {
        printf("Insira o elemento a ser removido: ");
        scanf("%d", &d);
        removeElemento(&a, d);
        getchar();
      } else if (c == 'B' || c == 'b') {
        printf("Insira o elemento a ser removido: ");
        scanf("%d", &d);
        removeElemento(&b, d);
        getchar();
      } else {
        printf("Opção inválida\n");
      }
      break;

    case 'e':
      criaInter(&i, a, b);
      printf("I: ");
      exibeConjunto(i);
      break;

    case 'f':
      printf("Criar A-B(1) ou B-A(2) ? ");
      scanf(" %d", &d);
      getchar();
      if(d==1){
        criaDiferenca(&r, a, b);
        printf("A-B: ");
        exibeConjunto(r);
      }else if(d==2){
        criaDiferenca(&r, b, a);
        printf("B-A: ");
        exibeConjunto(r); 
      }else{
        printf("Opção inválida\n");
      }
      break;

    case 'g':
      printf("escolha um conjunto (A/B): ");
      scanf(" %c", &c);
      getchar();
      printf("insira o elemento a testar: ");
      if (c == 'A' || c == 'a') {
        scanf("%d", &d);
        getchar();
        if (pertence(d, a)) {
          printf("%d pertence ao conjunto A\n", d);
        } else {
          printf("Não pertence ao conjunto A\n");
        }
      } else if (c == 'B' || c == 'b') {
        scanf("%d", &d);
        getchar();
        if (pertence(d, b)) {
          printf("%d pertence ao conjunto B\n", d);
        } else {
          printf("Não pertence ao conjunto B\n");
        }
      } else {
        printf("Opção inválida\n");
      }
      break;

    case 'h':
      printf("escolha um conjunto (A/B): ");
      scanf(" %c", &c);
      getchar();
      if (c == 'A' || c == 'a') {
        printf("O menor elemento do conjunto A é: %d\n", menorElemento(a));
      } else if (c == 'B' || c == 'b') {
        printf("O menor elemento do conjunto B é: %d\n", menorElemento(b));
      } else {
        printf("Opção inválida\n");
      }
      break;

    case 'i':
      printf("escolha um conjunto (A/B): ");
      scanf(" %c", &c);
      getchar();
      if (c == 'A' || c == 'a') {
        printf("O maior elemento do conjunto A é: %d\n", maiorElemento(a));
      } else if (c == 'B' || c == 'b') {
        printf("O maior elemento do conjunto B é: %d\n", maiorElemento(b));
      } else {
        printf("Opção inválida\n");
      }
      break;

    case 'j':
      if(mesmoConjunto(a, b)){
        printf("Os conjuntos A e B são iguais\n");
      }else{
        printf("Os conjuntos são diferentes\n");
      }
      break;

    case 'k':
      printf("escolha um conjunto (A/B): ");
      scanf(" %c", &c);
      getchar();
      if (c == 'A' || c == 'a') {
        printf("Tamanho de A: %d", tamanhoConj(a));
      } else if (c == 'B' || c == 'b') {
        printf("Tamanho de B: %d", tamanhoConj(b));
      } else {
        printf("Opção inválida\n");
      }
      break;

    case 'l':
      printf("escolha um conjunto (A/B): ");
      scanf(" %c", &c);
      getchar();
      if (c == 'A' || c == 'a') {
        if (testeVazio(a)) {
          printf("Conjunto vazio\n");
        } else {
          printf("Conjunto não é vazio\n");
        }
      } else if (c == 'B' || c == 'b') {
        if (testeVazio(b)) {
          printf("Conjunto vazio\n");
        } else {
          printf("Conjunto não é vazio\n");
        }
      } else {
        printf("Opção inválida\n");
      }
      break;

    case 'm':
      printf("\nTCHAU!");
      return 0;
    }
  }
}