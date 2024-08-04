from math import sqrt

keyboard = {'q': (0, 0), 'w': (1, 0), 'e': (2, 0), 'r': (3, 0), 't': (4, 0),
            'y': (5, 0), 'u': (6, 0), 'i': (7, 0), 'o': (8, 0), 'p': (9, 0),
            'a': (0, 1), 's': (1, 1), 'd': (2, 1), 'f': (3, 1), 'g': (4, 1),
            'h': (5, 1), 'j': (6, 1), 'k': (7, 1), 'l': (8, 1), 'z': (0, 2),
            'x': (1, 2), 'c': (2, 2), 'v': (3, 2), 'b': (4, 2), 'n': (5, 2),
            'm': (6, 2)}


def key_distance(key1, key2):
    x1, y1 = keyboard[key1]
    x2, y2 = keyboard[key2]
    distance = sqrt((x1 - x2)**2 + (y1 - y2)**2)
    return distance


def indel(word1, word2):
    """Indel is a variation of levensthein that
    only allows insertions and deletions but no
    replacements"""
    # Table creation
    a, b = len(word1) + 1, len(word2) + 1
    table = [[0 for _ in range(a)]
             for _ in range(b)]
    for x in range(1, a):
        table[0][x] = x
    for y in range(1, b):
        table[y][0] = y

    def C(c1, c2):
        if c1 == c2:
            return 0
        return float('inf')

    # Filling the table
    for i in range(1, b):
        for j in range(1, a):
            table[i][j] = min(table[i - 1][j] + 1, table[i][j - 1] + 1,
                              table[i - 1][j - 1] + C(word1[j - 1], word2[i - 1]))
    return table[b - 1][a - 1]


def hamming(word1, word2):
    a, b = len(word1), len(word2)
    if a > b:
        for _ in range(a - b):
            word2 += " "
    elif b > a:
        for _ in range(b - a):
            word1 += " "

    distance = 0
    for i in range(len(word1)):
        if word1[i] != word2[i]:
            distance += 1
    return distance


def hamming_mod(word1, word2):
    a, b = len(word1), len(word2)
    if a > b:
        for _ in range(a - b):
            word2 += " "
    elif b > a:
        for _ in range(b - a):
            word1 += " "

    distance = 0
    for i in range(len(word1)):
        if word1[i] == word2[i]:
            continue
        elif word1[i] not in keyboard or \
                word2[i] not in keyboard or \
                key_distance(word1[i], word2[i]) >= 2:
            distance += 1
        else:
            distance += 0.5
    return distance


def levensthein(word1, word2):
    # Table creation
    a, b = len(word1) + 1, len(word2) + 1
    table = [[0 for _ in range(a)]
             for _ in range(b)]
    for x in range(1, a):
        table[0][x] = x
    for y in range(1, b):
        table[y][0] = y

    def C(c1, c2):
        if c1 == c2:
            return 0
        return 1

    # Filling the table
    for i in range(1, b):
        for j in range(1, a):
            table[i][j] = min(table[i - 1][j] + 1, table[i][j - 1] + 1,
                              table[i - 1][j - 1] + C(word1[j - 1], word2[i - 1]))
    return table[b - 1][a - 1]


def levensthein_mod(word1, word2):
    # Table creation
    a, b = len(word1) + 1, len(word2) + 1
    table = [[0 for _ in range(a)]
             for _ in range(b)]
    for x in range(1, a):
        table[0][x] = x
    for y in range(1, b):
        table[y][0] = y

    def C(c1, c2):
        if c1 == c2:
            return 0
        elif key_distance(c1, c2) < 2:
            return 0.5
        return 1

    # Filling the table
    for i in range(1, b):
        for j in range(1, a):
            table[i][j] = min(table[i - 1][j] + 1, table[i][j - 1] + 1,
                              table[i - 1][j - 1] + C(word1[j - 1], word2[i - 1]))
    return table[b - 1][a - 1]
