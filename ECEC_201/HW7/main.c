#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


/* prints a line of 10 bytes (max) in hex with a space between each byte */
void print_bytes_hex(unsigned char *b, unsigned int nbytes)
{
  FILE *file;
  unsigned char data[10];
  char *fn = "test.dat";
  file = fopen(fn, "rb");
  int i = 0, offset = 0;

  while ((fread(data, 1, sizeof(data), file)) > 0) {
    printf("%6d  ", offset);
    for (i = 0; i < sizeof(data); i++)
    printf("%02x ", data[i]);
    printf(" ");

    for (i = nbytes; i < sizeof(data); i++)
      printf("   ");
    offset += nbytes;
    fseek(file, offset, SEEK_SET);
    for (i = 0; i < sizeof(data); i++) {
      unsigned char c = data[i];
      if (!isprint(c))
        c = '.';
      printf("%c", c);
    }
    printf("\n");
  }

  fclose(file);
}

/* prints a line of 10 bytes (max) in as characters.
 * non-printable bytes are printed as the period character. */
void print_bytes_char(unsigned char *b, unsigned int nbytes)
{
  FILE *file;
  unsigned char data[10];
  file = fopen("test.dat", "rb");
  int i = 0, offset = 0;

  while ((fread(data, 1, sizeof(data), file)) > 0) {
    printf("%6d  ", offset);
    for (i; i < sizeof(data); i++) {
      if (isprint(data[i]))
        printf("%c", data[i]);
      else
        printf(".");
    }
    printf("\n");
    offset += nbytes;
  }

  fclose(file);
}


int main()
{
  /* Your code goes here */
  FILE *file;
  char character; 
  file = fopen("test.dat", "rb");
  if (!file) {
    return fprintf(stderr, "Failed to open file");
  }
  unsigned char bytes[10];
  unsigned int nBytes = sizeof(bytes) / sizeof(bytes[0]);



  printf("Offset              Bytes              Characters\n");
  printf("------  -----------------------------  ----------\n");

  print_bytes_hex(bytes,nBytes);

  fclose(file);

  return 0;
}