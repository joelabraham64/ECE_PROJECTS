/*gcc -std=c89 -o main main.c*/

#include <stdio.h>

int main() {
    FILE *file;
    FILE *output;
    char character;
    int counter = 0, line_num = 1;
    
    output = fopen("count.txt", "w");
    file = fopen("lorum.txt", "r");


    /*Read and process each character*/
    while ((character = fgetc(file)) != EOF) {
        /*Process the character as needed*/
        if(character != '\n'){
            counter++;
        }  /*Replace this with your desired operation*/
        else{
            fprintf(output, "%d:%d\n", line_num, counter);
            line_num++;
            counter = 0;
        }
    }
        if (counter > 0) {
        fprintf(output, "%d:%d\n", line_num, counter);
        }

    /*Close the file*/
    fclose(file);
    fclose(output);


    return 0;
}
