#pragma once

#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

string str_trim(string str);

typedef struct {
  uint16_t cmd;
  uint16_t op1;
  uint16_t op2;
  uint16_t op3;
  bool empty;
} instruction;

bool next_op(FILE *file, instruction *inst);