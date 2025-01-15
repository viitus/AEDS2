#include <math.h>
#include <stdio.h>

typedef struct {
  int raio;
  int altura;
  float area;
  float volume;
} Cilindro;

float areaBase(int r) { 
  return M_PI * r * r; 
}

float areaLado(int r, int h) { 
  return 2 * M_PI * r * h; 
}

float areaTotal(int r, int h) {
  float aL = areaLado(r, h);
  float aB = areaBase(r);
  return 2 * aB + aL;
}

float volumeTotal(int r, int h) {
  float aB = areaBase(r);
  return h * aB;
}

Cilindro criaCilindro(int r, int h) {
  Cilindro c;
  c.raio = r;
  c.altura = h;
  c.area = areaTotal(r, h);
  c.volume = volumeTotal(r, h);
  return c;
}

void exibeCilindro(Cilindro c) {
  printf("\n---Cilindro---\n");
  printf("Raio: %d\n", c.raio);
  printf("Altura: %d\n", c.altura);
  printf("Area: %.2f\n", c.area);
  printf("Volume: %.2f\n", c.volume);
}

int main(void) {
  int r, h;
  Cilindro c;
  printf("Insira o raio: ");
  scanf("%d", &r);
  printf("Insira a altura: ");
  scanf("%d", &h);
  c = criaCilindro(r, h);
  exibeCilindro(c);
  return 0;
}