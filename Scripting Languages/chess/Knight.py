"""
Module containing the Knight class.
"""

import main
import Piece


class Knight(Piece.Piece):
    def __init__(self, color, position, image, rect):
        super().__init__(color, position, image, rect)

    def get_movement(self):
        """
        Function fills list of
        moves that could be potentially
        made with the knight.
        """
        self.movement = []

        x = main.LETTERS.index(self.position[0]) + 1
        y = int(self.position[1])

        if x - 2 > 0 and y + 1 < 9:
            n_s = main.LETTERS[x - 3] + str(y + 1)
            self.movement.append(n_s)

        if x - 2 > 0 and y - 1 > 0:
            n_s = main.LETTERS[x - 3] + str(y - 1)
            self.movement.append(n_s)

        if x + 2 < 9 and y + 1 < 9:
            n_s = main.LETTERS[x + 1] + str(y + 1)
            self.movement.append(n_s)

        if x + 2 < 9 and y - 1 > 0:
            n_s = main.LETTERS[x + 1] + str(y - 1)
            self.movement.append(n_s)

        if x - 1 > 0 and y - 2 > 0:
            n_s = main.LETTERS[x - 2] + str(y - 2)
            self.movement.append(n_s)

        if x - 1 > 0 and y + 2 < 9:
            n_s = main.LETTERS[x - 2] + str(y + 2)
            self.movement.append(n_s)

        if x + 1 < 9 and y - 2 > 0:
            n_s = main.LETTERS[x] + str(y - 2)
            self.movement.append(n_s)

        if x + 1 < 9 and y + 2 < 9:
            n_s = main.LETTERS[x] + str(y + 2)
            self.movement.append(n_s)

        # White and black control
        self.get_control()
