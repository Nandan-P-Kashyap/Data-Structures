#ifndef CONVERT_EXPRESSION_H
#define CONVERT_EXPRESSION_H

#include <iostream>
#include <cctype>
#include "Stack.h"
#include "outofbound.h"
#include"nomemory.h"

using namespace std;

template <class DS>
class convert_expression {
private:
    int n;
    DS* infix;
    DS* postfix;
    Stack<DS> S;

public:
    convert_expression(const DS* arr, int len, int stackSize = 100) : S(stackSize) {
        n = len;
        infix = new DS[n + 1];
        postfix = new DS[n + 1];
        for (int i = 0; i < n; i++) {
            infix[i] = arr[i];
        }
        infix[n] = '\0';
    }

    ~convert_expression() {
        delete[] infix;
        delete[] postfix;
    }

    bool isOperator(DS c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }

    int precedence(DS op) {
        switch (op) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            case '^':
                return 3;
            default:
                return 0;
        }
    }

    bool isRightAssociative(DS op) {
        return op == '^';
    }

    void infixToPostfix() {
        
        if (infix[0] == '\0') throw outofbound();
        int j = 0;
        for (int i = 0; i < n; ++i) {
            DS token = infix[i];

            if (isOperand(token)) {
                postfix[j++] = infix[i];
            } else if (token == '(') {
                S.push(token);
            } else if (token == ')') {
                while (!S.isEmpty() && S.top() != '(') {
                    postfix[j++] = S.top();
                    S.pop();
                }
                S.pop(); // Pop the '(' from the stack
            } else if (isOperator(token)) {
                while (!S.isEmpty() &&
                       ((isRightAssociative(token) && precedence(token) < precedence(S.top())) ||
                        (!isRightAssociative(token) && precedence(token) <= precedence(S.top())))) {
                    postfix[j++] = S.top();
                    S.pop();
                }
                S.push(token);
            }
        }

        // Pop all remaining operators from the stack to the output
        while (!S.isEmpty()) {
            postfix[j++] = S.top();
            S.pop();
        }

        // Displaying the postfix expression
        cout << "Postfix Expression: ";
        for (int i = 0; i < j; i++) {
            cout << postfix[i] << " ";
        }
        cout << endl;
    }

    void infixToPrefix() {
        if (infix[0] == '\0') throw outofbound();
        Stack<DS> outputStack(n);

        // Reverse the infix expression
        DS* reversedInfix = new DS[n + 1];
        for (int i = 0; i < n; ++i) {
            reversedInfix[i] = infix[n - 1 - i];
        }
        reversedInfix[n] = '\0';

        for (int i = 0; i < n; ++i) {
            DS token = reversedInfix[i];

            if (isOperand(token)) {
                outputStack.push(token);
            } else if (token == ')') {
                S.push(token);
            } else if (token == '(') {
                while (!S.isEmpty() && S.top() != ')') {
                    outputStack.push(S.top());
                    S.pop();
                }
                S.pop(); // Pop the ')' from the stack
            } else if (isOperator(token)) {
                while (!S.isEmpty() &&
                       ((isRightAssociative(token) && precedence(token) < precedence(S.top())) ||
                        (!isRightAssociative(token) && precedence(token) <= precedence(S.top())))) {
                    outputStack.push(S.top());
                    S.pop();
                }
                S.push(token);
            }
        }

        // Pop all remaining operators from the stack to the output stack
        while (!S.isEmpty()) {
            outputStack.push(S.top());
            S.pop();
        }

        // Collecting the output in reverse order
        int j = 0;
        while (!outputStack.isEmpty()) {
            postfix[j++] = outputStack.top();
            outputStack.pop();
        }

        // Reversing the collected output to get the correct prefix expression
        // for (int i = 0; i < j / 2; ++i) {
        //     DS temp = postfix[i];
        //     postfix[i] = postfix[j - 1 - i];
        //     postfix[j - 1 - i] = temp;
        // }

        // Displaying the prefix expression
        cout << "Prefix Expression: ";
        for (int i = 0; i < j; ++i) {
            cout << postfix[i] << " ";
        }
        cout << endl;

        delete[] reversedInfix;
    }

    DS* getfix() const {
        return postfix;
    }

private:
    bool isOperand(DS c) {
        return isalnum(c);
    }
};

#endif // CONVERT_EXPRESSION_H
