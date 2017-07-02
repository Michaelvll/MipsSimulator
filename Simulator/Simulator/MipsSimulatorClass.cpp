#include "MipsSimulatorClass.h"
#include "PipelineClass.h"
#include <vector>
#include <deque>
#include <string>
using std::string;
using std::clog;
using std::endl;
using std::vector;
using std::deque;

MipsSimulatorClass::MipsSimulatorClass()
{
	memory = new char[4 * 1024 * 1024];
	for (int i = 0; i < 4 * 1024 * 1024; ++i) {
		memory[i] = 0;
	}
	reg[UsefulStructures::reg_num::sp] = 4 * 1024 * 1024;

	// Initialize the unordered_map of register .no
	reg_num_tab["zero"] = UsefulStructures::reg_num::zero;
	reg_num_tab["at"] = UsefulStructures::reg_num::at;
	reg_num_tab["v0"] = UsefulStructures::reg_num::v0;
	reg_num_tab["v1"] = UsefulStructures::reg_num::v1;
	reg_num_tab["a0"] = UsefulStructures::reg_num::a0;
	reg_num_tab["a1"] = UsefulStructures::reg_num::a1;
	reg_num_tab["a2"] = UsefulStructures::reg_num::a2;
	reg_num_tab["a3"] = UsefulStructures::reg_num::a3;
	reg_num_tab["t0"] = UsefulStructures::reg_num::t0;
	reg_num_tab["t1"] = UsefulStructures::reg_num::t1;
	reg_num_tab["t2"] = UsefulStructures::reg_num::t2;
	reg_num_tab["t3"] = UsefulStructures::reg_num::t3;
	reg_num_tab["t4"] = UsefulStructures::reg_num::t4;
	reg_num_tab["t5"] = UsefulStructures::reg_num::t5;
	reg_num_tab["t6"] = UsefulStructures::reg_num::t6;
	reg_num_tab["t7"] = UsefulStructures::reg_num::t7;
	reg_num_tab["s0"] = UsefulStructures::reg_num::s0;
	reg_num_tab["s1"] = UsefulStructures::reg_num::s1;
	reg_num_tab["s2"] = UsefulStructures::reg_num::s2;
	reg_num_tab["s3"] = UsefulStructures::reg_num::s3;
	reg_num_tab["s4"] = UsefulStructures::reg_num::s4;
	reg_num_tab["s5"] = UsefulStructures::reg_num::s5;
	reg_num_tab["s6"] = UsefulStructures::reg_num::s6;
	reg_num_tab["s7"] = UsefulStructures::reg_num::s7;
	reg_num_tab["t8"] = UsefulStructures::reg_num::t8;
	reg_num_tab["t9"] = UsefulStructures::reg_num::t9;
	reg_num_tab["k0"] = UsefulStructures::reg_num::k0;
	reg_num_tab["k1"] = UsefulStructures::reg_num::k1;
	reg_num_tab["gp"] = UsefulStructures::reg_num::gp;
	reg_num_tab["sp"] = UsefulStructures::reg_num::sp;
	reg_num_tab["s8"] = UsefulStructures::reg_num::s8;
	reg_num_tab["fp"] = UsefulStructures::reg_num::fp;
	reg_num_tab["ra"] = UsefulStructures::reg_num::ra;
	reg_num_tab["lo"] = UsefulStructures::reg_num::lo;
	reg_num_tab["hi"] = UsefulStructures::reg_num::hi;
	reg_num_tab["pc"] = UsefulStructures::reg_num::pc;

	//Initialize the operation table from string to op_num
	op_num_tab["add"] = UsefulStructures::op_num::add;
	op_num_tab["addu"] = UsefulStructures::op_num::addu;
	op_num_tab["sub"] = UsefulStructures::op_num::sub;
	op_num_tab["subu"] = UsefulStructures::op_num::subu;
	op_num_tab["mul"] = UsefulStructures::op_num::mul;
	op_num_tab["mulu"] = UsefulStructures::op_num::mulu;
	op_num_tab["mul2"] = UsefulStructures::op_num::mul2;
	op_num_tab["mulu2"] = UsefulStructures::op_num::mulu2;
	op_num_tab["div"] = UsefulStructures::op_num::div;
	op_num_tab["divu"] = UsefulStructures::op_num::divu;
	op_num_tab["div2"] = UsefulStructures::op_num::div2;
	op_num_tab["divu2"] = UsefulStructures::op_num::divu2;
	op_num_tab["xor"] = UsefulStructures::op_num::xor1;
	op_num_tab["xoru"] = UsefulStructures::op_num::xoru;
	op_num_tab["neg"] = UsefulStructures::op_num::neg;
	op_num_tab["negu"] = UsefulStructures::op_num::negu;
	op_num_tab["rem"] = UsefulStructures::op_num::rem;
	op_num_tab["remu"] = UsefulStructures::op_num::remu;
	op_num_tab["li"] = UsefulStructures::op_num::li;
	op_num_tab["seq"] = UsefulStructures::op_num::seq;
	op_num_tab["sge"] = UsefulStructures::op_num::sge;
	op_num_tab["sgt"] = UsefulStructures::op_num::sgt;
	op_num_tab["sle"] = UsefulStructures::op_num::sle;
	op_num_tab["slt"] = UsefulStructures::op_num::slt;
	op_num_tab["sne"] = UsefulStructures::op_num::sne;
	op_num_tab["b"] = UsefulStructures::op_num::b;
	op_num_tab["beq"] = UsefulStructures::op_num::beq;
	op_num_tab["bne"] = UsefulStructures::op_num::bne;
	op_num_tab["bge"] = UsefulStructures::op_num::bge;
	op_num_tab["ble"] = UsefulStructures::op_num::ble;
	op_num_tab["bgt"] = UsefulStructures::op_num::bgt;
	op_num_tab["blt"] = UsefulStructures::op_num::blt;
	op_num_tab["beqz"] = UsefulStructures::op_num::beqz;
	op_num_tab["bnez"] = UsefulStructures::op_num::bnez;
	op_num_tab["blez"] = UsefulStructures::op_num::blez;
	op_num_tab["bgez"] = UsefulStructures::op_num::bgez;
	op_num_tab["bgtz"] = UsefulStructures::op_num::bgtz;
	op_num_tab["bltz"] = UsefulStructures::op_num::bltz;
	op_num_tab["j"] = UsefulStructures::op_num::j;
	op_num_tab["jr"] = UsefulStructures::op_num::jr;
	op_num_tab["jal"] = UsefulStructures::op_num::jal;
	op_num_tab["jalr"] = UsefulStructures::op_num::jalr;
	op_num_tab["la"] = UsefulStructures::op_num::la;
	op_num_tab["lb"] = UsefulStructures::op_num::lb;
	op_num_tab["lh"] = UsefulStructures::op_num::lh;
	op_num_tab["lw"] = UsefulStructures::op_num::lw;
	op_num_tab["sb"] = UsefulStructures::op_num::sb;
	op_num_tab["sh"] = UsefulStructures::op_num::sh;
	op_num_tab["sw"] = UsefulStructures::op_num::sw;
	op_num_tab["move"] = UsefulStructures::op_num::move;
	op_num_tab["mfhi"] = UsefulStructures::op_num::mfhi;
	op_num_tab["mflo"] = UsefulStructures::op_num::mflo;
	op_num_tab["nop"] = UsefulStructures::op_num::nop;
	op_num_tab["syscall"] = UsefulStructures::op_num::syscall;

	// Initialize the operation table from op_num to class
	op_class_tab[UsefulStructures::op_num::empty] = new CommandClass::Empty;
	op_class_tab[UsefulStructures::op_num::add] = new CommandClass::Add;
	op_class_tab[UsefulStructures::op_num::addu] = new CommandClass::Addu;
	op_class_tab[UsefulStructures::op_num::sub] = new CommandClass::Sub;
	op_class_tab[UsefulStructures::op_num::subu] = new CommandClass::Subu;
	op_class_tab[UsefulStructures::op_num::mul] = new CommandClass::Mul;
	op_class_tab[UsefulStructures::op_num::mulu] = new CommandClass::Mulu;
	op_class_tab[UsefulStructures::op_num::mul2] = new CommandClass::Mul2;
	op_class_tab[UsefulStructures::op_num::mulu2] = new CommandClass::Mulu2;
	op_class_tab[UsefulStructures::op_num::div] = new CommandClass::Div;
	op_class_tab[UsefulStructures::op_num::divu] = new CommandClass::Divu;
	op_class_tab[UsefulStructures::op_num::div2] = new CommandClass::Div2;
	op_class_tab[UsefulStructures::op_num::divu2] = new CommandClass::Divu2;
	op_class_tab[UsefulStructures::op_num::xor1] = new CommandClass::Xor1;
	op_class_tab[UsefulStructures::op_num::xoru] = new CommandClass::Xoru;
	op_class_tab[UsefulStructures::op_num::neg] = new CommandClass::Neg;
	op_class_tab[UsefulStructures::op_num::negu] = new CommandClass::Negu;
	op_class_tab[UsefulStructures::op_num::rem] = new CommandClass::Rem;
	op_class_tab[UsefulStructures::op_num::remu] = new CommandClass::Remu;
	op_class_tab[UsefulStructures::op_num::li] = new CommandClass::Li;
	op_class_tab[UsefulStructures::op_num::seq] = new CommandClass::Seq;
	op_class_tab[UsefulStructures::op_num::sge] = new CommandClass::Sge;
	op_class_tab[UsefulStructures::op_num::sgt] = new CommandClass::Sgt;
	op_class_tab[UsefulStructures::op_num::sle] = new CommandClass::Sle;
	op_class_tab[UsefulStructures::op_num::slt] = new CommandClass::Slt;
	op_class_tab[UsefulStructures::op_num::sne] = new CommandClass::Sne;
	op_class_tab[UsefulStructures::op_num::b] = new CommandClass::B;
	op_class_tab[UsefulStructures::op_num::beq] = new CommandClass::Beq;
	op_class_tab[UsefulStructures::op_num::bne] = new CommandClass::Bne;
	op_class_tab[UsefulStructures::op_num::bge] = new CommandClass::Bge;
	op_class_tab[UsefulStructures::op_num::ble] = new CommandClass::Ble;
	op_class_tab[UsefulStructures::op_num::bgt] = new CommandClass::Bgt;
	op_class_tab[UsefulStructures::op_num::blt] = new CommandClass::Blt;
	op_class_tab[UsefulStructures::op_num::beqz] = new CommandClass::Beqz;
	op_class_tab[UsefulStructures::op_num::bnez] = new CommandClass::Bnez;
	op_class_tab[UsefulStructures::op_num::blez] = new CommandClass::Blez;
	op_class_tab[UsefulStructures::op_num::bgez] = new CommandClass::Bgez;
	op_class_tab[UsefulStructures::op_num::bgtz] = new CommandClass::Bgtz;
	op_class_tab[UsefulStructures::op_num::bltz] = new CommandClass::Bltz;
	op_class_tab[UsefulStructures::op_num::j] = new CommandClass::J;
	op_class_tab[UsefulStructures::op_num::jr] = new CommandClass::Jr;
	op_class_tab[UsefulStructures::op_num::jal] = new CommandClass::Jal;
	op_class_tab[UsefulStructures::op_num::jalr] = new CommandClass::Jalr;
	op_class_tab[UsefulStructures::op_num::la] = new CommandClass::La;
	op_class_tab[UsefulStructures::op_num::lb] = new CommandClass::Lb;
	op_class_tab[UsefulStructures::op_num::lh] = new CommandClass::Lh;
	op_class_tab[UsefulStructures::op_num::lw] = new CommandClass::Lw;
	op_class_tab[UsefulStructures::op_num::sb] = new CommandClass::Sb;
	op_class_tab[UsefulStructures::op_num::sh] = new CommandClass::Sh;
	op_class_tab[UsefulStructures::op_num::sw] = new CommandClass::Sw;
	op_class_tab[UsefulStructures::op_num::move] = new CommandClass::Move;
	op_class_tab[UsefulStructures::op_num::mfhi] = new CommandClass::Mfhi;
	op_class_tab[UsefulStructures::op_num::mflo] = new CommandClass::Mflo;
	op_class_tab[UsefulStructures::op_num::nop] = new CommandClass::Nop;
	op_class_tab[UsefulStructures::op_num::syscall] = new CommandClass::Syscall;


}
MipsSimulatorClass::~MipsSimulatorClass()
{
	for (auto &x : op_class_tab) {
		delete x;
	}
	delete memory;
}

