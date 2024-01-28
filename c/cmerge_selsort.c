#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void (*swap_t)(void* lhs, void* rhs);
typedef void (*merge_t)(void* arr, unsigned l, unsigned m, unsigned r);

struct Complex
{
  int real, imag; 
};

void swapcomp(void* v1, void* v2)
{
  struct Complex* pv1 = (struct Complex*) v1;
  struct Complex* pv2 = (struct Complex*) v2;

  struct Complex tmp = *pv1;
  *pv1 = *pv2;
  *pv2 = tmp;
}

void swapint(void* v1, void* v2)
{
  int* num1 = (int*) v1;
  int* num2 = (int*) v2;

  int tmp = *num1;
  *num1 = *num2;
  *num2 = tmp;
}

void selsort(void* arr, unsigned size, unsigned l, unsigned r, swap_t swp)
{
  unsigned min = l;

  for (unsigned i = l; i < r; ++i)
  {
    for (unsigned j = i + 1; j < r + 1; ++j)
    {
      if (*((char*)arr + (j * size)) < *((char*)arr + (min * size)))
      {
        min = j;
      }
    }
    if ((char*)arr + (min * size) != (char*)arr + (i * size))
    {
      /* printf("called swp() for %u element\n", i); */
      swp((char*)arr + (min * size), (char*)arr + (i * size));
    }

    min = i + 1;
  }
}

void mergeint(void* arr, unsigned l, unsigned m, unsigned r)
{
  /* printf("MERGE STARTED\n"); */
  int* newarr = malloc(sizeof(int) * (r - l + 1));
  int* copyarr = (int*) arr;

  /* printf("did new array for %u elements\n", r - l + 1); */
  int* parr1 = &copyarr[l];//&arr[l]
  int* parr2 = &copyarr[m + 1]; //&arr[m + 1]
  /* printf("first merging %d and %d\n", *parr1, *parr2); */
  for (int i = 0; i < r - l + 1; ++i)
  {
    if (*parr1 == *parr2)
    {
      newarr[i] = *parr1;
    }
    if (*parr1 > *parr2)
    {
      newarr[i] = *parr2;

      if (copyarr[r] == *parr2)
      {
        parr2 = &copyarr[m];
      }
      else 
      {
        ++parr2;
      }

      /* printf("newarr = "); */
      /* for (int j = 0; j < i + 1; ++j) */
      /* { */
      /*   printf("%d ", newarr[j]); */
      /* } */
      /* printf("\n"); */
      /* printf("now merging %d and %d\n", *parr1, *parr2); */
    }
    else if (*parr1 < *parr2)
    {
      newarr[i] = *parr1;

      if (copyarr[m] == *parr1)
      {
        *parr1 = *parr2;
        if (*parr2 != copyarr[r])
        {
          ++parr2;
        }
      }
      else 
      {
        ++parr1;
      }

      /* printf("newarr = "); */
      /* for (int j = 0; j < i + 1; ++j) */
      /* { */
      /*   printf("%d ", newarr[j]); */
      /* } */
      /* printf("\n"); */
      /* printf("now merging %d and %d\n", *parr1, *parr2); */
    }
  }

  for (int i = l, j = 0; j < r - l + 1; ++i, ++j)
  {
    /* printf("arr[%d] (%d) = newarr[%d] (%d)\n", i, copyarr[i], j, newarr[j]); */
    copyarr[i] = newarr[j];
  }

  /* printf("newarr[i] = "); */
  /* for (int i = 0; i < r - l + 1; ++i) */
  /* { */
  /*   printf("%d ", newarr[i]); */
  /* } */
  /* printf("\n"); */

  /* printf("arr[i] = "); */
  /* for (int i = l; i < r + 1; ++i) */
  /* { */
  /*   printf("%d ", copyarr[i]); */
  /* } */
  /* printf("\n\n"); */
  free(newarr); 
}

void merge_sort_ultimate(void* arr, unsigned size, unsigned l, unsigned r, unsigned itstime, swap_t swp, merge_t merge)
{
  if (l >= r) 
  {
    /* printf("UP AND RETURN | l = %u | r = %u\n", l, r); */
    return;
  }

  unsigned m = (l + r) / 2;
  /* printf("UP | l = %u | r = %u | m = %u\n", l, r, m); */
  merge_sort_ultimate(arr, size, l, m, itstime, swp, merge);
  merge_sort_ultimate(arr, size, m + 1, r, itstime, swp, merge);
  /* printf("DOWN | l = %u | r = %u | m = %u\n", l, r, m); */
  if (r - l + 1 <= itstime)
  {
    /* printf("!!!! DOING SELSORT !!!\n"); */
    selsort(arr, size, l, r, swp);
    /* for (int i = l; i < r + 1; ++i) */
    /* { */
    /*   printf("%d ", *((char*)arr + (i * size))); */
    /* } */
    /* printf("\n"); */

  }
  else 
  {
    merge(arr, l, m, r);
  }
}

int main()
{
  srand(time(NULL));

  unsigned size = 100;
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

  swap_t swpint = &swapint;
  merge_t mrgint = &mergeint;
  merge_sort_ultimate(arr, sizeof(int), 0, sizeof(arr) / sizeof(arr[0]) - 1, 50, swpint, mrgint);

  for(int i = 0; i < size; ++i)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");

  /* struct Complex arrcomp[5] = {{1, 5}, {-3, 6}, {1, 0}, {0, 0}, {10, 10}}; */
  /* swap_t swpcomp = &swapcomp; */
  /* merge_t mrgcomp = &<your_own_merge_for_struct_Complex> */
  /* merge_sort_ultimate(arrcomp, sizeof(struct Complex), 0, sizeof(arrcomp) / sizeof(arrcomp[0]) - 1, 50, swpcomp, mrgcomp); */

  /* for(int i = 0; i < 5; ++i) */
  /* { */
  /*   printf("(%d, %d) ", arrcomp[i].real, arrcomp[i].imag); */
  /* } */
  /* printf("\n"); */

  return 0;
}
