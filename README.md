# MipsSimulator
This is a homework of PPCA.

## Function
This Simulator is used for execute the source code of Mips by simulating the CPU with C++ program.

## Features
* Read the code automatically
* Simulate the technique of five level pipeline(uncompleted)

## Implemention Details
Scan the source code twice:
* Firstly, execute the command related with the memory, put the commands in text area into a vector of string *preExpr* and get the address of the labels
* Secondly, replace the labels with the address, change the command strings into tokens and put them into a vector of Token *Expr*

## The meaning of r[4]
* r[4] == 1 clear
* r[4] == 2 write r[1] into reg[r[0]], r[3] into reg[r[2]]
* r[4] == 3 write r[1] into reg[r[0]]
* r[4] == 5 wait 5 cycles
* r[4] == -1 stopall
* r[4] == -2 stopall and cout << r[2]
* r[4] == -3 need read from mem at the adress r[1] to r[1]+r[2]-1. and write it back to reg[r[0]]		Load Command
* //r[4] == -4 need write back to register r[0]
* r[4] == -5 need write back r[1] of the length r[2] to mem[r[0]]    Store command
* r[4] == -6 need read int from I/O device to r[1]    Syscall 5
* r[4] == -7 need write back int from r[2] to I/O device    Syscall 1
* r[4] == -8 need to write back from r[2] to r[0]\(lo) and r[1]\(hi)
* r[4] == -9 need to write back string from memory[r[2]] to I/O device		Syscall 4
* r[4] == -10 need to allocate mem with length of r[2] and put the address to reg[r[0]]
* r[4] == -11 need to read a string from I/O device to memory[r[0]]   Syscall 8

## Pipeline
front	5	4	3	2	1	back
<---<---<---<---<---------------


## Commands that will read Rdest
mul2,mulu2,div2,divu2, beq, bne,bge,ble,bgt,blt,beqz,bnez,blez,bgez,bgtz,bltz,jr,jalr, sb, sh, sw