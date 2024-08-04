"""
Module containing the Bishop class.
"""

import main
import Piece


class Bishop(Piece.Piece):
    def __init__(self, color, position, image, rect):
        super().__init__(color, position, image, rect)

    def get_movement(self):
        """
        Function fills list of
        moves that could be potentially
        made with the bishop.
        """
        self.movement = []

        x = main.LETTERS.index(self.position[0]) + 1
        y = int(self.position[1])

        # Diagonal movement
        while x < 8 and y < 8:
            x += 1
            y += 1
            n_s = main.LETTERS[x - 1] + str(y)
            self.movement.append(n_s)
            if n_s in Piece.piece_pos:
                break

        x = main.LETTERS.index(self.position[0]) + 1
        y = int(self.position[1])

        while x < 8 and y > 1:
            x += 1
            y -= 1
            n_s = main.LETTERS[x - 1] + str(y)
            self.movement.append(n_s)
            if n_s in Piece.piece_pos:
                break

        x = main.LETTERS.index(self.position[0]) + 1
        y = int(self.position[1])

        while x > 1 and y < 8:
            x -= 1
            y += 1
            n_s = main.LETTERS[x - 1] + str(y)
            self.movement.append(n_s)
            if n_s in Piece.piece_pos:
                break

        x = main.LETTERS.index(self.position[0]) + 1
        y = int(self.position[1])

        while x > 1 and y > 1:
            x -= 1
            y -= 1
            n_s = main.LETTERS[x - 1] + str(y)
            self.movement.append(n_s)
            if n_s in Piece.piece_pos:
                break

        # White and black control
        self.get_control()
