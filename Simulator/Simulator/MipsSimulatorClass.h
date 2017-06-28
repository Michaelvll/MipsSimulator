#ifndef MIPSSIMULATORCLASS
#define MIPSSIMULATORCLASS
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "CommandClass.h"

using std::string;

class MipsSimulatorClass;

class MipsSimulatorClass {
public:
	enum r_state {
		none, regi, immi
	};
	struct Token {
		int op;
		int r[3];
		int offset[3];
		r_state rstate[3];
	};

private:
	enum op_num {
		add, addu, sub, subu, mul, mulu,mul2,mulu2, div,divu, div2, 
		divu2, xor, xoru, neg, negu, rem, remu, li, seq, sge, sgt, 
		sle,slt,sne, b, beq, bne, bge, ble, bgt, blt, beqz, bnez, blez, bgez, 
		bgtz,bltz, j, jr, jal, jalr, la, lb, lh, lw, sb, sh, sw, move, mfhi, 
		mflo,nop,syscall
	}; 
	// Command that different from the given ones (each one represents a serie:
	// add, sub, mul, div, xor, div
	enum state_num {
		data, text
	};
	enum reg_num {
		zero = 0, at, v0, v1, a0, a1, a2, a3,
		t0 = 8, t1, t2, t3, t4, t5, t6, t7,
		s0 = 16, s1, s2, s3, s4, s5, s6, s7,
		t8 = 24, t9, k0, k1, gp, sp, s8 = 30,
		fp = 30, ra
	};

	char memory[4 * 1024 * 1024];
	int reg[32] = { 0 };
	int &PC = reg[reg_num::sp];
	
	std::vector<Token> expr;
	std::unordered_map<string, op_num> op_num_tab;
	CommandClass::Command_Base *op_class_tab[op_num::syscall+1];
	std::unordered_map<string, int> reg_num_tab;
	std::unordered_map<string, int> txt_lab_tab;
	std::unordered_map<string, int> mem_lab_tab;

	template<typename T>
	T Get_Next_Num(const string &s, int &pos);
	string Get_Next_String(const string &s, int &pos);
	string String_Fetch(const string &s);
	bool isReg(const string &s);
	bool Text_labelProcess(const string &s, int &expr_pos, state_num &state);
	void Data_Process(string s, int &mem_pos, state_num &state);

public:
	MipsSimulatorClass();
	~MipsSimulatorClass();

	void readcode(std::istream &codein);
	void Instruction_Fetch();
	void Instruction_Decode_Data_Preparation();
	void Execution();
	void Memory_Access();
	void Write_Back();

	void exec(std::istream & codein, std::ostream & fout);





};
#endif //MIPSSIMULATORCLASS