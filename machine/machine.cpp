#include <cstdint>
#include <cstdio>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Argumentos inválidos. O programa aceita o caminho de um único "
           "arquivo.");
    exit(1);
  }

  char *filename = argv[1];

  FILE *bin = fopen(filename, "r");

  uint8_t buffer;
  int line_break_at = 4, i = 0;
  while (fread(&buffer, sizeof(uint8_t), 1, bin)) {
    printf("%d ", buffer);
    if (++i == line_break_at) {
      i = 0;
      printf("\n");
    }
  }
}