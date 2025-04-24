#include <cstdint>
#include <string>
#include <unordered_map>

using namespace std;

const uint16_t ADD = 0;
const uint16_t SUB = 1;
const uint16_t MUL = 2;
const uint16_t DIV = 3;
const uint16_t MV = 4;
const uint16_t ST = 5;
const uint16_t JMP = 6;
const uint16_t JEQ = 7;
const uint16_t JGT = 8;
const uint16_t JLT = 9;
const uint16_t W = 10;
const uint16_t R = 11;
const uint16_t STP = 12;

extern const unordered_map<string, uint16_t> instruction_map = {
    {"ADD", ADD}, {"SUB", SUB}, {"MUL", MUL}, {"DIV", DIV}, {"MV", MV},
    {"ST", ST},   {"JMP", JMP}, {"JEQ", JEQ}, {"JGT", JGT}, {"JLT", JLT},
    {"W", W},     {"R", R},     {"STP", STP},
};