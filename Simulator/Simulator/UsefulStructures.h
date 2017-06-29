#ifndef USEFULSTRUCTURES
#define USEFULSTRUCTURES
#include <iostream>
using std::ostream;

class UsefulStructures {
public:
	enum r_state {
		none, regi, immi
	};
	enum pip_run_state {
		run, pause, clear
	};
	struct Token {
		int op;
		int r[3];
		int offset;
		r_state rstate[3];
		Token& operator=(const Token& rt);
		friend ostream& operator<<(ostream & out, const Token &token);
	};

};

#endif //USEFULSTRUCTURES