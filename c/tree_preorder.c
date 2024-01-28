#include <stdio.h>
#include <stdlib.h>

struct node_t
{
  struct node_t* nextl;
  struct node_t* nextr;
  struct node_t* parent; // only for create_tree()
  int num;
};

struct node_t* create_tree()
{
  struct node_t* top = malloc(sizeof(struct node_t));
  top->parent = NULL;
  struct node_t* nodel, *noder;

  /* for (int i = 0; i < 7) */
  nodel = malloc(sizeof(struct node_t));
  noder = malloc(sizeof(struct node_t));
  top->num = 1;
  top->nextl = nodel; 
  top->nextr = noder; 
  top->nextl->parent = top;
  top->nextr->parent = top;
  top = top->nextl;

  nodel = malloc(sizeof(struct node_t));
  noder = malloc(sizeof(struct node_t));
  top->num = 2;
  top->nextl = nodel;
  top->nextr = noder; 
  top->nextl->parent = top;
  top->nextr->parent = top;
  top = top->nextl;

  top->num = 4;
  top->nextl = NULL;
  top->nextr = NULL; 
  top = top->parent;
  top = top->nextr;

  nodel = malloc(sizeof(struct node_t));
  noder = malloc(sizeof(struct node_t));
  top->num = 5;
  top->nextl = nodel;
  top->nextr = noder; 
  top->nextl->parent = top;
  top->nextr->parent = top;
  top = top->nextl;

  top->num = 6;
  top->nextl = NULL;
  top->nextr = NULL; 
  top = top->parent;
  top = top->nextr;

  top->num = 7;
  top->nextl = NULL;
  top->nextr = NULL; 
  top = top->parent;
  top = top->parent;
  top = top->parent;
  top = top->nextr;

  top->num = 3;
  top->nextl = NULL;
  top->nextr = NULL; 
  top = top->parent;

  return top;
}

struct node_t* delete_tree(struct node_t* top)
{
  if (top == NULL) return NULL;
  if (top->nextl == NULL) return top;
  top->nextl = delete_tree(top->nextl);
  free(top->nextl);
  top->nextr = delete_tree(top->nextr);
  free(top->nextr);
  return top;
}


int main()
{
  /* ! top NEEDS TO BE FREE() ! */
  struct node_t* top;
  top = create_tree(); 
  printf("one of node contains %d\n", top->nextl->nextr->nextl->num);
  top = delete_tree(top);
  printf("top->num = %d\n", top->num);
  free(top);


  return 0;
}
