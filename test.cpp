 #include<iostream>
 #include"convert_expression.h"
 using namespace std;
 
    int main() {
    const char arr[] = {'(' , 'a' , '*' , 'b' ,')' , '+' , 'e' , '/' ,'f' , '^' , 'g'};  // ( a * b ) + e / f ^ g 
    int len =  sizeof(arr) / sizeof(arr[0]);

    convert_expression<char> C(arr, len);
    cout<<"infix to prefix "<<endl;
    C.infixToPostfix();
    cout<<endl;
    cout<<"infix to postfix"<<endl;
    C.infixToPrefix();

    return 0;
}



