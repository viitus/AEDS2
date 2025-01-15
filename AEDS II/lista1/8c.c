#include <stdio.h>

int part1(int n) {
  int a1 = 0, a2 = 0, a3 = 0, a4 = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        a1++;
        a2++;
        a3++;
        a4++;
      }
    }
  }
  return a1 + a2 + a3 + a4;
}

int part2() {
  int a1 = 0, a2 = 0;
  a1++;
  a2++;
  return a1 + a2;
}

int main() {
  int n, p1, p2, r;
  printf("Insira n: ");
  scanf("%d", &n);
  p1 = part1(n);
  p2 = part2();
  r = p1 + p2;
  printf("f(n) = %d + %d = %d\n", p1, p2, r);
  return 0;
}