"""
Module containing the Rook class.
"""

import main
import Piece


class Rook(Piece.Piece):
    def __init__(self, color, position, image, rect):
        super().__init__(color, position, image, rect)

    def get_movement(self):
        """
        Function fills list of
        moves that could be potentially
        made with the rook.
        """
        self.movement = []

        x = main.LETTERS.index(self.position[0]) + 1
        y = int(self.position[1])

        # Horizontal movement
        while x < 8:
            x += 1
            n_s = main.LETTERS[x - 1] + self.position[1]
            self.movement.append(n_s)
            if n_s in Piece.piece_pos:
                break

        x = main.LETTERS.index(self.position[0]) + 1

        while x > 1:
            x -= 1
            n_s = main.LETTERS[x - 1] + self.position[1]
            self.movement.append(n_s)
            if n_s in Piece.piece_pos:
                break

        # Vertical movement
        while y < 8:
            y += 1
            n_s = self.position[0] + str(y)
            self.movement.append(n_s)
            if n_s in Piece.piece_pos:
                break

        y = int(self.position[1])

        while y > 1:
            y -= 1
            n_s = self.position[0] + str(y)
            self.movement.append(n_s)
            if n_s in Piece.piece_pos:
                break

        # White and black control
        self.get_control()
