#include <stdio.h>

int part1(int n) {
  int a1 = 0, a2 = 0;
  for (int i = 0; i < n; i++) {
    a1++;
    a2++;
  }
  return a1 + a2;
}

int part2(int n) {
  int a1 = 0, a2 = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a1++;
      a2++;
    }
  }
  return a1 + a2;
}

int part3(int n) {
  int a1 = 0;
  for (int i = n; i > 0; i /= 2) {
    a1++;
  }
  return a1 - 1;
}

int main() {
  int n, p1, p2, p3, r;
  printf("Insira n: ");
  scanf("%d", &n);
  p1 = part1(n);
  p2 = part2(n);
  p3 = part3(n);
  r = p1 + p2 + p3;
  printf("f(n) = %d + %d + %d = %d\n", p1, p2, p3, r);
  return 0;
}