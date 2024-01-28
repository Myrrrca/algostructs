#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node_t
{
  struct node_t* next;
  int num;
};

struct node_t* reverse(struct node_t* plist)
{
  if (plist == NULL) return NULL;
  if (plist->next == NULL) return plist;

  struct node_t* fst, *snd;
  fst = plist;
  snd = plist->next;
  plist->next = NULL;

  while (snd != NULL) {
    struct node_t* tmp = snd->next;
    snd->next = fst;
    fst = snd;
    snd = tmp;
  }
  return fst;
}

struct node_t* read_list(FILE* f)
{
  int n;
  struct node_t* el = NULL, *ol = NULL, *node, *lastol;
  while (fscanf(f, "%d", &n) == 1)
  {
    node = malloc(sizeof(struct node_t));
    node->num = n;
    if ((n & 1) == 0) {
      node->next = el;
      el = node;
      /* printf("n(even) = %d\n", el->num); */
    }
    else {
      if (ol == NULL)
        lastol = node; 
      node->next = ol;
      ol = node;
      /* printf("n(odd) = %d\n", ol->num); */
    }
  }
  if (ol == NULL)
    return reverse(el);

  assert(lastol->next == NULL);
  lastol->next = el;
  return reverse(ol);
}

void print_list(struct node_t* plist)
{
  for (; plist != NULL; plist = plist->next)
    printf("n = %d\n", plist->num);
  printf("\n");
}

void free_list(struct node_t* plist)
{
  for (; plist != NULL;)
  {
    struct node_t* tmp = plist->next;
    free(plist);
    plist = tmp;
  }
}

int main(int argc, char** argv)
{
  assert(argc == 2);
  FILE* f = fopen(argv[1], "r");
  struct node_t* result;
  
  result = read_list(f); 
  print_list(result);

  free_list(result);
  fclose(f);
  return 0;
}
