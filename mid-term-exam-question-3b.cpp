// Write all possible strings of length 5 which does not belong to the regular expression 0(1+01)*1
#include <iostream>
#include <regex>
#include <bitset>
using namespace std;

int main() {

    regex givenRE("0(1|01)*1");

    for (int i = 0; i < 32; i++) {
        bitset<5> binaryNumber(i);
        string binaryStr = binaryNumber.to_string();
        if (regex_match(binaryStr, givenRE)) {
            cout << binaryStr << " MATCHED" << endl;
        } else {
            cout << binaryStr << " Not Matched" << endl;
        }
    }

    return 0;
}
