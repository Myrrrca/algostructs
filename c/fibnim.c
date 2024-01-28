#include <assert.h>
#include <stdio.h>

int player_turn(int total, int possible)
{
  printf("Total is: %d\nEnter your number:\n", total);
  int mynum;
  char valid = 1; 
  int res; 
  while (valid)
  {
    res = scanf("%d", &mynum);
    assert(res == 1); 
    if (mynum > total || mynum <= 0 || mynum > possible)
    {
      printf("Incorrect input. Try again. Total: %d\n", total);
      valid = 1;
      continue;
    }
    valid = 0;
  }
  return mynum;

}

int next_turn(int total, int possible)
{
  printf("total %d possible %d ...\n", total, possible);
  if (total <= possible)
  {
    return total;
  }
  
  /* better to move this funtion on one level above */
  unsigned long long fib(unsigned n)
  {
    unsigned long long first = 0ull, second = 1ull; 
    if (n == 0) 
    {
      return 0ull;
    }
    for (int idx = 2; idx <= n; ++idx)
    {
      unsigned long long tmp = second;
      second = second + first;
      first = tmp;
    }
    return second;
  }

  int max, index;
  for (int i = 1; fib(i) < total; ++i)
  {
    max = i;
  }

  printf("max from fib(%d) is %llu\n", max, fib(max));

  unsigned long long sum = fib(max);
  printf("sum %llu\n", sum);
  for (int i = max - 1; i >= 0; --i)
  {
    printf("i is %d\n", i);
    if ((fib(i) + sum) < total)
    {
      sum += fib(i);
      printf("sum %llu and %llu is %llu\n", fib(i), sum - fib(i), sum);
      /* if (fib(i) > possible) */
      /* { */
      /*   continue; */
      /* } */
    }
      /* if (i > 3) */
      /* { */
      /*   continue; */
      /* } */

    if ((fib(i) + sum) == total)
    {
      /* if ((sum - fib(i)) <= possible) */
      /* { */

        return fib(i);
      /* } */
      /* index = i; */

    }
  }
  /* return fib(index); */
  return -1;

  /* for (int i = --res, j = 2; i >= 0; --i) */
  /* { */
  /*   if (fib(i) + fib(res) < total) */
  /*   { */
  /*     realloc(res, sizeof(unsigned long long) * j); */
  /*     res[j - 1] = i; */
  /*     ++j; */
  /*     printf("%llu", res[j - 1]); */
  /*   } */
  /* } */

  /* int fib[] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181}; */
  /* int sum = 0, size = sizeof(fib) / sizeof(fib[0]), index; */
  /* for (int i = 0; i < size; ++i) */
  /* { */
  /*   if (fib[i] < total) */
  /*   { */
  /*     index = i; */
  /*     sum = fib[i]; */
      /* printf("%d sum | %d i | %d fib[i]\n", sum, i, fib[i]); */
    /* } */
  /* } */
  /* printf(" ... %d\n", sum); */
  
  /* for (--index; index >= 0; --index) */
  /* { */
    /* printf("fib[i] %d\n", fib[index]); */
    /* if (fib[index] + sum < total) */
    /* { */
      /* sum += fib[index]; */
      /* printf("sum = %d\n", sum); */
    /* } */
    /* if (fib[index] + sum == total) */
    /* { */
      /* return fib[index]; */
    /* } */
  /* } */
  /* return -1; */
}

int main()
{
  unsigned long long b = next_turn(500500501, 11);
  int a = 500500501;
  printf("%d\n%llu\n", a, b);
  printf("\nЭто игра на двоих. Вы играете против компьютера\nИзначально дано N спичек. Первый игрок берёт любое количество, но не все сразу спички. Теперь второй может взять не больше, чем вдвое больше чем первый. Далее первый берёт не больше чем вдвое больше второго. И так далее. Выигрывает тот, кто взял последнюю спичку\n");
  printf("\nПример: Дано 11 спичек. Ваня ходит первый и берет 4 спички. Саша ходит вторым и не может взять больше чем 4 * 2 спичек. Саша берет 7 спичек и выигрывает игру\n");

  int total;
  printf("\nEnter total amount of matches:\n");
  int check = scanf("%d", &total);

  assert(check == 1);
  assert(total > 1);

  int max = total - 1, player_num = max / 2;
  char isPlayerStarts[2];

  printf("Total is: %d\n", total);
  printf("Do you want to do first move? y/N:\n");
  scanf("%s", isPlayerStarts);
/* int c; */
/* while ((c = getchar()) != '\n' && c != EOF) { } */
  if ((isPlayerStarts[0] == 'y' || isPlayerStarts[0] == 'Y') || isPlayerStarts[1] == '\n')
  {
    player_num = player_turn(total, max);
    total -= player_num;
    max = player_num * 2;
    if (total <= 0)
    {
      printf("Player won!\n");
    }
  }

  while (total > 0)
  {
    /* printf("%d %d\n", total, player_num * 2); */
    /* printf(" possible before com: %d\n", max); */
    int botnum = next_turn(total, max);
    printf("Computer picked %d\n", botnum);
    total -= botnum;
    max = botnum * 2;
    if(total <= 0)
    {
      printf("Computer won!\n");
      break;
    }
      
    /* printf(" possible before me: %d\n", max); */
    player_num = player_turn(total, max);
    total -= player_num;
    max = player_num * 2;
    if (total <= 0)
    {
      printf("Player won!\n");
      break;
    }
  }
}


