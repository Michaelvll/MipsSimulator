#include "MipsSimulatorClass.h"
#include "PipelineClass.h"
#include <vector>
#include <deque>
using std::log;
using std::endl;
using std::vector;
using std::deque;

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
	reg_num_tab["lo"] = reg_num::lo;
	reg_num_tab["hi"] = reg_num::hi;

	//Initialize the operation table from string to op_num
	op_num_tab["add"] = op_num::add;
	op_num_tab["addu"] = op_num::addu;
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

	// Initialize the type of operation table from op_num to type_op_num
	type_op[op_num::add] = type_op_num::sig;
	type_op[op_num::addu] = type_op_num::unsig;
	type_op[op_num::sub] = type_op_num::sig;
	type_op[op_num::subu] = type_op_num::unsig;
	type_op[op_num::mul] = type_op_num::sig;
	type_op[op_num::mulu] = type_op_num::unsig;
	type_op[op_num::mul2] = type_op_num::sig;
	type_op[op_num::mulu2] = type_op_num::sig;
	type_op[op_num::div] = type_op_num::sig;
	type_op[op_num::divu] = type_op_num::unsig;
	type_op[op_num::div2] = type_op_num::sig;
	type_op[op_num::divu2] = type_op_num::sig;
	type_op[op_num::xor] = type_op_num::sig;
	type_op[op_num::xoru] = type_op_num::unsig;
	type_op[op_num::neg] = type_op_num::sig;
	type_op[op_num::negu] = type_op_num::unsig;
	type_op[op_num::rem] = type_op_num::sig;
	type_op[op_num::remu] = type_op_num::unsig;
	type_op[op_num::li] = type_op_num::sig;
	type_op[op_num::seq] = type_op_num::sig;
	type_op[op_num::sge] = type_op_num::sig;
	type_op[op_num::sgt] = type_op_num::sig;
	type_op[op_num::sle] = type_op_num::sig;
	type_op[op_num::slt] = type_op_num::sig;
	type_op[op_num::sne] = type_op_num::sig;
	type_op[op_num::b] = type_op_num::sig;
	type_op[op_num::beq] = type_op_num::sig;
	type_op[op_num::bne] = type_op_num::sig;
	type_op[op_num::bge] = type_op_num::sig;
	type_op[op_num::ble] = type_op_num::sig;
	type_op[op_num::bgt] = type_op_num::sig;
	type_op[op_num::blt] = type_op_num::sig;
	type_op[op_num::beqz] = type_op_num::sig;
	type_op[op_num::bnez] = type_op_num::sig;
	type_op[op_num::blez] = type_op_num::sig;
	type_op[op_num::bgez] = type_op_num::sig;
	type_op[op_num::bgtz] = type_op_num::sig;
	type_op[op_num::bltz] = type_op_num::sig;
	type_op[op_num::j] = type_op_num::sig;
	type_op[op_num::jr] = type_op_num::sig;
	type_op[op_num::jal] = type_op_num::sig;
	type_op[op_num::jalr] = type_op_num::sig;
	type_op[op_num::la] = type_op_num::sig;
	type_op[op_num::lb] = type_op_num::sig;
	type_op[op_num::lh] = type_op_num::sig;
	type_op[op_num::lw] = type_op_num::sig;
	type_op[op_num::sb] = type_op_num::sig;
	type_op[op_num::sh] = type_op_num::sig;
	type_op[op_num::sw] = type_op_num::sig;
	type_op[op_num::move] = type_op_num::sig;
	type_op[op_num::mfhi] = type_op_num::sig;
	type_op[op_num::mflo] = type_op_num::sig;
	type_op[op_num::nop] = type_op_num::sig;
	type_op[op_num::syscall] = type_op_num::sig;



	// Initialize the operation table from op_num to class
	op_class_tab[0] = new CommandClass::Empty;
	op_class_tab[op_num::add] = new CommandClass::Add;
	op_class_tab[op_num::addu] = new CommandClass::Addu;
	op_class_tab[op_num::sub] = new CommandClass::Sub;
	op_class_tab[op_num::subu] = new CommandClass::Subu;
	op_class_tab[op_num::mul] = new CommandClass::Mul;
	op_class_tab[op_num::mulu] = new CommandClass::Mulu;
	op_class_tab[op_num::mul2] = new CommandClass::Mul2;
	op_class_tab[op_num::mulu2] = new CommandClass::Mulu2;
	op_class_tab[op_num::div] = new CommandClass::Div;
	op_class_tab[op_num::divu] = new CommandClass::Divu;
	op_class_tab[op_num::div2] = new CommandClass::Div2;
	op_class_tab[op_num::divu2] = new CommandClass::Divu2;
	op_class_tab[op_num::xor] = new CommandClass::Xor;
	op_class_tab[op_num::xoru] = new CommandClass::Xoru;
	op_class_tab[op_num::neg] = new CommandClass::Neg;
	op_class_tab[op_num::negu] = new CommandClass::Negu;
	op_class_tab[op_num::rem] = new CommandClass::Rem;
	op_class_tab[op_num::remu] = new CommandClass::Remu;
	op_class_tab[op_num::li] = new CommandClass::Li;
	op_class_tab[op_num::seq] = new CommandClass::Seq;
	op_class_tab[op_num::sge] = new CommandClass::Sge;
	op_class_tab[op_num::sgt] = new CommandClass::Sgt;
	op_class_tab[op_num::sle] = new CommandClass::Sle;
	op_class_tab[op_num::slt] = new CommandClass::Slt;
	op_class_tab[op_num::sne] = new CommandClass::Sne;
	op_class_tab[op_num::b] = new CommandClass::B;
	op_class_tab[op_num::beq] = new CommandClass::Beq;
	op_class_tab[op_num::bne] = new CommandClass::Bne;
	op_class_tab[op_num::bge] = new CommandClass::Bge;
	op_class_tab[op_num::ble] = new CommandClass::Ble;
	op_class_tab[op_num::bgt] = new CommandClass::Bgt;
	op_class_tab[op_num::blt] = new CommandClass::Blt;
	op_class_tab[op_num::beqz] = new CommandClass::Beqz;
	op_class_tab[op_num::bnez] = new CommandClass::Bnez;
	op_class_tab[op_num::blez] = new CommandClass::Blez;
	op_class_tab[op_num::bgez] = new CommandClass::Bgez;
	op_class_tab[op_num::bgtz] = new CommandClass::Bgtz;
	op_class_tab[op_num::bltz] = new CommandClass::Bltz;
	op_class_tab[op_num::j] = new CommandClass::J;
	op_class_tab[op_num::jr] = new CommandClass::Jr;
	op_class_tab[op_num::jal] = new CommandClass::Jal;
	op_class_tab[op_num::jalr] = new CommandClass::Jalr;
	op_class_tab[op_num::la] = new CommandClass::La;
	op_class_tab[op_num::lb] = new CommandClass::Lb;
	op_class_tab[op_num::lh] = new CommandClass::Lh;
	op_class_tab[op_num::lw] = new CommandClass::Lw;
	op_class_tab[op_num::sb] = new CommandClass::Sb;
	op_class_tab[op_num::sh] = new CommandClass::Sh;
	op_class_tab[op_num::sw] = new CommandClass::Sw;
	op_class_tab[op_num::move] = new CommandClass::Move;
	op_class_tab[op_num::mfhi] = new CommandClass::Mfhi;
	op_class_tab[op_num::mflo] = new CommandClass::Mflo;
	op_class_tab[op_num::nop] = new CommandClass::Nop;
	//op_class_tab[op_num::syscall] = new CommandClass::Syscall;


}
MipsSimulatorClass::~MipsSimulatorClass()
{
	for (auto x : op_class_tab) {
		delete x;
	}
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
	for (; pos < s.length() && s[pos] != ' ' && s[pos] != ':' && s[pos] != ')' && s[pos] != ','; ++pos) op += s[pos];
	for (; pos < s.length() && (s[pos] == ' ' || s[pos] == ',' || s[pos] == '\t' || s[pos] == ')'); ++pos);
	return op;
}

