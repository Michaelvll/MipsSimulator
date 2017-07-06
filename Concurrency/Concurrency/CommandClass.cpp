#include "CommandClass.h"
#include "MipsSimulatorClass.h"
#include <condition_variable>
#include <iostream>
#include <thread>
#include <mutex>
using std::cout;
using std::endl;
using std::cin;
using std::clog;
using std::mutex;
using std::unique_lock;

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
* r[4] == -10 need to allocate mem with length of r[2] and put the address to
* reg[r[0]]
* r[4] == -11 need to read a string from I/O device to r[0]
*/

bool CommandClass::Add::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Add" << endl;
	// MipsSimulator.log << "Execute Add" << endl;

	r[1] = static_cast<int>(r[1]) + static_cast<int>(r[2]);
	r[4] = 3;

	return true;
}

bool CommandClass::Addu::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])

	// clog << "Execute Addu" << endl;
	// MipsSimulator.log << "Execute Addu" << endl;

	unsigned a = static_cast<unsigned>(r[1]) + static_cast<unsigned>(r[2]);
	r[1] = static_cast<long long>(a);
	r[4] = 3;

	return true;
}

bool CommandClass::Sub::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Sub" << endl;
	// MipsSimulator.log << "Execute Sub" << endl;

	r[1] = static_cast<int>(r[1]) - static_cast<int>(r[2]);
	r[4] = 3;

	return true;
}

bool CommandClass::Subu::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])

	// clog << "Execute Subu" << endl;
	// MipsSimulator.log << "Execute Subu" << endl;

	unsigned a = static_cast<unsigned>(r[1]) - static_cast<unsigned>(r[2]);
	r[1] = static_cast<long long>(a);
	r[4] = 3;

	return true;
}

bool CommandClass::Mul::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Mul" << endl;
	// MipsSimulator.log << "Execute Mul" << endl;

	int a = static_cast<int>(r[1]) * static_cast<int>(r[2]);
	r[1] = static_cast<long long>(a);
	r[4] = 3;

	return true;
}

bool CommandClass::Mulu::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (long long)

	// clog << "Execute Mulu" << endl;
	// MipsSimulator.log << "Execute Mulu" << endl;

	unsigned c = static_cast<unsigned>(r[1]) * static_cast<unsigned>(r[2]);
	r[1] = static_cast<long long>(c);
	r[4] = 3;

	return true;
}

CommandClass::Mul2::Mul2() { read_first_reg = true; }

bool CommandClass::Mul2::exec(long long r[5]) {
	/// Input r[1] and r[4] which should be static_cast<long long> (unsigned)
	/// Output r[2] which can be used as s = reinterpret_cast<char*> (r[1]); char
	/// s1[2] = {s[0],s[1]return true;}; lo = *(reinterpret_cast<unsigned*>
	/// (s1));...

	// clog << "Execute Mul2" << endl;
	// MipsSimulator.log << "Execute Mul2" << endl;

	int a = static_cast<int>(r[4]), b = static_cast<int>(r[1]);
	r[2] = static_cast<long long>(a) * static_cast<long long>(b);
	r[0] = UsefulStructures::reg_num::lo;
	r[1] = UsefulStructures::reg_num::hi;
	r[4] = -8;

	return true;
}
CommandClass::Mulu2::Mulu2() { read_first_reg = true; }
bool CommandClass::Mulu2::exec(long long r[5]) {
	/// Input r[1] and r[4] which should be static_cast<long long> (unsigned)
	/// Output r[2] which can be used as s = reinterpret_cast<char*> (r[2]); char
	/// s1[2] = {s[0],s[1]return true;}; lo = *(reinterpret_cast<unsigned*>
	/// (s1));...

	// clog << "Execute Mulu2" << endl;
	// MipsSimulator.log << "Execute Mulu2" << endl;

	unsigned long long a = static_cast<unsigned long long>(r[1]),
		b = static_cast<unsigned long long>(r[4]);
	unsigned long long c = a * b;
	r[2] = static_cast<long long>(c);
	r[0] = UsefulStructures::reg_num::lo;
	r[1] = UsefulStructures::reg_num::hi;
	r[4] = -8;

	return true;
}

bool CommandClass::Div::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Div" << endl;
	// MipsSimulator.log << "Execute Div" << endl;

	r[1] = static_cast<int>(r[1]) / static_cast<int>(r[2]);
	r[4] = 3;

	return true;
}

