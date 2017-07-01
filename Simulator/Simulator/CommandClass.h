#ifndef COMMANDCLASS
#define COMMANDCLASS
#include "UsefulStructures.h"
#include <string>
using std::string;

class CommandClass {
public:
	class Command_Base {
	public:
		bool read_first_reg = false;
		void data_preparation(const UsefulStructures::Token &token, long long res[5], int &state, int busyreg[4]);
		virtual bool exec(long long r[5], int busy_reg[4]) = 0;
		void memory_access(long long r[5], string &s);
		void write_back(long long r[5], int busyreg[4], string &s);
		virtual ~Command_Base();
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

	class Mul2: public Command_Base {
	public:
		Mul2();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Mulu2 : public Command_Base {
	public:
		Mulu2 ();
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

	class Div2: public Command_Base {
	public:
		Div2();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Divu2: public Command_Base {
	public:
		Divu2();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class xor1 : public Command_Base {
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

	class Beq: public Command_Base {
	public:
		Beq();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bne: public Command_Base {
	public:
		Bne();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bge: public Command_Base {
	public:
		Bge();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Ble: public Command_Base {
	public:
		Ble();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bgt: public Command_Base {
	public:
		Bgt();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Blt: public Command_Base {
	public:
		Blt();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Beqz: public Command_Base {
	public:
		Beqz();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bnez: public Command_Base {
	public:
		Bnez();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Blez: public Command_Base {
	public:
		Blez();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bgez: public Command_Base {
	public:
		Bgez();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bgtz: public Command_Base {
	public:
		Bgtz();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Bltz: public Command_Base {
	public:
		Bltz();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class J : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Jr: public Command_Base {
	public:
		Jr();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Jal : public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Jalr: public Command_Base {
	public:
		Jalr();
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

	class Sb: public Command_Base {
	public:
		Sb();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Sh: public Command_Base {
	public:
		Sh();
		bool exec(long long r[5], int busy_reg[2]);
	};

	class Sw: public Command_Base {
	public:
		Sw();
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

	class Syscall:public Command_Base {
	public:
		bool exec(long long r[5], int busy_reg[2]);
	};
};

#endif //COMMANDCLASS
