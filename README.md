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