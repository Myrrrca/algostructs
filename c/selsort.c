#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* v1, int* v2)
{
  unsigned tmp = *v1;
  *v1 = *v2;
  *v2 = tmp;
}

void selsort(int* arr, unsigned len)
{
  unsigned min = 0;

  for (unsigned i = 0; i < len - 1; ++i)
  {
    for (unsigned j = i + 1; j < len; ++j)
    {
      if (arr[j] < arr[min])
      {
        min = j;
      }
    }

    if (arr[min] != arr[i])
    {
      swap(&arr[min], &arr[i]);
    }
    min = i + 1;
  }
}

int main()
{
  srand(time(NULL));

  unsigned size = 1000;
  int arr[size];
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

  selsort(arr, size);

  for(int i = 0; i < size; ++i)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}