string MipsSimulatorClass::String_Fetch(const string & s)
{
	string fs;
	size_t pos = 0;
	for (; pos < s.length(); ++pos) {
		if (s[pos] == '\"' || '\'')continue;
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

inline bool MipsSimulatorClass::isReg(const string & s)
{
	for (auto x : s) if (x == '$') return true;
	return false;
}

bool MipsSimulatorClass::Text_labelProcess(const string &s, int &expr_pos, state_num &state)
{
	/// Process the command in text area

	size_t pos = 0;
	string op = Get_Next_String(s, pos);

	if (pos < s.length() && s[pos] == ':') {
		txt_lab_tab[op] = expr_pos;

		log << "Get a text_label: \"" << op << "\" of the expr_pos  " << expr_pos << endl;

		++pos;
		for (; pos < s.length(); ++pos) {
			string op = Get_Next_String(s, pos);
			txt_lab_tab[op] = expr_pos; // Record the position of the label in text with unordered_map

			log << "Get a text_label: \"" << op << "\" of the expr_pos  " << expr_pos << endl;
		}
		return true;
	}
	else if (op[0] == '.') {
		// s[pos] != ':'
		// This command is started with '.'

		if (op == ".data") {
			state = state_num::data;
			log << "Get a command \".data\" and change the state"
				<< endl;
		}
		else if (op == ".text") {
			state = state_num::text;
			log << "Get a command \".text\"" << endl;
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
	size_t pos = 0;
	string op = Get_Next_String(s, pos);

	if (pos < s.length() && s[pos] == ':') {
		mem_lab_tab[op] = mem_pos;

		log << "Get a mem_label: \"" << op << "\" of the mem_pos " << mem_pos << endl;

		++pos;
		for (; pos < s.length(); ++pos) {
			string op = Get_Next_String(s, pos);
			mem_lab_tab[op] = mem_pos;// Record the position of the mem label with unordered_map

			log << "Get a mem_label: " << op << " of the mem_pos " << mem_pos << endl;
		}
	}
	else if (op[0] == '.') {
		if (op == ".data") {
			state = state_num::data;
			log << "Get a command \".data\"" << endl;
		}
		else if (op == ".text") {
			state = state_num::text;
			log << "Get a command \".text\" and change the state" << endl;
		}
		else if (op == ".align") {
			int n = Get_Next_Num<int>(s, pos);
			log << "Get a command \".align " << n << "\"" << endl;
			log << "Previous mem_pos: " << mem_pos << endl;

			int delta = 1 << n;
			int k = 0, newpos = 0;
			for (; newpos < mem_pos; ++k) {
				newpos += delta;
			}
			mem_pos = newpos;

			log << "Mem_pos is changed to: " << mem_pos << endl;
		}
		else if (op == ".ascii") {
			string oristr = Get_Next_String(s, pos);
			string str = String_Fetch(oristr);
			log << "Get a command \".ascii " << str << "\"" << endl;
			log << "Previous mem_pos: " << mem_pos << endl;

			for (unsigned int i = 0; i < str.length(); ++i) {
				memory[mem_pos++] = str[i];
			}
			log << "Put the string (without end signal) " << str << " into the memory at: " << mem_pos << endl;
		}
		else if (op == ".asciiz") {
			string oristr = Get_Next_String(s, pos);
			string str = String_Fetch(oristr);
			log << "Get a command \".asciiz " << str << "\"" << endl;
			log << "Previous mem_pos: " << mem_pos << endl;

			for (unsigned int i = 0; i < str.length(); ++i) {
				memory[mem_pos++] = str[i];
			}
			memory[mem_pos++] = '\0';
			log << "Put the string (with end signal) " << str << " into the memory at: " << mem_pos << endl;
		}
		else if (op == ".byte") {
			vector<char> vstr;
			while (pos < s.length()) {
				string str = Get_Next_String(s, pos);
				str = String_Fetch(str);
				if (str != "") str.push_back(str[0]);
			}

			log << "Get a command \".byte ";
			for (auto x : vstr) log << x << ' ';
			log << "\"" << endl;
			log << "Previous mem_pos: " << mem_pos << endl;

			log << "Put the byte ";
			for (auto x : vstr) {
				memory[mem_pos++] = x;
				log << x << ' ';
			}
			log << "into the memory and the mem_pos is changed to " << mem_pos << endl;
		}
		else if (op == ".half") {
			vector<short> vn;
			while (pos < s.length()) {
				short n = Get_Next_Num<short>(s, pos);
				vn.push_back(n);
			}
			log << "Get a command \".half ";
			for (auto x : vn) log << x << ' ';
			log << "\"" << endl;
			log << "Previous mem_pos: " << mem_pos << endl;

			log << "Put the half ";
			for (auto x : vn) {
				char* byte = reinterpret_cast<char*> (&x);
				memory[mem_pos++] = byte[0];
				memory[mem_pos++] = byte[1];
				log << *(reinterpret_cast<short*> (byte)) << ' ';
			}
			log << "into the memory and the mem_pos is changed to " << mem_pos << endl;
		}
		else if (op == ".word") {
			vector<int> vn;
			while (pos < s.length()) {
				int n = Get_Next_Num<int>(s, pos);
				vn.push_back(n);
			}
			log << "Get a command \".word ";
			for (auto x : vn) log << x << ' ';
			log << "\"" << endl;
			log << "Previous mem_pos: " << mem_pos << endl;

			log << "Put the word ";
			for (auto x : vn) {
				char* byte = reinterpret_cast<char*> (&x);
				memory[mem_pos++] = byte[0];
				memory[mem_pos++] = byte[1];
				memory[mem_pos++] = byte[2];
				memory[mem_pos++] = byte[3];
				log << *(reinterpret_cast<int*> (byte)) << ' ';
			}
			log << "into the memory and the mem_pos is changed to " << mem_pos << endl;
		}
		else if (op == ".space") {
			int n = Get_Next_Num<int>(s, pos);
			log << "Get a command \".space " << n << "\"" << endl;
			log << "Previous mem_pos: " << mem_pos << endl;
			mem_pos += n;
			log << "Change the mem_pos to: " << mem_pos << endl;
		}
		else {
			log << "Get an unknown command!!!!" << endl;
			throw(0);
		}
	}
	else if (op == "") {
		return;
	}
	else {
		log << "Get unknown command!!!!!!" << endl;
		throw(0);
	}
}


void MipsSimulatorClass::readcode(std::istream & codein)
{
	/// Process the Mips code from the stream codein, which comes from a whole file
	log.open("C:/AResource/PPCA/mips/Data/Readcode.log");

	vector<string> preExpr;
	log << "===================================================================================================" << endl;
	log << "===================================================================================================" << endl;
	log << "Code reading START" << endl;
	log << "===================================================================================================" << endl;
	log << "First scanning START" << endl;
	log << "===================================================================================================" << endl;

	// First scanning of the source code
	// Execute all the command in .data and record the mem_label into a unordered map
	// Put the commands in .text into a vector<string> preExpr and record the text_label into a unordered map
	string tmps;
	int expr_pos = 0, mem_pos = 0;
	state_num state = state_num::data;

	// For log
	int linenum = 0;

	while (getline(codein, tmps)) {
		log << "---------------------------------------------------------------------------------------------------" << endl;
		// For log
		++linenum;

		if (state == state_num::text) {
			// Get the position of the text labels

			log << "Start a Code_Process of the Line " << linenum << " in " << (state == state_num::data ? "data" : "text") << " mod" << endl;
			log << "The origin line is \"" << tmps << "\"" << endl;

			bool re = Text_labelProcess(tmps, expr_pos, state);
			if (re) continue;
			++expr_pos;
			preExpr.push_back(tmps);

			log << "Get a command: " << tmps << " and push it to the vector of preExpr" << endl;
		}
		else {
			// state == data

			log << "Start a Code_Process of the Line " << linenum << " in " << (state == state_num::data ? "data" : "text") << " mod" << endl;
			log << "The origin line is \"" << tmps << "\"" << endl;
			Data_Process(tmps, mem_pos, state);

		}
	}
	// Output preExpr for test
	std::ofstream pE("C:/AResource/PPCA/mips/Data/preExpr.out");
	for (auto x : preExpr) pE << x << endl;
	pE.close();

	log << "---------------------------------------------------------------------------------------------------" << endl;
	log << "First scanning COMPLETE!" << endl;

	log << "===================================================================================================" << endl;
	log << "Second scanning START" << endl;
	log << "===================================================================================================" << endl;

	// Second scanning of the preExpr
	// Change the string into tokens
	// Change the labels into address

	// For log
	int nowline = 0;

	for (auto x : preExpr) {
		// For log
		++nowline;
		log << "---------------------------------------------------------------------------------------------------" << endl;
		log << "Start a Token_Process of the Line " << nowline << " in preEpr" << endl;
		log << "The origin command is: " << x << endl;
		size_t pos = 0;
		UsefulStructures::Token token;
		string op = Get_Next_String(x, pos);
		if (op == "mul" || op == "mulu" || op == "div" || op == "divu") {
			unsigned tmppos = pos;
			string r1, r2, r3;
			r1 = Get_Next_String(x, tmppos);
			r2 = Get_Next_String(x, tmppos);
			r3 = Get_Next_String(x, tmppos);
			if (r3 == "") op += '2';
		}
		token.op = op_num_tab[op];
		
		log << "Find the op is: " << op << endl;

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
					log << "The r[" << i << "] is a immidiate number " << n << endl;
				}
				else {
					// r[i] is a text_label
					int n;
					if (txt_lab_tab.find(r[i]) != txt_lab_tab.end()) {
						n = txt_lab_tab[r[i]];
						log << "The r[" << i << "] is a text_label \"" << r[i] << "\" represent the Line " << n << endl;
					}
					else {
						n = mem_lab_tab[r[i]];
						log << "The r[" << i << "] is a mem_label \"" << r[i] << "\" represent the mem_pos" << n << endl;
					}
					token.r[i] = n;
				}
			}
			else if (rstate[i] == UsefulStructures::r_state::none) {
				token.r[i] = 0;
				token.rstate[i] = UsefulStructures::r_state::none;
				log << "The r[" << i << "] is none" << endl;
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

				log << "The r[" << i << "] is a register " << reg_name << " represent the reg_num " << n;
				if (offset != 0) {
					token.offset = offset;
					log << " with offset " << offset;
				}
				log << endl;
			}
		}
	}
	log << "---------------------------------------------------------------------------------------------------" << endl;
	log << "Second scanning COMPLETE" << endl;
	log << "===================================================================================================" << endl;
	log << "Code reading COMPLETE" << endl;
	log << "===================================================================================================" << endl;
	log << "===================================================================================================" << endl;
	log.close();
	//remember to figure out which mul, mulu, div and divu the command is!!!!!!!!!!!!!!!!!!!!

	preExpr.clear();
}

void MipsSimulatorClass::pipeline()
{
	log.open("C:/AResource/PPCA/mips/Data/Exec.log");
	log << "===================================================================================================" << endl;
	log << "===================================================================================================" << endl;
	log << "Pipline START" << endl;
	log << "===================================================================================================" << endl;

	long long cycle = 0;
	deque<PipelineClass> line;
	while (PC < expr.size()) {
		UsefulStructures::pip_run_state run_state = UsefulStructures::pip_run_state::run;
		++cycle;
		log << "---------------------------------------------------------------------------------------------------" << endl;
		log << "Cycle " << cycle << " START" << endl;

		for (auto x : line) {
			x.StartNext(run_state);
		}
		if (line.size() == 0 || line.back().nowpip > 1) line.push_back(PipelineClass(PC));
	}
	log.close();
}


void MipsSimulatorClass::exec(std::istream & codein)
{
	// Read code from the source and prepare the commands into vector<Token> Expr
	readcode(codein);

	// Start 5 pipeline
	pipeline();

}

