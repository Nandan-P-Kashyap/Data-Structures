#include <iostream>
#include <math.h>
#include "Stack.h"
#include "convert_expression.h"

using namespace std;

template <class DS>
class expression_evaluation {
private:
    int n;
    DS* arr;
    Stack<int> st1;

public:
    expression_evaluation(const DS* a, int len) : st1(len) { // Accept const DS*
        n = len;
        arr = new DS[n + 1];
        for (int i = 0; i < n; i++) {
            arr[i] = a[i];
        }
        arr[n] = '\0';
    }

    ~expression_evaluation() {
        delete[] arr;
    }

    void post_eval() {
        convert_expression<DS> postfixConverter(arr, n);
        postfixConverter.infixToPostfix();
        st1.clear();

        DS* post = postfixConverter.getfix();
        for (int i = 0; i < n; i++) {
            if (post[i] >= '0' && post[i] <= '9') {
                st1.push(post[i] - '0');
            } else if (isOperator(post[i])) {
                int op2 = st1.top();
                st1.pop();
                int op1 = st1.top();
                st1.pop();

                switch (post[i]) {
                    case '+':
                        st1.push(op1 + op2);
                        break;
                    case '-':
                        st1.push(op1 - op2);
                        break;
                    case '*':
                        st1.push(op1 * op2);
                        break;
                    case '/':
                        st1.push(op1 / op2);
                        break;
                    case '^':
                        st1.push(pow(op1, op2) + 1);
                        break;
                }
            }
        }

        cout << "Final answer is: " << st1.top() << endl;
    }

    void prefix_eval() {
    convert_expression<DS> prefixConverter(arr, n);
    prefixConverter.infixToPrefix();
    DS* pre = prefixConverter.getfix(); 
    //cout << "value successfully passed" << endl;
    
    // DS  pre[] = { '/' , '+' , '2' , '5','7'};
    // n = 5;
    st1.clear();
    //cout<<"value of stack header is "<<st1.head<<endl;

    for (int i = n - 1; i >= 0; i--) {
            if (pre[i] >= '0' && pre[i] <= '9') {
                st1.push(pre[i] - '0');
            } else if (isOperator(pre[i])) {
                int op1 = st1.top();
                st1.pop();
                int op2 = st1.top();
                st1.pop();

                switch (pre[i]) {
                    case '+':
                        st1.push(op1 + op2);
                        break;
                    case '-':
                        st1.push(op1 - op2);
                        break;
                    case '*':
                        st1.push(op1 * op2);
                        break;
                    case '/':
                        st1.push(op1 / op2);
                        break;
                    case '^':
                        st1.push(pow(op1, op2) + 1);
                        break;
                }
            }

            // cout<<"st1-top "<<i<<" is "<<st1.top()<<endl;
        }

    cout << "Final answer is: " << st1.top() << endl;
}


private:
    bool isOperator(DS c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }
};

int main() {
    const char a[] = {'2' ,'+' , '1' , '*' ,'5' , '^' ,'2'}; //2 + 1 * 5 ^ 2
    int len = sizeof(a) / sizeof(a[0]);
    expression_evaluation<char> C(a, len);
    C.prefix_eval();
    C.post_eval();

    return 0;
}
