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

void check_reg_index(machine *m, uint8_t index) {
  if (index >= 4) {
    std::cerr << "Error: Invalid register index " << (int)index
              << " at PC=" << m->pc << std::endl;
    std::terminate();
  }
}

void check_mem_index(machine *m, uint16_t index) {
  if (index >= 320) {
    std::cerr << "Error: Invalid memory index " << index << " at PC=" << m->pc
              << std::endl;
    std::terminate();
  }
}

void ADD(machine *m) {
  check_reg_index(m, 0);
  check_reg_index(m, 1);
  check_reg_index(m, 2);
  uint8_t val = m->regs[1] + m->regs[2];
  m->regs[0] = val;
  m->ula_out = val;
  printf("%" PRIu8 " + %" PRIu8 " = %" PRIu8 "\n", m->regs[1], m->regs[2], val);
}

void SUB(machine *m) {
  check_reg_index(m, 0);
  check_reg_index(m, 1);
  check_reg_index(m, 2);
  uint8_t val = m->regs[1] - m->regs[2];
  m->regs[0] = val;
  m->ula_out = val;
}

void MUL(machine *m) {
  check_reg_index(m, 0);
  check_reg_index(m, 1);
  check_reg_index(m, 2);
  uint8_t val = m->regs[1] * m->regs[2];
  m->regs[0] = val;
  m->ula_out = val;
}

void DIV(machine *m) {
  check_reg_index(m, 0);
  check_reg_index(m, 1);
  check_reg_index(m, 2);
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
  check_reg_index(m, line.op1);
  check_mem_index(m, line.op2);
  memcpy(&m->regs[line.op1], &m->memory[line.op2], 4);
}

void ST(machine *m) {
  inst_b line = m->memory[m->pc];
  check_reg_index(m, line.op1);
  check_mem_index(m, line.op2);
  memcpy(&m->memory[line.op2], &m->regs[line.op1], 4);
}

void JMP(machine *m) {
  inst_b line = m->memory[m->pc];
  check_mem_index(m, line.op1);
  m->pc = line.op1 - 1;
}

void JEQ(machine *m) {
  inst_b line = m->memory[m->pc];
  check_reg_index(m, line.op1);
  check_reg_index(m, line.op2);
  check_mem_index(m, line.op3);
  if (m->regs[line.op1] == m->regs[line.op2])
    m->pc = line.op3 - 1;
}

void JGT(machine *m) {
  inst_b line = m->memory[m->pc];
  check_reg_index(m, line.op1);
  check_reg_index(m, line.op2);
  check_mem_index(m, line.op3);
  if (m->regs[line.op1] > m->regs[line.op2])
    m->pc = line.op3 - 1;
}

void JLT(machine *m) {
  inst_b line = m->memory[m->pc];
  check_reg_index(m, line.op1);
  check_reg_index(m, line.op2);
  check_mem_index(m, line.op3);
  if (m->regs[line.op1] < m->regs[line.op2])
    m->pc = line.op3 - 1;
}

void W(machine *m) {
  inst_b line = m->memory[m->pc];
  check_reg_index(m, line.op1);
  printf("output: %" PRIu8 "\n", m->regs[line.op1]);
}

void R(machine *m) {
  inst_b line = m->memory[m->pc];
  check_reg_index(m, line.op1);
  uint8_t input;
  printf("input? ");
  do {
    input = getchar();
  } while (input == '\n' || input == '\r' ||
           input == ' '); // Skip spaces and newlines
  m->regs[line.op1] = input;
}

void STP(machine *m) { std::cout << "STP" << std::endl; }

std::vector<std::function<void(machine *)>> instruction_set = {
    ADD, SUB, MUL, DIV, MV, ST, JMP, JEQ, JGT, JLT, W, R, STP};