bool CommandClass::Divu::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Divu" << endl;
	// MipsSimulator.log << "Execute Divu" << endl;

	r[1] = static_cast<unsigned>(r[1]) / static_cast<unsigned>(r[2]);
	r[4] = 3;

	return true;
}
CommandClass::Div2::Div2() { read_first_reg = true; }
bool CommandClass::Div2::exec(long long r[5]) {
	/// Input r[1] and r[4] which should be static_cast<long long> (unsigned)
	/// Output r[2] which can be used as s = reinterpret_cast<char*> (r[2]);
	/// char s1[2] = {s[0],s[1]}; lo = *(reinterpret_cast<unsigned*> (s1));...

	// clog << "Execute Div2" << endl;
	// MipsSimulator.log << "Execute Div2" << endl;

	int a = static_cast<int>(r[4]), b = static_cast<int>(r[1]);
	r[2] = a / b;
	r[2] |= (static_cast<unsigned long long>(a % b) << 32);
	r[0] = UsefulStructures::reg_num::lo;
	r[1] = UsefulStructures::reg_num::hi;
	r[4] = -8;

	return true;
}
CommandClass::Divu2::Divu2() { read_first_reg = true; }
bool CommandClass::Divu2::exec(long long r[5]) {
	/// Input r[1] and r[4] which should be static_cast<long long> (unsigned)
	/// Output r[2] which can be used as s = reinterpret_cast<char*> (r[2]);
	/// char s1[2] = {s[0],s[1]}; lo = *(reinterpert_cast<unsigned*> (s1));...

	// clog << "Execute Divu2" << endl;
	// MipsSimulator.log << "Execute Divu2" << endl;

	unsigned a = static_cast<unsigned>(r[4]), b = static_cast<unsigned>(r[1]);
	r[2] = a / b;
	r[2] |= (static_cast<unsigned long long>(a % b) << 32);
	r[0] = UsefulStructures::reg_num::lo;
	r[1] = UsefulStructures::reg_num::hi;
	r[4] = -8;

	return true;
}

bool CommandClass::Xor1::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute xor1" << endl;
	// MipsSimulator.log << "Execute Xor1" << endl;

	r[1] = r[1] ^ r[2];
	r[4] = 3;

	return true;
}

bool CommandClass::Xoru::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Xoru" << endl;
	// MipsSimulator.log << "Execute Xoru" << endl;

	r[1] = r[1] ^ r[2];
	r[4] = 3;

	return true;
}

bool CommandClass::Neg::exec(long long r[5]) {
	/// Input r[1] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Neg" << endl;
	// MipsSimulator.log << "Execute Neg" << endl;

	r[1] = -r[1];
	r[4] = 3;

	return true;
}

bool CommandClass::Negu::exec(long long r[5]) {
	/// Input r[1] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])

	// clog << "Execute Negu" << endl;
	// MipsSimulator.log << "Execute Negu" << endl;

	unsigned a = static_cast<unsigned>(r[1]);
	unsigned b = -a;
	r[1] = static_cast<long long>(b);
	r[4] = 3;

	return true;
}

bool CommandClass::Rem::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Rem" << endl;
	// MipsSimulator.log << "Execute Rem" << endl;

	int c = static_cast<int>(r[1]) % static_cast<int>(r[2]);
	r[1] = static_cast<long long>(c);
	r[4] = 3;

	return true;
}

bool CommandClass::Remu::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])

	// clog << "Execute Remu" << endl;
	// MipsSimulator.log << "Execute Remu" << endl;

	unsigned a = static_cast<unsigned>(r[1]) % static_cast<unsigned>(r[2]);
	r[1] = a;
	r[4] = 3;

	return true;
}

bool CommandClass::Li::exec(long long r[5]) {

	// clog << "Execute Li" << endl;
	// MipsSimulator.log << "Execute Li" << endl;

	r[4] = 3;

	return true;
}

bool CommandClass::Seq::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Seq" << endl;
	// MipsSimulator.log << "Execute Seq" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a == b) ? 1 : 0;
	r[4] = 3;

	return true;
}

bool CommandClass::Sge::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Sge" << endl;
	// MipsSimulator.log << "Execute Sge" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a >= b) ? 1 : 0;
	r[4] = 3;

	return true;
}

bool CommandClass::Sgt::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Sgt" << endl;
	// MipsSimulator.log << "Execute Sgt" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a > b) ? 1 : 0;
	r[4] = 3;

	return true;
}

bool CommandClass::Sle::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Sle" << endl;
	// MipsSimulator.log << "Execute Sle" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a <= b) ? 1 : 0;
	r[4] = 3;

	return true;
}

