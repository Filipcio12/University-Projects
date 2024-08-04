"""
This module contains the Piece class
which is the parent class for the
different types of chess pieces.

It is a sort of template for the
more specific pieces.
"""

piece_pos = {}
w_control = []
b_control = []


class Piece:
    def __init__(self, color, position, image, rect):
        """
        Function initializes the Piece object.
        :param color: either 'white' or 'black'
        :param position: chess coordinates for
                        example: 'a1' or 'h8'
        :param image: image of the piece
        :param rect: rectangle of the image
        """

        self.color = color
        self.position = position
        self.image = image
        self.rect = rect
        self.selected = False
        self.movement = []
        self.legal_moves = []
        self.captures = []
        self.has_moved = False

    def get_control(self):
        """
        Function adds squares controlled
        by the piece to either
        w_control or b_control.
        """
        if self.color == 'white':
            for s in self.movement:
                if s not in w_control:
                    w_control.append(s)

        if self.color == 'black':
            for s in self.movement:
                if s not in b_control:
                    b_control.append(s)

    def get_legal_moves(self):
        """
        Function fills list of
        legal moves that can be made
        with the piece.
        """
        self.legal_moves = self.movement

    def get_captures(self):
        """
        Function fills list of
        captures that can be made
        with the piece.
        """
        self.captures = self.legal_moves
