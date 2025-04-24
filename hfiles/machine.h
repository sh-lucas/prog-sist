#pragma once

#include <cstdint>
#include <cstdio>
#include <functional>
#include <vector>

typedef struct inst_b {
  uint16_t cmd;
  uint16_t op1;
  uint16_t op2;
  uint16_t op3;
} inst_b;

typedef struct machine {
  inst_b memory[320];
  int pc;
  int ula_out;
  int regs[4];
} machine;

extern std::vector<std::function<void(machine *)>> instruction_set;

extern bool debug_mode;

machine load(FILE *file);