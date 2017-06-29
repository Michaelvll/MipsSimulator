#include "CommandClass.h"
#include "MipsSimulatorClass.h"
#include "PipelineClass.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

extern MipsSimulatorClass MipsSimulator;
extern UsefulStructures usefulstructures;

/// If return false && r[4] == 1 || 5, then stop the instruction before
/// If return false && r[4] == -1, then stop the program
/// if return false && r[4] == -2, then stop the program and return r[2]
/// Label is then in r[1]

/*
* r[4] == 1 clear
* r[4] == 5 wait 5 cycles
* r[4] == -1 stopall
* r[4] == -2 stopall and cout << r[2]
* r[4] == -3 need read from mem at the adress r[1] to r[1]+r[2]
* //r[4] == -4 need write back to register r[0]
* r[4] == -5 need write back to mem
* r[4] == -6 need read int from I/O device to r[1]
* r[4] == -7 need write back int from r[1] to I/O device
* r[4] == -8 need to write back from r[2] to r[0]\(lo) and r[1]\(hi)
* r[4] == -9 need to write back string from s to I/O device
* r[4] == -10 need to allocate mem with length of r[2] and put the address to reg[r[0]]
* r[4] == -11 need to read a string from I/O device to r[0]
*/

bool CommandClass::Add::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Add" << endl;

	r[1] = static_cast<int>(r[1]) + static_cast<int>(r[2]);
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Addu::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])
	MipsSimulator.log << "Execute Addu" << endl;

	r[1] = r[1] + r[2];
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Sub::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Sub" << endl;

	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[1] = static_cast<int>(r[1]) - static_cast<int>(r[2]);
	r[4] = 0;
	return true;
}

bool CommandClass::Subu::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])
	MipsSimulator.log << "Execute Subu" << endl;

	r[1] = r[1] - r[2];
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Mul::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Mul" << endl;

	int a = static_cast<int>(r[1]) * static_cast<int>(r[2]);
	r[1] = static_cast<long long> (a);
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Mulu::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (long long)
	MipsSimulator.log << "Execute Mulu" << endl;

	r[1] = static_cast<unsigned>(r[1]) * static_cast<unsigned>(r[2]);
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Mul2::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[4] which should be static_cast<long long> (unsigned)
	/// Output r[2] which can be used as s = reinterpret_cast<char*> (r[1]); char s1[2] = {s[0],s[1]return true;}; lo = *(reinterpret_cast<unsigned*> (s1));...
	MipsSimulator.log << "Execute Mul2" << endl;

	r[2] = r[1] * r[4];
	r[0] = UsefulStructures::reg_num::lo;
	r[1] = UsefulStructures::reg_num::hi;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	usefulstructures.addBusy(static_cast<unsigned>(r[1]), busy_reg);
	r[4] = -8;
	return true;
}

bool CommandClass::Mulu2::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[4] which should be static_cast<long long> (unsigned)
	/// Output r[2] which can be used as s = reinterpret_cast<char*> (r[2]); char s1[2] = {s[0],s[1]return true;}; lo = *(reinterpret_cast<unsigned*> (s1));...
	MipsSimulator.log << "Execute Mulu2" << endl;

	unsigned long long a = static_cast<unsigned long long>(r[1]), b = static_cast<unsigned long long>(r[4]);
	unsigned long long c = a * b;
	r[2] = static_cast<long long>(c);
	r[0] = UsefulStructures::reg_num::lo;
	r[1] = UsefulStructures::reg_num::hi;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	usefulstructures.addBusy(static_cast<unsigned>(r[1]), busy_reg);
	r[4] = -8;
	return true;
}

bool CommandClass::Div::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Div" << endl;

	r[1] = static_cast<int>(r[1]) / static_cast<int>(r[2]);
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Divu::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Divu" << endl;

	r[1] = static_cast<unsigned>(r[1]) / static_cast<unsigned>(r[2]);
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Div2::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[4] which should be static_cast<long long> (unsigned)
	/// Output r[2] which can be used as s = reinterpret_cast<char*> (r[2]); 
	/// char s1[2] = {s[0],s[1]}; lo = *(reinterpret_cast<unsigned*> (s1));...
	MipsSimulator.log << "Execute Div2" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[4]);
	r[2] = a / b;
	r[2] |= (static_cast<unsigned long long>(a % b) << 32);
	r[0] = UsefulStructures::reg_num::lo;
	r[1] = UsefulStructures::reg_num::hi;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	usefulstructures.addBusy(static_cast<unsigned>(r[1]), busy_reg);
	r[4] = -8;
	return true;
}

