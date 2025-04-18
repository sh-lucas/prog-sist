#include "../hfiles/machine.h"
#include <cstdio>
#include <iostream>

using namespace std;

void printBinaryLine(inst_b *buffer) {
  printf("%d ", buffer->cmd);
  printf("%d ", buffer->op1);
  printf("%d ", buffer->op2);
  printf("%d", buffer->op3);
  cout << endl;
}

machine load(FILE *file) {
  machine machine = {0};
  for (int i = 0; i < 320; i++) {
    machine.memory[i] = {
        0, 0, 0, 0}; // Assuming inst_b has four fields: cmd, op1, op2, op3
  }
  machine.pc = 0;

  int stack_ptr = 0;

  uint32_t buffer;
  while (fread(&buffer, sizeof(uint32_t), 1, file)) {
    inst_b *inst = (inst_b *)&buffer;

    machine.memory[stack_ptr].cmd = inst->cmd;
    machine.memory[stack_ptr].op1 = inst->op1;
    machine.memory[stack_ptr].op2 = inst->op2;
    machine.memory[stack_ptr].op3 = inst->op3;
    stack_ptr++;
  }

  return machine;
}