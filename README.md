# MipsSimulator
This is a project of PPCA.

By Zhanghao Wu

2017 Summer

## Function
This Simulator is used for execute the source code of Mips by simulating the CPU with C++ program.

## Features
* Read the code automatically
* Simulate the technique of five-stage pipeline
* Branch predictor: Two-level adaptive predictor

## Implemention Details
### Readcode
Scan the source code twice:
1. Firstly, execute the command related with the memory, put the commands in text area into a vector of string *preExpr* and get the address of the labels.
2. Secondly, replace the labels with the address, change the command strings into tokens and put them into a vector of Token *Expr*.
### Pipeline
#### General
Every instruction(will be represented by ins. in the later context) on the pipeline is represented by a class called *PiplineClass*. The structure of the deque is in the [line](#Image_of_the_deque) below (some of the stages may not appear in some cycles for there might be some hazard that pause the pipeline for some cycle).

<a name="Image_of_the_deque">Line of the pipeline</a>

|   Stage:   | line.front |      5     |      4     |      3     |      2     |      1     |  line.back |
| ---------- | ---------- | ---------- | ---------- | ---------- | ---------- | ---------- | ---------- |

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

### Two-level adaptive predictor
The correctness of the predictor is in the appendix



## Some important lists
### <b name="meaning_of_r4">The meaning of r[4]</b>
* r[4] == 0 (Don't Jump): Do nothing in the last two stages
* r[4] == 1(Jump ins. with start in b): Clear the ins. behind this ins. on the pipline, and pause the pipeline behind until this ins. is finished
* r[4] == 2(Jal, Jalr): Clear and Write r[1] into reg[r[0]]
* r[4] == 3(Common Command): Write r[1] into reg[r[0]]
* r[4] == 4(J, Jr, B): Do nothing in the last two stages
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

## Appendix
### Correctness of the predictor

TEST  lvalue2-5110379024-wuhang
Condition jump number: 9
Correct prediction number: 5
Rate: 0.555556

TEST  gcd-5090379042-jiaxiao
Condition jump number: 43
Correct prediction number: 27
Rate: 0.627907

TEST  manyarguments-5100379110-daibo
Condition jump number: 13
Correct prediction number: 8
Rate: 0.615385

TEST  tak-5090379042-jiaxiao
Condition jump number: 60644
Correct prediction number: 47627
Rate: 0.785354

TEST  builtin-5140519064-youyurong
Condition jump number: 51
Correct prediction number: 31
Rate: 0.607843

TEST  array_test1-mahaojun
Condition jump number: 59
Correct prediction number: 43
Rate: 0.728814

TEST  pi-5090379042-jiaxiao
Condition jump number: 287364
Correct prediction number: 287113
Rate: 0.999127

TEST  class_test-mahaojun
Condition jump number: 3
Correct prediction number: 1
Rate: 0.333333

TEST  hanoi-5100379110-daibo
Condition jump number: 1038
Correct prediction number: 641
Rate: 0.617534

TEST  twinprime-5090379042-jiaxiao
Condition jump number: 93900
Correct prediction number: 90726
Rate: 0.966198

TEST  array_test2-mahaojun
Condition jump number: 73
Correct prediction number: 57
Rate: 0.780822

TEST  basicopt1-5100309127-hetianxing
Condition jump number: 38580
Correct prediction number: 38155
Rate: 0.988984

TEST  qsort-5100379110-daibo
Condition jump number: 332765
Correct prediction number: 318855
Rate: 0.958199

TEST  string_test-huyuncong
Condition jump number: 110
Correct prediction number: 71
Rate: 0.645455

TEST  statement_test-huyuncong
Condition jump number: 144
Correct prediction number: 105
Rate: 0.729167

TEST  hashmap-5100309127-hetianxing
Condition jump number: 44049
Correct prediction number: 42566
Rate: 0.966333

TEST  queens-5100379110-daibo
Condition jump number: 70033
Correct prediction number: 54552
Rate: 0.778947

TEST  multiarray-5100309153-yanghuan
Condition jump number: 606
Correct prediction number: 526
Rate: 0.867987

TEST  function_test-huyuncong
Condition jump number: 92
Correct prediction number: 62
Rate: 0.673913

TEST  heapsort-5100379110-daibo
Condition jump number: 679042
Correct prediction number: 615725
Rate: 0.906755

TEST  horse-5100309153-yanghuan
Condition jump number: 468141
Correct prediction number: 444493
Rate: 0.949485

TEST  superloop-5090379042-jiaxiao
Condition jump number: 490292
Correct prediction number: 458806
Rate: 0.935781

TEST  maxflow-5100379110-daibo
Condition jump number: 1246529
Correct prediction number: 1229679
Rate: 0.986482

TEST  horse3-5100309153-yanghuan
Condition jump number: 581502
Correct prediction number: 546809
Rate: 0.940339

TEST  prime-5100309153-yanghuan
Condition jump number: 210521
Correct prediction number: 199732
Rate: 0.948751

TEST  bulgarian-5110379024-wuhang
Condition jump number: 113837
Correct prediction number: 106539
Rate: 0.935891

TEST  magic-5100309153-yanghuan
Condition jump number: 96705
Correct prediction number: 78715
Rate: 0.81397

TEST  expr-5110309085-jintianxing
Condition jump number: 107
Correct prediction number: 87
Rate: 0.813084

TEST  horse2-5100309153-yanghuan
Condition jump number: 486501
Correct prediction number: 467454
Rate: 0.960849

TEST  spill2-5100379110-daibo
Condition jump number: 6224
Correct prediction number: 6192
Rate: 0.994859
