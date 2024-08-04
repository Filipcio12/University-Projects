"""
Module containing the King class.
"""

import main
import Piece


class King(Piece.Piece):
    def __init__(self, color, position, image, rect):
        super().__init__(color, position, image, rect)
        self.in_check = False

    def get_movement(self):
        """
        Function fills list of
        moves that could potentially
        be made with the king.
        """
        self.movement = []

        x = main.LETTERS.index(self.position[0]) + 1
        y = int(self.position[1])

        # Horizontal movement
        if x + 1 < 9:
            self.movement.append(main.LETTERS[x]
                                 + self.position[1])
        if x - 1 > 0:
            self.movement.append(main.LETTERS[x - 2]
                                 + self.position[1])

        # Vertical movement
        if y + 1 < 9:
            self.movement.append(self.position[0]
                                 + str(y + 1))
        if y - 1 > 0:
            self.movement.append(self.position[0]
                                 + str(y - 1))

        # Diagonal movement
        if x + 1 < 9 and y + 1 < 9:
            self.movement.append(main.LETTERS[x]
                                 + str(y + 1))
        if x - 1 > 0 and y + 1 < 9:
            self.movement.append(main.LETTERS[x - 2]
                                 + str(y + 1))
        if x + 1 < 9 and y - 1 > 0:
            self.movement.append(main.LETTERS[x]
                                 + str(y - 1))
        if x - 1 > 0 and y - 1 > 0:
            self.movement.append(main.LETTERS[x - 2]
                                 + str(y - 1))

        # White and black control
        self.get_control()

    def get_legal_moves(self):
        """
        Function fills list of moves
        that can be legally made with
        the king.
        """
        self.legal_moves = []

        # Determining legal moves
        for s in self.movement:
            if self.color == 'white' \
                    and s not in Piece.b_control:
                self.legal_moves.append(s)

            if self.color == 'black' \
                    and s not in Piece.w_control:
                self.legal_moves.append(s)
