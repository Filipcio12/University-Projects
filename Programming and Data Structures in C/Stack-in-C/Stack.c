#include "Stack.h"
#include <stdio.h>

void init(Stack* s)
{
	s->top = 0;
	s->size = 0;
	s->data = NULL;
}

void destroy(Stack* s)
{
	free(s->data);
}

void incrementSize(Stack* s)
{
	size_t newSize = (s->size + 1) * 2;
	int* newData = (int*)realloc(s->data, newSize * sizeof(int));
	if (!newData) {
		free(s->data);
		fprintf(stderr, "Memory allocation error.\n");
		exit(1);
	}
	s->data = newData;
	s->size = newSize;
}

void push(Stack* s, int element)
{
	if (s->top >= s->size) {
		incrementSize(s);
	}
	s->data[s->top++] = element;
}

int pop(Stack* s)
{
	// assert(s->top > 0);
	if (!(s->top > 0)) {
		free(s->data);
		fprintf(stderr, "Can't pop from an empty stack.\n");
		exit(1);
	}
	return s->data[--s->top];
}

bool isEmpty(const Stack* s)
{
	return (s->top <= 0);
}
