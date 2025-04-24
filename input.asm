# ADD                a0 = a1 + a2;
# SUB                a0 = a1 - a2;
# MUL                a0 = a1 * a2;
# DIV                a0 = a1 / a2;
# MV  op1 op2        regs[op1] = mem[op2];
# ST  op1 op2        mem[op1] = regs[op2];
# JMP op1            pc = op1;
# JEQ op1 op2 op3    op1 == op2 --> pc = op3;
# JGT op1 op2 op3    op1 > op2  --> pc = op3;
# JLT op1 op2 op3    op1 < op2  --> pc = op3;
# W   op1            prints regs[op1] to cout;
# R   op1            reads cin to regs[op1];
# STP                stops the machine;

R 1
R 2
ADD
W 0
STP