template<typename T>
inline T MipsSimulatorClass::Get_Next_Num(const string &s, size_t &pos)
{
	for (; pos < s.length() && (s[pos] == ' ' || s[pos] == ',' || s[pos] == ':' || s[pos] == '\t'); ++pos);
	T n = 0;
	bool neg = false;
	if (s[pos] == '-') neg = true, ++pos;
	for (; pos < s.length() && (s[pos] <= '9' && s[pos] >= '0'); ++pos) {
		n *= 10;
		n += s[pos] - '0';
	}
	for (; pos < s.length() && (s[pos] == ' ' || s[pos] == ',' || s[pos] == '\t'); ++pos);

	return neg ? -n : n;
}

inline string MipsSimulatorClass::Get_Next_String(const string &s, size_t &pos)
{
	string op;
	for (; pos < s.length() && (s[pos] == ' ' || s[pos] == ',' || s[pos] == ':' || s[pos] == '\t' || s[pos] == '('); ++pos);
	for (; pos < s.length() && s[pos] != ' ' && s[pos] != ':' && s[pos] != ')' && s[pos] != ',' && s[pos] != '#'; ++pos) op += s[pos];
	for (; pos < s.length() && (s[pos] == ' ' || s[pos] == ',' || s[pos] == '\t' || s[pos] == ')'); ++pos)if (s[pos] == '#') break;
	if (pos < s.length() && s[pos] == '#') pos = s.length();
	return op;
}

