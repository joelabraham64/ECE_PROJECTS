/* Homework 6: Question 2
   Compile with: gcc -std=c89 -o Q2 Q2.c
   Then run your compiled program with: ./Q2
*/
#include <stdlib.h>
#include <stdio.h>

#define ELEMENTS 8

int *create_array(int n, int initial_value) {
  int *arr = NULL;
  int i;
  arr = (int *) malloc(n * sizeof(int)); /*allocate memory for n ints*/
  if(arr == NULL) { /*if memory allocation fails*/
    return NULL; /* return NULL pointer*/
  }

  for(i = 0; i < n; i++) {
    arr[i] = initial_value; /*initialize each element with the initial_value*/
  }
  return arr; /*return the pointer to the allocated memory*/
}


int main()
{
  int i;
  int *foo;

  foo = create_array(ELEMENTS, 79);

  if (foo)
    for (i=0; i<ELEMENTS; i++)    
      printf("%d: %d\n", i, foo[i]);

  free(foo);

  return 0;
}