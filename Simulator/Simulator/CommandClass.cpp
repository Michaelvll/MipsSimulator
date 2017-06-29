#include "CommandClass.h"
#include "MipsSimulatorClass.h"
#include "PipelineClass.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

extern MipsSimulatorClass MipsSimulator;
/// If return false && r[3] == 1 || 5, then stop the instruction before
/// If return false && r[3] == -1, then stop the program
/// if return false && r[3] == -2, then stop the program and return r[2]
/// Label is then in r[1]
bool CommandClass::Add::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Add" << endl;

	r[1] = static_cast<int>(r[1]) + static_cast<int>(r[2]);
	return true;
}

bool CommandClass::Addu::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])
	MipsSimulator.log << "Execute Addu" << endl;

	r[1] = r[1] + r[2];
	return true;
}

bool CommandClass::Sub::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Sub" << endl;

	r[1] = static_cast<int>(r[1]) - static_cast<int>(r[2]);
	return true;
}

bool CommandClass::Subu::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])
	MipsSimulator.log << "Execute Subu" << endl;

	r[1] = r[1] - r[2];
	return true;
}

bool CommandClass::Mul::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Mul" << endl;

	int a = static_cast<int>(r[1]) * static_cast<int>(r[2]);
	r[1] = static_cast<long long> (a);
	return true;
}

bool CommandClass::Mulu::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (long long)
	MipsSimulator.log << "Execute Mulu" << endl;

	r[1] = static_cast<unsigned>(r[1]) * static_cast<unsigned>(r[2]);
	return true;
}

bool CommandClass::Mul2::exec(long long r[4])
{
	/// Input r[2] and r[3] which should be static_cast<long long> (unsigned)
	/// Output r[2] which can be used as s = reinterpret_cast<char*> (r[1]); char s1[2] = {s[0],s[1]return true;}; lo = *(reinterpret_cast<unsigned*> (s1));...
	MipsSimulator.log << "Execute Mul2" << endl;

	r[2] = r[2] * r[3];
	return true;
}

void CommandClass::Mul2::data_preparation(const UsefulStructures::Token & token, long long res[4])
{
}

bool CommandClass::Mulu2::exec(long long r[4])
{
	/// Input r[2] and r[3] which should be static_cast<long long> (unsigned)
	/// Output r[2] which can be used as s = reinterpret_cast<char*> (r[2]); char s1[2] = {s[0],s[1]return true;}; lo = *(reinterpret_cast<unsigned*> (s1));...
	MipsSimulator.log << "Execute Mulu2" << endl;

	unsigned long long a = static_cast<unsigned long long>(r[2]), b = static_cast<unsigned long long>(r[3]);
	unsigned long long c = a * b;
	r[2] = static_cast<long long>(c);
	return true;
}

void CommandClass::Mulu2::data_preparation(const UsefulStructures::Token & token, long long res[4])
{
}

bool CommandClass::Div::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Div" << endl;

	r[1] = static_cast<int>(r[1]) / static_cast<int>(r[2]);
	return true;
}

bool CommandClass::Divu::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Divu" << endl;

	r[1] = static_cast<unsigned>(r[1]) / static_cast<unsigned>(r[2]);
	return true;
}

bool CommandClass::Div2::exec(long long r[4])
{
	/// Input r[2] and r[3] which should be static_cast<long long> (unsigned)
	/// Output r[2] which can be used as s = reinterpret_cast<char*> (r[2]); 
	/// char s1[2] = {s[0],s[1]}; lo = *(reinterpret_cast<unsigned*> (s1));...	MipsSimulator.log << "Execute Div2" << endl;


	int a = static_cast<int>(r[2]), b = static_cast<int>(r[3]);
	r[2] = a / b;
	r[2] |= (static_cast<unsigned long long>(a % b) << 32);
	return true;
}

void CommandClass::Div2::data_preparation(const UsefulStructures::Token & token, long long res[4])
{
}

bool CommandClass::Divu2::exec(long long r[4])
{
	/// Input r[2] and r[3] which should be static_cast<long long> (unsigned)
	/// Output r[2] which can be used as s = reinterpret_cast<char*> (r[2]); 
	/// char s1[2] = {s[0],s[1]}; lo = *(reinterpert_cast<unsigned*> (s1));...	MipsSimulator.log << "Execute Divu2" << endl;


	unsigned a = static_cast<unsigned>(r[2]), b = static_cast<unsigned>(r[3]);
	r[2] = a / b;
	r[2] |= (static_cast<unsigned long long>(a % b) << 32);
	return true;
}

void CommandClass::Divu2::data_preparation(const UsefulStructures::Token & token, long long res[4])
{
}

