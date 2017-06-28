#include "CommandClass.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

/// If return false && r[0] == 1 || 5, then stop the instruction before
/// If return false && r[0] == -1, then stop the program
/// if return false && r[0] == -2, then stop the program and return r[2]
/// Label is then in r[1]
bool CommandClass::Add::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = static_cast<int>(r[1]) + static_cast<int>(r[2]);
	return true;
}

bool CommandClass::Addu::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])
	r[1] = r[1] + r[2];
	return true;
}

bool CommandClass::Sub::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = static_cast<int>(r[1]) - static_cast<int>(r[2]);
	return true;
}

bool CommandClass::Subu::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])
	r[1] = r[1] - r[2];
	return true;
}

bool CommandClass::Mul::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	int a = static_cast<int>(r[1]) * static_cast<int>(r[2]);
	r[1] = static_cast<long long> (a);
	return true;
}

bool CommandClass::Mulu::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (long long)
	r[1] = static_cast<unsigned>(r[1]) * static_cast<unsigned>(r[2]);
	return true;
}

bool CommandClass::Mul2::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as s = reinterpret_cast<char*> (r[1]); char s1[2] = {s[0],s[1]return true;}; lo = *(reinterpret_cast<unsigned*> (s1));...
	r[1] = r[1] * r[2];
	return true;
}

bool CommandClass::Mulu2::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as s = reinterpret_cast<char*> (r[1]); char s1[2] = {s[0],s[1]return true;}; lo = *(reinterpret_cast<unsigned*> (s1));...
	unsigned long long a = r[1], b = r[2];
	unsigned long long c = a * b;
	r[1] = *(reinterpret_cast<long long*>(c));
	return true;
}

bool CommandClass::Div::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = static_cast<int>(r[1]) / static_cast<int>(r[2]);
	return true;
}

bool CommandClass::Divu::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = r[1] / r[2];
	return true;
}

bool CommandClass::Div2::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as s = reinterpret_cast<char*> (r[1]); 
	/// char s1[2] = {s[0],s[1]}; lo = *(reinterpret_cast<unsigned*> (s1));...
	int a = static_cast<int>(r[1]), b = static_cast<int>(r[2]);
	r[1] = a / b;
	r[1] |= (static_cast<unsigned long long>(a % b) << 32);
	return true;
}

bool CommandClass::Divu2::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as s = reinterpret_cast<char*> (r[1]); 
	/// char s1[2] = {s[0],s[1]}; lo = *(reinterpert_cast<unsigned*> (s1));...
	unsigned a = static_cast<unsigned>(r[1]), b = static_cast<unsigned>(r[2]);
	r[1] = a / b;
	r[1] |= (static_cast<unsigned long long>(a % b) << 32);
	return true;
}

bool CommandClass::Xor::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = r[1] ^ r[2];
	return true;
}

bool CommandClass::Xoru::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = r[1] ^ r[2];
	return true;
}

bool CommandClass::Neg::exec(long long r[4])
{
	/// Input r[1] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = -r[1];
	return true;
}

bool CommandClass::Negu::exec(long long r[4])
{
	/// Input r[1] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])
	unsigned a = static_cast<unsigned> (r[1]);
	unsigned b = -a;
	r[1] = static_cast<long long> (b);
	return true;
}

bool CommandClass::Rem::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = r[1] % r[2];
	return true;
}

bool CommandClass::Remu::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (unsigned)
	/// Output r[1] which can be used as static_cast<unsigned> (r[1])
	r[1] = r[1] % r[2];
	return true;
}

bool CommandClass::Li::exec(long long r[4])
{
	return true;
}

bool CommandClass::Seq::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = (r[1] == r[2] ? 1 : 0);
	return true;
}

bool CommandClass::Sge::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = (r[1] >= r[2]) ? 1 : 0;
	return true;
}

bool CommandClass::Sgt::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = (r[1] > r[2]) ? 1 : 0;
	return true;
}

bool CommandClass::Sle::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = (r[1] <= r[2]) ? 1 : 0;
	return true;
}

bool CommandClass::Slt::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = (r[1] < r[2]) ? 1 : 0;
	return true;
}

