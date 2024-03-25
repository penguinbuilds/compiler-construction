#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <regex>
#include <string>
using namespace std;

vector<string> langKeywords = {
    "DECLARE", "SET", "PRINT", "DEL", "QUIT"
};

vector<string> langOperators = {"+", "="};

unordered_map<char, int> variable;

regex declare("^DECLARE [a-z]");
regex setEqualToNum("^SET [a-z] [=] \\d+(\\.\\d+)?");
regex setEqualToSum("^SET [a-z] [=] [a-z] [+] [a-z]");
regex print("^PRINT [a-z]");
regex del("^DEL [a-z]");

int main() {

    ifstream readFromFile("open-ended-input-02.txt");
    ofstream writeToFile("open-ended-output.txt");

    string token;
    int count = 0;
    int keywords = 0;
    int operators = 0;
    int varCount = 0;

    unordered_map<char, int> variableInstances;

    while (readFromFile >> token) {
        for (string &it: langKeywords) {
            if (token == it) {
                keywords++;
            }
        }
        for (string &it: langOperators) {
            if (token == it) {
                operators++;
            }
        }
        if (token.size() == 1) {
            char ch = token[0];
            if (ch >= 97 && ch <= 122 && variableInstances.count(ch) == 0) {
                variableInstances[ch]++;
                varCount++;
            }
        }
        count++;
    }

    readFromFile.clear();
    readFromFile.seekg(ios::beg);

    string line;

    char temp;

    while (getline(readFromFile, line) && line != "QUIT") {
        
        if (regex_match(line, declare)) {

            temp = line[8];
            variable[temp] = 0;

        } else if (regex_match(line, setEqualToNum)) {

            temp = line[4];

            if (variable.count(temp) != 0) {
                int val;
                val = stoi(line.substr(8));
                variable[temp] = val;
            } else {
                writeToFile << "ERROR: Attempted to assign value to undeclared variable." << endl;
                break;
            }

        } else if (regex_match(line, setEqualToSum)) {

            temp = line[4];

            char var1, var2;
            var1 = line[8];
            var2 = line[12];

            if (variable.count(temp) != 0 && variable.count(var1) != 0 && variable.count(var2) != 0) {
                variable[temp] = variable[var1] + variable[var2];
            } else {
                writeToFile << "ERROR: Undeclared variable involved in addition." << endl;
                break;
            }

        } else if (regex_match(line, print)) {

            temp = line[6];

            if (variable.count(temp) != 0) {
                writeToFile << variable[temp] << endl;
            } else {
                writeToFile << "ERROR: Attempted to print undeclared variable." << endl;
                break;
            }

        } else if (regex_match(line, del)) {

            temp = line[4];

            if (variable.count(temp) != 0) {
                variable.erase(temp);
            } else {
                writeToFile << "ERROR: Attempted to delete non-existent variable." << endl;
                break;
            }

        } else {
            writeToFile << "ERROR: Illegible Instruction" << endl;
            break;
        }

    }

    readFromFile.close();
    writeToFile.close();

    cout << "Total number of tokens: " << count << endl;
    cout << "Total number of keywords: " << keywords << endl;
    cout << "Total number of operators: " << operators << endl;
    cout << "Total number of unique variables: " << varCount << endl;
    cout << endl;

    return 0;
}