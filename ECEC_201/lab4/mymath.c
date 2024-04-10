#include <stdio.h>
#include <limits.h>

int compute_fibs (unsigned long int *fibs, unsigned int *N){
    int i;
    *fibs = 0;
    *(fibs+1) = 1;
    for (i = 2; i<*N; N++)
    {
        if ((ULONG_MAX - *(fibs+i-2)) < *(fibs+i-1))
            *N=i;
        *(fibs+i)  = *(fibs+i-1) + *(fibs+i-1);
    }

    return 0;
}

   
