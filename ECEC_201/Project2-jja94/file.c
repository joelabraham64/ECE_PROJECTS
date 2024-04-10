#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct parms {
  char *filename;
  unsigned char mode;
};

typedef struct parms Parms;

void print_usage(const char *cmd);
int get_parms(Parms *parms, const char *modes, int argc, char **argv);
char *filename_add_ext(const char *filename, const char *ext);
char *filename_rm_ext(const char *filename);
int check_ext(const char *filename);
int check_magic(FILE *fp);
void compress(const char *filename);
void expand(const char *filename);
void debug(const char *filename);
void generate(const char *filename);

int main(int argc, char **argv)
{
  Parms parms;
  void (*action[])(const char *filename) = {
    compress,
    expand,
    debug,
    generate
  };

  if(!get_parms(&parms, "cxdg", argc, argv)) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  action[parms.mode](parms.filename);

  return 0;
}

void print_usage(const char *cmd) {
  // Existing implementation...
}

int get_parms(Parms *parms, const char *modes, int argc, char **argv) {
  // Existing implementation...
}

char *filename_add_ext(const char *filename, const char *ext) {
  // Existing implementation...
}

char *filename_rm_ext(const char *filename) {
  // Existing implementation...
}

int check_ext(const char *filename) {
  // Existing implementation...
}

int check_magic(FILE *fp) {
  // Existing implementation...
}

void compress(const char *filename) {
  FILE *input = fopen(filename, "rb");
  if (!input) {
    fprintf(stderr, "Failed to open input file: %s\n", filename);
    return;
  }

  char *outputFilename = filename_add_ext(filename, ".rle");
  FILE *output = fopen(outputFilename, "wb");
  free(outputFilename);

  if (!output) {
    fprintf(stderr, "Failed to create output file: %s.rle\n", filename);
    fclose(input);
    return;
  }

  unsigned char magic[] = {0x21, 0x52, 0x4c, 0x45};
  fwrite(magic, sizeof(unsigned char), 4, output);

  unsigned char current, next;
  int count = 1;
  fread(&current, sizeof(unsigned char), 1, input);

  while (fread(&next, sizeof(unsigned char), 1, input) > 0) {
    if (next == current && count < 255) {
      count++;
    } else {
      fwrite(&count, sizeof(unsigned char), 1, output);
      fwrite(&current, sizeof(unsigned char), 1, output);
      current = next;
      count = 1;
    }
  }

  fwrite(&count, sizeof(unsigned char), 1, output);
  fwrite(&current, sizeof(unsigned char), 1, output);

  fclose(input);
  fclose(output);

  printf("File %s has been compressed as %s.rle\n", filename, filename);
}

void expand(const char *filename) {
  if (!check_ext(filename)) {
    fprintf(stderr, "Invalid file extension. The file must have the '.rle' extension.\n");
    return;
  }

  FILE *input = fopen(filename, "rb");
  if (!input) {
    fprintf(stderr, "Failed to open input file '%s'.\n", filename);
    return;
  }

  if (!check_magic(input)) {
    fprintf(stderr, "Invalid file format. The input file does not have the expected magic byte sequence.\n");
    fclose(input);
    return;
  }

  char *newFilename = filename_rm_ext(filename);
  FILE *output = fopen(newFilename, "wb");
  free(newFilename);

  if (!output) {
    fprintf(stderr, "Failed to create output file '%s'.\n", newFilename);
    fclose(input);
    return;
  }

  unsigned char count, value;
  while (fread(&count, sizeof(unsigned char), 1, input) == 1 &&
         fread(&value, sizeof(unsigned char), 1, input) == 1) {
    for (int i = 0; i < count; i++) {
      fwrite(&value, sizeof(unsigned char), 1, output);
    }
  }

  fclose(input);
  fclose(output);
}

void debug(const char *filename) {
  // Existing implementation
}