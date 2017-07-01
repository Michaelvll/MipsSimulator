#ifndef MIPSSIMULATORCLASS
#define MIPSSIMULATORCLASS
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "CommandClass.h"
#include <fstream>
#include <set>
#include "UsefulStructures.h"

using std::string;
using std::ostream;

class MipsSimulatorClass;

class MipsSimulatorClass {
	friend class CommandClass::Command_Base;
private:
	
	// Command that different from the given ones (each one represents a serie:
	// add, sub, mul, div, xor1, div
	enum state_num {
		data, text
	};

	
	
public:
	char* memory;
	unsigned reg[35] = { 0 };
	unsigned &PC = reg[UsefulStructures::reg_num::pc];
	std::vector<UsefulStructures::Token> expr;
	std::unordered_map<string, UsefulStructures::op_num> op_num_tab;
	CommandClass::Command_Base *op_class_tab[UsefulStructures::op_num::syscall];
	std::unordered_map<string, int> reg_num_tab;
	std::unordered_map<string, int> txt_lab_tab;
	std::unordered_map<string, int> mem_lab_tab;
	int expr_pos = 0, mem_pos = 0;

	enum type_op_num {
		sig, unsig
	};

	std::ofstream log;

private:
	template<typename T>
	T Get_Next_Num(const string &s, size_t &pos);
	string Get_Next_String(const string &s, size_t &pos);
	string String_Fetch(const string &s);
	bool isReg(const string &s);
	bool Text_labelProcess(const string &s, int &expr_pos, state_num &state);
	void Data_Process(string s, int &mem_pos, state_num &state);
	void readcode(std::istream &codein);
	void pipeline();

public:
	MipsSimulatorClass();
	~MipsSimulatorClass();

	void exec(std::istream & codein);
};
#endif //MIPSSIMULATORCLASS