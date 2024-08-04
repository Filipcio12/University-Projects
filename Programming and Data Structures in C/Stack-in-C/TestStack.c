#include "Stack.h"
#include <stdio.h>

int main()
{
	Stack stack;
	init(&stack);
	
	for (size_t i = 0; i < 1000; ++i) {
		push(&stack, i);
	}
	
	for (size_t i = 0; i < 1000; ++i) {
		printf("%d\n", pop(&stack));
	}
	
	if (isEmpty(&stack)) {
		printf("Stack is empty!");
	}
	
	//pop(&stack);
	
	destroy(&stack);
	return 0;
}
