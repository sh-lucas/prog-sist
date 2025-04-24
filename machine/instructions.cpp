#include "../hfiles/machine.h"

#include <cstdint>
#include <cstring>
#include <functional>
#include <vector>

#include <iostream>

const uint8_t reg0_code = 0;
const uint8_t reg1_code = 0;
const uint8_t reg2_code = 0;
const uint8_t reg3_code = 0;

// add                a0 = a1 + a2;
// sub                a0 = a1 - a2;
// mul                a0 = a1 * a2;
// div                a0 = a1 / a2;
// mv  op1 op2        regs[op1] = mem[op2];
// st  op1 op2        mem[op1] = regs[op2];
// jmp op1            pc = op1;
// jeq op1 op2 op3    op1 == op2 --> pc = op3;
// jgt op1 op2 op3    op1 > op2  --> pc = op3;
// jlt op1 op2 op3    op1 < op2  --> pc = op3;
// w   op1            prints regs[op1] to cout;
// r   op1            reads cin to regs[op1];
// stp                stops the machine;

void ADD(machine *m) {
  /* ADD operation */
  uint8_t val = m->regs[1] + m->regs[2];
  m->regs[0] = val;
  m->ula_out = val;
}

void SUB(machine *m) {
  /* SUB operation */
  uint8_t val = m->regs[1] - m->regs[2];
  m->regs[0] = val;
  m->ula_out = val;
}

void MUL(machine *m) {
  /* MUL operation */
  uint8_t val = m->regs[1] * m->regs[2];
  m->regs[0] = val;
  m->ula_out = val;
}

void DIV(machine *m) {
  /* DIV operation */
  if (m->regs[2] != 0) {
    uint8_t val = m->regs[1] / m->regs[2];
    m->regs[0] = val;
    m->ula_out = val;
  } else {
    std::cerr << "Error: Division by zero" << std::endl;
  }
}

// mv reg <- mem
void MV(machine *m) {
  // pega a posição da memória apontada por op2 e
  // coloca dentro do registrador indexado por op1
  inst_b line = m->memory[m->pc];
  // breaks if I change the type from uint8_t.
  memcpy(&m->regs[line.op1], &m->memory[line.op2], 4);
}

// st mem <- reg
void ST(machine *m) {
  // pega o valor do registrador indexado por op1 e
  // coloca na posição da memória apontada por op2
  inst_b line = m->memory[m->pc];
  memcpy(&m->memory[line.op2], &m->regs[line.op1], 4);
}

// jmp op
void JMP(machine *m) {
  /* JMP operation */
  inst_b line = m->memory[m->pc];
  m->pc = line.op1 - 1;
  // -1 por que ao final dessa instrução vai acontecer um ++
}

// jeq reg1 reg2 op
void JEQ(machine *m) {
  /* JEQ operation */
  inst_b line = m->memory[m->pc];
  if (m->regs[line.op1] == m->regs[line.op2])
    m->pc = line.op1 - 1;
}

// jgt reg1 reg2 op
void JGT(machine *m) {
  /* JGT operation */
  inst_b line = m->memory[m->pc];
  if (m->regs[line.op1] > m->regs[line.op2])
    m->pc = line.op1 - 1;
}

// jlt reg1 reg2 op
void JLT(machine *m) {
  /* JLT operation */
  inst_b line = m->memory[m->pc];
  if (m->regs[line.op1] < m->regs[line.op2])
    m->pc = line.op1 - 1;
}

// w reg1
void W(machine *m) {
  /* W operation */
  inst_b line = m->memory[m->pc];
  printf("%c", m->regs[line.op1]);
}

// r reg1 (reads from cin into reg1)
void R(machine *m) {
  /* R operation */
  inst_b line = m->memory[m->pc];
  scanf("%d", &m->regs[line.op1]);
}

void STP(machine *m) {
  /* STP operation */
  std::cout << "STP" << std::endl;
}

std::vector<std::function<void(machine *)>> instruction_set = {
    ADD, SUB, MUL, DIV, MV, ST, JMP, JEQ, JGT, JLT, W, R, STP};