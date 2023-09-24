#include <stdio.h>

int mdc(int a, int b) {
  int resto = a % b;
  while (resto != 0) {
    a = b;
    b = resto;
    resto = a % b;
  }
  return b;
}

int main() {
  int a, b;
  printf("1° Número: ");
  scanf("%d", &a);
  printf("2° Número: ");
  scanf("%d", &b);
  printf("mdc(%d, %d) = %d\n", a, b, mdc(a, b));
}

