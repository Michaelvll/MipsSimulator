# MipsSimulator
This is a project of PPCA.

By Zhanghao Wu

2017 Summer

## Function
This Simulator is used for execute the source code of Mips by simulating the CPU with C++ program.

## Features
* Read the code automatically
* Simulate the technique of five stage pipeline(naive mode)

## Implemention Details
### Readcode
Scan the source code twice:
1. Firstly, execute the command related with the memory, put the commands in text area into a vector of string *preExpr* and get the address of the labels.
2. Secondly, replace the labels with the address, change the command strings into tokens and put them into a vector of Token *Expr*.
### Pipeline
#### General
Every instruction(will be represented by ins. in the later context) on the pipeline is represented by a class called *PiplineClass*. The structure of the deque is in the [image](#Image_of_the_deque) (some of the stages may not appear in some cycles for there might be some hazard that pause the pipeline for some cycle).
<a name="Image_of_the_deque">
| Stage: | line.front |   5   |   4   |   3   |   2   |   1   |  line.back |
| ---- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |
</a>

And the pipeline is simulated by a deque(called *line*) of *piplineClass*es. In every clock cycle, the line will be traversed. And for each ins. got they will call the function *StartNext* which will figure out whether there is a hazard for this stage to execute, and execute the stage or pause the pipeline behind it.

### Five stages
1. Instruction Fetch(IF)
	* Fetch the instruction from the memory (in this simulator the instruction is stored in another container, but it can be assumed that it is in the memory). 
	* In this stage control hazard might take place for the memory can be read or write once in a same clock cycle.
2. Instruction Decoding and Data Preparation(ID)
	* Data preparation stage of the product on the pipeline. 
	* Get all of the numbers needed from those register.
	* In stage level data hazard might happened when the register, needed to be read has not finished writing process by the ins. behind it. If a register needed to be read is in busy mode then pause the pipeline behind this ins.
3. Execution(EXEC)
	* Execution of the ins. on the pipeline.
	* In this stage the command will be fully recognized and the calculations will be done.
	* Register that will be written in is locked into busy mode
4. Memory Access(MA)
	* Memory Access stage of the ins. on pipeline.
	* Load/write the data from/to the RAM or the I/O devices 
	* In this stage might read or write the Ram which may cause the control hazard to the instruction fetch stage.
5. Write Back(WB)
	* Write back stage of the ins. on pipeline
	* Write back the results of the stages before to certain registers(including PC register)
	* The locked register will be released
### Data transit between stages
As every ins. has its own datas, the *PipelineClass* includes all of the data needed by this ins.(some data will not be updated until certain stages finished). In *PipelineClass*, there are a *long long* array *r* of the size of 5 and a *Token* structure *token* that record the command of this ins.. The former one is aimed at record the result get from the stages, in order to simulate the transit of the data from one stage to the next stage. 

Generally, 
1. In *IF* stage the the token will be updated for the machine read the RAM at the position represented by PC.
2. In ID stage the array *r* will be updated as:
	* r[0]: the first arguement
	* r[1]: the content of the register at the position the second arguement(if exists) represents, or the number of immidiant number or the label
	* r[2]: the content of the register at the position the third arguement(if exists) represents, or the number of immidiant number or the label
	* r[3]: the offset of the register(if exists)
	* r[4]: the content of the register at the position r[0] represents(if needed, according to the bool *read_first_reg* in the class of command)
3. In EXEC stage the array *r* will be updated again, by change the r[0] to the register this ins. should write back to, r[1] to the result of the EXEC stage (there will be other conditions so r[4] is used to represent the next behaviors the machine should do). r[4] will be updated by numbers represent different behavior in next stages (the number is listed in the [The meaning of r[4]](#meaning_of_r4) part)
4. In MA stage according to the value of r[4] the machine will load data from the RAM or do other corresponding behaviors
5. In WB stage according to the value of r[4] the machine will write back r[1] to the register at the position of r[0] represents or do other things.

## Some important lists
### <b name="meaning_of_r4">The meaning of r[4]</b>
* r[4] == 1(Jump ins.): Clear the ins. behind this ins. on the pipline, and pause the pipeline behind until this ins. is finished
* r[4] == 2(Jal, Jalr): Clear and Write r[1] into reg[r[0]], r[3] into reg[r[2]]
* r[4] == 3(Common Command): Write r[1] into reg[r[0]]
* r[4] == 5(Nop): Wait 5 cycles
* r[4] == -1(Syscall 10): Stopall
* r[4] == -2(Syscall 17): Stopall and cout << r[2]
* r[4] == -3(Load Command): Need to read from mem at the adress r[1] to r[1]+r[2]-1. and write it back to reg[r[0]]
* r[4] == -5(Store command): Need write back r[1] of the length r[2] to mem[r[0]]
* r[4] == -6(Syscall 5): Need to read int from I/O device to r[1] and write back to reg[r[0]]i.e.reg[$v0]
* r[4] == -7(Syscall 1): Need to write back int from r[2] to I/O device
* r[4] == -8(Mul2, Div2, Mulu2, Divu2): Need to write back from r[2] to reg[r[0]]i.e.reg[$lo] and r[1]i.e.reg[$hi]
* r[4] == -9(Syscall 4): Need to write back string from memory[r[2]] to I/O device
* r[4] == -10(Syscall 9): Need to allocate mem with length of r[2] and put the address to reg[r[0]]
* r[4] == -11(Syscall 8): Need to read a string from I/O device to memory[r[0]]

### Commands that will read Rdest (the register represented by the first arguement)
mul2, mulu2, div2, divu2, beq, bne, bge, ble, bgt, blt, beqz, bnez, blez, bgez, bgtz, bltz, jr, jalr, sb, sh, sw