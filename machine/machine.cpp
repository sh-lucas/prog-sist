#include "../hfiles/machine.h"
#include "../hfiles/consts.h"
#include <cstdio>
#include <cstdlib>
#include <inttypes.h>
#include <iostream>

using namespace std;

bool debug_mode = false;

int main(int argc, char *argv[]) {
  // validação de erros
  if (argc > 3 || argc < 2) {
    printf("Argumentos inválidos. O programa aceita o caminho de um único "
           "arquivo.");
    exit(1);
  }

  debug_mode = (argc == 3 && string(argv[2]) == "-db");

  char *filename = argv[1];

  FILE *bin = fopen(filename, "r");

  machine machine = load(bin);
  inst_b line;
  while (line.cmd != STP) {
    line = machine.memory[machine.pc];

    // modo debug
    if (debug_mode) {
      printf("cmd: %" PRIu16, line.cmd);
      printf("\top1: %" PRIu16, line.op1);
      printf("\top2: %" PRIu16, line.op2);
      printf("\top3: %" PRIu16, line.op3);

      printf("\t|\treg0: %" PRIu16, machine.regs[0]);
      printf("\treg1: %" PRIu16, machine.regs[1]);
      printf("\treg2: %" PRIu16, machine.regs[2]);
      printf("\treg3: %" PRIu16 "\n", machine.regs[3]);
    }

    if (instruction_set[line.cmd]) {
      instruction_set[line.cmd](&machine);
    } else {
      cout << "Error! Invalid command at instruction section. \nLine number: "
           << machine.pc << endl;
      exit(1);
    }
    machine.pc++;
  }
}
