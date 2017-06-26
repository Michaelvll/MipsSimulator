#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
	string code_path, input_path, output_path;
	if (argc < 3)
	{
		cout << "for usage as an non-interactive tool: MipsSimulator <your Mips source code> <inputfile> <outputfile>" << endl;
		cout << "Please input your source code path:";
		getline(cin, code_path);
		cout << "Please input your input file path:";
		getline(cin, input_path);
		cout << "Please input the output file path:";
		getline(cin, output_path);
	}
	else {
		code_path = string(argv[1]);
		input_path = string(argv[2]);
		output_path = string(argv[3]);
	}

	ifstream code(code_path);
	ifstream fin(input_path);
	ofstream fout(output_path);
	MipsSimulator.run(code, fin, fout);
	code.close();
	fin.close();
	fout.close();
}