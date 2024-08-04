#include "Stack.h"

Stack::Stack()
{
    top = 0;
    size = 0;
    data = NULL;
}

Stack::~Stack()
{
    free(data);
}

void Stack::incrementSize()
{
    size_t newSize = (size + 1) * 2;
    int* newData = (int*)realloc(data, newSize * sizeof(int));
    if (!newData) {
        free(data);
        abort();
    }
    data = newData;
    size = newSize;
}

void Stack::push(int element)
{
    if (top >= size) {
        incrementSize();
    }
    data[top++] = element;
}

int Stack::pop()
{
    if (top > 0) {
        return data[--top];
    }
    free(data);
    fprintf(stderr, "Can't pop from an empty stack.\n");
    abort();
}

bool Stack::isEmpty()
{
    if (top > 0) {
        return 0;
    }
    return 1;
}