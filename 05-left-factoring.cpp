#include <iostream>
#include <vector>
using namespace std;

void removeLeftFactoring(vector<char> production) {

    char nonTerminal = production[0];
    int pipeLoc;

    vector<char> firstHalf;
    vector<char> secondHalf;
    vector<char> alpha;
    vector<char> beta;
    vector<char> gamma;

    for (int i = 3; i < production.size(); i++) {
        if (production[i] == '|') {
            pipeLoc = i;
            break;
        } else {
            firstHalf.emplace_back(production[i]);
        }
    }
    for (int i = pipeLoc+1; i < production.size(); i++) {
        secondHalf.emplace_back(production[i]);
    }

    int x = 0;
    while (firstHalf[x] == secondHalf[x]) {
        alpha.emplace_back(firstHalf[x]);
        x++;
    }

    if (alpha.size() == 0) {
        cout << "Left Factoring not present." << endl;
        return;
    }

    for (int i = x; i < firstHalf.size(); i++) {
        beta.emplace_back(firstHalf[i]);
    }

    for (int i = x; i < secondHalf.size(); i++) {
        gamma.emplace_back(secondHalf[i]);
    }

    string a(alpha.begin(), alpha.end());

    string b;
    if (beta.size() == 0) {
        b = "$";
    } else {
        b = string(beta.begin(), beta.end());
    }

    string y;
    if (gamma.size() == 0) {
        y = "$";
    } else {
        y = string(gamma.begin(), gamma.end());
    }

    cout << "Production after removal of Left Factoring: " << endl;
    cout << nonTerminal << "  -> " << a << nonTerminal << "'" << endl;
    cout << nonTerminal << "' -> " << b << "|" << y << endl;
}

int main() {

    string exp;
    vector<char> production;

    cout << "Enter the production: ";
    cin >> exp;

    for (char c : exp) {
        production.emplace_back(c);
    }
    
    removeLeftFactoring(production);

    return 0;
}