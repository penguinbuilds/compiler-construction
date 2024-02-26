#include <iostream>
#include <vector>
using namespace std;

void removeLeftRecursion(vector<char> production) {

    if (production[0] != production[3]) {
        cout << "Left Recursion not present." << endl;
        return;
    }

    char nonTerminal = production[0];
    int pipeLoc;

    vector<char> alpha;
    vector<char> beta;

    for (int i = 4; i < production.size(); i++) {
        if (production[i] == '|') {
            pipeLoc = i;
            break;
        } else {
            alpha.emplace_back(production[i]);
        }
    }
    for (int i = pipeLoc+1; i < production.size(); i++) {
        beta.emplace_back(production[i]);
    }

    string a(alpha.begin(), alpha.end());
    string b(beta.begin(), beta.end());

    cout << "Production after removal of Left Recursion: " << endl;
    cout << nonTerminal << "  -> " << b << nonTerminal << "'" << endl;
    cout << nonTerminal << "' -> " << a << nonTerminal << "'|$" << endl;
}

int main() {

    string exp;
    vector<char> production;

    cout << "Enter the production: ";
    cin >> exp;

    for (char c : exp) {
        production.emplace_back(c);
    }    

    removeLeftRecursion(production);

    cout << endl;
    return 0;
}