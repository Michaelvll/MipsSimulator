#include "UsefulStructures.h"

UsefulStructures usefulstructures;

ostream & operator<<(ostream & out, const UsefulStructures::Token & token)
{
	out << "Token{[op] " << token.op << ", [r]{ " << token.r[0] << ", " << token.r[1]
		<< ", " << token.r[2] << " }, [rstate]{ " << token.rstate[0] << ", " << token.rstate[1] << ", "
		<< token.rstate[2] << " }, [offset]" << token.offset << " }";
	return out;
}

ostream & operator<<(ostream & out, const UsefulStructures::arguToken & token)
{
	out << "arguToken{ [r]{ " << token.r[0] << ", " << token.r[1]
		<< ", " << token.r[2] << " }, [rstate]{ " << token.rstate[0] << ", " << token.rstate[1] << ", "
		<< token.rstate[2] << " }, [offset]" << token.offset << " }";
	return out;
}

UsefulStructures::Token & UsefulStructures::Token::operator=(const Token & rt)
{
	op = rt.op;
	for (int i = 0; i < 3; ++i) {
		r[i] = rt.r[i];
		rstate[i] = rt.rstate[i];
	}
	offset = rt.offset;
	return *this;
}

UsefulStructures::arguToken & UsefulStructures::arguToken::operator=(const Token & rt)
{
	for (int i = 0; i < 3; ++i) {
		r[i] = rt.r[i];
		rstate[i] = rt.rstate[i];
	}
	offset = rt.offset;
	return *this;
}

bool UsefulStructures::Busy(const int &nowreg, int busyreg[4])
{
	for (int i = 0; i < 4; ++i) {
		if (nowreg == busyreg[i]) return true;
	}
	return false;
}

void UsefulStructures::addBusy(const int &nowreg, int busyreg[4])
{
	if (Busy(nowreg, busyreg)) return;
	// For debug
	bool flag = false;

	for (int i = 0; i < 4; ++i) {
		if (busyreg[i] == -1) {
			busyreg[i] = nowreg;
			flag = true;
			break;
		}
	}
	// For debug
	if (!flag) std::cerr << "Failed to put in the busy reg!!!!!!!!!!" << std::endl;
}

void UsefulStructures::delBusy(const int & nowreg, int busyreg[4])
{
	for (int i = 0; i < 4; ++i) {
		if (nowreg == busyreg[i]) {
			busyreg[i] = -1;
			break;
		}
	}
}
