#include <stdio.h>
#include "mymath.h"

#define ELEMENTS 100

int main()
{
	  unsigned int i;
	  unsigned long int fibs[ELEMENTS];
	  unsigned int n = ELEMENTS;

	  compute_fibs (fibs, &n);
	  for (i=0; i<n; i++)
	      printf ("fibs[%u]: %lu\n", i, fibs[i]);

	  printf ("Displaying %u fibs\n", n);
		      
		      return 0;
}