bool CommandClass::Slt::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Slt" << endl;
	// MipsSimulator.log << "Execute Slt" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a < b) ? 1 : 0;
	r[4] = 3;

	return true;
}

bool CommandClass::Sne::exec(long long r[5]) {
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])

	// clog << "Execute Sne" << endl;
	// MipsSimulator.log << "Execute Sne" << endl;

	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = (a != b) ? 1 : 0;
	r[4] = 3;

	return true;
}

bool CommandClass::B::exec(long long r[5]) {
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute B" << endl;
	// MipsSimulator.log << "Execute B" << endl;

	r[1] = r[0];
	r[4] = 1;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Beq::Beq() { read_first_reg = true; }

bool CommandClass::Beq::exec(long long r[5]) {
	/// Input r[0] and  which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Beq" << endl;
	// MipsSimulator.log << "Execute Beq" << endl;

	int a = static_cast<int>(r[4]), b = static_cast<int>(r[1]);
	if (a == b) {
		r[4] = 1;
		r[1] = r[2];
	}
	else
		r[4] = 0;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Bne::Bne() { read_first_reg = true; }

bool CommandClass::Bne::exec(long long r[5]) {
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Bne" << endl;
	// MipsSimulator.log << "Execute Bne" << endl;

	int a = static_cast<int>(r[4]), b = static_cast<int>(r[1]);
	if (a != b) {
		r[4] = 1;
		r[1] = r[2];
	}
	else
		r[4] = 0;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Bge::Bge() { read_first_reg = true; }

bool CommandClass::Bge::exec(long long r[5]) {
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Bge" << endl;
	// MipsSimulator.log << "Execute Bge" << endl;

	int a = static_cast<int>(r[4]), b = static_cast<int>(r[1]);
	if (a >= b) {
		r[4] = 1;
		r[1] = r[2];
	}
	else
		r[4] = 0;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Ble::Ble() { read_first_reg = true; }

bool CommandClass::Ble::exec(long long r[5]) {
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Ble" << endl;
	// MipsSimulator.log << "Execute Ble" << endl;

	int a = static_cast<int>(r[4]), b = static_cast<int>(r[1]);
	if (a <= b) {
		r[4] = 1;
		r[1] = r[2];
	}
	else
		r[4] = 0;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Bgt::Bgt() { read_first_reg = true; }

bool CommandClass::Bgt::exec(long long r[5]) {
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Bgt" << endl;
	// MipsSimulator.log << "Execute Bgt" << endl;

	int a = static_cast<int>(r[4]), b = static_cast<int>(r[1]);
	if (a > b) {
		r[4] = 1;
		r[1] = r[2];
	}
	else
		r[4] = 0;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Blt::Blt() { read_first_reg = true; }

bool CommandClass::Blt::exec(long long r[5]) {
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Blt" << endl;
	// MipsSimulator.log << "Execute Blt" << endl;

	int a = static_cast<int>(r[4]), b = static_cast<int>(r[1]);
	if (a < b) {
		r[4] = 1;
		r[1] = r[2];
	}
	else
		r[4] = 0;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Beqz::Beqz() { read_first_reg = true; }

bool CommandClass::Beqz::exec(long long r[5]) {
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Beqz" << endl;
	// MipsSimulator.log << "Execute Beqz" << endl;

	int a = static_cast<int>(r[4]);
	if (a == 0) {
		r[4] = 1;
	}
	else
		r[4] = 0;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Bnez::Bnez() { read_first_reg = true; }

bool CommandClass::Bnez::exec(long long r[5]) {
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Bnez" << endl;
	// MipsSimulator.log << "Execute Bnez" << endl;

	int a = static_cast<int>(r[4]);
	if (a != 0) {
		r[4] = 1;
	}
	else
		r[4] = 0;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Blez::Blez() { read_first_reg = true; }

bool CommandClass::Blez::exec(long long r[5]) {
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Blez" << endl;
	// MipsSimulator.log << "Execute Blez" << endl;

	int a = static_cast<int>(r[4]);
	if (a <= 0) {
		r[4] = 1;
	}
	else
		r[4] = 0;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Bgez::Bgez() { read_first_reg = true; }

bool CommandClass::Bgez::exec(long long r[5]) {
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Bgez" << endl;
	// MipsSimulator.log << "Execute Bgez" << endl;

	int a = static_cast<int>(r[4]);
	if (a >= 0) {
		r[4] = 1;
	}
	else
		r[4] = 0;
	r[0] = UsefulStructures::reg_num::pc;
	return false;
}

CommandClass::Bgtz::Bgtz() { read_first_reg = true; }

bool CommandClass::Bgtz::exec(long long r[5]) {
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Bgtz" << endl;
	// MipsSimulator.log << "Execute Bgtz" << endl;

	int a = static_cast<int>(r[4]);
	if (a > 0) {
		r[4] = 1;
	}
	else
		r[4] = 0;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Bltz::Bltz() { read_first_reg = true; }

bool CommandClass::Bltz::exec(long long r[5]) {
	/// Input r[0] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Bltz" << endl;
	// MipsSimulator.log << "Execute Bltz" << endl;

	int a = static_cast<int>(r[4]);
	if (a < 0) {
		r[4] = 1;
	}
	else
		r[4] = 0;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

bool CommandClass::J::exec(long long r[5]) {
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute J" << endl;
	// MipsSimulator.log << "Execute J" << endl;

	r[1] = r[0];
	r[4] = 1;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Jr::Jr() { read_first_reg = true; }

bool CommandClass::Jr::exec(long long r[5]) {
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Jr" << endl;
	// MipsSimulator.log << "Execute Jr" << endl;

	r[1] = r[4];
	r[4] = 1;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

bool CommandClass::Jal::exec(long long r[5]) {
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Jal" << endl;
	// MipsSimulator.log << "Execute Jal" << endl;

	r[1] = r[0];
	r[4] = 2;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

CommandClass::Jalr::Jalr() { read_first_reg = true; }

bool CommandClass::Jalr::exec(long long r[5]) {
	/// Input r[0] and r[1] which should be static_cast<long long> (unsigned)
	/// Output r[4], if (r[4]) goto r[1] i.e reg[r[0]] = r[1]

	// clog << "Execute Jalr" << endl;
	// MipsSimulator.log << "Execute Jalr" << endl;

	r[1] = r[4];
	r[4] = 2;
	r[0] = UsefulStructures::reg_num::pc;

	return false;
}

bool CommandClass::La::exec(long long r[5]) {
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should be loaded

	// clog << "Execute La" << endl;
	// MipsSimulator.log << "Execute La" << endl;

	r[1] += r[3];
	r[2] = 0;
	r[4] = -3;

	return true;
}

bool CommandClass::Lb::exec(long long r[5]) {
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should be loaded

	// clog << "Execute Lb" << endl;
	// MipsSimulator.log << "Execute Lb" << endl;

	r[1] += r[3];
	r[2] = 1;
	r[4] = -3;

	return true;
}

bool CommandClass::Lh::exec(long long r[5]) {
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should be loaded

	// clog << "Execute Lh" << endl;
	// MipsSimulator.log << "Execute Lh" << endl;

	r[1] += r[3];
	r[2] = 2;
	r[4] = -3;

	return true;
}

bool CommandClass::Lw::exec(long long r[5]) {
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should be loaded

	// clog << "Execute Lw" << endl;
	// MipsSimulator.log << "Execute Lw" << endl;

	r[1] += r[3];
	r[2] = 4;
	r[4] = -3;

	return true;
}

CommandClass::Sb::Sb() { read_first_reg = true; }

bool CommandClass::Sb::exec(long long r[5]) {
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should save in

	// clog << "Execute Sb" << endl;
	// MipsSimulator.log << "Execute Sb" << endl;

	r[0] = r[1] + r[3];
	r[1] = r[4];
	r[2] = 1;
	r[4] = -5;
	return true;
}

CommandClass::Sh::Sh() { read_first_reg = true; }

bool CommandClass::Sh::exec(long long r[5]) {
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should save in

	// clog << "Execute Sh" << endl;
	// MipsSimulator.log << "Execute Sh" << endl;

	r[0] = r[1] + r[3];
	r[1] = r[4];
	r[2] = 2;
	r[4] = -5;
	return true;
}

CommandClass::Sw::Sw() { read_first_reg = true; }

bool CommandClass::Sw::exec(long long r[5]) {
	/// r[0] is the no of rdest
	/// r[1] is the address in memory
	/// r[2] is the number of bytes that should save in

	// clog << "Execute Sw" << endl;
	// MipsSimulator.log << "Execute Sw" << endl;

	r[0] = r[1] + r[3];
	r[1] = r[4];
	r[2] = 4;
	r[4] = -5;
	return true;
}

bool CommandClass::Move::exec(long long r[5]) {
	// clog << "Execute Move" << endl;
	// MipsSimulator.log << "Execute Move" << endl;

	r[4] = 3;

	return true;
}

bool CommandClass::Mfhi::exec(long long r[5]) {
	// clog << "Execute Mfhi" << endl;
	// MipsSimulator.log << "Execute Mfhi" << endl;

	r[4] = 3;

	return true;
}

bool CommandClass::Mflo::exec(long long r[5]) {
	// clog << "Execute Mflo" << endl;
	// MipsSimulator.log << "Execute Mflo" << endl;

	r[4] = 3;

	return true;
}

bool CommandClass::Nop::exec(long long r[5]) {
	r[4] = 5;

	// clog << "Execute Nop" << endl;
	// MipsSimulator.log << "Execute Nop" << endl;
	return false;
}

bool CommandClass::Syscall::exec(long long r[5]) {
	/// r[0] is the the num of $v0
	/// r[1] is the content of $v0
	/// r[2] is the content of $a0
	/// r[3] is the content of $a1

	// clog << "Execute Syscall" << endl;
	// MipsSimulator.log << "Execute Syscall" << endl;

	if (r[1] == 1) {
		r[4] = -7;
	}
	else if (r[1] == 4) {
		r[4] = -9;
	}
	else if (r[1] == 5) {
		r[4] = -6;
	}
	else if (r[1] == 8) {
		r[4] = -11;
	}
	else if (r[1] == 9) {
		r[4] = -10;
	}
	else if (r[1] == 10) {
		r[4] = -1;
	}
	else if (r[1] == 17) {
		r[4] = -2;
	}
	return false;
}

bool CommandClass::Empty::exec(long long r[5]) {
	// clog << "Execute Empty!!!!" << endl;
	// MipsSimulator.log << "Execute Empty!!!!" << endl;

	return false;
}

void CommandClass::Command_Base::data_preparation(const UsefulStructures::Token &token, long long res[5]) {
	/// res[0] = origin of the argue1
	/// res[1] = represented content of arue2
	/// res[2] = represented content of arue3
	/// res[3] = offset
	/// res[4] = represented content of argue1
	if (token.rstate[0] == UsefulStructures::r_state::none) {
		// TODO syscall
		/// r[0] is the the num of $v0
		/// r[1] is the content of $v0
		/// r[2] is the content of $a0
		/// r[3] is the content of $a1
		res[0] = UsefulStructures::reg_num::v0;
		res[1] = MipsSimulator.reg[UsefulStructures::reg_num::v0];
		res[2] = MipsSimulator.reg[UsefulStructures::reg_num::a0];
		res[3] = MipsSimulator.reg[UsefulStructures::reg_num::a1];

		unique_lock<mutex> lk(MipsSimulator.bsyrg);
		if (usefulstructures.Busy(UsefulStructures::reg_num::v0,
			MipsSimulator.busyreg)) {
			MipsSimulator.run_state = UsefulStructures::pip_run_state::pause;
			// clog << "Find the reg$v0 is busy and pause" << endl;
			// MipsSimulator.log << "Find the reg$v0 is busy and pause" << endl;
			return;
		}
		if (usefulstructures.Busy(UsefulStructures::reg_num::a0,
			MipsSimulator.busyreg) &&
			res[1] != 5 && res[1] != 10) {
			MipsSimulator.run_state = UsefulStructures::pip_run_state::pause;
			// clog << "Find the reg$a0 is busy and pause" << endl;
			// MipsSimulator.log << "Find the reg$a0 is busy and pause" << endl;
			return;
		}
		if (usefulstructures.Busy(UsefulStructures::reg_num::a1,
			MipsSimulator.busyreg) &&
			res[1] == 8) {
			MipsSimulator.run_state = UsefulStructures::pip_run_state::pause;
			// clog << "Find the reg$a1 is busy and pause" << endl;
			// MipsSimulator.log << "Find the reg$a1 is busy and pause" << endl;
			return;
		}

		// clog << "Get r[0] as reg$v0: " << res[0] << "\nr[1] as content of
		// regi$v0: " << res[1] << "\nr[2] as the content of reg$a0: " << res[2] <<
		// "\nr[3] as the content of reg$a1: "<< res[3] << endl;
		// MipsSimulator.log << "Get r[0] as reg$v0: " << res[0] << "\nr[1] as
		// content of regi$v0: "<< res[1] << "\nr[2] as the content of reg$a0: " <<
		// res[2] << "\nr[3] as the content of reg$a1: "<< res[3] << endl;
	}
	else {
		res[0] = static_cast<long long>(token.r[0]);
		res[3] = static_cast<long long>(token.offset);

		// clog << "Get r[0] as reg: " << res[0] << '\n';
		// MipsSimulator.log << "Get r[0] as reg:(except b j) " << res[0] << '\n';

		// clog << "r[3] as the offset: " << res[3] << endl;
		// MipsSimulator.log << "r[3] as the offset: " << res[3] << endl;

		for (int i = 1; i < 3; ++i) {
			if (token.rstate[i] == UsefulStructures::r_state::regi) {
				unique_lock<mutex> lk(MipsSimulator.bsyrg);
				if (usefulstructures.Busy(token.r[i], MipsSimulator.busyreg)) {
					// clog << "Find the reg$" << token.r[i] << " is busy and pause" <<
					// endl;
					// MipsSimulator.log << "Find the reg$" << token.r[i] << " is busy and
					// pause" << endl;

					MipsSimulator.run_state = UsefulStructures::pip_run_state::pause;
					return;
				}
				unsigned tmp = MipsSimulator.reg[token.r[i]];
				res[i] = static_cast<long long>(tmp);

				// clog << "r[" << i << "] as the content of reg$" << token.r[i] << ": "
				// << res[i] << '\n';
				// MipsSimulator.log << "r[" << i << "] as the content of reg$" <<
				// token.r[i] << ": " << res[i] << '\n';
			}
			else if (token.rstate[i] == UsefulStructures::r_state::immi) {
				res[i] = static_cast<long long>(token.r[i]);

				// clog << "r[" << i << "] as a immidiate num: " << res[i] << endl;
				// MipsSimulator.log << "r[" << i << "] as a immidiate num: " << res[i]
				// << endl;
			}
		}

		if (token.op == UsefulStructures::op_num::mfhi) {
			unique_lock<mutex> lk(MipsSimulator.bsyrg);
			if (usefulstructures.Busy(UsefulStructures::reg_num::hi,
				MipsSimulator.busyreg)) {
				// clog << "Find the reg$hi is busy and pause" << endl;
				// MipsSimulator.log << "Find the reg$hi is busy and pause" << endl;

				MipsSimulator.run_state = UsefulStructures::pip_run_state::pause;
				return;
			}
			unsigned tmp = MipsSimulator.reg[UsefulStructures::reg_num::hi];
			res[1] = static_cast<long long>(tmp);

			// clog << "r[" << 1 << "] as the content of reg$hi: " << res[1] << '\n';
			// MipsSimulator.log << "r[" << 1 << "] as the content of reg$hi: " <<
			// res[1] << '\n';
		}
		else if (token.op == UsefulStructures::op_num::mflo) {
			unique_lock<mutex> lk(MipsSimulator.bsyrg);
			if (usefulstructures.Busy(UsefulStructures::reg_num::lo,
				MipsSimulator.busyreg)) {
				// clog << "Find the reg$lo is busy and pause" << endl;
				// MipsSimulator.log << "Find the reg$lo is busy and pause" << endl;

				MipsSimulator.run_state = UsefulStructures::pip_run_state::pause;
				return;
			}
			unsigned tmp = MipsSimulator.reg[UsefulStructures::reg_num::lo];
			res[1] = static_cast<long long>(tmp);

			// clog << "r[" << 1 << "] as the content of reg$lo: " << res[1] << '\n';
			// MipsSimulator.log << "r[" << 1 << "] as the content of reg$lo: " <<
			// res[1] << '\n';
		}

		if (MipsSimulator.op_class_tab[token.op]->read_first_reg &&
			token.rstate[0] == UsefulStructures::r_state::regi) {
			// clog << "Now op needs to read the first reg$" << res[0] << endl;
			// MipsSimulator.log << "Now op needs to read the first reg$" << res[0] <<
			// endl;
			unique_lock<mutex> lk(MipsSimulator.bsyrg);
			if (usefulstructures.Busy(static_cast<unsigned>(res[0]),
				MipsSimulator.busyreg)) {
				MipsSimulator.run_state = UsefulStructures::pip_run_state::pause;
				// clog << "Find the reg$"<< res[0] <<" is busy and pause" << endl;
				// MipsSimulator.log << "Find the reg$" << res[0] << " is busy and
				// pause" << endl;
				return;
			}
			res[4] = static_cast<long long>(MipsSimulator.reg[res[0]]);
			// MipsSimulator.log << "r[4] as the content of reg$" << res[0] << ": " <<
			// res[4] << endl;
		}
	}
}

void CommandClass::Command_Base::memory_access(long long r[5]) {
	if (r[4] == -9) {
		char c = MipsSimulator.memory[r[2]];
		string s;
		for (int i = 1; c != 0; ++i) {
			s += c;
			c = MipsSimulator.memory[r[2] + i];
		}
		// clog << "r[4] is -9, and get a string from mem[r[2]](mem[" << r[2] << "])
		// and the string is " << s << endl;
		// MipsSimulator.log << "r[4] is -9, and get a string from mem[r[2]](mem["
		// << r[2] << "]) and the string is " << s << endl;

		// clog << " write back to the I/O device with the string " << s << endl;
		// MipsSimulator.log << " write back to the I/O device with the string " <<
		// s << endl;
		cout << s;
	}
	else if (r[4] == -6) {
		/// syscall
		/// r[0] is the the num of $v0
		/// r[1] is the content of $v0
		/// r[2] is the content of $a0
		/// r[3] is the content of $a1
		int a;
		cin >> a;
		r[1] = static_cast<long long>(a);
		// clog << "r[4] is -6, and get a int from I/O device which is " << a <<
		// endl;
		// MipsSimulator.log << "r[4] is -6, and get a int from I/O device which is
		// " << a << endl;
	}
	else if (r[4] == -3) {
		char tmp[4] = { 0 };
		for (int i = 0; i < r[2]; ++i) {
			tmp[i] = MipsSimulator.memory[r[1] + i];
		}

		// clog << "r[4] is -3, and get a string from the mem[r[0]] to
		// mem[r[0]+r[2]-1](" << r[1] << ", " << r[0] + r[2] - 1 << ")  and the
		// string is " << s << endl;
		// MipsSimulator.log << "r[4] is -3, and get a number from the mem[r[0]] to
		// mem[r[0]+r[2]-1](" << r[1] << ", " << r[1] + r[2] - 1 << ")  and the
		// number is " << *(reinterpret_cast<unsigned*>(tmp)) << endl;
		if (r[2] != 0)
			r[1] = *(reinterpret_cast<unsigned *>(tmp));
	}
	else if (r[4] == -11) {
		string s;
		cin >> s;
		if (s.length() > static_cast<unsigned>(r[3] - 1))
			s = s.substr(0, static_cast<int>(r[3]) - 1);
		// clog << "r[4] is -11, and get a string of length " << s.length() << "
		// from the I/O device which is " << s << endl;
		// MipsSimulator.log << "r[4] is -11, and get a string of length " <<
		// s.length() << " from the I/O device which is " << s << endl;

		// clog << " write the string read from the I/O device back to the memory["
		// << r[2] << "] to memory[" << r[2] + s.length() - 1 << "]" << endl;
		// MipsSimulator.log << " write the string read from the I/O device back to
		// the memory[" << r[2] << "] to memory[" << r[2] + s.length() - 1 << "]" <<
		// endl;
		for (unsigned i = 0; i < s.length(); ++i) {
			MipsSimulator.memory[static_cast<unsigned>(r[2]) + i] = s[i];
		}
		// if (r[2] + s.length() > MipsSimulator.mem_pos) MipsSimulator.mem_pos =
		// static_cast<int>(r[2]) + s.length();
	}
	else if (r[4] == -2) {
		// clog << " write back to the I/O device for syscall 17 with the int " <<
		// static_cast<int>(r[2]) << endl;
		// MipsSimulator.log << "write back to the I/O device for syscall 17 with
		// the int " << static_cast<int>(r[2]) << endl;
		cout << static_cast<int>(r[2]);
	}
	else if (r[4] == -5) {
		// clog << " write back to the memory[" << r[0] << "] to memory[" << r[0] +
		// r[2] - 1 << "] with the chars reinterpreted from " << r[1] << endl;
		// MipsSimulator.log << " write back to the memory[" << r[0] << "] to
		// memory[" << r[0] + r[2] - 1 << "] with the chars reinterpreted from " <<
		// r[1] << endl;
		char *tmp = reinterpret_cast<char *>(&r[1]);
		for (int i = 0; i < r[2]; ++i) {
			if (r[0] + i > 4 * 1024 * 1024)
				throw(0);
			MipsSimulator.memory[r[0] + i] = tmp[i];
		}
		// if (r[0] + r[2] > MipsSimulator.mem_pos) MipsSimulator.mem_pos =
		// static_cast<int>(r[0] + r[2]);
	}
	else if (r[4] == -7) {
		// clog << " write back to the I/O device for syscall 1 with the int " <<
		// static_cast<int>(r[2]) << endl;
		// MipsSimulator.log << " write back to the I/O device for syscall 1 with
		// the int " << static_cast<int>(r[2]) << endl;
		cout << static_cast<int>(r[2]);
	}
	else if (r[4] == -10) {
		// clog << " allocate new place with length of " << static_cast<unsigned>
		// (r[2]) << endl;
		// MipsSimulator.log << " allocate new place with length of " <<
		// static_cast<unsigned> (r[2]) << endl;
		MipsSimulator.mem_pos += static_cast<int>(r[2]);
	}
	else if (r[4] < -11 || r[4] > 5 || r[4] == 4) {
		// clog << "Get a unknown r[4]!!!!!!!!" << endl;
		// MipsSimulator.log << "Get a unknown r[4]!!!!!!!!" << endl;
		throw(0);
	}
}

void CommandClass::Command_Base::write_back(long long r[5]) {
	// clog << "r[4] is " << r[4];
	// MipsSimulator.log << "r[4] is " << r[4];
	if (r[4] >= 0 || r[4] == -6) {
		// clog << " write back to reg$" << r[0] << " using the data " <<
		// static_cast<unsigned>(r[1]) << endl;
		// MipsSimulator.log << " write back to reg$" << r[0] << " using the data "
		// << static_cast<unsigned>(r[1]) << endl;
		MipsSimulator.reg[r[0]] = static_cast<unsigned>(r[1]);
		unique_lock<mutex> lk(MipsSimulator.bsyrg);
		usefulstructures.delBusy(static_cast<int>(r[0]), MipsSimulator.busyreg);
		if (r[4] == 2) {
			// MipsSimulator.log << "write back to reg$" << r[2] << " using the data "
			// << static_cast<unsigned>(r[3]) << endl;
			MipsSimulator.reg[r[2]] = static_cast<unsigned>(r[3]);
			usefulstructures.delBusy(static_cast<int>(r[2]), MipsSimulator.busyreg);
		}
	}
	else if (r[4] == -8) {
		// clog << " write back to the reg$" << r[0] << "(lo) and reg$" << r[1] <<
		// "(hi) with the chars(4 chars each) reinterpreted from " << r[2] << endl;
		// MipsSimulator.log << " write back to the reg$" << r[0] << "(lo) and reg$"
		// << r[1] << "(hi) with the chars(4 chars each) reinterpreted from " <<
		// r[2] << endl;
		char *tmp = reinterpret_cast<char *>(&r[2]);
		char s1[4] = { tmp[0], tmp[1], tmp[2], tmp[3] },
			s2[4] = { tmp[4], tmp[5], tmp[6], tmp[7] };
		MipsSimulator.reg[r[0]] = *(reinterpret_cast<unsigned *>(s1));
		MipsSimulator.reg[r[1]] = *(reinterpret_cast<unsigned *>(s2));
		unique_lock<mutex> lk(MipsSimulator.bsyrg);
		usefulstructures.delBusy(static_cast<int>(r[0]), MipsSimulator.busyreg);
		usefulstructures.delBusy(static_cast<int>(r[1]), MipsSimulator.busyreg);
	}
	else if (r[4] == -10) {
		// clog << " write back the first address of the allocated space in memory
		// of the length of "<< static_cast<int>(r[2]) <<" back to reg$" << r[0] <<
		// endl;
		// MipsSimulator.log << " write back the first address of the allocated
		// space in memory of the length of "<< static_cast<int>(r[2]) <<" back to
		// reg$" << r[0] << endl;
		MipsSimulator.reg[r[0]] = MipsSimulator.mem_pos - static_cast<int>(r[2]);
		unique_lock<mutex> lk(MipsSimulator.bsyrg);
		usefulstructures.delBusy(static_cast<int>(r[0]), MipsSimulator.busyreg);
	}
	else if (r[4] == -3) {
		unsigned tmp = static_cast<unsigned>(r[1]);
		MipsSimulator.reg[r[0]] = tmp;

		// For log
		if (r[2] == 0) {
			// clog << "Put the address: " << r[1] << " into reg$" << r[0] << endl;
			// MipsSimulator.log << " Put the address: " << r[1] << " into reg$" <<
			// r[0] << endl;
		}
		else {
			// clog << "Get a number: " << *(reinterpret_cast<unsigned*>(tmp)) <<
			// endl;
			// MipsSimulator.log << " Write back the number " << tmp << " back to the
			// reg$" << r[0] << endl;
		}
		unique_lock<mutex> lk(MipsSimulator.bsyrg);
		usefulstructures.delBusy(static_cast<unsigned>(r[0]),
			MipsSimulator.busyreg);
	}
}

CommandClass::Command_Base::~Command_Base() {}
