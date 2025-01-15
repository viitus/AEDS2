#include <stdio.h>

int part1(int n) {
  int a = 0, b = 0, c = 0, d = 0, e = 0;
  for (int i = 0; i < n; i++) {
    a++;
    b++;
    c++;
    d++;
    e++;
  }
  return a + b + c + d + e;
}

int part2(int n) {
  int a = 0, b = 0, c = 0, d = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        a++;
        b++;
        c++;
        d++;
      }
    }
  }
  return a + b + c + d;
}

int main(void) {
  int n, p1, p2, r;
  printf("Insira n: ");
  scanf("%d", &n);
  p1 = part1(n);
  p2 = part2(n);
  r = p1 + p2;
  printf("f(n) = %d + %d = %d\n", p1, p2, r);
  return 0;
}