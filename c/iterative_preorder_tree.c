#include <stdio.h>
#include <stdlib.h>

struct node_t
{
  struct node_t* nextl;
  struct node_t* nextr;
  struct node_t* parent; // only for create_tree()
  int num;
};

struct stack_node
{
  struct stack_node* next;
  struct node_t* node;
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

void push(struct stack_node** stack, struct node_t* top) 
{
  struct stack_node* tmp = malloc(sizeof(struct stack_node));
  tmp->next = *stack;
  tmp->node = top;
  *stack = tmp;
}

struct node_t* pop(struct stack_node** stack)
{
  struct stack_node* tmp;
  struct node_t* result = (*stack)->node;
  tmp = (*stack)->next;
  free(*stack);
  *stack = tmp;
  return result;
}

struct node_t* print_tree(struct node_t* top)
{
  struct stack_node* stack = NULL;
  push(&stack, top);
  printf("top of stack contains %d\n", stack->node->num);

  while (stack != NULL) {
    /* int count = 0; */
  /* while (count < 1) { */
    

    top = pop(&stack);
    printf("top after pop = %d\n", top->num);
    if (stack == NULL) {
      printf("top of stack contains NULL\n");
    }
    else {
      printf("top of stack contains %d\n", stack->node->num);
    }
    if (top->nextl == NULL) {
      if (top->nextr == NULL) {
        /* ++count; */
        printf("after %d is NULL\n\n", top->num);
        printf("!!!%d!!!\n", top->num);
        continue;
      }
      push(&stack, top->nextr);
      continue;
    }
    if(top->nextr == NULL) {
      push(&stack, top->nextl);
      continue;
    }
    push(&stack, top->nextr);
    push(&stack, top->nextl);
    printf("after two pushes top of stack contains %d\n\n", stack->node->num);
    
    /* ++count; */
  }
  return top;
}


int main()
{
  /* ! top NEEDS TO BE FREE() ! */
  struct node_t* top;
  top = create_tree(); 
  /* printf("one of node contains %d\n", top->nextl->nextr->nextl->num); */
  top = print_tree(top);
  /* printf("top->num = %d\n", top->num); */
  /* free(top); */


  return 0;
}

