#include "MipsSimulatorClass.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

MipsSimulatorClass MipsSimulator;

int main(int argc, char *argv[]) {
  // debug
  // string code_path =
  // "C:/AResource/PPCA/mips/Data/testsuit-1/array_test2-mahaojun.s";

  string code_path;

  if (argc < 2) {
    cout << "for usage as an non-interactive tool: mipssimulator <your mips "
            "source code> <output path>"
         << endl;
    cout << "please input your source code path:";
    getline(cin, code_path);
  } else {
    code_path = string(argv[1]);
  }

  ifstream code(code_path);

  MipsSimulator.exec(code);
  code.close();

  return 0;
}