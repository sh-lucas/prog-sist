#include "../hfiles/machine.h"

#include <cstdint>
#include <cstring>
#include <functional>
#include <inttypes.h>
#include <iostream>
#include <vector>

const uint8_t reg0_code = 0;
const uint8_t reg1_code = 0;
const uint8_t reg2_code = 0;
const uint8_t reg3_code = 0;

void ADD(machine *m) {
  uint8_t val = m->regs[1] + m->regs[2];
  m->regs[0] = val;
  m->ula_out = val;

  if (debug_mode) {
    printf("%" PRIu8 " + %" PRIu8 " = %" PRIu8 "\n", m->regs[1], m->regs[2],
           val);
  }
}

void SUB(machine *m) {
  uint8_t val = m->regs[1] - m->regs[2];
  m->regs[0] = val;
  m->ula_out = val;
}

void MUL(machine *m) {
  uint8_t val = m->regs[1] * m->regs[2];
  m->regs[0] = val;
  m->ula_out = val;
}

void DIV(machine *m) {
  if (m->regs[2] != 0) {
    uint8_t val = m->regs[1] / m->regs[2];
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
  printf("output: %" PRIu8 "\n", m->regs[line.op1]);
}

void R(machine *m) {
  inst_b line = m->memory[m->pc];
  uint8_t input;
  printf("input: ");
  int num = 0;
  scanf("%d", &num);
  m->regs[line.op1] = static_cast<uint8_t>(num);
}

void STP(machine *m) {
  if (debug_mode)
    std::cout << "STP" << std::endl;
}

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