string MipsSimulatorClass::String_Fetch(const string & s, size_t &pos)
{
	string fs;
	//size_t pos = 0;
	for (; pos < s.length() && (s[pos] == ' ' || s[pos] == ',' || s[pos] == ':' || s[pos] == '\t' || s[pos] == '('); ++pos);
	int quot = 2;
	for (; pos < s.length(); ++pos) {
		if (s[pos] == '\"') {
			quot = 2;
			break;
		}
		else if (s[pos] == '\'') {
			quot = 1;
			break;
		}
	}
	++pos;
	for (; pos < s.length(); ++pos) {
		if (s[pos] == '\"' && quot == 2) {
			++pos;
			break;
		}
		else if (s[pos] == '\'' && quot == 1) {
			++pos;
			break;
		}
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
				break;
			}
		}
		else {
			fs += s[pos];
		}
	}

	return fs;
}

inline bool MipsSimulatorClass::isReg(const string & s)
{
	for (auto x : s) if (x == '$') return true;
	return false;
}

bool MipsSimulatorClass::Text_labelProcess(const string &s, state_num &state)
{
	/// Process the command in text area

	size_t pos = 0;
	string op = Get_Next_String(s, pos);

	if (pos < s.length() && s[pos] == ':') {
		txt_lab_tab[op] = expr_pos;

		//clog << "Get a text_label: \"" << op << "\" of the expr_pos  " << expr_pos << endl;
		//log <<  "Get a text_label: \"" << op << "\" of the expr_pos  " << expr_pos << endl;



		++pos;
		for (; pos < s.length(); ++pos) {
			string op1 = Get_Next_String(s, pos);
			txt_lab_tab[op1] = expr_pos; // Record the position of the label in text with unordered_map

			//clog << "Get a text_label: \"" << op << "\" of the expr_pos  " << expr_pos << endl;
			//log <<  "Get a text_label: \"" << op1 << "\" of the expr_pos  " << expr_pos << endl;


		}
		return true;
	}
	else if (op[0] == '.') {
		// s[pos] != ':'
		// This command is started with '.'

		if (op == ".data") {
			state = state_num::data;
			//clog << "Get a command \".data\" and change the state" << endl;
			//log <<  "Get a command \".data\" and change the state" << endl;

		}
		else if (op == ".text") {
			state = state_num::text;
			//clog << "Get a command \".text\"" << endl;
			//log <<  "Get a command \".text\"" << endl;


		}
		return true;
	}
	else if (op == "") {
		return true;
	}
	return false;
}

