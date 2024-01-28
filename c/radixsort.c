#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  srand(time(NULL));

  /* clock_t start_time = clock(); */

  /* int a[] = {126, 670, 343, 432, 316, 173, 556, 348}; */
  /* int acpy[] = {126, 670, 343, 432, 316, 173, 556, 348}; */

  int size = 10;
  /* int a[10] = {255, 166, 189, 209, 224, 107, 179, 130, 106, 268}; */
  int a[size]; 
  /* int a[10] = {278, 284, 212, 104, 120, 167, 206, 267, 111, 287}; */
  int acpy[size];
  for(int i = 0; i < size; ++i)
    a[i] = rand() % 889 ;

  for(int i = 0; i < size - 1; ++i)
  {
    int tmp = a[size - i - 1];
    int randi = rand() % (size - i);
    a[size - i - 1] = a[randi];
    a[randi] = tmp;
  }
  for (int i = 0; i < size - 1; ++i)
    acpy[i] = a[i];    


  unsigned ndigits = 3;
  unsigned n = size;

  for (int i = 0; i < n; ++i)
    printf("%d ", a[i]);
  printf("\n");

  int expn = 1;
  for (int i = 0; i < ndigits; ++i)
  {
    int b[11] = {0};
    for (int j = 0; j < n; ++j)
      b[(a[j] / expn) % 10] += 1;

    for (int i = 0; i < n + 1; ++i)
      printf("%d ", b[i]);
    printf("\n");

    for (int j = 1; j < n + 1; ++j)
      b[j] += b[j - 1];

    for (int j = n - 1; j > 0; --j)
      b[j] = b[j - 1];
    b[0] = 0;

    for (int i = 0; i < n + 1; ++i)
      printf("%d ", b[i]);
    printf("\n");

    // mycode
    for (int j = 0; j < n; ++j)
    {
      /* int tmpi = b[(a[j] / expn) % 10 - 1]; */
      int tmpi = b[(a[j] / expn) % 10];
      if (a[j] / expn % 10 != 0)
      {
        /* printf("NOT 0!\n"); */
        /* tmpi = b[(a[j] / expn) % 10 - 1]; */
        /* tmpi = b[(a[j] / expn) % 10 ] - 1; */
      }

      printf("tmpi = %d\n", tmpi);
      acpy[tmpi] = a[j];
      /* b[(a[j] / expn) % 10 - 1] += 1; */
      /* if (tmpi != 0) */
      /*   b[(a[j] / expn) % 10 - 1] += 1; */
      /* else  */
      /*   b[(a[j] / expn) % 10] += 1; */
      /* b[tmpi] += 1; */
      /* if ((a[j] / expn) % 10 == 0) */
      /* { */
      /*   printf("ABOBA\n"); */
      /*   b[(a[j] / expn) % 10] += 1; */
      /* } */
      /* else  */
      /* { */
        b[(a[j] / expn) % 10] += 1;
      /* } */

    }

    for (int i = 0; i < n; ++i)
      printf("%d ", acpy[i]);
    printf("\n");

    expn *= 10;

    for (int j = 0; j < n; ++j)
      a[j] = acpy[j];
  }
  
  /* clock_t end_time = clock(); */
  /**/
  /* double elapsed_time_sec = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; */
  /* double elapsed_time_millisec = elapsed_time_sec * 1000.0; */
  /**/
  /* printf("time: %d.%d sec\n", (int)elapsed_time_sec, (int)elapsed_time_millisec); */

  return 0;
}
