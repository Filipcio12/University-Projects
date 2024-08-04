class Node:
    def __init__(self, value):
        self.value = value
        self.next = None


class LinkedList:
    def __init__(self):
        self.first = None

    def add(self, a):
        current = self.first
        if current is None:
            self.first = Node(a)
        else:
            while current.next is not None:
                current = current.next
            current.next = Node(a)

    def pop(self):
        if self.first is not None:
            current = self.first
            self.first = current.next
            return current.value
        else:
            return 'List is empty'
