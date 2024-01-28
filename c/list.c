#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node_t
{
  struct node_t* next;
  int num;
};

struct node_t* read_list(FILE* f)
{
  int n;
  struct node_t* el = NULL, *ol = NULL, *node;
  while (fscanf(f, "%d", &n) == 1) {
    printf("n = %d\n", n);
    node = malloc(sizeof(struct node_t));
    node->num = n;

    if (el == NULL) {
      el = node;
      ol = el;
    }
    else {
      el->next = node;
      el = node;
    }

    /* if ((n & 0x1) == 0) { */
      /* el->next = node; */
      /* node->next = el; */
      /* el = node; */
    /* } */
  }
  /* return el; */
  return ol;
}

struct node_t* reverse(struct node_t* top) 
{
  struct node_t* xs;
  if (NULL == top) return NULL;
  if (NULL == top->next) return top;
  xs = reverse(top->next);
  top->next->next = top;
  top->next = NULL;
  return xs;
}

struct node_t* read_list_backwards(FILE* f)
{
  int n;
  struct node_t* el = NULL, *ol = NULL, *node, *lastol = NULL, *lastel = NULL;
  while (fscanf(f, "%d", &n) == 1) {
    printf("n = %d\n", n);
    node = malloc(sizeof(struct node_t));
    node->num = n;

    if ((n & 0x1) == 0) {
      if (el == NULL) {
        lastel = node;
        /* printf("!!!%p\n", lastel); */
      }
      node->next = el;
      /* printf("node->next = %p\n", node->next); */
      el = node;
    }
    else {
      if (ol == NULL) 
        lastol = node;
      node->next = ol;
      ol = node;
    }
  }
  /* printf("!!!lastel %p\n", el->next->next->next); */
  /* printf("!!! %p\n", ol->next->next->next->next->next->next); */
  if (lastol == NULL)
    return reverse(el);

  assert(lastol->next == NULL);
  lastol->next = el; 
  return reverse(ol);
}

void print_list(const struct node_t* plist)
{
  /* const struct node_t* p; */
  /* for (p = plist; p != NULL; p = p->next) */
  /*   printf("%d ", p->num); */
  /* printf("\n"); */
  for (; plist != NULL; plist = plist->next)
    printf("%d ", plist->num);
  printf("\n");
}

void free_list(struct node_t* plist)
{
  struct node_t* p;
  for (p = plist; p != NULL;) {
    struct node_t* tmp = p->next;
    free(p);
    p = tmp;
  }
}

int main(int argc, char** argv)
{
  struct node_t* result;
  assert(argc == 2);
  FILE* f = fopen(argv[1], "r");
  if (!f) {
    perror("error opening file");
    abort();
  }

  result = read_list_backwards(f);

  print_list(result);
  free_list(result);

  fclose(f);
  return 0;
}
