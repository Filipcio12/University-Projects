"""
Module containing the Pawn class.
"""

import main
import Piece


class Pawn(Piece.Piece):
    def __init__(self, color, position, image, rect):
        super().__init__(color, position, image, rect)
        self.has_jumped = False

    def get_captures(self):
        """
        Function fills list of
        captures that could be
        potentially made with the
        pawn.
        """
        self.captures = []

        x = main.LETTERS.index(self.position[0]) + 1
        y = int(self.position[1])

        if self.color == 'white' and y + 1 < 9:

            if x + 1 < 9:
                n_s = main.LETTERS[x] + str(y + 1)
                self.captures.append(n_s)

            if x - 1 > 0:
                n_s = main.LETTERS[x - 2] + str(y + 1)
                self.captures.append(n_s)

        if self.color == 'black' and y - 1 > 0:

            if x + 1 < 9:
                n_s = main.LETTERS[x] + str(y - 1)
                self.captures.append(n_s)

            if x - 1 > 0:
                n_s = main.LETTERS[x - 2] + str(y - 1)
                self.captures.append(n_s)

    def get_control(self):
        """
        Function adds the squares
        controlled by the pawn
        to either w_control or
        b_control.
        """
        if self.color == 'white':
            for s in self.captures:
                if s not in Piece.w_control:
                    Piece.w_control.append(s)

        if self.color == 'black':
            for s in self.captures:
                if s not in Piece.b_control:
                    Piece.b_control.append(s)

    def get_movement(self):
        """
        Function fills list of
        moves that could be potentially
        made with the pawn.
        :return:
        """
        self.get_captures()

        self.movement = []

        x = main.LETTERS.index(self.position[0]) + 1
        y = int(self.position[1])

        if self.color == 'white':

            if y + 1 < 9:
                n_s = main.LETTERS[x - 1] + str(y + 1)
                self.movement.append(n_s)

        if self.color == 'black':

            if y - 1 > 0:
                n_s = main.LETTERS[x - 1] + str(y - 1)
                self.movement.append(n_s)

        # White and black control
        self.get_control()
