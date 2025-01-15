#include <stdio.h>

typedef struct {
  int lado;
  int area;
  int volume;
} Cubo;

int areaFace(int l) { 
  return l * l; 
}

int areaTotal(int l) { 
  return 6 * areaFace(l); 
}

Cubo criaCubo(int l) {
  Cubo c;
  c.area = areaTotal(l);
  c.volume = areaFace(l) * l;
  c.lado = l;
  return c;
}

void exibeCubo(Cubo c) {
  printf("\n---Cubo:---\n");
  printf("LADO:    %dcm\n", c.lado);
  printf("AREA:    %dcm^2\n", c.area);
  printf("VOLUME:  %dcm^3\n", c.volume);
}

int main(void) {
  printf("Insira um inteiro: ");
  int x;
  scanf("%d", &x);
  Cubo c = criaCubo(x);
  exibeCubo(c);
  return 0;
}