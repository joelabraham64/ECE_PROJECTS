#include <stdio.h>

int main() {
    FILE *file;
    FILE *output;
    char character;
    int counter = 0, line_num = 1;

    output = fopen("counts.txt", "w");
    file = fopen("lorum.txt", "r");


    do {
        character = fgetc(file);  // Read a character from the file

        
            // Process the character as needed
            if (character == '\n' || character == EOF) {
                fprintf(output, "%d:%d\n", line_num, counter);
                line_num++;
                counter = 0;
                
            } else {
                counter++;
            }
        
    } while (character != EOF);

    /*Close the file*/
    fclose(file);
    fclose(output);

    return 0;
}
