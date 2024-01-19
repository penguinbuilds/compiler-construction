#include <iostream>
#include <fstream>
using namespace std;

int main() {

    ifstream readFromFile("02-input-file.txt");
    ofstream writeToFile("02-output-file.txt");

    char ch;
    int count = 0;
    bool isToken = false;

    while (readFromFile.get(ch)) {
        writeToFile.put(ch);

        if (ch == ' ' || ch == '\n') {
            isToken = false;
        } else if (!isToken) {
            isToken = true;
            count++;
        }
    }

    readFromFile.close();
    writeToFile.close();

    cout << "File copied successfully." << endl;
    cout << "No. of tokens: " << count << endl;

    return 0;
}