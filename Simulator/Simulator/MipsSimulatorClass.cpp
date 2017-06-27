#include "MipsSimulatorClass.h"
#include <vector>
using std::clog;
using std::endl;
using std::vector;


MipsSimulatorClass::Token::Token(int _op, int _rs, int _rt, int _rd)
	: op(_op), rs(_rs), rt(_rt), rd(_rd) {}

MipsSimulatorClass::MipsSimulatorClass()
{
	// Initialize the unordered_map of register .no
	reg_num_tab["zero"] = reg_num::zero;
	reg_num_tab["at"] = reg_num::at;
	reg_num_tab["v0"] = reg_num::v0;
	reg_num_tab["v1"] = reg_num::v1;
	reg_num_tab["a0"] = reg_num::a0;
	reg_num_tab["a1"] = reg_num::a1;
	reg_num_tab["a2"] = reg_num::a2;
	reg_num_tab["a3"] = reg_num::a3;
	reg_num_tab["t0"] = reg_num::t0;
	reg_num_tab["t1"] = reg_num::t1;
	reg_num_tab["t2"] = reg_num::t2;
	reg_num_tab["t3"] = reg_num::t3;
	reg_num_tab["t4"] = reg_num::t4;
	reg_num_tab["t5"] = reg_num::t5;
	reg_num_tab["t6"] = reg_num::t6;
	reg_num_tab["t7"] = reg_num::t7;
	reg_num_tab["s0"] = reg_num::s0;
	reg_num_tab["s1"] = reg_num::s1;
	reg_num_tab["s2"] = reg_num::s2;
	reg_num_tab["s3"] = reg_num::s3;
	reg_num_tab["s4"] = reg_num::s4;
	reg_num_tab["s5"] = reg_num::s5;
	reg_num_tab["s6"] = reg_num::s6;
	reg_num_tab["s7"] = reg_num::s7;
	reg_num_tab["t8"] = reg_num::t8;
	reg_num_tab["t9"] = reg_num::t9;
	reg_num_tab["k0"] = reg_num::k0;
	reg_num_tab["k1"] = reg_num::k1;
	reg_num_tab["gp"] = reg_num::gp;
	reg_num_tab["sp"] = reg_num::sp;
	reg_num_tab["s8"] = reg_num::s8;
	reg_num_tab["fp"] = reg_num::fp;
	reg_num_tab["ra"] = reg_num::ra;

	//Initialize the operation table from string to op_num
	op_num_tab["add"] = op_num::add;
	op_num_tab["addu"] = op_num::addu;
	op_num_tab["addiu"] = op_num::addiu;
	op_num_tab["sub"] = op_num::sub;
	op_num_tab["subu"] = op_num::subu;
	op_num_tab["mul"] = op_num::mul;
	op_num_tab["mulu"] = op_num::mulu;
	op_num_tab["mul2"] = op_num::mul2;
	op_num_tab["mulu2"] = op_num::mulu2;
	op_num_tab["div"] = op_num::div;
	op_num_tab["divu"] = op_num::divu;
	op_num_tab["div2"] = op_num::div2;
	op_num_tab["divu2"] = op_num::divu2;
	op_num_tab["xor"] = op_num::xor;
	op_num_tab["xoru"] = op_num::xoru;
	op_num_tab["neg"] = op_num::neg;
	op_num_tab["negu"] = op_num::negu;
	op_num_tab["rem"] = op_num::rem;
	op_num_tab["remu"] = op_num::remu;
	op_num_tab["li"] = op_num::li;
	op_num_tab["seq"] = op_num::seq;
	op_num_tab["sge"] = op_num::sge;
	op_num_tab["sgt"] = op_num::sgt;
	op_num_tab["sle"] = op_num::sle;
	op_num_tab["slt"] = op_num::slt;
	op_num_tab["sne"] = op_num::sne;
	op_num_tab["b"] = op_num::b;
	op_num_tab["beq"] = op_num::beq;
	op_num_tab["bne"] = op_num::bne;
	op_num_tab["bge"] = op_num::bge;
	op_num_tab["ble"] = op_num::ble;
	op_num_tab["bgt"] = op_num::bgt;
	op_num_tab["blt"] = op_num::blt;
	op_num_tab["beqz"] = op_num::beqz;
	op_num_tab["bnez"] = op_num::bnez;
	op_num_tab["blez"] = op_num::blez;
	op_num_tab["bgez"] = op_num::bgez;
	op_num_tab["bgtz"] = op_num::bgtz;
	op_num_tab["bltz"] = op_num::bltz;
	op_num_tab["j"] = op_num::j;
	op_num_tab["jr"] = op_num::jr;
	op_num_tab["jal"] = op_num::jal;
	op_num_tab["jalr"] = op_num::jalr;
	op_num_tab["la"] = op_num::la;
	op_num_tab["lb"] = op_num::lb;
	op_num_tab["lh"] = op_num::lh;
	op_num_tab["lw"] = op_num::lw;
	op_num_tab["sb"] = op_num::sb;
	op_num_tab["sh"] = op_num::sh;
	op_num_tab["sw"] = op_num::sw;
	op_num_tab["move"] = op_num::move;
	op_num_tab["mfhi"] = op_num::mfhi;
	op_num_tab["mflo"] = op_num::mflo;
	op_num_tab["nop"] = op_num::nop;
	op_num_tab["syscall"] = op_num::syscall;


	// Initialize the operation table from op_num to class
	/*op_class_tab[op_num::add] = new Add;
	op_class_tab[op_num::addu] = new Addu;
	op_class_tab[op_num::addiu] = new Addiu;
	op_class_tab[op_num::sub] = new Sub;
	op_class_tab[op_num::subu] = new Subu;
	op_class_tab[op_num::mul] = new Mul;
	op_class_tab[op_num::mulu] = new Mulu;
	op_class_tab[op_num::mul2] = new Mul2;
	op_class_tab[op_num::mulu2] = new Mulu2;
	op_class_tab[op_num::div] = new Div;
	op_class_tab[op_num::divu] = new Divu;
	op_class_tab[op_num::div2] = new Div2;
	op_class_tab[op_num::divu2] = new Divu2;
	op_class_tab[op_num::xor] = new Xor;
	op_class_tab[op_num::xoru] = new Xoru;
	op_class_tab[op_num::neg] = new Neg;
	op_class_tab[op_num::negu] = new Negu;
	op_class_tab[op_num::rem] = new Rem;
	op_class_tab[op_num::remu] = new Remu;
	op_class_tab[op_num::li] = new Li;
	op_class_tab[op_num::seq] = new Seq;
	op_class_tab[op_num::sge] = new Sge;
	op_class_tab[op_num::sgt] = new Sgt;
	op_class_tab[op_num::sle] = new Sle;
	op_class_tab[op_num::slt] = new Slt;
	op_class_tab[op_num::sne] = new Sne;
	op_class_tab[op_num::b] = new B;
	op_class_tab[op_num::beq] = new Beq;
	op_class_tab[op_num::bne] = new Bne;
	op_class_tab[op_num::bge] = new Bge;
	op_class_tab[op_num::ble] = new Ble;
	op_class_tab[op_num::bgt] = new Bgt;
	op_class_tab[op_num::blt] = new Blt;
	op_class_tab[op_num::beqz] = new Beqz;
	op_class_tab[op_num::bnez] = new Bnez;
	op_class_tab[op_num::blez] = new Blez;
	op_class_tab[op_num::bgez] = new Bgez;
	op_class_tab[op_num::bgtz] = new Bgtz;
	op_class_tab[op_num::bltz] = new Bltz;
	op_class_tab[op_num::j] = new J;
	op_class_tab[op_num::jr] = new Jr;
	op_class_tab[op_num::jal] = new Jal;
	op_class_tab[op_num::jalr] = new Jalr;
	op_class_tab[op_num::la] = new La;
	op_class_tab[op_num::lb] = new Lb;
	op_class_tab[op_num::lh] = new Lh;
	op_class_tab[op_num::lw] = new Lw;
	op_class_tab[op_num::sb] = new Sb;
	op_class_tab[op_num::sh] = new Sh;
	op_class_tab[op_num::sw] = new Sw;
	op_class_tab[op_num::move] = new Move;
	op_class_tab[op_num::mfhi] = new Mfhi;
	op_class_tab[op_num::mflo] = new Mflo;
	op_class_tab[op_num::nop] = new Nop;
	op_class_tab[op_num::syscall] = new Syscall;*/

}
template<typename T>
inline T MipsSimulatorClass::Get_Next_Num(const string &s, int &pos)
{
	for (; s[pos] == ' ' || s[pos] == ',' || s[pos] == ':' || s[pos] == '\t'; ++pos);
	T n = 0;
	bool neg = false;
	if (s[pos] == '-') neg = true;
	for (; s[pos] <= '9' && s[pos] >= '0'; ++pos) {
		n *= 10;
		n += s[pos] - '0';
	}
	for (; s[pos] == ' ' || s[pos] == ',' || s[pos] == '\t'; ++pos);

	return neg ? -n : n;
}

