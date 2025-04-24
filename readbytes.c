#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  printf("cmd \top1 \top2 \top3\n");
  printf("--------------------------------\n");

  if (argc < 2) {
    fprintf(stderr, "Usage: %s <binary_file>\n", argv[0]);
    return 1;
  }

  FILE *file = fopen(argv[1], "rb");
  if (!file) {
    perror("fopen");
    return 1;
  }

  uint8_t byte;
  int count = 0;
  while (fread(&byte, sizeof(uint8_t), 1, file) == 1) {
    printf("%u\t", byte);
    if (++count % 4 == 0)
      printf("\n");
  }

  fclose(file);
  return 0;
}