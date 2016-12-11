#include <stdio.h>
#include <stdlib.h>

void pipe_out(FILE *fp_from, FILE *fp_to);
void pipe_short(unsigned short num, FILE *fp_to);

int main(int argc, char *argv[]) {

  FILE *fp_base;
  FILE *fp_inject;
  FILE *fp_dest;

  fp_dest = fopen("output.jpg", "wb");

  // Pipe in part 1 of jpg, up to size
  if ((fp_base = fopen("part1.jpg", "rb")) == NULL) {
    printf("part1.jpg is missing. Restore this file and try again.\n");
    exit(1);
  }
  pipe_out(fp_base, fp_dest);
  fclose(fp_base);

  // Pipe in height
  pipe_short((short)16, fp_dest);

  // Pipe in a width
  pipe_short((short)16, fp_dest);

  // Pipe in part 2 of jpg, up to data
  if ((fp_base = fopen("part2.jpg", "rb")) == NULL) {
    printf("part2.jpg is missing. Restore this file and try again.\n");
    exit(1);
  }
  pipe_out(fp_base, fp_dest);
  fclose(fp_base);

  // Inject
  if ((fp_inject = fopen(argv[1], "rb")) == NULL) {
    printf("%s can't be found.\n", argv[1]);
    exit(1);
  }
  pipe_out(fp_inject, fp_dest);
  fclose(fp_inject);

  if ((fp_base = fopen("part3.jpg", "rb")) == NULL) {
    printf("part3.jpg is missing. Restore this file and try again.\n");
    exit(1);
  }
  pipe_out(fp_base, fp_dest);
  fclose(fp_base);

  fclose(fp_dest);
  printf("Success!\n");

  return 0;
}

void pipe_out(FILE *fp_from, FILE *fp_to) {
  unsigned char buffer[2];
  int base_buffer_size = 0;
  while ((base_buffer_size = fread(buffer, 1, 2, fp_from)) > 0) {
    if (base_buffer_size == 2) {
      fwrite(buffer, 1, 2, fp_to);
    } else {
      fwrite(buffer, 1, 1, fp_to);
    }
  }
}

void pipe_short(unsigned short num, FILE *fp_to) {
  unsigned char buffer[2];
  buffer[0] = (char) (num >> 8);
  buffer[1] = (char) (num & 0x00FF);
  fwrite(buffer, 1, 2, fp_to);
}
