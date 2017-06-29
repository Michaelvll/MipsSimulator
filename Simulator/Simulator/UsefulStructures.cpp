#include "UsefulStructures.h"

ostream & operator<<(ostream & out, const UsefulStructures::Token & token)
{
	out << "\nToken{[op] " << token.op << ", [r]{ " << token.r[0] << ", " << token.r[1]
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
