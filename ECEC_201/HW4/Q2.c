/* Homework 4: Question 2
   Compile with: gcc -std=c89 -o Q2 Q2.c
   Then run your compiled program with: ./Q2

    In the file Q2.c, write the function definition for the function find_largest().
    The function find_largest() accepts two parameters:
    1. A pointer to an array of ints
    2. The number of elements in the array
    
    Your function should return the address of the largest element in the array passed to it.
    Do not modify the array (i.e. do not sort it, reorder it, etc).
    Only modify find_largest().  Do not modify main().
*/

#include <stdio.h>

int *find_largest (int *a, int n)
{
    int i = 0;
    int *largest = &a[0];

    for(i; i < n; i++){
        if(*largest < a[i])
        largest = &a[i];
    }

    return largest;
}


int main ()
{
  int *largest;
  
  int numbers[] = {10,  1, 54,  8, 78, 13,  4,
                   32, 72, 13, 43, 66, 42, 21,
                   41, 87, 23, 11, 52,  7,  2,
                    3, 33,  5,  9, 67, 12, 17};

  int n = sizeof(numbers)/sizeof(int);
  
  largest = find_largest(numbers, n);
  
  printf("Of the %d numbers passed,\n", n);
  printf("%d was the largest\n", *largest);
  
  return 0;
}