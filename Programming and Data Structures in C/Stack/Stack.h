#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    size_t top;
    size_t size;
    int* data;
} Stack;

void init(Stack* s);
void destroy(Stack* s);
void push(Stack* s, int element);
int pop(Stack* s);
bool isEmpty(const Stack* s);
