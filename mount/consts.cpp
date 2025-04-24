#include <cstdint>
#include <string>
#include <unordered_map>

using namespace std;

const uint8_t ADD = 0;
const uint8_t SUB = 1;
const uint8_t MUL = 2;
const uint8_t DIV = 3;
const uint8_t MV = 4;
const uint8_t ST = 5;
const uint8_t JMP = 6;
const uint8_t JEQ = 7;
const uint8_t JGT = 8;
const uint8_t JLT = 9;
const uint8_t W = 10;
const uint8_t R = 11;
const uint8_t STP = 12;

extern const unordered_map<string, uint8_t> instruction_map = {
    {"ADD", ADD}, {"SUB", SUB}, {"MUL", MUL}, {"DIV", DIV}, {"MV", MV},
    {"ST", ST},   {"JMP", JMP}, {"JEQ", JEQ}, {"JGT", JGT}, {"JLT", JLT},
    {"W", W},     {"R", R},     {"STP", STP},
};