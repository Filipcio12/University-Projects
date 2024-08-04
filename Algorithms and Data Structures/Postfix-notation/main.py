import Stack
from Stack import Stack
from LinkedList import LinkedList

# Dictionary for order of operations
ORDER = {'(': 3, ')': 3,
         '+': 2, '-': 2,
         '*': 1, '/': 1}


def is_float(string):
    try:
        float(string)
        return True
    except ValueError:
        return False


def in_to_post(infix):
    output = ''

    stack = Stack(len(infix))
    index = 0

    while True:
        if index >= len(infix):
            break

        token = ''
        while index < len(infix) \
                and infix[index] != ' ':
            token = token + infix[index]
            index += 1
        index += 1

        if is_float(token):
            output = output + token + ' '

        elif token in ORDER.keys():
            if token == '(':
                stack.push('(')

            elif token == ')':
                while not stack.isempty() \
                        and stack.top() != '(':
                    output = output + stack.pop() + ' '
                stack.pop()

            elif stack.isempty() \
                    or ORDER[token] > ORDER[stack.top()]:
                stack.push(token)

            else:
                while not stack.isempty() \
                        and ORDER[token] <= ORDER[stack.top()] \
                        and stack.top() != '(':
                    output = output + stack.pop() + ' '
                stack.push(token)
        else:
            return 'Incorrect expression'

    while not stack.isempty():
        output = output + stack.pop() + ' '

    return output


def postcalc(postfix):
    stack = Stack(len(postfix))
    index = 0

    while True:
        if index >= len(postfix):
            break

        token = ''
        while index < len(postfix) \
                and postfix[index] != ' ':
            token = token + postfix[index]
            index += 1
        index += 1

        if is_float(token):
            stack.push(token)

        elif token in ['+', '-', '*', '/']:
            b = float(stack.pop())
            a = float(stack.pop())

            if token == "+":
                stack.push(a + b)
            elif token == '-':
                stack.push(a - b)
            elif token == '*':
                stack.push(a * b)
            elif token == '/':
                stack.push(a / b)

        else:
            return 'Incorrect expression'

    if not stack.isempty():
        output = stack.pop()
    else:
        return 'Incorrect expression'

    if stack.isempty():
        return output
    else:
        return 'Incorrect expression'


def is_palindrome(expression):
    stack = Stack(len(expression))
    linklist = LinkedList()

    for x in expression:
        stack.push(x)
        linklist.add(x)

    while not stack.isempty():
        a = stack.pop()
        b = linklist.pop()

        if a != b:
            return False

    return True


def main1():
    infix = '( 3 * 6 + 2 ) + ( 14 / 3 + 4 )'
    postfix = in_to_post(infix)
    result = postcalc(postfix)
    print(result)


def main2():
    word = '3120213'
    print(is_palindrome(word))


if __name__ == "__main__":
    main2()