inline string MipsSimulatorClass::Get_Next_String(const string &s, int &pos)
{
	string op;
	for (; s[pos] == ' ' || s[pos] == ',' || s[pos] == ':' ||s[pos] =='\t'; ++pos);
	for (; s[pos] != ' ' && s[pos] != ':' && s[pos] != 0; ++pos) op += s[pos];
	for (; s[pos] == ' ' || s[pos] == ',' || s[pos] == '\t'; ++pos);
	return op;
}

string MipsSimulatorClass::String_Fetch(const string & s)
{
	string fs;
	int pos = 0;
	for (; s[pos] != 0; ++pos) {
		if (s[pos] == '\"')continue;
		else if (s[pos] == '\\') {
			++pos;
			switch (s[pos]) {
			case 'n':
				fs += '\n';
				break;
			case 'r':
				fs += '\r';
				break;
			case '\\':
				fs += '\\';
				break;
			case 't':
				fs += '\t';
				break;
			case 'a':
				fs += '\a';
				break;
			case 'b':
				fs += '\b';
				break;
			case 'f':
				fs += '\f';
				break;
			case 'v':
				fs += '\v';
				break;
			case '\'':
				fs += '\'';
				break;
			case '\"':
				fs += '\"';
				break;
			case '\?':
				fs += '\?';
				break;
			case '\0':
				fs += '\0';
			}
		}
		else {
			fs += s[pos];
		}
	}

	return fs;
}