void MipsSimulatorClass::Data_Process(string s, state_num & state)
{
	size_t pos = 0;
	string op = Get_Next_String(s, pos);

	if (pos < s.length() && s[pos] == ':') {
		mem_lab_tab[op] = mem_pos;

		//clog << "Get a mem_label: \"" << op << "\" of the mem_pos " << mem_pos << endl;
		//log <<  "Get a mem_label: \"" << op << "\" of the mem_pos " << mem_pos << endl;



		++pos;
		for (; pos < s.length(); ++pos) {
			string op1 = Get_Next_String(s, pos);
			mem_lab_tab[op1] = mem_pos;// Record the position of the mem label with unordered_map

			//clog << "Get a mem_label: " << op << " of the mem_pos " << mem_pos << endl;
			//log <<  "Get a mem_label: " << op1 << " of the mem_pos " << mem_pos << endl;


		}
	}
	else if (op[0] == '.') {
		if (op == ".data") {
			state = state_num::data;
			//clog << "Get a command \".data\"" << endl;
			//log <<  "Get a command \".data\"" << endl;


		}
		else if (op == ".text") {
			state = state_num::text;
			//clog << "Get a command \".text\" and change the state" << endl;
			//log <<  "Get a command \".text\" and change the state" << endl;


		}
		else if (op == ".align") {
			int n = Get_Next_Num<int>(s, pos);
			//clog << "Get a command \".align " << n << "\"" << endl;
			//log <<  "Get a command \".align " << n << "\"" << endl;


			//clog << "Previous mem_pos: " << mem_pos << endl;
			//log <<  "Previous mem_pos: " << mem_pos << endl;



			int delta = 1 << n;
			int k = 0, newpos = 0;
			for (; newpos < mem_pos; ++k) {
				newpos += delta;
			}
			mem_pos = newpos;

			//clog << "Mem_pos is changed to: " << mem_pos << endl;
			//log <<  "Mem_pos is changed to: " << mem_pos << endl;


		}
		else if (op == ".ascii") {
			//string oristr = Get_Next_String(s, pos);
			string str = String_Fetch(s, pos);
			//clog << "Get a command \".ascii " << str << "\"" << endl;
			//log <<  "Get a command \".ascii " << str << "\"" << endl;


			//clog << "Previous mem_pos: " << mem_pos << endl;
			//log <<  "Previous mem_pos: " << mem_pos << endl;



			for (unsigned int i = 0; i < str.length(); ++i) {
				memory[mem_pos++] = str[i];
			}
			//clog << "Put the string (without end signal) " << str << " into the memory at: " << mem_pos << endl;
			//log <<  "Put the string (without end signal) " << str << " into the memory at: " << mem_pos << endl;


		}
		else if (op == ".asciiz") {
			//string oristr = Get_Next_String(s, pos);
			string str = String_Fetch(s, pos);
			//clog << "Get a command \".asciiz " << str << "\"" << endl;
			//log <<  "Get a command \".asciiz " << str << "\"" << endl;


			//clog << "Previous mem_pos: " << mem_pos << endl;
			//log <<  "Previous mem_pos: " << mem_pos << endl;



			for (unsigned int i = 0; i < str.length(); ++i) {
				memory[mem_pos++] = str[i];
			}
			memory[mem_pos++] = '\0';
			//clog << "Put the string (with end signal) " << str << " into the memory at: " << mem_pos << endl;
			//log <<  "Put the string (with end signal) " << str << " into the memory at: " << mem_pos << endl;


		}
		else if (op == ".byte") {
			vector<char> vstr;
			while (pos < s.length()) {
				string str = Get_Next_String(s, pos);
				size_t tmp = 0;
				str = String_Fetch(str, tmp);
				if (str != "") str.push_back(str[0]);
			}

			//clog << "Get a command \".byte ";
			//log <<  "Get a command \".byte ";


			for (auto x : vstr) {
				//clog << x << ' ';
				//log <<  x << ' ';

			}

			//clog << "\"" << endl;
			//log <<  "\"" << endl;


			//clog << "Previous mem_pos: " << mem_pos << endl;
			//log <<  "Previous mem_pos: " << mem_pos << endl;



			//clog << "Put the byte ";
			//log <<  "Put the byte ";


			for (auto x : vstr) {
				memory[mem_pos++] = x;
				//clog << x << ' ';
				//log <<  x << ' ';


			}
			//clog << "into the memory and the mem_pos is changed to " << mem_pos << endl;
			//log <<  "into the memory and the mem_pos is changed to " << mem_pos << endl;


		}
		else if (op == ".half") {
			vector<short> vn;
			while (pos < s.length()) {
				short n = Get_Next_Num<short>(s, pos);
				vn.push_back(n);
			}
			//clog << "Get a command \".half ";
			//log <<  "Get a command \".half ";


			for (auto x : vn) {
				//clog << x << ' ';
				//log <<  x << ' ';

			}

			//clog << "\"" << endl;
			//log <<  "\"" << endl;


			//clog << "Previous mem_pos: " << mem_pos << endl;
			//log <<  "Previous mem_pos: " << mem_pos << endl;



			//clog << "Put the half ";
			//log <<  "Put the half ";


			for (auto x : vn) {
				char* byte = reinterpret_cast<char*> (&x);
				memory[mem_pos++] = byte[0];
				memory[mem_pos++] = byte[1];
				//clog << *(reinterpret_cast<short*> (byte)) << ' ';
				//log <<  *(reinterpret_cast<short*> (byte)) << ' ';


			}
			//clog << "into the memory and the mem_pos is changed to " << mem_pos << endl;
			//log <<  "into the memory and the mem_pos is changed to " << mem_pos << endl;


		}
		else if (op == ".word") {
			vector<int> vn;
			while (pos < s.length()) {
				int n = Get_Next_Num<int>(s, pos);
				vn.push_back(n);
			}
			//clog << "Get a command \".word ";
			//log <<  "Get a command \".word ";


			for (auto x : vn) {
				//clog << x << ' ';
				//log <<  x << ' ';

			}

			//clog << "\"" << endl;
			//log <<  "\"" << endl;


			//clog << "Previous mem_pos: " << mem_pos << endl;
			//log <<  "Previous mem_pos: " << mem_pos << endl;



			//clog << "Put the word ";
			//log <<  "Put the word ";


			for (auto x : vn) {
				char* byte = reinterpret_cast<char*> (&x);
				memory[mem_pos++] = byte[0];
				memory[mem_pos++] = byte[1];
				memory[mem_pos++] = byte[2];
				memory[mem_pos++] = byte[3];
				//clog << *(reinterpret_cast<int*> (byte)) << ' ';
				//log <<  *(reinterpret_cast<int*> (byte)) << ' ';


			}
			//clog << "into the memory and the mem_pos is changed to " << mem_pos << endl;
			//log <<  "into the memory and the mem_pos is changed to " << mem_pos << endl;


		}
		else if (op == ".space") {
			int n = Get_Next_Num<int>(s, pos);
			//clog << "Get a command \".space " << n << "\"" << endl;
			//log <<  "Get a command \".space " << n << "\"" << endl;


			//clog << "Previous mem_pos: " << mem_pos << endl;
			//log <<  "Previous mem_pos: " << mem_pos << endl;


			mem_pos += n;
			//clog << "Change the mem_pos to: " << mem_pos << endl;
			//log <<  "Change the mem_pos to: " << mem_pos << endl;


		}
		else {
			//clog << "Get an unknown command!!!!" << endl;
			//log <<  "Get an unknown command!!!!" << endl;


			throw(0);
		}
	}
	else if (op == "") {
		return;
	}
	else {
		//clog << "Get unknown command!!!!!!" << endl;
		//log <<  "Get unknown command!!!!!!" << endl;


		throw(0);
	}
}


