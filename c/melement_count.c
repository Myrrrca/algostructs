#include <stdio.h>
#include <assert.h>

int majority_element(int const* parr, unsigned len)
{
  int m = parr[0];
  int i = 0;
  for (unsigned j = 0; j < len; ++j)
  {
    printf("m = %d | i = %d\n", m, i);
    ++parr;
    if (*(parr) != m)
    {
      if (i == 0)
      {
        m = *parr;
      }
       else 
      {
        --i;
      }
    }
    else 
    {
      ++i;
    }
  }
  return m;
}

int main()
{
  int arr[11] = {3, 2, 2, 3, 3, 5, 2, 2, 6, 2, 2};
  int x = majority_element(arr, 11);
  assert(x == 2);

  return 0;
}
