#include <math.h>
#include <stdio.h>

typedef struct {
  int raio;
  float area;
  float volume;
} Esfera;

float areaEsfera(int r) { return 4 * M_PI * r * r; }

float volumeEsfera(int r) { return r * r * r * M_PI * 4 / 3; }

Esfera criaEsfera(int r) {
  Esfera e;
  e.raio = r;
  e.area = areaEsfera(r);
  e.volume = volumeEsfera(r);
  return e;
}

void exibeEsfera(Esfera c) {
  printf("\n---Esfera---\n");
  printf("Raio: %d\n", c.raio);
  printf("Area: %.2f\n", c.area);
  printf("Volume: %.2f\n", c.volume);
}

int main(void) {
  int r;
  Esfera c;
  printf("Insira o raio: ");
  scanf("%d", &r);
  c = criaEsfera(r);
  exibeEsfera(c);
  return 0;
}