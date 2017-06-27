#include <iostream>
#include <string>
#include <fstream>
#include "MipsSimulatorClass.h"
using namespace std;

int main(int argc, char *argv[]) {
	//debug
	string code_path = "C:/AResource/PPCA/mips/Data/testsuit-1/array_test2-mahaojun.s", 
		output_path = "C:/AResource/PPCA/mips/Data/test.txt";

	//if (argc < 2) {
	//	cout << "for usage as an non-interactive tool: mipssimulator <your mips source code> <output path>" << endl;
	//	cout << "please input your source code path:";
	//	getline(cin, code_path);
	//	cout << "please input your output path:";
	//	getline(cin, output_path);
	//}
	//else {
	//	code_path = string(argv[1]);
	//}

	ifstream code(code_path);
	ofstream fout(output_path);
	MipsSimulatorClass MipsSimulator;
	MipsSimulator.exec(code, fout);
	code.close();
	fout.close();

	return 0;
}