#include <stdio.h>
#include "strlib.h"

int my_strlen (const char *str){
    int i=0;
    while (str[i] != '\0')
        i++;
    return i;
}



int my_strcmp (const char *str1, const char *str2){
int i = 0;
    while (str1[i] == str2[i]) {
        /*while they are same, check the next ith element of str1 and str2*/
        if (str1[i] == '\0') {
            /*if str1 ends, return*/
            return 0;
        }
        i++;
    }
    /*the first two non-matching characters have been found, we subtract*/
    return (int) str1[i] - (int) str2[i];
}
