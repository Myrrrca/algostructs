#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFError(char* format, ...)
{
  va_list args;
  unsigned length = strlen(format);
  fprintf(stderr, "length = %u\n", length);
  unsigned i;
  va_start(args, format);
  /* char buff[4048]; */
  char* buff;

  for (i = 0; i < length; ++i) {
    if (format[i] == '%') {
      if (format[i + 1] == 's') {
        buff = va_arg(args, char*);
        for (int i = 0; i < strlen(buff); ++i) {
          fprintf(stderr, "%c", buff[i]);
        }
        i += 2;
      }
    } 
    fprintf(stderr, "%c", format[i]);
  }
  fprintf(stderr, ": ");
  perror("");
  va_end(args);
}

void printFError2(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  char buff[256];
  vsprintf(buff, format, args);
  perror(buff);
  va_end(args);
}

int find_in_file(const char* name, int needle)
{
  FILE* f;
  unsigned count = 0;

  f = fopen(name, "r");
  if (!f)
  {
    /* perror("error opening file"); */
    /* printFError("error opening '%s'", name); */
    printFError2("error opening '%s'", name);
    abort();
    return 0;
  }

  for (;;)
  {
    int res, n;
    res = fscanf(f, "%d", &n);
    if (res == EOF)
      break;
    if (res != 1)
    {
      fprintf(stderr, "file %s have broken format\n", name);
      abort();
    }
    if (needle == n)
      count += 1;
  }

  fclose(f);
  return count;
}

int main(int argc, char** argv)
{
  int n; 
  char* endptr;

  if (argc < 3)
  {
    fprintf(stderr, "call: %s <n> <files...>\n", argv[0]);
    return 1;
  }

  n = strtol(argv[1], &endptr, 10);  
  if(endptr == argv[1])
  {
    fprintf(stderr, "<%s> cannot be converted to int\n", argv[1]);
    return 1;
  }
  
  unsigned count = 0;
  for (int i = 2; i < argc; ++i)
    count += find_in_file(argv[i], n);
  printf("count = %u\n", count);
  
  return 0;
}
