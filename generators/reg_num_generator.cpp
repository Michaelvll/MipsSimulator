#include <iostream>
#include <string>
using namespace std;

int main() {
    string s[] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0",
                  "t1",   "t2", "t3", "t4", "t5", "t6", "t7", "s0", "s1",
                  "s2",   "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0",
                  "k1",   "gp", "sp", "s8", "ra", "lo", "lh"};

    for (int i = 0; i < 32; ++i) {
        string ans = "reg_num_tab[\"" + s[i] + "\"] = reg_num::" + s[i] + ";";
        cout << ans << endl;
    }

    return 0;
}