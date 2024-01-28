#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main()
{
  srand(time(NULL));

  int size = 10;
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

  inssort(arr, size);

  for(int i = 0; i < size; ++i)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}
