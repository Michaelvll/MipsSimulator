#ifndef COMMANDCLASS
#define COMMANDCLASS
#include "UsefulStructures.h"

class CommandClass {
public:
	class Command_Base {
	protected:
		virtual bool exec(long long r[4]) = 0;
		virtual void data_preparation(const UsefulStructures::Token &token, long long res[4]);
	};
	/// Classes of command
	class Empty:public Command_Base{
	public:
		bool exec(long long r[4]);
	};
	class Add : public Command_Base{
	public:
		bool exec(long long r[4]);
	};

	class Addu : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Sub : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Subu : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Mul : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Mulu : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Mul2 : public Command_Base {
	public:
		bool exec(long long r[4]);
		virtual void data_preparation(const UsefulStructures::Token &token, long long res[4]);

	};

	class Mulu2 : public Command_Base {
	public:
		bool exec(long long r[4]);
		virtual void data_preparation(const UsefulStructures::Token &token, long long res[4]);
	};

	class Div : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Divu : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Div2 : public Command_Base {
	public:
		bool exec(long long r[4]);
		virtual void data_preparation(const UsefulStructures::Token &token, long long res[4]);
	};

	class Divu2 : public Command_Base {
	public:
		bool exec(long long r[4]);
		virtual void data_preparation(const UsefulStructures::Token &token, long long res[4]);
	};

	class Xor : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Xoru : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Neg : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Negu : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Rem : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Remu : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Li : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Seq : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Sge : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Sgt : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Sle : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Slt : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Sne : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class B : public Command_Base {
	public:
		bool exec(long long r[4]);
		virtual void data_preparation(const UsefulStructures::Token &token, long long res[4]);
	};

	class Beq : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Bne : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Bge : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Ble : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Bgt : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Blt : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Beqz : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Bnez : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Blez : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Bgez : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Bgtz : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Bltz : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class J : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Jr : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Jal : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Jalr : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class La : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Lb : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Lh : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Lw : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Sb : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Sh : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Sw : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Move : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Mfhi : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Mflo : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Nop : public Command_Base {
	public:
		bool exec(long long r[4]);
	};

	class Syscall {
	public:
		bool exec(long long r[4]);
	};
};

#endif //COMMANDCLASS