bool CommandClass::Divu2::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[4] which should be static_cast<long long> (unsigned)
	/// Output r[2] which can be used as s = reinterpret_cast<char*> (r[2]); 
	/// char s1[2] = {s[0],s[1]}; lo = *(reinterpert_cast<unsigned*> (s1));...
	MipsSimulator.log << "Execute Divu2" << endl;

	unsigned a = static_cast<unsigned>(r[1]), b = static_cast<unsigned>(r[4]);
	r[2] = a / b;
	r[2] |= (static_cast<unsigned long long>(a % b) << 32);
	r[0] = UsefulStructures::reg_num::lo;
	r[1] = UsefulStructures::reg_num::hi;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	usefulstructures.addBusy(static_cast<unsigned>(r[1]), busy_reg);
	r[4] = -8;
	return true;
}

bool CommandClass::Xor::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Xor" << endl;

	r[1] = r[1] ^ r[2];
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Xoru::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Xoru" << endl;

	r[1] = r[1] ^ r[2];
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Neg::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Neg" << endl;

	r[1] = -r[1];
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Negu::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])
	MipsSimulator.log << "Execute Negu" << endl;

	unsigned a = static_cast<unsigned> (r[1]);
	unsigned b = -a;
	r[1] = static_cast<long long> (b);
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Rem::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Rem" << endl;

	int c = static_cast<int>(r[1]) % static_cast<int>(r[2]);
	r[1] = static_cast<long long>(c);
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Remu::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])
	MipsSimulator.log << "Execute Remu" << endl;

	r[1] = r[1] % r[2];
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Li::exec(long long r[5], int busy_reg[2])
{
	MipsSimulator.log << "Execute Li" << endl;

	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Seq::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Seq" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a == b) ? 1 : 0;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Sge::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Sge" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a >= b) ? 1 : 0;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Sgt::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Sgt" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a > b) ? 1 : 0;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Sle::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Sle" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a <= b) ? 1 : 0;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Slt::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Slt" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a < b) ? 1 : 0;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Sne::exec(long long r[5], int busy_reg[2])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	MipsSimulator.log << "Execute Sne" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a != b) ? 1 : 0;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::B::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute B" << endl;

	r[1] = r[0];
	r[4] = 1;
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Beq::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] and  which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Beq" << endl;

	r[4] = (r[0] == r[1]) ? 1 : 0;
	r[1] = r[2];
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Bne::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Bne" << endl;

	r[4] = (r[0] != r[1]) ? 1 : 0;
	r[1] = r[2];
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Bge::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Bge" << endl;

	int a = static_cast<int>(r[0]), b = static_cast<int>(r[1]);
	r[4] = (a >= b) ? 1 : 0;
	r[1] = r[2];
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Ble::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Ble" << endl;

	int a = static_cast<int>(r[0]), b = static_cast<int>(r[1]);
	r[4] = (a <= b) ? 1 : 0;
	r[1] = r[2];
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Bgt::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Bgt" << endl;

	int a = static_cast<int>(r[0]), b = static_cast<int>(r[1]);
	r[4] = (a > b) ? 1 : 0;
	r[1] = r[2];
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Blt::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Blt" << endl;

	int a = static_cast<int>(r[0]), b = static_cast<int>(r[1]);
	r[4] = (a < b) ? 1 : 0;
	r[1] = r[2];
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Beqz::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Beqz" << endl;

	int a = static_cast<int>(r[0]);
	r[4] = (a == 0) ? 1 : 0; r[1] = r[2];
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Bnez::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Bnez" << endl;

	int a = static_cast<int>(r[0]);
	r[4] = (a != 0) ? 1 : 0;
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Blez::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Blez" << endl;

	int a = static_cast<int>(r[0]);
	r[4] = (a <= 0) ? 1 : 0;
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Bgez::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Bgez" << endl;

	int a = static_cast<int>(r[0]);
	r[4] = (a >= 0) ? 1 : 0;
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Bgtz::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Bgtz" << endl;

	int a = static_cast<int>(r[0]);
	r[4] = (a > 0) ? 1 : 0;
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Bltz::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Bltz" << endl;

	int a = static_cast<int>(r[0]);
	r[4] = (a < 0) ? 1 : 0;
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::J::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute J" << endl;

	r[1] = r[0];
	r[4] = 1;
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Jr::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Jr" << endl;

	r[1] = r[0];
	r[4] = 1;
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Jal::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Jal" << endl;

	r[1] = r[0];
	r[4] = 1;
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::Jalr::exec(long long r[5], int busy_reg[2])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]
	MipsSimulator.log << "Execute Jalr" << endl;

	r[1] = r[0];
	r[4] = 1;
	r[0] = UsefulStructures::reg_num::pc;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return false;
}

