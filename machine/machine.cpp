#include "../hfiles/machine.h"
#include "../hfiles/consts.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Argumentos inválidos. O programa aceita o caminho de um único "
           "arquivo.");
    exit(1);
  }

  char *filename = argv[1];

  FILE *bin = fopen(filename, "r");

  machine machine = load(bin);
  inst_b line;
  while (line.cmd != STP) {
    if (instruction_set[line.cmd]) {
      instruction_set[line.cmd](&machine);
    } else {
      cout << "Error! Invalid command at instruction section. \nLine number: "
           << machine.pc << endl;
      exit(1);
    }
    line = machine.memory[machine.pc++];
  }
}
