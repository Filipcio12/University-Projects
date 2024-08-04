#include "Stack.h"

int main() {
    Stack stack;
    stack.push(5);
    stack.push(2);
    std::cout << "Pop: " << stack.pop() << "\n";
    std::cout << "Pop: " << stack.pop() << "\n";
    std::cout << "Pop: " << stack.pop() << "\n";
    return 0;
}