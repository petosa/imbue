#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  FILE *fp_base;
  FILE *fp_inject;
  FILE *fp_dest;
  unsigned char buffer[2];
  int base_buffer_size = 0;
  int inject_buffer_size = 0;

  if ((fp_base = fopen("base.jpg", "rb")) == NULL) {
    printf("base.jpg is missing. Restore this file and try again.");
    fclose(fp_base);
    exit(1);
  }
  if ((fp_inject = fopen(argv[1], "rb")) == NULL) {
    printf("Error reading in file '%s'. Does it exist?\n", argv[1]);
    fclose(fp_base);
    fclose(fp_inject);
    exit(1);
  }
  fp_dest = fopen("output.jpg", "wb");
  while ((base_buffer_size = fread(buffer, 1, 2, fp_base)) > 0) {
    if (buffer[0] == 0xFF && buffer[1] == 0xD9) { // Ready for injection
      while ((inject_buffer_size = fread(buffer, 1, 2, fp_inject)) > 0) {
        fwrite(buffer, 1, 2, fp_dest);
      }
      buffer[0] = 0xFF;
      buffer[1] = 0xD9;
    }
    fwrite(buffer, 1, 2, fp_dest);
  }
  printf("\nSuccess!\n");
  fclose(fp_base);
  fclose(fp_inject);
  fclose(fp_dest);
  return 0;
}
