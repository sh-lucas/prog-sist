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
  // Pega a "célula" de memória no endereço op1
  inst_b data_cell = m->memory[line.op1];
  // Imprime apenas o primeiro campo, que é onde guardamos o número
  printf("output: %" PRIu16 "\n", data_cell.cmd);
}

void R(machine *m) {
  inst_b line = m->memory[m->pc];
  uint16_t input_val; // Usamos um uint16_t para guardar o valor
  printf("input: ");
  scanf("%" SCNu16, &input_val); // Lemos como um uint16_t

  // Escrevemos o valor lido no primeiro campo da célula de memória
  // Os outros campos (op1, op2, op3) ficarão com lixo, mas não os usamos.
  m->memory[line.op1].cmd = input_val;
}

void STP(machine *m) {
  if (debug_mode)
    std::cout << "STP" << std::endl;
  exit(0);
}

void MVI(machine *m) {
  inst_b line = m->memory[m->pc];
  // Simplesmente copia o valor do operando 2 para o registrador op1
  m->regs[line.op1] = line.op2;
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
  MVI,
};