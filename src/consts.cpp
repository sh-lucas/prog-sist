#include <string>
#include <unordered_map>

using namespace std;

const int ADD = 0;
const int SUB = 1;
const int MUL = 2;
const int DIV = 3;
const int MV = 4;
const int ST = 5;
const int JMP = 6;
const int JEQ = 7;
const int JGT = 8;
const int JLT = 9;
const int W = 10;
const int R = 11;
const int STP = 12;

extern const unordered_map<string, int> instruction_map = {
    {"ADD", ADD}, {"SUB", SUB}, {"MUL", MUL}, {"DIV", DIV}, {"MV", MV},
    {"ST", ST},   {"JMP", JMP}, {"JEQ", JEQ}, {"JGT", JGT}, {"JLT", JLT},
    {"WRITE", W}, {"READ", R},  {"STP", STP},
};