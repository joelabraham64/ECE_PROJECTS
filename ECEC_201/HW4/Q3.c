/* Homework 4: Question 3
   Compile with: gcc -std=c89 -o Q3 Q3.c
   Then run your compiled program with: ./Q3
    In the file Q3.c, rewrite the function zero_array() to use pointers instead of array indexing.  When you are done, the function 
    should still perform the same function -- setting all elements of the array to zero..
    In other words, completely eliminate the variable i and all uses of the [ ] operator.
    Only modify zero_array().  Do not modify main() or print_contents().
    
    Tips:
        -- You will still need one local variable, but it will be a pointer.
        -- You will still use the for-loop, but the initializer, stopping condition, and update will all change.
        -- The body of the loop will also change, but it will still only be one line.

*/

#include <stdio.h>

void zero_array (int *a, int n)
{
  /* Only modify this function */
  int *i = a;
  
  for (; i<a+n; i++)
    *i = 0;
}




void print_contents (int *a, int n)
{
  int i;
  
  for (i=0; i<n; i++) {
    printf("%2d ", a[i]);
    
    if (!((i+1) % 7))
      printf("\n");
  }
}


int main ()
{
  int numbers[] = {10,  1, 54,  8, 78, 13,  4,
                   32, 72, 13, 43, 66, 42, 21,
                   41, 87, 23, 11, 52,  7,  2,
                    3, 33,  5,  9, 67, 12, 17};
  
  int n = sizeof(numbers)/sizeof(int);
  
  printf("Contents of numbers[] BEFORE:\n");
  print_contents(numbers, n);
  
  zero_array(numbers, n);
  
  printf("\nContents of numbers[] AFTER:\n");
  print_contents(numbers, n);
    
  return 0;
}