bool CommandClass::La::exec(long long r[5], int busy_reg[2])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should be loaded
	MipsSimulator.log << "Execute La" << endl;

	r[1] += r[3];
	r[2] = 0;
	r[4] = -3;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return true;
}

bool CommandClass::Lb::exec(long long r[5], int busy_reg[2])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should be loaded
	MipsSimulator.log << "Execute Lb" << endl;

	r[1] += r[3];
	r[2] = 1;
	r[4] = -3;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return true;
}

bool CommandClass::Lh::exec(long long r[5], int busy_reg[2])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should be loaded
	MipsSimulator.log << "Execute Lh" << endl;

	r[1] += r[3];
	r[2] = 2;
	r[4] = -3;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return true;
}

bool CommandClass::Lw::exec(long long r[5], int busy_reg[2])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should be loaded
	MipsSimulator.log << "Execute Lw" << endl;

	r[1] += r[3];
	r[2] = 4;
	r[4] = -3;
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	return true;
}

bool CommandClass::Sb::exec(long long r[5], int busy_reg[2])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should save in
	MipsSimulator.log << "Execute Sb" << endl;

	r[1] += r[3];
	r[2] = 1;
	r[4] = -5;
	return true;
}

bool CommandClass::Sh::exec(long long r[5], int busy_reg[2])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should save in
	MipsSimulator.log << "Execute Sh" << endl;

	r[1] += r[3];
	r[2] = 2;
	r[4] = -5;
	return true;
}

bool CommandClass::Sw::exec(long long r[5], int busy_reg[2])
{
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should save in
	MipsSimulator.log << "Execute Sw" << endl;

	r[1] += r[3];
	r[2] = 4;
	r[4] = -5;
	return true;
}

