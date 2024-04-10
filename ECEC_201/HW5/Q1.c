/* Homework 5: Question 1
   Compile with: gcc -std=c89 -o Q1 Q1.c
   Then run your compiled program with: ./Q1
*/

#include <stdio.h>


int g(int val)
{
  return val * val;
}


int sum(int (*g)(int), int i, int j){
  int k = 0;
  if(i<j){
    for(i; i<=j; i++)
      k += (*g)(i);
      return k;
  }
 

  if(i==j)
  return (*g)(i) + (*g)(j);

  if(i>j)
  return 0;

}


int main()
{
  printf("Result: %d\n", sum(g, 10, 20));

  return 0;
}