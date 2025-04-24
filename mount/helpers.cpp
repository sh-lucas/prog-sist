#include "../hfiles/consts.h" // Include the header file where ADD is
#include <cstdint>
#include <string>

using namespace std;

string hello = "4";

string str_trim(string str) {
  // Remove trailing newline and carriage return characters
  while (!str.empty() &&
         (str.back() == '\n' || str.back() == '\r' || isspace(str.back())))
    str.pop_back();

  // Remove leading spaces and other blank characters
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

bool next_op(FILE *file, instruction *inst) {
  inst->empty = 0;
  inst->cmd = 0;
  inst->op1 = 0;
  inst->op2 = 0;
  inst->op3 = 0;

  char buffer[40];
  if (!fgets(buffer, 40, file)) {
    inst->empty = true;
    return 0;
  }

  string line = str_trim(string(buffer));

  if (line.empty() || line.front() == '#' || line == "") {
    // no instruction, but works
    inst->empty = 1;
    return 1;
  }

  string command = line.substr(0, line.find(' '));
  line = line.substr(line.find(' ') + 1);

  string ops[3];
  int opc = 0;

  // gets the operands in order
  while (line.find(' ') != string::npos) {
    ops[opc++] = line.substr(0, line.find(' '));
    line = line.substr(line.find(' ') + 1);
  }
  if (opc > 3) {
    exit(1);
  }
  // to get the last arg (there is space in the end)
  ops[opc++] = line.substr(0, line.find('\0'));
  line = line.substr(line.find('\0') + 1);

  inst->cmd = instruction_map.at(command.c_str());
  inst->op1 = atoi(ops[0].c_str());
  inst->op2 = atoi(ops[1].c_str());
  inst->op3 = atoi(ops[2].c_str());

  return 1;
}