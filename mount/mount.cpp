// #include "../hfiles/consts.h" // Include the header file where ADD is
// declared
#include "../hfiles/helpers.h" // Include the header file where str_trim is declared
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  string filename = argv[1];
  if (argc != 2) {
    cout << "No filename provided. Using default input.asm" << endl;
    filename = "input.asm";
  }

  FILE *file = fopen(filename.c_str(), "r");
  FILE *output = fopen("output.bin", "w+b");

  string line;

  instruction inst;

  int pc = 0;
  while (next_op(file, &inst)) {
    if (!inst.empty) {
      int cmd = inst.cmd;

      fwrite(&inst.cmd, sizeof(uint16_t), 1, output);
      fwrite(&inst.op1, sizeof(uint16_t), 1, output);
      fwrite(&inst.op2, sizeof(uint16_t), 1, output);
      fwrite(&inst.op3, sizeof(uint16_t), 1, output);
    }
  }
}