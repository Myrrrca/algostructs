#include <stdio.h>
#include <assert.h>

int majority_element(int const* parr, unsigned len)
{
  int x = majority_element_main(parr, 0, len - 1);
  return x;
}

int majority_element_main(int const* parr, unsigned l, unsigned r)
{
  printf("l = %u | r = %u\n", l, r);
  if (l >= r)
  {
    printf("RETURNING %d\n", parr[r]);
    return parr[r];
  }

  unsigned m = (r + l) / 2;
  int x = majority_element_main(parr, l, m);
  int y = majority_element_main(parr, m + 1, r);
  unsigned xcount = 0, ycount = 0;

  printf("TIME TO COMPARE %d and %d (l = %u, r = %u)\n", x, y, l, r);
  if (x == y)
    return x;

  for (int i = l; i <= r; ++i)
  {
    if (parr[i] == x)
      ++xcount;
    if (parr[i] == y)
      ++ycount;
  }
  printf("'%d' we have %u times | '%d' we have %u times\n", x, xcount, y, ycount);
  if (xcount == ycount) 
    return x;
  return (xcount > ycount) ? x : y;
}

int main()
{
  int arr[11] = {3, 2, 2, 3, 3, 5, 2, 2, 6, 2, 2};
  int x = majority_element(arr, 11);
  printf("x = %d\n", x);
  /* assert(x == 2); */

  return 0;
}

