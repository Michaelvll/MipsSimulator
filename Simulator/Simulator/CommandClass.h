#ifndef COMMANDCLASS
#define COMMANDCLASS

class CommandClass {
public:
	class Command_Base {
	protected:
		virtual void exec(int r[3], int rstate[3]) = 0;
	};
	/// Classes of command
	class Add : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Addu : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Sub : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Subu : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Mul : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Mulu : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Mul2 : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Mulu2 : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Div : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Divu : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Div2 : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Divu2 : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Xor : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Xoru : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Neg : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Negu : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Rem : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Remu : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Li : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Seq : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Sge : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Sgt : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Sle : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Slt : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Sne : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class B : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Beq : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Bne : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Bge : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Ble : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Bgt : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Blt : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Beqz : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Bnez : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Blez : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Bgez : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Bgtz : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Bltz : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class J : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Jr : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Jal : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Jalr : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class La : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Lb : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Lh : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Lw : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Sb : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Sh : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Sw : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Move : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Mfhi : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Mflo : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Nop : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

	class Syscall : public Command_Base {
	public:
		void exec(int r[3], int rstate[3]);
	};

};

#endif //COMMANDCLASS
