#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
using namespace std;

vector<string> cppKeywords = {
    "int", "float", "string", "char", "long", "bool", "cout", "cin",
    "void", "printf", "return", "if", "else", "while", "for", "double",
    "endl", "true", "false", "do", "default", "private", "public", "case",
    "break", "not", "switch", "class", "struct"
};

vector<string> cppPunctuators = {
    ",", ".", "(", ")", "{", "}", ";", ":", "[", "]"
};

vector<string> cppOperators = {
    "+", "-", "/", "*", "%", "<", ">", "&", "|", "=", "^",
    "!", "<<", ">>", "==", "+=", "++", "--", "!=", "||", "&&"
};

vector<string> variableReferenceTable;

int isUniqueVariable(string token) {
    for (int a = 0; a < variableReferenceTable.size(); a++) {
        if (token == variableReferenceTable[a]) {
            return 0;
        }
    }
    for (int b = 0; b < cppKeywords.size(); b++) {
        if (token == cppKeywords[b]) {
            return 0;
        }
    }
    return 1;
}

int main() {

    string token;

    int keywords = 0;
    int userDefinedFunctions = 0;
    int literals = 0;
    int constants = 0;
    int operators = 0;
    int punctuators = 0;
    int stringCount = 0;
    int total_tokens = 0;

    regex intChecker("\\d+");
    regex stringChecker("^\".*\"$");
    regex funcChecker("^[a-zA-Z_]\\w*[(]\\w*\\s?\\w*[)]$");
    regex varChecker("^[a-zA-Z_]\\w*$");
    regex commentChecker("[/][/].*");

    ifstream readFromFile("03-input-file.txt");
    ofstream writeToFile("03-output-file.txt");

    while (readFromFile >> token) {
        for (int i = 0; i < cppKeywords.size(); i++) {
            if (token == cppKeywords[i]) {
                keywords++;
            }
        }
        for (int j = 0; j < cppPunctuators.size(); j++) {
            if (token == cppPunctuators[j]) {
                punctuators++;
            }  
        }
        for (int k = 0; k < cppOperators.size(); k++) {
            if (token == cppOperators[k]) {
                operators++;
            }  
        }
        if (regex_match(token, intChecker)) {
            constants++;
        }
        if (regex_match(token, stringChecker)) {
            stringCount++;
        }
        if (regex_match(token, funcChecker)) {
            userDefinedFunctions++;
        }
        if (regex_match(token, varChecker) && isUniqueVariable(token)) {
            variableReferenceTable.push_back(token);
            literals++;
        } 
        if (!regex_match(token, commentChecker)) {
            writeToFile << token;
            if (!regex_match(token, stringChecker)) {
                total_tokens++;
            }
        }   
    }

    cout << "Keywords: " << keywords << endl;
    cout << "Literals: " << literals << endl;
    cout << "User Defined Functions: " << userDefinedFunctions << endl;
    cout << "Constants: " << constants << endl;
    cout << "Punctuators: " << punctuators << endl;
    cout << "Operators: " << operators << endl;
    cout << "No. of strings: " << stringCount << endl;
    cout << "Total number of tokens: " << total_tokens << endl;
    cout << endl;    

    readFromFile.close();
    writeToFile.close();

    return 0;
}