#pragma once

#include <cstdint>
#include <cstdio>
#include <functional>
#include <vector>

typedef struct inst_b {
  uint8_t cmd;
  uint8_t op1;
  uint8_t op2;
  uint8_t op3;
} inst_b;

typedef struct machine {
  inst_b memory[320];
  int pc;
} machine;

extern std::vector<std::function<void(machine *)>> instruction_set;

machine load(FILE *file);