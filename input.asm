# add                a0 = a1 + a2;
# sub                a0 = a1 - a2;
# mul                a0 = a1 * a2;
# div                a0 = a1 / a2;
# mv  op1 op2        regs[op1] = mem[op2];
# st  op1 op2        mem[op1] = regs[op2];
# jmp op1            pc = op1;
# jeq op1 op2 op3    op1 == op2 --> pc = op3;
# jgt op1 op2 op3    op1 > op2  --> pc = op3;
# jlt op1 op2 op3    op1 < op2  --> pc = op3;
# w   op1            prints regs[op1] to cout;
# r   op1            reads cin to regs[op1];
# stp                stops the machine;
ADD 4 2 2
# ADD 3 2
SUB 4 7 2
MV 2
STP