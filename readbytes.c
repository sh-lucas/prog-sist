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

  uint16_t word; // 16-bit value
  int count = 0;
  while (fread(&word, sizeof(uint16_t), 1, file) == 1) {
    printf("%u\t", word); // Print 16-bit value as unsigned integer
    if (++count % 4 == 0)
      printf("\n");
  }

  fclose(file);
  return 0;
}