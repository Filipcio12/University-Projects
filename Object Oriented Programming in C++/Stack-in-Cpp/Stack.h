#pragma once

#include <cstdlib>
#include <iostream>

class Stack {
    size_t top;
    size_t size;
    int* data;

    public:
        Stack();
        void push(int element);
        int pop();
        bool isEmpty();
        ~Stack();

    private:
        void incrementSize();
};