#include <stdlib.h>
#include <stdio.h>

struct queue {
  int val;
  struct queue *next;
};

void enqueue(struct queue **Q, struct queue *item) {
  if (*Q == NULL) {
    *Q = item;
    item->next = NULL;
  } else {
    struct queue *tail = *Q;
    while (tail->next != NULL) {
      tail = tail->next;
    }
    tail->next = item;
    item->next = NULL;
  }
}


struct queue*dequeue(struct queue**Q){
  if (*Q == NULL)
  return NULL;
  else{
    struct queue *item = *Q;
    *Q = (*Q)->next;
    return item;
  }
}



int main(int argc, char **argv)
{
  int i, num_items;
  struct queue *Q = NULL;
  struct queue *item;

  if (argc != 2) {
    printf("Usage: %s queue_size\n", argv[0]);
    return 0;
  }

  /* atoi() converts a string to an integer */
  num_items = atoi(argv[1]);

  /* load the queue with items: 0, 1, 2, 3, ... */
  for (i=0; i<num_items; i++) {
    item = malloc(sizeof(*item));

    if (!item) {
      printf("Failed to malloc() item! Exiting...\n");
      return EXIT_FAILURE;
    }

    item->val = i;
    enqueue(&Q, item);
  }

  /* unload the queue and print the value of each item */
  while (item = dequeue(&Q)) {
    printf("%d\n", item->val);
    free(item);
  }

  return 0;
}
