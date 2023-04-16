#include <stdio.h>  /* for fprintf */
#include <stdlib.h> /* for atoi */

int myAdd(int a, int b) {
  a += 1; /* shorthand for a = a + 1 */
  b++;    /* ditto */
  return a + b;
}

int main(int argc, char *argv[]) {
  (void)argc;  /* cast to void to suppress unused parameter warning */

  int a = atoi(argv[1]);
  int b = atoi(argv[2]);

  int sum = myAdd(a, b);
  fprintf(stdout, "sum of %d + %d = %d\n", a, b, sum);

  return 0;
}
