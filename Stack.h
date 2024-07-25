#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "nomemory.h"
#include "outofbound.h"

using namespace std;

template<class DS>
class Stack {
public:
    int size;
    DS *arr;
    int head;

    Stack(int s) : size(s), head(-1) {
        arr = new DS[size];
    }

    ~Stack() {
        delete[] arr;
    }

    // Add elements
    Stack& push(const DS& v) {
        if (head == size - 1) throw nomemory(size);

        arr[++head] = v;
        //cout << v << " successfully inserted" << endl;
        return *this;
    }

    DS pop() {
        if (head == -1) throw outofbound();
        return arr[head--];
    }

    DS top() {
        if (head == -1) throw outofbound();
        return arr[head];
    }
    DS clear(){
        while(head == 0){
            --head;
        }
    }

    bool isEmpty() {
        return head == -1;
    }
};

#endif // STACK_H