bool MipsSimulatorClass::Text_labelProcess(const string &s, int &expr_pos, state_num &state)
{
	/// Process the command in text area

	int pos = 0;
	string op = Get_Next_String(s, pos);

	if (s[pos] == ':') {
		txt_lab_tab[op] = expr_pos;

		clog << "Get a text_label: \"" << op << "\" of the expr_pos  " << expr_pos << endl;

		++pos;
		for (; s[pos] != 0; ++pos) {
			string op = Get_Next_String(s, pos);
			txt_lab_tab[op] = expr_pos; // Record the position of the label in text with unordered_map

			clog << "Get a text_label: \"" << op << "\" of the expr_pos  " << expr_pos << endl;
		}
		return true;
	}
	else if (op[0] == '.') {
		// s[pos] != ':'
		// This command is started with '.'

		if (op == ".data") {
			state = state_num::data;
			clog << "Get a command \".data\" and change the state"
				<< endl;
		}
		else if (op == ".text") {
			state = state_num::text;
			clog << "Get a command \".text\"" << endl;
		}
		return true;
	}
	else if (op == "") {
		return true;
	}
	return false;
}

void MipsSimulatorClass::Data_Process(string s, int &mem_pos, state_num & state)
{
	int pos = 0;
	string op = Get_Next_String(s, pos);

	if (s[pos] == ':') {
		mem_lab_tab[op] = mem_pos;

		clog << "Get a mem_label: \"" << op << "\" of the mem_pos " << mem_pos << endl;

		++pos;
		for (; s[pos] != 0; ++pos) {
			string op = Get_Next_String(s, pos);
			mem_lab_tab[op] = mem_pos;// Record the position of the mem label with unordered_map

			clog << "Get a mem_label: " << op << " of the mem_pos " << mem_pos << endl;
		}
	}
	else if (op[0] == '.') {
		if (op == ".data") {
			state = state_num::data;
			clog << "Get a command \".data\"" << endl;
		}
		else if (op == ".text") {
			state = state_num::text;
			clog << "Get a command \".text\" and change the state" << endl;
		}
		else if (op == ".align") {
			int n = Get_Next_Num<int>(s, pos);
			clog << "Get a command \".align " << n << "\"" << endl;
			clog << "Previous mem_pos: " << mem_pos << endl;

			int delta = 1 << n;
			int k = 0, newpos = 0;
			for (; newpos < mem_pos; ++k) {
				newpos += delta;
			}
			mem_pos = newpos;

			clog << "Mem_pos is changed to: " << mem_pos << endl;
		}
		else if (op == ".ascii") {
			string oristr = Get_Next_String(s, pos);
			string str = String_Fetch(oristr);
			clog << "Get a command \".ascii " << str << "\"" << endl;
			clog << "Previous mem_pos: " << mem_pos << endl;

			for (unsigned int i = 0; i < str.length(); ++i) {
				memory[mem_pos++] = str[i];
			}
			clog << "Put the string (without end signal) " << str << " into the memory at: " << mem_pos << endl;
		}
		else if (op == ".asciiz") {
			string oristr = Get_Next_String(s, pos);
			string str = String_Fetch(oristr);
			clog << "Get a command \".asciiz " << str << "\"" << endl;
			clog << "Previous mem_pos: " << mem_pos << endl;

			for (unsigned int i = 0; i <= str.length(); ++i) {
				memory[mem_pos++] = str[i];
			}
			clog << "Put the string (with end signal) " << str << " into the memory at: " << mem_pos << endl;
		}
		else if (op == ".byte") {
			vector<char> vstr;
			while (s[pos] != 0) {
				string str = Get_Next_String(s, pos);
				if (str != "") str.push_back(str[0]);
			}

			clog << "Get a command \".byte ";
			for (auto x : vstr) clog << x << ' ';
			clog << "\"" << endl;
			clog << "Previous mem_pos: " << mem_pos << endl;

			clog << "Put the byte ";
			for (auto x : vstr) {
				memory[mem_pos++] = x;
				clog << x << ' ';
			}
			clog << "into the memory and the mem_pos is changed to " << mem_pos << endl;
		}
		else if (op == ".half") {
			vector<short> vn;
			while (s[pos] != 0) {
				short n = Get_Next_Num<short>(s, pos);
				vn.push_back(n);
			}
			clog << "Get a command \".half ";
			for (auto x : vn) clog << x << ' ';
			clog << "\"" << endl;
			clog << "Previous mem_pos: " << mem_pos << endl;

			clog << "Put the half ";
			for (auto x : vn) {
				char* byte = reinterpret_cast<char*> (&x);
				memory[mem_pos++] = byte[0];
				memory[mem_pos++] = byte[1];
				clog << *(reinterpret_cast<short*> (byte))<< ' ';
			}
			clog << "into the memory and the mem_pos is changed to " << mem_pos << endl;
		}
		else if (op == ".word") {
			vector<int> vn;
			while (s[pos] != 0) {
				int n = Get_Next_Num<int>(s, pos);
				vn.push_back(n);
			}
			clog << "Get a command \".word ";
			for (auto x : vn) clog << x << ' ';
			clog << "\"" << endl;
			clog << "Previous mem_pos: " << mem_pos << endl;

			clog << "Put the word ";
			for (auto x : vn) {
				char* byte = reinterpret_cast<char*> (&x);
				memory[mem_pos++] = byte[0];
				memory[mem_pos++] = byte[1];
				memory[mem_pos++] = byte[2];
				memory[mem_pos++] = byte[3];
				clog << *(reinterpret_cast<int*> (byte)) << ' ';
			}
			clog << "into the memory and the mem_pos is changed to " << mem_pos << endl;
		}
		else if (op == ".space") {
			int n = Get_Next_Num<int>(s, pos);
			clog << "Get a command \".space " << n << "\"" << endl;
			clog << "Previous mem_pos: " << mem_pos << endl;
			mem_pos += n;
			clog << "Change the mem_pos to: " << mem_pos << endl;
		}
		else {
			clog << "Get an unknown command!!!!" << endl;
			throw(0);
		}
	}
	else if (op == "") {
		return;
	}
	else {
		clog << "Get unknown command!!!!!!" << endl;
		throw(0);
	}
}



