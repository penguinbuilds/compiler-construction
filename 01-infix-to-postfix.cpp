#include <iostream>
using namespace std;

#define MAX 100

class stack {
public:
    int top;
    char arr[MAX];
    stack();
    int isEmpty();
    int isFull();
    void push(char item);
    void pop();
};

stack::stack() {
    top = -1;
}

int stack::isEmpty() {
    if (top == -1)
    {
        return 1;
    } else
    {
        return 0;
    }    
}

int stack::isFull() {
    if (top == MAX - 1)
    {
        return 1;
    } else
    {
        return 0;
    }    
}

void stack::push(char item) {
    top++;
    arr[top] = item;
}

void stack::pop() {
    top--;
}

int precedence(char c) {
    if (c == '^') {
        return 2;
    } else if (c == '*' || c == '/') {
        return 1;
    } else if (c == '+' || c == '-') {
        return 0;
    } else {
        return -1;
    }
}

int isOperand(char c) {
    if (c >= 48 && c <= 57 || c >= 65 && c <= 90 || c >= 97 && c <= 122) {
        return 1;
    } else {
        return 0;
    }
}

void infixToPostfix(string exp) {
    stack op;
    string ans;

    for (int i = 0; i < exp.length(); i++) {
        char c = exp[i];

        if (isOperand(c)) {
            ans += c;
        } else if (c == '(') {
            op.push(c);
        } else if ( c == ')') {
            while (!op.isEmpty() && op.arr[op.top] != '(') {
                ans += op.arr[op.top];
                op.pop();
            }
            if (op.arr[op.top] == '(') {
                op.pop();
            } else {
                cout << "Invalid expression: Unbalanced parentheses." << endl;
                return;
            }
        } else {
            while (!op.isEmpty() && precedence(c) <= precedence(op.arr[op.top])) {
                ans += op.arr[op.top];
                op.pop();
            }
            op.push(c);
        }
    }

    while (!op.isEmpty()) {
        if (op.arr[op.top] == '(' || op.arr[op.top] == ')') {
            cout << "Invalid expression: Unbalanced parentheses." << endl;
            return;
        }
        ans += op.arr[op.top];
        op.pop();
    }    

    cout << "Postfix Expression: " << ans << endl;
}

int main() {

    string exp;

    cout << "Please enter the infix expression: ";
    cin >> exp;

    infixToPostfix(exp);

    return 0;
}