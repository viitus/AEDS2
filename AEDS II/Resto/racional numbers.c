#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int numerador;
  int denominador;
} racional;

racional criaRac(int n, int d) {
  racional r;
  r.numerador = n;
  r.denominador = d;
  return r;
}

racional somaRac(racional a, racional b) {
  racional s;
  s.numerador = (a.numerador * b.denominador) + (b.numerador * a.denominador);
  s.denominador = a.denominador * b.denominador;
  return s;
}

racional multRac(racional a, racional b) {
  racional m;
  m.numerador = a.numerador * b.numerador;
  m.denominador = a.denominador * b.denominador;
  return m;
}

racional divRac(racional a, racional b) {
  racional d;
  d.numerador = a.numerador * b.denominador;
  d.denominador = a.denominador * b.numerador;
  return d;
}

int testeIgual(racional a, racional b) {
  if (a.denominador * b.numerador == a.numerador * b.denominador) {
    return 1;
  } else {
    return 0;
  }
}

void exibeRac(racional a) { printf("(%d/%d)", a.numerador, a.denominador); }

int main(void) {
  int n, d;
  racional a, b;
  printf("\n---A---\n");
  printf("Numerador: ");
  scanf("%d", &n);
  printf("Denominador: ");
  scanf("%d", &d);
  a = criaRac(n, d);

  printf("\n---B---\n");
  printf("Numerador: ");
  scanf("%d", &n);
  printf("Denominador: ");
  scanf("%d", &d);
  b = criaRac(n, d);

  while (1) {
    printf("\n---MENU---\n"
           "1) Soma \n"
           "2) Multiplica\n"
           "3) Divide\n"
           "4) São iguais?\n"
           "0) Sair\n");
    int opcao;
    scanf("%d", &opcao);
    racional x;
    switch (opcao) {
    case 1:
      x = somaRac(a, b);
      exibeRac(a);
      printf(" + ");
      exibeRac(b);
      printf(" = ");
      exibeRac(x);
      break;

    case 2:
      x = multRac(a, b);
      exibeRac(a);
      printf(" - ");
      exibeRac(b);
      printf(" = ");
      exibeRac(x);
      break;

    case 3:
      x = divRac(a, b);
      exibeRac(a);
      printf(" / ");
      exibeRac(b);
      printf(" = ");
      exibeRac(x);
      break;

    case 4:
      if (testeIgual(a, b)) {
        printf("A e B são iguais.\n");
      } else {
        printf("A e B são difentes.\n");
      }
      break;

    case 0:
      printf("TCHAU.\n");
      return 0;
    }
  }
}