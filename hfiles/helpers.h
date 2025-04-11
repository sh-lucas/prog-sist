#pragma once

#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

string str_trim(string str);

typedef struct {
  uint8_t cmd;
  uint8_t op1;
  uint8_t op2;
  uint8_t op3;
  bool empty;
} instruction;

bool next_op(FILE *file, instruction *inst);