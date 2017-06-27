#ifndef COMMANDCLASS
#define COMMANDCLASS

class Command_Base {
protected:
	virtual void exec(int &rs, int &rt, int &rd) = 0;
};
/// Classes of command
class Add : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Addu : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Addiu : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Sub : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Subu : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Mul : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Mulu : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Mul2 : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Mulu2 : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Div : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Divu : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Div2 : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Divu2 : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Xor : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Xoru : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Neg : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Negu : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Rem : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Remu : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Li : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Seq : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Sge : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Sgt : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Sle : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Slt : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Sne : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class B : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Beq : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Bne : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Bge : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Ble : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Bgt : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Blt : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Beqz : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Bnez : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Blez : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Bgez : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Bgtz : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Bltz : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class J : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Jr : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Jal : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Jalr : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class La : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Lb : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Lh : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Lw : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Sb : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Sh : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Sw : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Move : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Mfhi : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Mflo : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Nop : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

class Syscall : public Command_Base {
public:
	void exec(int &rs, int &rt, int &rd);
};

#endif //COMMANDCLASS