bool CommandClass::Xor::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Xor" << endl;

	r[1] = r[1] ^ r[2];
	return true;
}

bool CommandClass::Xoru::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Xoru" << endl;

	r[1] = r[1] ^ r[2];
	return true;
}

bool CommandClass::Neg::exec(long long r[4])
{
	/// Input r[1] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Neg" << endl;

	r[1] = -r[1];
	return true;
}

bool CommandClass::Negu::exec(long long r[4])
{
	/// Input r[1] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])
	MipsSimulator.log << "Execute Negu" << endl;

	unsigned a = static_cast<unsigned> (r[1]);
	unsigned b = -a;
	r[1] = static_cast<long long> (b);
	return true;
}

bool CommandClass::Rem::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Rem" << endl;

	int c = static_cast<int>(r[1]) % static_cast<int>(r[2]);
	r[1] = static_cast<long long>(c);
	return true;
}

bool CommandClass::Remu::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])
	MipsSimulator.log << "Execute Remu" << endl;

	r[1] = r[1] % r[2];
	return true;
}

bool CommandClass::Li::exec(long long r[4])
{
	MipsSimulator.log << "Execute Li" << endl;

	return true;
}


bool CommandClass::Seq::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Seq" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a == b) ? 1 : 0;
	return true;
}

bool CommandClass::Sge::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Sge" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a >= b) ? 1 : 0;
	return true;
}

bool CommandClass::Sgt::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Sgt" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a > b) ? 1 : 0;
	return true;
}

bool CommandClass::Sle::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Sle" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a <= b) ? 1 : 0;
	return true;
}

bool CommandClass::Slt::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Slt" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a < b) ? 1 : 0;
	return true;
}

bool CommandClass::Sne::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Sne" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a != b) ? 1 : 0;
	return true;
}

bool CommandClass::B::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[0]) goto r[3]
	MipsSimulator.log << "Execute B" << endl;

	r[1] = r[0];
	r[3] = 1;
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

void CommandClass::B::data_preparation(const UsefulStructures::Token & token, long long res[4])
{
}

bool CommandClass::Beq::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[0]) goto r[3]
	MipsSimulator.log << "Execute Beq" << endl;

	r[3] = (r[0] == r[1]) ? 1 : 0;
	r[1] = r[2];
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Bne::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[0]) goto r[3]
	MipsSimulator.log << "Execute Bne" << endl;

	r[3] = (r[0] != r[1]) ? 1 : 0;
	r[1] = r[2];
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Bge::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[0]) goto r[3]
	MipsSimulator.log << "Execute Bge" << endl;

	int a = static_cast<int>(r[0]), b = static_cast<int>(r[1]);
	r[3] = (a >= b) ? 1 : 0;
	r[1] = r[2];
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Ble::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute Ble" << endl;

	int a = static_cast<int>(r[0]), b = static_cast<int>(r[1]);
	r[3] = (a <= b) ? 1 : 0;
	r[1] = r[2];
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Bgt::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute Bgt" << endl;

	int a = static_cast<int>(r[0]), b = static_cast<int>(r[1]);
	r[3] = (a > b) ? 1 : 0;
	r[1] = r[2];
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Blt::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute Blt" << endl;

	int a = static_cast<int>(r[0]), b = static_cast<int>(r[1]);
	r[3] = (a < b) ? 1 : 0;
	r[1] = r[2];
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Beqz::exec(long long r[4])
{
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute Beqz" << endl;

	int a = static_cast<int>(r[0]);
	r[3] = (a == 0) ? 1 : 0; r[1] = r[2];
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Bnez::exec(long long r[4])
{
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute Bnez" << endl;

	int a = static_cast<int>(r[0]);
	r[3] = (a != 0) ? 1 : 0;
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Blez::exec(long long r[4])
{
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute Blez" << endl;

	int a = static_cast<int>(r[0]);
	r[3] = (a <= 0) ? 1 : 0;
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Bgez::exec(long long r[4])
{
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute Bgez" << endl;

	int a = static_cast<int>(r[0]);
	r[3] = (a >= 0) ? 1 : 0;
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Bgtz::exec(long long r[4])
{
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute Bgtz" << endl;

	int a = static_cast<int>(r[0]);
	r[3] = (a > 0) ? 1 : 0;
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Bltz::exec(long long r[4])
{
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute Bltz" << endl;

	int a = static_cast<int>(r[0]);
	r[3] = (a < 0) ? 1 : 0;
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::J::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute J" << endl;

	r[1] = r[0];
	r[3] = 1;
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Jr::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute Jr" << endl;

	r[1] = r[0];
	r[3] = 1;
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Jal::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute Jal" << endl;

	r[1] = r[0];
	r[3] = 1;
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::Jalr::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[3], if (r[3]) goto r[1]
	MipsSimulator.log << "Execute Jalr" << endl;

	r[1] = r[0];
	r[3] = 1;
	r[0] = MipsSimulator.reg_num_tab["sp"];
	return false;
}

bool CommandClass::La::exec(long long r[4])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should be loaded	MipsSimulator.log << "Execute La" << endl;


	r[1] += r[3];
	r[2] = 0;
	return true;
}

bool CommandClass::Lb::exec(long long r[4])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should be loaded	MipsSimulator.log << "Execute Lb" << endl;


	r[1] += r[3];
	r[2] = 1;
	return true;
}

bool CommandClass::Lh::exec(long long r[4])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should be loaded	MipsSimulator.log << "Execute Lh" << endl;


	r[1] += r[3];
	r[2] = 2;
	return true;
}

bool CommandClass::Lw::exec(long long r[4])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should be loaded	MipsSimulator.log << "Execute Lw" << endl;


	r[1] += r[3];
	r[2] = 4;
	return true;
}

bool CommandClass::Sb::exec(long long r[4])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should save in	MipsSimulator.log << "Execute Sb" << endl;


	r[1] += r[3];
	r[2] = 1;
	return true;
}

