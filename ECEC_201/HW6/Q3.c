/* Homework 6: Question 3
   Compile with: gcc -std=c89 -o Q3 Q3.c
   Then run your compiled program with: ./Q3
*/
#include <stdlib.h>
#include <stdio.h>

struct list {
  int val;
  struct list *next;
};

/* from Lecture 6 */
void list_add_head(struct list **head, struct list *item)
{
  item->next = *head;
  *head = item;
}

/* from Lecture 6 (just for your reference) */
struct list *list_pop_head(struct list **head)
{
  struct list *cur;

  cur = *head;
  if (cur) {
    *head = cur->next;
    cur->next = NULL;
  }

  return cur;
}

/* you write this one! */
int list_count(struct list *head){
  struct list *current = head;
  int count = 0;

while(head->next != NULL){
    count++;
    head = head->next;}
    return count;
}

/* you write this one! */
struct list *list_pop_tail(struct list **head)
{/*intialize it*/
  struct list *current = *head;
  struct list *prev = NULL;
  if (current == NULL) {
    return NULL;
  }

  /* iterates over the list to tail*/
  while (current-> next != NULL) {
    prev = current; /* update the 'prev' pointer */
    current = current-> next; /* 'cur' pointer to the next item in the list */
  }

  /* when it exits the while loop, 'cur' points to the last item in the list */
  if (prev != NULL) {
    prev -> next = NULL;
  }
  else {
    *head = NULL; /*set the head pointer to NULL if the last item is also the first item in the list */
  }
  return current;
}


int main()
{
  int i;
  struct list *item;
  struct list *head = NULL;

  /* load up the list with ten items */
  for (i=0; i<10; i++) {
    item = malloc(sizeof(*item));
    item->val = i;
    list_add_head(&head, item);
    printf("Added %p (val: %d) to list.\n", item, item->val);
  }

  printf("# of items: %d\n", list_count(head));

  /* remove each item and print its value */
  while (item = list_pop_tail(&head)) {
    printf("Removed %p (val: %d)\n", item, item->val);
    free(item);
  }

  return 0;
}