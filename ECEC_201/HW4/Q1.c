/* Homework 4: Question 1
   Compile with: gcc -std=c89 -o Q1 Q1.c
   Then run your compiled program with: ./Q1


   Write the function definition for function swap() in the file Q1.c so that it swaps the values of the two ints located at the two memory locations passed to it.
   Only modify the function swap().  Do not modify main().
*/

#include <stdio.h>

void swap (int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


int main ()
{
  int x = 27;
  int y = 99;
  
  printf("Before swap:\n");
  printf("  x: %d\n", x);
  printf("  y: %d\n", y);
  
  swap(&x, &y);
  
  printf("After swap:\n");
  printf("  x: %d\n", x);
  printf("  y: %d\n", y);
  
  return 0;
}