#include <iostream>
#include <string>
using namespace std;

int main() {
    string s =
        "add, addu, addiu, sub, subu, mul, mulu,mul2,mulu2, div,divu, div2, "
        "divu2, xor, xoru, neg, negu, rem, remu, li, seq, sge, sgt, "
        "sle,slt,sne, b, beq, bne, bge, ble, bgt, blt, beqz, bnez, blez, bgez, "
        "bgtz,bltz, j, jr, jal, jalr, la, lb, lh, lw, sb, sh, sw, move, mfhi, "
        "mflo,nop,syscall";

    int pos = 0;
    for (; pos < s.length(); ++pos) {
        for (; pos < s.length() && (s[pos] == ' ' || s[pos] == ','); ++pos)
            ;
        if (s[pos] == 0) break;
        string tmp;
        for (; s[pos] != ',' && s[pos] != ' ' && pos < s.length(); ++pos) {
            tmp += s[pos];
        }
        tmp[0] = toupper(tmp[0]);
        cout << "class " + tmp + " : public Command_Base {\n"
             << "public:\n"
             << "\tvoid exec(int &rs, int &rt, int &rd);\n"
             << "};\n"
             << endl;
        ;
    }
    return 0;
}