void MipsSimulatorClass::readcode(std::istream & codein)
{
	/// Process the Mips code from the stream codein, which comes from a whole file

	vector<string> preExpr;
	clog << "===============================================================" << endl;
	clog << "Code reading START" << endl;

	clog << "First scanning START" << endl;

	// First scanning of the source code
	// Execute all the command in .data and record the mem_label into a unordered map
	// Put the commands in .text into a vector<string> preExpr and record the text_label into a unordered map
	string tmps;
	int expr_pos = 0, mem_pos = 0;
	state_num state = state_num::data;

	// For clog
	int linenum = 0;

	while (getline(codein, tmps)) {
		// For clog
		++linenum;
		clog << "---------------------------------------------------------------" << endl;

		if (state == state_num::text) {
			// Get the position of the text labels

			clog << "Start a Data_Process of the Line " << linenum << " in " << (state == state_num::data ? "data" : "text") << " mod" << endl;
			clog << "The origin line is \"" << tmps << "\"" <<endl;

			bool re = Text_labelProcess(tmps, expr_pos, state);
			if (re) continue;
			++expr_pos;
			preExpr.push_back(tmps);

			clog << "Get a command: " << tmps << " and push it to the vector of preExpr" << endl;
		}
		else {
			// state == data
			clog << "Start a Data_Process of the Line " << linenum << " in " << (state == state_num::data? "data":"text") << " mod"<< endl;
			clog << "The origin line is \"" << tmps << "\"" << endl;
			Data_Process(tmps, mem_pos, state);

		}
		clog << "First scanning COMPLETE!" << endl;
	}

	clog << "===============================================================" << endl;
	clog << "Second scanning START" << endl;

	// Second scanning of the preExpr

	//remember to figure out which mul, mulu, div and divu the command is!!!!!!!!!!!!!!!!!!!!

	preExpr.clear();
}

void MipsSimulatorClass::Instruction_Fetch()
{
}

void MipsSimulatorClass::Instruction_Decode_Data_Preparation()
{
}

void MipsSimulatorClass::Execution()
{
}

void MipsSimulatorClass::Memory_Access()
{
}

void MipsSimulatorClass::Write_Back()
{
}

void MipsSimulatorClass::exec(std::istream & codein, std::ostream & fout)
{
	readcode(codein);

	//debug
	//for (auto x : expr) {
	//	std::clog << x << std::endl;
	//}


}


