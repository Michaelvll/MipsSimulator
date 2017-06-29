#ifndef COMMANDCLASS
#define COMMANDCLASS
#include "UsefulStructures.h"
#include <string>
using std::string;

class CommandClass {
public:
	class Command_Base {
	public:
		void data_preparation(const UsefulStructures::arguToken &argutoken, long long res[5], int &state, int busyreg[4]);
		virtual bool exec(long long r[5], int busy_reg[4]) = 0;
		void memory_access(long long r[5], string &s);
		void write_back(long long r[5], int busyreg[4], string &s);
	};
	/// Classes of command
	class Empty:public Command_Base{
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};
	class Add : public Command_Base{
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Addu : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Sub : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Subu : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Mul : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Mulu : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Mul2 : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Mulu2 : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Div : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Divu : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Div2 : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Divu2 : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Xor : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Xoru : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Neg : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Negu : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Rem : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Remu : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Li : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Seq : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Sge : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Sgt : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Sle : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Slt : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Sne : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class B : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Beq : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bne : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bge : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Ble : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bgt : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Blt : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Beqz : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bnez : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Blez : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bgez : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bgtz : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bltz : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class J : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Jr : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Jal : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Jalr : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class La : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Lb : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Lh : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Lw : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Sb : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Sh : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Sw : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Move : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Mfhi : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Mflo : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Nop : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Syscall {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};
};

#endif //COMMANDCLASS
