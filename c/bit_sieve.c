#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

struct sieve_t
{
  unsigned size;
  unsigned char* sieve;
};

/* unsigned long long sieve_bound(unsigned num) */
/* { */
/*   double dnum = num; */
/*   double dres = dnum * (log(dnum) + log(log(dnum))); */
/*   return (unsigned long long) round(dres); */
/* } */

unsigned is_prime(struct sieve_t s, unsigned x)
{
  if (x < 2) return 0;

  for (int i = 2; i * i <= x; ++i)
  {
    if (x % i == 0) return 0;
  }
  return 1;

}

struct sieve_t init_sieve(unsigned size)
{
  /* if (size > 20)  */
  /* { */
  /*   size = sieve_bound(size); */
  /* } */

  assert(size > 0);

  struct sieve_t tmp; 
  tmp.size = size;
  int allocsize = (size / (sizeof(char) * 8)) + 1;
  if (size % (sizeof(char) * 8) == 0)
    --allocsize; 
  printf("allocsize %d\n", allocsize);
  tmp.sieve = calloc(allocsize, sizeof(char)); 

  for (unsigned i = 0, counter = 0; size > 0; ++counter, --size)
  {
    if (tmp.sieve[i] >> (counter % 8) == 1)
      continue;

    unsigned num = is_prime(tmp, counter + 1);
    printf("num = %u | ", num);
    tmp.sieve[i] |= num << counter; 
    printf("sieve[%u(%u)] %d\n", i, counter, tmp.sieve[i] >> counter);
    /* if (tmp.sieve[i] >> bit == 1) */
    /* { */
    /*   for (unsigned j = (num + 1) * (num + 1); j < tmp.size; j *= j) */
    /*   { */
    /*     tmp.sieve[j - 1] = 1; */
    /*   } */
    /* } */
    if (counter % 7 == 0 && counter != 0)
    {
      ++i;
    }

  }

  return tmp;
}


/* unsigned char is_prime(struct sieve_t s, unsigned num) */
/* { */
/*   assert(num <= s.size); */
/*   return s.sieve[num - 1] == 0 ? 0 : 1; */
/* } */

void free_sieve(struct sieve_t* s)
{
  free(s->sieve);
  s->sieve = NULL;
  s->size = 0;
}

int main()
{
  unsigned size = 0;
  scanf("%ud", &size);
 
  struct sieve_t s = init_sieve(size);
  printf("!!! %d !!!\n", s.sieve[0]);

  assert(s.sieve != NULL && s.size > 0);

  /* assert(is_prime(s, 0) == 0); */
  /* assert(is_prime(s, 1) == 0); */
  assert(is_prime(s, 2) == 1);
  assert(is_prime(s, 3) == 1);
  /* assert(is_prime(s, 4) == 0); */
  assert(is_prime(s, 5) == 1);
  /* assert(is_prime(s, 96) == 0); */
  assert(is_prime(s, 97) == 1);
  /* assert(is_prime(s, 98) == 0); */

  for (int i = 0, counter = 0; counter < s.size; ++counter)
  {
    printf("%d ", (s.sieve[i] >> counter) & 1);

    if (counter % 7 == 0 && counter != 0)
    {
      ++i;
    }

  }

  free_sieve(&s);

  return 0;
}

