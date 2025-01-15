#include <stdio.h>

int part1(int n) {
  int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0, a8 = 0, a9 = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
          a1++;
          a2++;
          a3++;
          a4++;
          a5++;
          a6++;
          a7++;
          a8++;
          a9++;
        }
      }
    }
  }
  return a1 + a2 + a3 + a4 + a5 + a6 + a7 + a8 + a9;
}

int part2(int n) {
  int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      a1++;
      a2++;
      a3++;
      a4++;
      a5++;
    }
  }
  return a1 + a2 + a3 + a4 + a5;
}

int part3(int n) {
  int a1 = 0;
  for (int i = n; i > 0; i -= 2) {
    a1++;
  }
  return a1;
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