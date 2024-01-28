#include <stdio.h>
#include <stdlib.h>

struct node_t
{
  struct node_t* next;
  int num;
};

void printarr(int* arr, int size) 
{
  printf("arr = ");
  for (int i = 0; i < size; ++i)
    printf("%d ", arr[i]);
  printf("\n");
}

int find_max(int* arr, int size)
{
  int max = arr[0];
  for (int i = 1; i < size; ++i)
    if (arr[i] > max)
      max = arr[i];
  return max;
}

struct node_t** read_arr(int* arr, unsigned size)
{
  /* struct node_t* mlist[size]; */
  struct node_t** mlist = malloc(sizeof(struct node_t) * size);
  for (int i = 0; i < size; ++i) {
    mlist[i] = malloc(sizeof(struct node_t));
    mlist[i]->next = NULL;
    mlist[i]->num = 0;
  }

  int max = find_max(arr, size);
  int bucket_size = max / size;
  printf("size of one bucket = %d\n", bucket_size);

  struct node_t* node;
  int tmp_bsize = bucket_size;
  for (int i = 0, bcount = 0; i < size; ++i) {
    node = malloc(sizeof(struct node_t));
    while (arr[i] > tmp_bsize) {
      tmp_bsize += bucket_size;
      ++tmp_bsize;
      ++bcount;
    }
    /* printf("bucket_num is %d(%d - %d) for %d element\n", bcount, tmp_bsize - bucket_size, tmp_bsize, arr[i]); */
    tmp_bsize = bucket_size;

    node->next = mlist[bcount];
    node->num = arr[i];

    struct node_t* orignode;
    orignode = node;

    for (; arr[i] > node->next->num; node = node->next) {
      if (node->next->next == NULL)
        break;
    }

    if (node->next->next == NULL && node == orignode) {
      mlist[bcount] = node; 
    }
    else if (node->next->next == NULL) {
      orignode->next = node->next;
      node->next = orignode;
    }
    else {
      mlist[bcount] = node; 
    }

    /* printf("now %d stored in mlist[%d]\n\n", mlist[bcount]->num, bcount); */
    bcount = 0;
  }
  /* printf("mlist[1] = %d -> %d\n", mlist[1]->num, mlist[1]->next->num); */
  /* printf("mlist[4] = %d -> %d -> %d -> %d\n", mlist[4]->num, mlist[4]->next->num, mlist[4]->next->next->num, mlist[4]->next->next->next->num); */
  return mlist;
}

void print_list(struct node_t** mlist, unsigned size)
{
  struct node_t** tmp = mlist;
  for (unsigned i = 0; i < size; ++i) {
    for (; tmp[i] != NULL; tmp[i] = tmp[i]->next)
    printf("%d ", tmp[i]->num);
    /* for (; mlist[i]->next != NULL; mlist[i] = mlist[i]->next) { */
    /*   printf("%d ", mlist[i]->num); */
    /* } */
    /* printf("0 "); */
  }
  printf("\n");
}

int main()
{
  int arr[] = {126, 348, 343, 432, 316, 171, 556, 670};
  /* int arr[] = {10, 187, 329, 731, 517, 71, 468, 429, 237, 621, 860}; */
  unsigned size = sizeof(arr) / sizeof(arr[0]);
  struct node_t** result;

  printarr(arr, size);
  result = read_arr(arr, size);
  /* printf("%d\n", result[0]->num); */
  print_list(result, size);

  return 0; 
}
