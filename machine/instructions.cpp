#include "../hfiles/machine.h"

#include <cstdint>
#include <cstring>
#include <functional>
#include <inttypes.h>
#include <iostream>
#include <vector>

const uint16_t reg0_code = 0;
const uint16_t reg1_code = 0;
const uint16_t reg2_code = 0;
const uint16_t reg3_code = 0;

void ADD(machine *m) {
  uint16_t val = m->regs[1] + m->regs[2];
  m->regs[0] = val;
  m->ula_out = val;

  if (debug_mode) {
    printf("%" PRIu16 " + %" PRIu16 " = %" PRIu16 "\n", m->regs[1], m->regs[2],
           val);
  }
}

void SUB(machine *m) {
  uint16_t val = m->regs[1] - m->regs[2];
  m->regs[0] = val;
  m->ula_out = val;
}

void MUL(machine *m) {
  uint16_t val = m->regs[1] * m->regs[2];
  m->regs[0] = val;
  m->ula_out = val;
}

void DIV(machine *m) {
  if (m->regs[2] != 0) {
    uint16_t val = m->regs[1] / m->regs[2];
    m->regs[0] = val;
    m->ula_out = val;
  } else {
    std::cerr << "Error: Division by zero at PC=" << m->pc << std::endl;
    std::terminate();
  }
}

void MV(machine *m) {
  inst_b line = m->memory[m->pc];
  memcpy(&m->regs[line.op1], &m->memory[line.op2], 4);
}

void ST(machine *m) {
  inst_b line = m->memory[m->pc];
  memcpy(&m->memory[line.op2], &m->regs[line.op1], 4);
}

void JMP(machine *m) {
  inst_b line = m->memory[m->pc];
  m->pc = line.op1 - 1;
}

void JEQ(machine *m) {
  inst_b line = m->memory[m->pc];
  if (m->regs[line.op1] == m->regs[line.op2])
    m->pc = line.op3 - 1;
}

void JGT(machine *m) {
  inst_b line = m->memory[m->pc];
  if (m->regs[line.op1] > m->regs[line.op2])
    m->pc = line.op3 - 1;
}

void JLT(machine *m) {
  inst_b line = m->memory[m->pc];
  if (m->regs[line.op1] < m->regs[line.op2])
    m->pc = line.op3 - 1;
}

void W(machine *m) {
  inst_b line = m->memory[m->pc];
  int *cvrt = (int *)&m->memory[line.op1];
  printf("output: %u\n", *cvrt);
}

void R(machine *m) {
  inst_b line = m->memory[m->pc];
  uint16_t input;
  printf("input: ");
  int num = 0;
  scanf("%d", &num);
  inst_b *cvrt = (inst_b *)&num;
  m->memory[line.op1] = *cvrt;
}

void STP(machine *m) {
  if (debug_mode)
    std::cout << "STP" << std::endl;
}

// é um mapa que associa o índice à função da instrução
// clang-format off
std::vector<std::function<void(machine *)>> instruction_set = {
  ADD,
  SUB,
  MUL,
  DIV,
  MV,
  ST,
  JMP,
  JEQ,
  JGT,
  JLT,
  W,
  R,
  STP,
};