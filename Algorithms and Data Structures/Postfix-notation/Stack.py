class Stack:
    def __init__(self, size: int):
        self.size = size
        self.arr = size * [None]
        self.index = -1

    def isempty(self):
        if self.index == -1:
            return True
        else:
            return False

    def isfull(self):
        if self.index == self.size:
            return True
        else:
            return False

    def push(self, a):
        if not self.isfull():
            self.index += 1
            self.arr[self.index] = a

    def top(self):
        if not self.isempty():
            return self.arr[self.index]

    def pop(self):
        if not self.isempty():
            a = self.arr[self.index]
            self.index -= 1
            return a
