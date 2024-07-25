#include <iostream>
#include<stack>
#include "Stack.h"

using namespace std;

template<class DS>
class convert_expression {
private:
    int n;
    DS *infix;
    DS *postfix;
    DS *prefix;
    stack<DS> S;

public:
    convert_expression(const DS* arr, int len, int stackSize = 100) : S(stackSize) {
        n = len;
        infix = new DS[n + 1];
        postfix = new DS[n + 1];
        prefix = new DS[n +1];
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
        if(infix[0] == '\0')throw outofbound();
        int j = 0;
        for (int i = 0; i < n; ++i) {
            DS token = infix[i];

            if (S(token)) {
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


//infix to prefix
    void infixToPrefix() {
        if (infix[0] == '\0')
            throw outofbound();

        S.clear();
        DS prefix[n]; // Array to store the prefix expression
        int j = 0; // Counter for prefix expression

        // Reverse the infix expression and convert to prefix
        for (int i = n - 1; i >= 0; --i) {
            DS token = infix[i];

            if (S(token)) {
                prefix[j++] = token; // Append operands directly to prefix expression
            } else if (token == ')') {
                S.push(token); // Push ')' to operator stack
            } else if (token == '(') {
                // Pop operators from operator stack until ')' is encountered
                while (!S.isEmpty() && S.top() != ')') {
                    prefix[j++] = S.top(); // Append operator to prefix expression
                    S.pop();
                }
                S.pop(); // Pop the ')' from the stack
            } else if (isOperator(token)) {
                // Pop operators from operator stack with higher or equal precedence
                while (!S.isEmpty() &&
                    ((isRightAssociative(token) && precedence(token) < precedence(S.top())) ||
                        (!isRightAssociative(token) && precedence(token) <= precedence(S.top())))) {
                    prefix[j++] = S.top(); // Append operator to prefix expression
                    S.pop();
                }
                S.push(token); // Push the current operator to operator stack
            }
        }

        // Pop remaining operators from operator stack to prefix array
        while (!S.isEmpty()) {
            prefix[j++] = S.top(); // Append operator to prefix expression
            S.pop();
        }

        // Manually reverse the prefix expression to get the correct order
        for (int i = 0; i < j / 2; ++i) {
            DS temp = prefix[i];
            prefix[i] = prefix[j - i - 1];
            prefix[j - i - 1] = temp;
        }

        // Displaying the prefix expression
        cout << "Prefix Expression: ";
        for (int i = 0; i < j; i++) {
            cout << prefix[i] << " ";
        }
        cout << endl;
    }

    private:
        bool S(DS c) {
            return isalnum(c);
        }
};

int main() {
    const char arr[] = {'(','a','+','b',')','*','(', 'c','+','d',')','/','e','^','f'};  //( a + b ) * (c + d) / e ^ f
    int len = sizeof(arr) / sizeof(arr[0]);

    convert_expression<char> C(arr, len);
    cout<<"infix to prefix "<<endl;
    C.infixToPostfix();
    cout<<endl;
    cout<<"infix to postfix"<<endl;
    C.infixToPrefix();

    return 0;
}
