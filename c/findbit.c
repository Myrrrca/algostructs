/* finds min and max index of bits that setted in "1" in a number */

#include <stdio.h>
#include <assert.h>

int main()
{
  long long x;
  int min = -1, max = -1, index;
  char try = scanf("%lld", &x);
  assert(try == 1);

  int sizebit = sizeof(long long) * 8;
  for (int i = 0; i < sizebit; ++i)
  {
    index = i;
    if ((x & 1) == 1)
    {
      min = i;
      break;
    }
    x = x >> 1;
  }
  
  printf("%d ", min);


  for (int i = index; i < sizebit; ++i)
  {
    if ((x & 1) == 1)
    {
      max = i;
    }
    x = x >> 1;
  }

  printf("%d", max);

  return 0;
}