bool CommandClass::Move::exec(long long r[5], int busy_reg[2])
{
	MipsSimulator.log << "Execute Move" << endl;

	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Mfhi::exec(long long r[5], int busy_reg[2])
{
	MipsSimulator.log << "Execute Mfhi" << endl;
	r[1] = static_cast<long long>(MipsSimulator.reg[UsefulStructures::reg_num::hi]);
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Mflo::exec(long long r[5], int busy_reg[2])
{
	MipsSimulator.log << "Execute Mflo" << endl;

	r[1] = static_cast<long long>(MipsSimulator.reg[UsefulStructures::reg_num::lo]);
	usefulstructures.addBusy(static_cast<unsigned>(r[0]), busy_reg);
	r[4] = 0;
	return true;
}

bool CommandClass::Nop::exec(long long r[5], int busy_reg[2])
{
	r[4] = 5;
	MipsSimulator.log << "Execute Nop" << endl;

	return false;
}

bool CommandClass::Syscall::exec(long long r[5], int busy_reg[2])
{
	/// r[0] is the the num of $v0
	/// r[1] is the content of $v0
	/// r[2] is the content of $a0
	/// r[3] is the content of $a1
	MipsSimulator.log << "Execute Syscall" << endl;

	switch (r[1]) {
	case 1:
		r[4] = -7;
		break;
	case 4:
		r[4] = -9;
		break;
	case 5:
		r[4] = -6;
		usefulstructures.addBusy(UsefulStructures::reg_num::v0, busy_reg);
		break;
	case 8:
		r[4] = -3;
		break;
	case 9:
		r[4] = -10;
		usefulstructures.addBusy(UsefulStructures::reg_num::v0, busy_reg);
		break;
	case 10:
		r[4] = -1;
		break;
	case 17:
		r[4] = -2;
		break;
	}
	return false;
}

bool CommandClass::Empty::exec(long long r[5], int busy_reg[2])
{
	MipsSimulator.log << "Execute Empty!!!!" << endl;

	return false;
}

void CommandClass::Command_Base::data_preparation(const UsefulStructures::arguToken & argutoken, long long res[5], int &state, int busyreg[4])
{
	/// res[0] = origin of the argue1
	/// res[1] = represented num of arue2
	/// res[2] = represented num of arue3
	/// res[3] = offset
	/// res[4] = represented num of argue1
	bool empty = false;
	if (argutoken.rstate[0] == UsefulStructures::r_state::none) {
		//TODO syscall
		/// r[0] is the the num of $v0
		/// r[1] is the content of $v0
		/// r[2] is the content of $a0
		/// r[3] is the content of $a1
		UsefulStructures us;
		if (us.Busy(UsefulStructures::reg_num::v0, busyreg)
			|| us.Busy(UsefulStructures::reg_num::a0, busyreg)
			|| us.Busy(UsefulStructures::reg_num::a1, busyreg)) {
			state = UsefulStructures::pip_run_state::pause;
			return;
		}
		else {
			res[0] = UsefulStructures::reg_num::v0;
			res[1] = MipsSimulator.reg[UsefulStructures::reg_num::v0];
			res[2] = MipsSimulator.reg[UsefulStructures::reg_num::a0];
			res[4] = MipsSimulator.reg[UsefulStructures::reg_num::a1];
		}
	}
	else {
		res[0] = static_cast<long long> (argutoken.r[0]);
		res[3] = static_cast<long long> (argutoken.offset);
		for (int i = 1; i < 3; ++i) {
			if (argutoken.rstate[i] == UsefulStructures::r_state::regi) {
				if (usefulstructures.Busy(argutoken.r[i], busyreg)) {
					state = UsefulStructures::pip_run_state::pause;
					return;
				}
				unsigned tmp = MipsSimulator.reg[argutoken.r[i]];
				res[i] = static_cast<long long> (tmp);
			}
			else if (argutoken.rstate[i] == UsefulStructures::r_state::immi) {
				unsigned tmp = argutoken.r[i];
				res[i] = static_cast<long long> (tmp);
			}
		}
		if (argutoken.rstate[0] == UsefulStructures::r_state::regi)
			res[4] = static_cast<long long> (MipsSimulator.reg[argutoken.r[0]]);
	}
}

void CommandClass::Command_Base::memory_access(long long r[5], string &s)
{
	if (r[4] == -9) {
		char c = MipsSimulator.memory[r[1]];
		for (int i = 1; c != 0; ++i) {
			s += c;
			c = MipsSimulator.memory[r[1] + i];
		}
	}
	else if (r[4] == -6) {
		/// syscall
		/// r[0] is the the num of $v0
		/// r[1] is the content of $v0
		/// r[2] is the content of $a0
		/// r[3] is the content of $a1
		int a;
		cin >> a;
		r[1] = static_cast<long long> (a);
	}
	else if (r[4] == -3) {
		if (r[2] != 0) {
			for (int i = 0; i < r[2]; ++i) {
				s += MipsSimulator.memory[r[0] + i];
			}
		}
	}
	else if (r[4] == -11) {
		cin >> s;
		if (static_cast<unsigned>(r[3] - 1) < s.length()) {
			s.substr(0, static_cast<unsigned>(r[3] - 1));
		}
	}
}

void CommandClass::Command_Base::write_back(long long r[5], int busyreg[4], string & s)
{
	if (r[4] >= 0 || r[4] == -6) {
		MipsSimulator.reg[r[0]] = static_cast<unsigned>(r[1]);
	}
	else if (r[4] == -2) {
		cout << r[2] << endl;
	}
	else if (r[4] == -9) {
		cout << s << endl;
	}
	else if (r[4] == -5) {
		char *tmp = reinterpret_cast<char*> (r[1]);
		for (int i = 0; i < r[2]; ++i) {
			MipsSimulator.reg[r[0]+i] = tmp[i];
		}
		if (r[0] + r[2] > MipsSimulator.mem_pos)
			MipsSimulator.mem_pos = static_cast<int>(r[0] + r[2]);
	}
	else if (r[4] == -7) {
		cout << r[2] << endl;
	}
	else if (r[4] == -8){
		char *tmp = reinterpret_cast<char*>(r[2]);
		r[0] = tmp[0];
		r[1] = tmp[1];
	}
	else if (r[4] == -10) {
		MipsSimulator.reg[static_cast<unsigned>(r[0])] = MipsSimulator.mem_pos;
		MipsSimulator.mem_pos += static_cast<int>(r[2]);
	}
	else if (r[4] == -11) {
		for (unsigned i = 0; i < s.length(); ++i) {
			MipsSimulator.memory[static_cast<unsigned>(r[2]) + i] = s[i];
		}
		if (r[2] + s.length() > MipsSimulator.mem_pos) 
			MipsSimulator.mem_pos = static_cast<int>(r[2]) + s.length();
	}
}
