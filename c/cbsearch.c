#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int (*cmp_t)(void const* lhs, void const* rhs);

unsigned moveright(int* arr, int key, unsigned last)
{
  unsigned maxi = last, mini = 0;
  unsigned middlei = (maxi + mini) / 2;

  while (maxi > mini)
  {
    if (arr[middlei] > key)
    {
      if (maxi - mini == 1)
      {
        break;
      }
      else 
      {
        maxi = middlei - 1;
      }
    }
    else if (arr[middlei] < key)
    {
      mini = middlei + 1;
    }
    middlei = (maxi + mini) / 2;
  }

  if (arr[middlei] < key && arr[middlei + 1] > key)
  {
    ++middlei;
  }

  maxi = last;
  while (maxi > middlei)
  {
    arr[maxi] = arr[maxi - 1];
    --maxi;
  }

  return middlei;
}

void inssort(int* arr, unsigned len)
{
  for (unsigned i = 1; i < len; ++i)
  {
    int key = arr[i];
    unsigned pos = moveright(arr, key, i);
    arr[pos] = key;
  }
}

unsigned binary_search(int const* parr, unsigned len, int elem)
{
  int l = 0;
  int r = len - 1;
  while (l <= r)
  {
    int m = l + (r - l) / 2;
    if (parr[m] == elem) return m;
    else if (parr[m] < elem) l = m + 1;
    else if (parr[m] > elem) r = m - 1;
  }
  return len;
}

int intless(void const* lhs, void const* rhs)
{
  const int* ilhs = (int*) lhs;
  const int* irhs = (int*) rhs;

  if(*ilhs > *irhs) return 1;
  if(*ilhs < *irhs) return -1;
  return 0;
}

void* cbsearch(void const* key, void const* base, int num, int size, cmp_t cmp)
{
  int l = 0;
  int r = num - 1;
  while (l <= r)
  {
    int m = l + (r - l) / 2;
    int res = cmp((char* const)base + (m * size), key);
    if (res == 1) r = m - 1;
    if (res == -1) l = m + 1;
    if (res == 0) return (char* const)base + (m * size);
    printf("l = %d | r = %d | m = %d | res = %d | arr[m] = %d\n", l, r, m, res, *((char* const)base + (m * size)));
  }
  return (char* const)base + (num * size);
}

int main()
{
  srand(time(NULL));

  int size = 10;
  int arr[size];
  int key = 3;

  for(int i = 0; i < size; ++i)
  {
    arr[i] = i + 1;
  }

  for(int i = 0; i < size - 1; ++i)
  {
    int tmp = arr[size - i - 1];
    int randi = rand() % (size - i);
    arr[size - i - 1] = arr[randi];
    arr[randi] = tmp;
  }

  for(int i = 0; i < size; ++i)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");

  inssort(arr, size);

  for(int i = 0; i < size; ++i)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");

  unsigned res1 = binary_search(arr, size, key);
  printf("searched for 3, index is %u\n", res1);

  int* pkey = &key;
  cmp_t cmpint = &intless;
  int* res2 = (int*)cbsearch(pkey, arr, size, sizeof(int), cmpint);
  printf("searched for %d, value is %d\n", key, *res2);

  return 0;
}

