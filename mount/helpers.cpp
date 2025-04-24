#include "../hfiles/consts.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

string str_trim(string str) {
  while (!str.empty() &&
         (str.back() == '\n' || str.back() == '\r' || isspace(str.back())))
    str.pop_back();
  while (!str.empty() && isspace(str.front()))
    str.erase(0, 1);
  return str;
}

typedef struct {
  uint8_t cmd;
  uint8_t op1;
  uint8_t op2;
  uint8_t op3;
  bool empty;
} instruction;

extern const unordered_map<string, uint8_t> instruction_map;

bool next_op(FILE *file, instruction *inst) {
  inst->empty = false;
  inst->cmd = 0;
  inst->op1 = 0;
  inst->op2 = 0;
  inst->op3 = 0;

  char buffer[100];
  if (!fgets(buffer, sizeof(buffer), file)) {
    inst->empty = true;
    return false;
  }

  string line = str_trim(string(buffer));
  if (line.empty() || line[0] == '#') {
    inst->empty = true;
    return true;
  }

  stringstream ss(line);
  string command;
  ss >> command;

  auto it = instruction_map.find(command);
  if (it == instruction_map.end()) {
    inst->empty = true;
    return true;
  }

  inst->cmd = it->second;

  string token;
  int count = 0;
  while (ss >> token && count < 3) {
    uint8_t val = atoi(token.c_str());
    if (count == 0)
      inst->op1 = val;
    else if (count == 1)
      inst->op2 = val;
    else if (count == 2)
      inst->op3 = val;
    count++;
  }

  // valores que não foram lidos permanecem zero
  return true;
}