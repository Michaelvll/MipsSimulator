#ifndef MIPSSIMULATORCLASS
#define MIPSSIMULATORCLASS
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class MipsSimulatorClass;

class MipsSimulatorClass {
private:
	enum reg_num{
		zero = 0, at, v0, v1, a0, a1, a2, a3,
		t0 = 8, t1, t2, t3, t4, t5, t6, t7, 
		s0 = 16, s1, s2, s3, s4, s5, s6, s7, 
		t8 = 24, t9, k0, k1, gp, sp, s8 = 30, 
		fp = 30, ra
	};
	unsigned char memory[4 * 1024 * 1024];
	int reg[32] = { 0 };
	int &PC = reg[reg_num::sp];
	std::vector<std::string> expr;
	std::unordered_map<std::string, int> reg_num_tab;
	std::unordered_map<std::string, int> label_table;

public:
	MipsSimulatorClass();

	void readcode(std::istream &codein);
	void Instruction_Fetch();
	void Instruction_Decode_Data_Preparation();
	void Execution();
	void Memory_Access();
	void Write_Back();

	void Run(std::istream & codein, std::istream & fin, std::ostream & fout) {

	}
};
#endif //MIPSSIMULATORCLASS