bool CommandClass::Sh::exec(long long r[4])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should save in	MipsSimulator.log << "Execute Sh" << endl;


	r[1] += r[3];
	r[2] = 2;
	return true;
}

bool CommandClass::Sw::exec(long long r[4])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should save in	MipsSimulator.log << "Execute Sw" << endl;


	r[1] += r[3];
	r[2] = 4;
	return true;
}

bool CommandClass::Move::exec(long long r[4])
{
	MipsSimulator.log << "Execute Move" << endl;

	return true;
}

bool CommandClass::Mfhi::exec(long long r[4])
{
	MipsSimulator.log << "Execute Mfhi" << endl;

	return true;
}

bool CommandClass::Mflo::exec(long long r[4])
{
	MipsSimulator.log << "Execute Mflo" << endl;

	return true;
}

bool CommandClass::Nop::exec(long long r[4])
{
	r[3] = 5;
	MipsSimulator.log << "Execute Nop" << endl;
	return false;

}

bool CommandClass::Syscall::exec(long long r[4])
{
	/// r[0] is the the num of $v0
	/// r[1] is the content of $v0
	/// r[2] is the content of $a0
	/// r[3] is the content of $a1
	MipsSimulator.log << "Execute Syscall" << endl;

	switch (r[1]) {
	case 1:
		cout << r[1] << endl;
		break;
	case 5:
		cin >> r[1];
		break;
	case 10:
		r[3] = -1;
		break;
	case 17:
		r[3] = -2;
		break;
	}
	return false;
}

bool CommandClass::Empty::exec(long long r[4])
{
	MipsSimulator.log << "Execute Empty" << endl;

	return false;
}


void CommandClass::Command_Base::data_preparation(const UsefulStructures::Token & token, long long res[4])
{
	if (token.op != MipsSimulatorClass::op_num::mul2 &&token.op != MipsSimulatorClass::op_num::mulu2 &&
		token.op != MipsSimulatorClass::op_num::div2 && token.op != MipsSimulatorClass::op_num::divu2) {
		res[0] = static_cast<long long> (token.r[0]);
		res[3] = static_cast<long long> (token.offset);
		for (int i = 1; i < 3; ++i) {
			if (token.rstate[i] == UsefulStructures::r_state::regi) {
				unsigned tmp = MipsSimulator.reg[token.r[i]];
				res[i] = static_cast<long long> (tmp);
			}
			else if (token.rstate[i] == UsefulStructures::r_state::immi) {
				unsigned tmp = token.r[i];
				res[i] = static_cast<long long> (tmp);
			}
		}
	}
	else {
		res[2] = MipsSimulator.reg[token.r[0]];
		if (token.rstate[1] == UsefulStructures::r_state::regi) {
			unsigned tmp = MipsSimulator.reg[token.r[1]];
			res[3] = static_cast<long long> (tmp);
		}
		else if (token.rstate[1] == UsefulStructures::r_state::immi) {
			unsigned tmp = token.r[1];
			res[3] = static_cast<long long> (tmp);
		}
		res[0] = MipsSimulatorClass::reg_num::lo;
		res[1] = MipsSimulatorClass::reg_num::hi;
	}
}