bool CommandClass::Sne::exec(long long r[4])
{
	/// Input r[1] and r[2] which should be static_cast<long long> (int)
	/// Output r[1] which can be used as static_cast<int> (r[1])
	r[1] = (r[1] != r[2]) ? 1 : 0;
	return true;
}

bool CommandClass::B::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[1] = r[0];
	r[0] = 1;
	return false;
}

bool CommandClass::Beq::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[0] = (r[0] == r[1]) ? 1 : 0;
	r[1] = r[2];
	return false;
}

bool CommandClass::Bne::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[0] = (r[0] != r[1]) ? 1 : 0;
	r[1] = r[2];
	return false;
}

bool CommandClass::Bge::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[0] = (r[0] >= r[1]) ? 1 : 0;
	r[1] = r[2];
	return false;
}

bool CommandClass::Ble::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[0] = (r[0] <= r[1]) ? 1 : 0;
	r[1] = r[2];
	return false;
}

bool CommandClass::Bgt::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[0] = (r[0] > r[1]) ? 1 : 0;
	r[1] = r[2];
	return false;
}

bool CommandClass::Blt::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[0] = (r[0] < r[1]) ? 1 : 0;
	r[1] = r[2];
	return false;
}

bool CommandClass::Beqz::exec(long long r[4])
{
	/// Input r[0] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[0] = (r[0] == 0) ? 1 : 0; r[1] = r[2];
	return false;
}

bool CommandClass::Bnez::exec(long long r[4])
{
	/// Input r[0] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[0] = (r[0] != 0) ? 1 : 0;
	return false;
}

bool CommandClass::Blez::exec(long long r[4])
{
	/// Input r[0] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[0] = (r[0] <= 0) ? 1 : 0;
	return false;
}

bool CommandClass::Bgez::exec(long long r[4])
{
	/// Input r[0] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[0] = (r[0] >= 0) ? 1 : 0;
	return false;
}

bool CommandClass::Bgtz::exec(long long r[4])
{
	/// Input r[0] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[0] = (r[0] > 0) ? 1 : 0;
	return false;
}

bool CommandClass::Bltz::exec(long long r[4])
{
	/// Input r[0] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[0] = (r[0] < 0) ? 1 : 0;
	return false;
}

bool CommandClass::J::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[1] = r[0];
	r[0] = 1;
	return false;
}

bool CommandClass::Jr::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[1] = r[0];
	r[0] = 1;
	return false;
}

bool CommandClass::Jal::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[1] = r[0];
	r[0] = 1;
	return false;
}

bool CommandClass::Jalr::exec(long long r[4])
{
	/// Input r[0] and r[1] which should be static_cast<long long> (int)
	/// Output r[0], if (r[0]) goto r[1]
	r[1] = r[0];
	r[0] = 1;
	return false;
}

bool CommandClass::La::exec(long long r[4])
{
	return true;
}

bool CommandClass::Lb::exec(long long r[4])
{
	return true;
}

bool CommandClass::Lh::exec(long long r[4])
{
	return true;
}

bool CommandClass::Lw::exec(long long r[4])
{
	return true;
}

bool CommandClass::Sb::exec(long long r[4])
{
	return true;
}

bool CommandClass::Sh::exec(long long r[4])
{
	return true;
}

bool CommandClass::Sw::exec(long long r[4])
{
	return true;
}

bool CommandClass::Move::exec(long long r[4])
{
	return true;
}

bool CommandClass::Mfhi::exec(long long r[4])
{
	return true;
}

bool CommandClass::Mflo::exec(long long r[4])
{
	return true;
}

bool CommandClass::Nop::exec(long long r[4])
{
	r[0] = 5;
	return false;
}

bool CommandClass::Syscall::exec(long long r[4])
{
	/// r[0] is the the num of $v0
	/// r[1] is the content of $v0
	/// r[2] is the content of $a0
	/// r[3] is the content of $a1

	switch (r[1]) {
	case 1:
		cout << r[1] << endl;
		break;
	case 5:
		cin >> r[1];
		break;
	case 10:
		r[0] = -1;
		break;
	case 17:
		r[0] = -2;
		break;
	}
	return false;
}

bool CommandClass::Empty::exec(long long r[4])
{
	return false;
}
