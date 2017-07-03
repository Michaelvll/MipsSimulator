#ifndef USEFULSTRUCTURES
#define USEFULSTRUCTURES
#include <iostream>
using std::ostream;

class UsefulStructures {
public:
	enum op_num {
		empty, add = 1, addu, sub, subu, mul, mulu, mul2, mulu2, div, divu, div2,
		divu2, xor1, xoru, neg, negu, rem, remu, li, seq, sge, sgt,
		sle, slt, sne, b, beq, bne, bge, ble, bgt, blt, beqz, bnez, blez, bgez,
		bgtz, bltz, j, jr, jal, jalr, la, lb, lh, lw, sb, sh, sw, move, mfhi,
		mflo, nop, syscall
	};
	enum reg_num {
		zero = 0, at, v0, v1, a0, a1, a2, a3,
		t0 = 8, t1, t2, t3, t4, t5, t6, t7,
		s0 = 16, s1, s2, s3, s4, s5, s6, s7,
		t8 = 24, t9, k0, k1, gp, sp, s8 = 30,
		fp = 30, ra, lo, hi,pc
	};
	enum r_state {
		none, regi, immi
	};
	enum pip_run_state {
		run, pause, clear, predict_taken,stopALL
	};
	struct Token {
		int op = 0;
		int r[3] = { 0 };
		int offset= 0;
		r_state rstate[3] = { r_state::none,r_state::none,r_state::none };
		Token& operator=(const Token& rt);
		friend ostream& operator<<(ostream & out, const Token &token);
	};
	struct arguToken {
		int r[3];
		int offset;
		r_state rstate[3];
		arguToken & operator=(const Token& rt);
		friend ostream& operator<<(ostream & out, const arguToken &token);
	};
	bool Busy(const int &nowreg, int busyreg[4]);
	void addBusy(const int &nowreg, int busyreg[4]);
	void delBusy(const int &nowreg, int busyreg[4]);
};

#endif //USEFULSTRUCTURES