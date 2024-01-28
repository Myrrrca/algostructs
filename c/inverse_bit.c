/* inversion of the selected bit from a number in the array */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

int main()
{
  int x, bit;

  char try = scanf("%d", &x);
  assert(try == 1);
  int* bytes = malloc(x);

  for (int i = 0; i < x; ++i)
  {
    try = scanf(" %d", &bytes[i]);
    assert(try == 1);
    if (bytes[i] > pow(2, sizeof(char) * 8))
      abort();
  }

  try = scanf(" %d", &bit);
  assert(try == 1);
  /* not nessesary */
  printf("byte = %d\n", (bytes[bit / 8] >> (bit % 8)) & 1);

  bytes[bit / 8] ^= 1 << (bit % 8);  

  for (int i = 0; i < x; ++i)
  {
    printf("%d ", bytes[i]);
  }

  return 0;
}
