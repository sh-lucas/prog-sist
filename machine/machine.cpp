#include "../hfiles/machine.h"
#include "../hfiles/consts.h"
#include <cstdio>
#include <cstdlib>
#include <inttypes.h>
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
    line = machine.memory[machine.pc];

    printf("cmd: %" PRIu8, line.cmd);
    printf("\top1: %" PRIu8, line.op1);
    printf("\top2: %" PRIu8, line.op2);
    printf("\top3: %" PRIu8, line.op3);

    printf("\t|\treg0: %" PRIu8, machine.regs[0]);
    printf("\treg1: %" PRIu8, machine.regs[1]);
    printf("\treg2: %" PRIu8, machine.regs[2]);
    printf("\treg3: %" PRIu8 "\n", machine.regs[3]);

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
