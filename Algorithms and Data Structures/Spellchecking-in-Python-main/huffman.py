class Node:
    def __init__(self, val, char=None, left=None, right=None) -> None:
        self.val = val
        self.char = char
        self.left = left
        self.right = right


def huffman(string):
    # Finding char frequencies
    freq = {}
    for c in string:
        if c not in freq:
            freq[c] = 1
        else:
            freq[c] += 1

    # Creating a list of leaf nodes
    queue = []
    for char in freq:
        queue.append(Node(freq[char], char))

    queue = sorted(queue, key=lambda n: n.val)

    # Heap generation
    root = None
    while len(queue) > 1:
        element1 = queue.pop(0)
        element2 = queue.pop(0)
        sum = element1.val + element2.val
        root = Node(sum, None, element1, element2)
        queue.append(root)
        queue = sorted(queue, key=lambda n: n.val)

    # Codes generation
    codes = {}
    stack = [(root, "")]
    while stack:
        parent, code = stack.pop(0)
        if parent.char is not None:
            codes[parent.char] = code
        if parent.left is not None:
            stack.append((parent.left, code + '0'))
        if parent.right is not None:
            stack.append((parent.right, code + '1'))

    return codes


def convert_chars(string, codes):
    output = ""
    for c in string:
        output += codes[c]
    return output


def main():
    string = 'I love data structures'
    codes = huffman(string)
    print(f"codes:  {codes}")
    print(f"string: {convert_chars(string, codes)}")


if __name__ == "__main__":
    main()