void MipsSimulatorClass::readcode(std::istream & codein)
{
	/// Process the Mips code from the stream codein, which comes from a whole file
	log.open("C:/AResource/PPCA/mips/Data/Readcode.log");


	vector<string> preExpr;
	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;
	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;
	//clog << "Code reading START" << endl;
	//log <<  "Code reading START" << endl;
	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;
	//clog << "First scanning START" << endl;
	//log <<  "First scanning START" << endl;
	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;

	// First scanning of the source code
	// Execute all the command in .data and record the mem_label into a unordered map
	// Put the commands in .text into a vector<string> preExpr and record the text_label into a unordered map
	string tmps;
	//int expr_pos = 0, mem_pos = 0;
	state_num state = state_num::data;

	// For //clog

	// For log
	int linenum = 0;

	while (getline(codein, tmps)) {
		//clog << "---------------------------------------------------------------------------------------------------" << endl;
		//log <<  "---------------------------------------------------------------------------------------------------" << endl;
		// For //clog
		// For log
		++linenum;

		if (state == state_num::text) {
			// Get the position of the text labels

			//clog << "Start a Code_Process of the Line " << linenum << " in " << (state == state_num::data ? "data" : "text") << " mod" << endl;
			//log <<  "Start a Code_Process of the Line " << linenum << " in " << (state == state_num::data ? "data" : "text") << " mod" << endl;
			//clog << "The origin line is \"" << tmps << "\"" << endl;
			//log <<  "The origin line is \"" << tmps << "\"" << endl;

			bool re = Text_labelProcess(tmps, state);
			if (re) continue;
			++expr_pos;
			preExpr.push_back(tmps);

			//clog << "Get a command: " << tmps << " and push it to the vector of preExpr" << endl;
			//log <<  "Get a command: " << tmps << " and push it to the vector of preExpr" << endl;


		}
		else {
			// state == data

			//clog << "Start a Code_Process of the Line " << linenum << " in " << (state == state_num::data ? "data" : "text") << " mod" << endl;
			//log <<  "Start a Code_Process of the Line " << linenum << " in " << (state == state_num::data ? "data" : "text") << " mod" << endl;
			//clog << "The origin line is \"" << tmps << "\"" << endl;
			//log <<  "The origin line is \"" << tmps << "\"" << endl;

			Data_Process(tmps, state);

		}
	}
	// Output preExpr for test
	std::ofstream pE("C:/AResource/PPCA/mips/Data/preExpr.out");
	for (auto x : preExpr) pE << x << endl;
	pE.close();

	//clog << "---------------------------------------------------------------------------------------------------" << endl;
	//log <<  "---------------------------------------------------------------------------------------------------" << endl;


	//clog << "First scanning COMPLETE!" << endl;
	//log <<  "First scanning COMPLETE!" << endl;



	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;


	//clog << "Second scanning START" << endl;
	//log <<  "Second scanning START" << endl;


	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;



	// Second scanning of the preExpr
	// Change the string into tokens
	// Change the labels into address

	// For //clog

	// For log


	int nowline = 0;

	for (auto x : preExpr) {
		// For //clog

		// For log


		++nowline;
		//clog << "---------------------------------------------------------------------------------------------------" << endl;
		//log <<  "---------------------------------------------------------------------------------------------------" << endl;


		//clog << "Start a Token_Process of the Line " << nowline << " in preEpr" << endl;
		//log <<  "Start a Token_Process of the Line " << nowline << " in preEpr" << endl;


		//clog << "The origin command is: " << x << endl;
		//log <<  "The origin command is: " << x << endl;


		size_t pos = 0;
		UsefulStructures::Token token;
		string op = Get_Next_String(x, pos);
		if (op == "mul" || op == "mulu" || op == "div" || op == "divu") {
			size_t tmppos = pos;
			string r1, r2, r3;
			r1 = Get_Next_String(x, tmppos);
			r2 = Get_Next_String(x, tmppos);
			r3 = Get_Next_String(x, tmppos);
			if (r3 == "") op += '2';
		}
		token.op = op_num_tab[op];

		//clog << "Find the op is: " << op << endl;
		//log <<  "Find the op is: " << op << endl;



		string r[3];
		int rstate[3];
		for (int i = 0; i < 3; ++i) {
			r[i] = Get_Next_String(x, pos);
			if (r[i] == "") rstate[i] = UsefulStructures::r_state::none;
			else if (isReg(r[i])) rstate[i] = UsefulStructures::r_state::regi;
			else rstate[i] = UsefulStructures::r_state::immi;
		}

		for (int i = 0; i < 3; ++i) {
			if (rstate[i] == UsefulStructures::r_state::immi) {
				token.rstate[i] = UsefulStructures::r_state::immi;
				if (r[i][0] == '-' || (r[i][0] <= '9'  && r[i][0] >= '0')) {
					size_t t = 0;
					int n = Get_Next_Num<int>(r[i], t);
					token.r[i] = n;
					//clog << "The r[" << i << "] is a immidiate number " << n << endl;
					//log <<  "The r[" << i << "] is a immidiate number " << n << endl;


				}
				else {
					// r[i] is a text_label
					int n;
					if (txt_lab_tab.find(r[i]) != txt_lab_tab.end()) {
						n = txt_lab_tab[r[i]];
						//clog << "The r[" << i << "] is a text_label \"" << r[i] << "\" represent the Line " << n << endl;
						//log <<  "The r[" << i << "] is a text_label \"" << r[i] << "\" represent the Line " << n << endl;


					}
					else {
						n = mem_lab_tab[r[i]];
						//clog << "The r[" << i << "] is a mem_label \"" << r[i] << "\" represent the mem_pos" << n << endl;
						//log <<  "The r[" << i << "] is a mem_label \"" << r[i] << "\" represent the mem_pos" << n << endl;


					}
					token.r[i] = n;
				}
			}
			else if (rstate[i] == UsefulStructures::r_state::none) {
				token.r[i] = 0;
				token.rstate[i] = UsefulStructures::r_state::none;
				//clog << "The r[" << i << "] is none" << endl;
				//log <<  "The r[" << i << "] is none" << endl;


			}
			else {
				// rstate[i] == regi
				int offset = 0;
				string orireg = r[i];
				if (r[i][0] != '$') {
					size_t t = 0;
					offset = Get_Next_Num<int>(r[i], t);
					orireg = Get_Next_String(r[i], t);
				}
				string reg_name;
				for (int t = 1; orireg[t] != 0; ++t) {
					reg_name += orireg[t];
				}
				int n;
				size_t t = 0;
				if (reg_name[0] <= '9' && reg_name[0] >= '0') n = Get_Next_Num<int>(reg_name, t);
				else n = reg_num_tab[reg_name];

				token.r[i] = n;
				token.rstate[i] = UsefulStructures::r_state::regi;

				//clog << "The r[" << i << "] is a register " << reg_name << " represent the reg_num " << n;
				//log <<  "The r[" << i << "] is a register " << reg_name << " represent the reg_num " << n;


				if (offset != 0) {
					token.offset = offset;
					//clog << " with offset " << offset;
					//log <<  " with offset " << offset;


				}
				//clog << endl;
				//log <<  endl;


			}
		}
		expr.push_back(token);
	}
	//clog << "---------------------------------------------------------------------------------------------------" << endl;
	//log <<  "---------------------------------------------------------------------------------------------------" << endl;


	//clog << "Second scanning COMPLETE" << endl;
	//log <<  "Second scanning COMPLETE" << endl;


	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;


	//clog << "Code reading COMPLETE" << endl;
	//log <<  "Code reading COMPLETE" << endl;


	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;


	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;


	log.close();

	//remember to figure out which mul, mulu, div and divu the command is!!!!!!!!!!!!!!!!!!!!

	preExpr.clear();
}

