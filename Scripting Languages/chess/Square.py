"""
This module contains the Square class
which objects represent every square
on the chess board.
"""

import main

# Global variable
selected_square = []


class Square:
    def __init__(self, color, position, rect):
        """
        Function initializes the Square object.
        :param color: either LIGHT or DARK
        :param position: chess coordinates for
                        example: 'a1' or 'h8'
        :param rect: rectangle of the square
        """
        self.original_color = color
        self.color = color
        self.position = position
        self.rect = rect

    def get_selected(self):
        """
        Function changes the color
        of the square to GREEN
        and adds it to the list
        of selected squares.
        """
        global selected_square
        selected_square.append(self)
        self.color = main.GREEN

    def get_unselected(self):
        """
        Function changes the color
        of the square back to its
        original and resets the
        list of selected squares.
        """
        global selected_square
        selected_square = []
        self.color = self.original_color