void MipsSimulatorClass::pipeline()
{
	log.open("C:/AResource/PPCA/mips/Data/Exec.log");

	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;


	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;


	//clog << "Pipline START" << endl;
	//log <<  "Pipline START" << endl;


	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;


	PC = txt_lab_tab["main"];
	long long cycle = 0;
	deque<PipelineClass> line;
	int wait = 0;
	int busyreg[4] = { -1, -1, -1, -1 };
	int run_state = UsefulStructures::pip_run_state::run;
	while (true) {
		++cycle;

		bool memory_busy = false;
		if (PC < expr.size() && (line.empty() || (run_state == UsefulStructures::pip_run_state::run &&line.back().nowpip > 1)))
			line.push_back(PipelineClass(PC));
		if (line.empty()) {
			//clog << "There is nothing in pipeline before syscall 10 or 17 appear" << endl;
			//log <<  "There is nothing in pipeline before syscall 10 or 17 appear" << endl;
			break;
		}
		if (run_state != UsefulStructures::pip_run_state::clear)
			run_state = UsefulStructures::pip_run_state::run;
		if (line.empty())
			run_state = UsefulStructures::pip_run_state::run;

		if (wait > 0) {
			--wait;
			run_state = UsefulStructures::pip_run_state::pause;
			//clog << "---------------------------------------------------------------------------------------------------" << endl;
			//log <<  "---------------------------------------------------------------------------------------------------" << endl;
			//clog << "Cycle " << cycle << " WAIT" << endl;
			//log <<  "Cycle " << cycle << " WAIT" << endl;
		}
		else {
			//clog << "---------------------------------------------------------------------------------------------------" << endl;
			//log <<  "---------------------------------------------------------------------------------------------------" << endl;
			//clog << "Cycle " << cycle << " START" << endl;
			//log <<  "Cycle " << cycle << " START" << endl;
		}

		for (deque<PipelineClass>::iterator it = line.begin(); it != line.end(); ++it) {
			it->StartNext(run_state, memory_busy, wait, busyreg);
		}

		if (run_state == UsefulStructures::pip_run_state::stopALL) {
			//clog << "\nGet stopALL command, end the execution!" << endl;
			//log <<  "\nGet stopALL command, end the execution!" << endl;
			break;
		}

		if (run_state == UsefulStructures::pip_run_state::clear) {
			//clog << "\nGet clear command, clear the instructions before execution" << endl;
			//log <<  "\nGet clear command, clear the instructions before execution" << endl;
			while (line.back().nowpip <= 3) line.pop_back();
		}

		while (line.size() != 0 && line.front().nowpip > 5) line.pop_front();
	}

	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;
	//clog << "Pipline COMPLETE" << endl;
	//log <<  "Pipline COMPLETE" << endl;
	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;
	//clog << "===================================================================================================" << endl;
	//log <<  "===================================================================================================" << endl;

	log.close();

}


void MipsSimulatorClass::exec(std::istream & codein)
{
	// Read code from the source and prepare the commands into vector<Token> Expr
	readcode(codein);

	// Start 5 pipeline
	pipeline();

}

