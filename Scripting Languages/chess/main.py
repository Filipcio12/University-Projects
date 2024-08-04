"""
Final project for Scripting Languages 2023
by Filip Fajfer

It's a chess game for two players.
"""

import pygame
import sys

import Bishop
import Knight
import Pawn
import Piece
import Rook
import Square
import King
import Queen

# Global constants
WINDOW_WIDTH, WINDOW_HEIGHT = 504, 504
WINDOW = (WINDOW_WIDTH, WINDOW_HEIGHT)

N = 8
SQUARE_WIDTH = WINDOW_WIDTH / N
SQUARE_HEIGHT = WINDOW_HEIGHT / N
DIMENSIONS = (SQUARE_WIDTH, SQUARE_HEIGHT)

PIECE_WIDTH = SQUARE_WIDTH * 0.8
PIECE_HEIGHT = SQUARE_HEIGHT * 0.8

LIGHT = pygame.Color('white')  # 255, 233, 197
DARK = pygame.Color('gray')  # 189, 154, 122
GREEN = pygame.Color('green')
RED = pygame.Color('red')

LETTERS = ('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h')

screen = pygame.display.set_mode(WINDOW)


def start_menu():
    """
    Creates a start menu for the game.
    Click 'PLAY' to start the game.
    """
    screen = pygame.display.set_mode(WINDOW)

    # Chess message
    chess_font = pygame.font.Font('freesansbold.ttf', WINDOW_HEIGHT // 5)
    chess = chess_font.render('CHESS', True, LIGHT)
    chess_box = chess.get_rect()
    chess_box.midtop = screen.get_rect().midtop
    chess_box.top += WINDOW_HEIGHT // 10

    # Title message
    title_font = pygame.font.Font('freesansbold.ttf', WINDOW_HEIGHT // 10)
    title = title_font.render("SL Final Project", True, LIGHT)
    title_box = title.get_rect()
    title_box.midtop = chess_box.midbottom

    # Author message
    author_font = pygame.font.Font('freesansbold.ttf', WINDOW_HEIGHT // 20)
    author = author_font.render("by Filip Fajfer", True, LIGHT)
    author_box = author.get_rect()
    author_box.midtop = title_box.midtop
    author_box.top += WINDOW_HEIGHT // 10

    # Play message
    play_font = pygame.font.Font('freesansbold.ttf', WINDOW_HEIGHT // 10)
    play = play_font.render("PLAY", True, LIGHT)
    play_box = play.get_rect()
    play_box.midbottom = screen.get_rect().midbottom
    play_box.top -= WINDOW_HEIGHT // 5

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = pygame.mouse.get_pos()
                if play_box.collidepoint(mouse_pos):
                    return

        screen.fill(DARK)
        screen.blit(title, title_box)
        screen.blit(author, author_box)
        screen.blit(chess, chess_box)
        screen.blit(play, play_box)
        pygame.display.flip()


def end_screen(message):
    """
    Displays an ending message
    to the player.

    message -> string containing
    the message to be displayed

    Click the 'x' in the right top
    corner to close the game.
    """
    global screen
    myfont = pygame.font.Font('freesansbold.ttf',
                              WINDOW_HEIGHT // 10)
    msg = myfont.render(message, True, RED)
    msg_box = msg.get_rect()
    msg_box.center = screen.get_rect().center

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

        screen.blit(msg, msg_box)
        pygame.display.flip()


def pawn_promotion(color, left, top):
    """
    The function displays the screen
    for promotion of pawns.

    color -> color of the promoting
    pawn

    left -> coordinate of the left side
    of the square on which the pawn is
    promoting

    top -> coordinate of the top side
    of the square on which the pawn is
    promoting

    The function returns the index
    of the square in the list of squares
    on which is the piece the pawn was
    chosen to promote to.

    queen -> 0
    knight -> 1
    rook -> 2
    bishop -> 3
    """
    screen = pygame.display.set_mode(WINDOW)
    squares = []

    pieces_sources_white = ['white_queen.png', 'white_knight.png',
                            'white_rook.png', 'white_bishop.png']

    pieces_sources_black = ['black_queen.png', 'black_knight.png',
                            'black_rook.png', 'black_bishop.png']

    pieces = []

    if color == 'white':
        for x in range(4):
            squares.append(pygame.Rect(left, top + x * SQUARE_HEIGHT,
                                       SQUARE_WIDTH, SQUARE_HEIGHT))

        for i in range(4):
            image = pygame.image.load(pieces_sources_white[i])
            image = pygame.transform.scale(image, (PIECE_WIDTH, PIECE_HEIGHT))
            piece = image.get_rect()
            piece.center = squares[i].center
            pieces.append((image, piece))

    if color == 'black':
        for x in range(4):
            squares.append(pygame.Rect(left, top - x * SQUARE_HEIGHT,
                                       SQUARE_HEIGHT, SQUARE_WIDTH))

        for i in range(4):
            image = pygame.image.load(pieces_sources_black[i])
            image = pygame.transform.scale(image, (PIECE_WIDTH, PIECE_HEIGHT))
            piece = image.get_rect()
            piece.center = squares[i].center
            pieces.append((image, piece))

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = pygame.mouse.get_pos()
                for i in range(4):
                    if squares[i].collidepoint(mouse_pos):
                        return i

        if color == 'white':
            for s in squares:
                pygame.draw.rect(screen, DARK, s)

        if color == 'black':
            for s in squares:
                pygame.draw.rect(screen, LIGHT, s)

        for i in range(4):
            screen.blit(pieces[i][0], pieces[i][1])

        pygame.display.flip()


def main():
    """
    The main function of the chess game.
    Contains the code for most of the
    features of the game.
    """
    # Initialization
    pygame.init()

    start_menu()

    # Creating squares
    origin = [0, 0]
    squares = {}

    for i in range(N):
        origin[1] = SQUARE_HEIGHT * i

        for j in range(N):
            origin[0] = SQUARE_WIDTH * j
            rect = pygame.Rect(origin, DIMENSIONS)
            position = LETTERS[j] + str(8 - i)

            if (i % 2 == 0 and j % 2 == 0) or \
                    (i % 2 == 1 and j % 2 == 1):
                squares[position] = Square.Square(LIGHT, position, rect)
            else:
                squares[position] = Square.Square(DARK, position, rect)

    # Creating pieces

    pieces = []

    # White king
    image = pygame.image.load('white_king.png')
    image = pygame.transform.scale(image, (PIECE_WIDTH, PIECE_HEIGHT))
    white_king = King.King('white', 'e1', image, image.get_rect())
    pieces.append(white_king)

    # White queen
    image = pygame.image.load('white_queen.png')
    image = pygame.transform.scale(image, (PIECE_WIDTH, PIECE_HEIGHT))
    white_queen = Queen.Queen('white', 'd1', image, image.get_rect())
    pieces.append(white_queen)

    # Black king
    image = pygame.image.load('black_king.png')
    image = pygame.transform.scale(image, (PIECE_WIDTH, PIECE_HEIGHT))
    black_king = King.King('black', 'e8', image, image.get_rect())
    pieces.append(black_king)

    # Black queen
    image = pygame.image.load('black_queen.png')
    image = pygame.transform.scale(image, (PIECE_WIDTH, PIECE_HEIGHT))
    black_queen = Queen.Queen('black', 'd8', image, image.get_rect())
    pieces.append(black_queen)

    # White rooks
    image = pygame.image.load('white_rook.png')
    image = pygame.transform.scale(image, (PIECE_WIDTH, PIECE_HEIGHT))
    white_rook1 = Rook.Rook('white', 'a1', image, image.get_rect())
    pieces.append(white_rook1)
    white_rook2 = Rook.Rook('white', 'h1', image, image.get_rect())
    pieces.append(white_rook2)

    # Black rooks
    image = pygame.image.load('black_rook.png')
    image = pygame.transform.scale(image, (PIECE_WIDTH, PIECE_HEIGHT))
    black_rook1 = Rook.Rook('black', 'a8', image, image.get_rect())
    pieces.append(black_rook1)
    black_rook2 = Rook.Rook('black', 'h8', image, image.get_rect())
    pieces.append(black_rook2)

    # White bishops
    image = pygame.image.load('white_bishop.png')
    image = pygame.transform.scale(image, (PIECE_WIDTH, PIECE_HEIGHT))
    white_bishop1 = Bishop.Bishop('white', 'c1', image, image.get_rect())
    pieces.append(white_bishop1)
    white_bishop2 = Bishop.Bishop('white', 'f1', image, image.get_rect())
    pieces.append(white_bishop2)

    # Black bishops
    image = pygame.image.load('black_bishop.png')
    image = pygame.transform.scale(image, (PIECE_WIDTH, PIECE_HEIGHT))
    black_bishop1 = Bishop.Bishop('black', 'c8', image, image.get_rect())
    pieces.append(black_bishop1)
    black_bishop2 = Bishop.Bishop('black', 'f8', image, image.get_rect())
    pieces.append(black_bishop2)

    # White knights
    image = pygame.image.load('white_knight.png')
    image = pygame.transform.scale(image, (PIECE_WIDTH, PIECE_HEIGHT))
    white_knight1 = Knight.Knight('white', 'b1', image, image.get_rect())
    pieces.append(white_knight1)
    white_knight2 = Knight.Knight('white', 'g1', image, image.get_rect())
    pieces.append(white_knight2)

    # Black knights
    image = pygame.image.load('black_knight.png')
    image = pygame.transform.scale(image, (PIECE_WIDTH, PIECE_HEIGHT))
    black_knight1 = Knight.Knight('black', 'b8', image, image.get_rect())
    pieces.append(black_knight1)
    black_knight2 = Knight.Knight('black', 'g8', image, image.get_rect())
    pieces.append(black_knight2)

    # White pawns
    image = pygame.image.load('white_pawn.png')
    image = pygame.transform.scale(image, (PIECE_WIDTH * 0.8,
                                   PIECE_HEIGHT * 0.8))

    white_pawns = []
    for x in range(8):
        white_pawns.append(Pawn.Pawn('white', LETTERS[x] + '2',
                                     image, image.get_rect()))
        pieces.append(white_pawns[x])

    # Black pawns
    image = pygame.image.load('black_pawn.png')
    image = pygame.transform.scale(image, (PIECE_WIDTH * 0.8,
                                   PIECE_HEIGHT * 0.8))

    black_pawns = []
    for x in range(8):
        black_pawns.append(Pawn.Pawn('black', LETTERS[x] + '7',
                                     image, image.get_rect()))
        pieces.append(black_pawns[x])

    # Adding turn logic
    colors = ['white', 'black']
    turns = 1

    for p in pieces:
        Piece.piece_pos[p.position] = p

    list_of_positions = [Piece.piece_pos]
    new_position = True

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

            if event.type == pygame.MOUSEBUTTONDOWN:
                mouse_pos = pygame.mouse.get_pos()

                if len(Square.selected_square) > 0:
                    for p in Piece.piece_pos.values():
                        if Square.selected_square[0].position == p.position:
                            p.selected = True

                        for position in squares:
                            if squares[position].rect.collidepoint(mouse_pos):

                                # White castling
                                if white_king.selected and \
                                        not white_king.has_moved and \
                                        not white_king.in_check:

                                    # King-side castling
                                    if 'f1' not in Piece.piece_pos and \
                                            'g1' not in Piece.piece_pos and \
                                            'f1' not in Piece.b_control and \
                                            'g1' not in Piece.b_control:

                                        if (position == 'g1' or
                                            position == 'h1') and \
                                                not white_rook2.has_moved:
                                            white_king.position = 'g1'
                                            white_rook2.position = 'f1'
                                            white_king.has_moved = True
                                            white_rook2.has_moved = True
                                            turns += 1
                                            new_position = True

                                            for pawn in white_pawns:
                                                pawn.has_jumped = False

                                            for pawn in black_pawns:
                                                pawn.has_jumped = False

                                    # Queen-side castling
                                    if 'b1' not in Piece.piece_pos and \
                                            'c1' not in Piece.piece_pos and \
                                            'd1' not in Piece.piece_pos and \
                                            'b1' not in Piece.b_control and \
                                            'c1' not in Piece.b_control and \
                                            'd1' not in Piece.b_control:

                                        if (position == 'c1' or
                                            position == 'a1') and \
                                                not white_rook1.has_moved:
                                            white_king.position = 'c1'
                                            white_rook1.position = 'd1'
                                            white_king.has_moved = True
                                            white_rook1.has_moved = True
                                            turns += 1
                                            new_position = True

                                            for pawn in white_pawns:
                                                pawn.has_jumped = False

                                            for pawn in black_pawns:
                                                pawn.has_jumped = False

                                # Black castling
                                if black_king.selected and \
                                        not black_king.has_moved and \
                                        not black_king.in_check:

                                    # King-side castling
                                    if 'f8' not in Piece.piece_pos and \
                                            'g8' not in Piece.piece_pos and \
                                            'f8' not in Piece.w_control and \
                                            'g8' not in Piece.w_control:

                                        if (position == 'g8' or
                                            position == 'h8') and \
                                                not black_rook2.has_moved:
                                            black_king.position = 'g8'
                                            black_rook2.position = 'f8'
                                            black_king.has_moved = True
                                            black_rook2.has_moved = True
                                            turns += 1
                                            new_position = True

                                            for pawn in white_pawns:
                                                pawn.has_jumped = False

                                            for pawn in black_pawns:
                                                pawn.has_jumped = False

                                    # Queen-side castling
                                    if 'b8' not in Piece.piece_pos and \
                                            'c8' not in Piece.piece_pos and \
                                            'd8' not in Piece.piece_pos and \
                                            'b8' not in Piece.w_control and \
                                            'c8' not in Piece.w_control and \
                                            'd8' not in Piece.w_control:

                                        if (position == 'c8' or
                                            position == 'a8') and \
                                                not black_rook1.has_moved:
                                            black_king.position = 'c8'
                                            black_rook1.position = 'd8'
                                            black_king.has_moved = True
                                            black_rook1.has_moved = True
                                            turns += 1
                                            new_position = True

                                            for pawn in white_pawns:
                                                pawn.has_jumped = False

                                            for pawn in black_pawns:
                                                pawn.has_jumped = False

                                # Pawn jump
                                if p.selected and \
                                        p in white_pawns and \
                                        p.position[1] == '2' and \
                                        position == p.position[0] + '4' and \
                                        (p.position[0]
                                         + '3') not in Piece.piece_pos and \
                                        (p.position[0]
                                         + '4') not in Piece.piece_pos:
                                    p.position = position
                                    p.has_moved = True
                                    p.has_jumped = True
                                    turns += 1
                                    new_position = True

                                    for pawn in black_pawns:
                                        pawn.has_jumped = False

                                if p.selected and \
                                        p in black_pawns and \
                                        p.position[1] == '7' and \
                                        position == p.position[0] + '5' and \
                                        (p.position[0]
                                         + '6') not in Piece.piece_pos and \
                                        (p.position[0]
                                         + '5') not in Piece.piece_pos:
                                    p.position = position
                                    p.has_moved = True
                                    p.has_jumped = True
                                    turns += 1
                                    new_position = True

                                    for pawn in white_pawns:
                                        pawn.has_jumped = False

                                # En passant for white pawns
                                if p.selected and p in white_pawns:
                                    x = LETTERS.index(p.position[0]) + 1
                                    y = int(p.position[1])

                                    if x + 1 < 9:
                                        n_s = LETTERS[x] + str(y)
                                        if n_s in Piece.piece_pos and \
                                                (Piece.piece_pos[n_s]
                                                 in black_pawns) and \
                                                Piece.piece_pos[n_s].has_jumped:
                                            if position == (LETTERS[x]
                                                            + str(y + 1)):
                                                p.position = (LETTERS[x]
                                                              + str(y + 1))
                                                f = Piece.piece_pos[n_s]
                                                pieces.remove(f)
                                                p.has_moved = True
                                                turns += 1
                                                new_position = True

                                                for pawn in white_pawns:
                                                    pawn.has_jumped = False

                                                for pawn in black_pawns:
                                                    pawn.has_jumped = False

                                    if x - 1 > 0:
                                        n_s = LETTERS[x - 2] + str(y)
                                        if n_s in Piece.piece_pos and \
                                                (Piece.piece_pos[n_s]
                                                 in black_pawns) and \
                                                Piece.piece_pos[n_s].has_jumped:
                                            if position == (LETTERS[x - 2]
                                                            + str(y + 1)):
                                                p.position = (LETTERS[x - 2]
                                                              + str(y + 1))
                                                f = Piece.piece_pos[n_s]
                                                pieces.remove(f)
                                                p.has_moved = True
                                                turns += 1
                                                new_position = True

                                                for pawn in white_pawns:
                                                    pawn.has_jumped = False

                                                for pawn in black_pawns:
                                                    pawn.has_jumped = False

                                # En passant for black pawns
                                if p.selected and p in black_pawns:
                                    x = LETTERS.index(p.position[0]) + 1
                                    y = int(p.position[1])

                                    if x + 1 < 9:
                                        n_s = LETTERS[x] + str(y)
                                        if n_s in Piece.piece_pos and \
                                                (Piece.piece_pos[n_s]
                                                 in white_pawns) and \
                                                Piece.piece_pos[n_s].has_jumped:
                                            if position == (LETTERS[x]
                                                            + str(y - 1)):
                                                p.position = (LETTERS[x]
                                                              + str(y - 1))
                                                f = Piece.piece_pos[n_s]
                                                pieces.remove(f)
                                                p.has_moved = True
                                                turns += 1
                                                new_position = True

                                                for pawn in white_pawns:
                                                    pawn.has_jumped = False

                                                for pawn in black_pawns:
                                                    pawn.has_jumped = False

                                    if x - 1 > 0:
                                        n_s = LETTERS[x - 2] + str(y)
                                        if n_s in Piece.piece_pos and \
                                                (Piece.piece_pos[n_s]
                                                 in white_pawns) and \
                                                Piece.piece_pos[n_s].has_jumped:
                                            if position == (LETTERS[x - 2]
                                                            + str(y - 1)):
                                                p.position = (LETTERS[x - 2]
                                                              + str(y - 1))
                                                f = Piece.piece_pos[n_s]
                                                pieces.remove(f)
                                                p.has_moved = True
                                                turns += 1
                                                new_position = True

                                                for pawn in white_pawns:
                                                    pawn.has_jumped = False

                                                for pawn in black_pawns:
                                                    pawn.has_jumped = False

                                # Simple movement
                                if p.selected and position in p.legal_moves \
                                        and position not in Piece.piece_pos:
                                    p.position = position
                                    p.has_moved = True
                                    turns += 1
                                    new_position = True

                                    for pawn in white_pawns:
                                        pawn.has_jumped = False

                                    for pawn in black_pawns:
                                        pawn.has_jumped = False

                                # Capturing
                                if p.selected and position in p.captures \
                                        and position in Piece.piece_pos \
                                        and (Piece.piece_pos[position].color
                                             != p.color):
                                    pieces.remove(Piece.piece_pos[position])
                                    p.position = position
                                    p.has_moved = True
                                    turns += 1
                                    new_position = True

                                    for pawn in white_pawns:
                                        pawn.has_jumped = False

                                    for pawn in black_pawns:
                                        pawn.has_jumped = False

                        p.selected = False

                    Square.selected_square[0].get_unselected()

                    if white_king.in_check:
                        squares[white_king.position].color = RED

                    if black_king.in_check:
                        squares[black_king.position].color = RED
                else:
                    for position in squares:
                        if squares[position].rect.collidepoint(mouse_pos) \
                                and position in Piece.piece_pos \
                                and (Piece.piece_pos[position].color
                                     == colors[(turns - 1) % 2]):
                            squares[position].get_selected()

        if new_position:
            # Pawn promotion
            for p in pieces:
                if p in white_pawns and \
                        p.position[1] == '8':
                    white_pawns.remove(p)
                    which_piece = pawn_promotion('white',
                                                 squares[p.position].rect.left,
                                                 squares[p.position].rect.top)
                    if which_piece == 0:
                        image = pygame.image.load('white_queen.png')
                        image = pygame.transform.scale(image, (PIECE_WIDTH,
                                                       PIECE_HEIGHT))
                        image_box = image.get_rect()
                        pieces[pieces.index(p)] = Queen.Queen('white',
                                                              p.position,
                                                              image,
                                                              image_box)
                    if which_piece == 1:
                        image = pygame.image.load('white_knight.png')
                        image = pygame.transform.scale(image, (PIECE_WIDTH,
                                                       PIECE_HEIGHT))
                        image_box = image.get_rect()
                        pieces[pieces.index(p)] = Knight.Knight('white',
                                                                p.position,
                                                                image,
                                                                image_box)
                    if which_piece == 2:
                        image = pygame.image.load('white_rook.png')
                        image = pygame.transform.scale(image, (PIECE_WIDTH,
                                                       PIECE_HEIGHT))
                        image_box = image.get_rect()
                        pieces[pieces.index(p)] = Rook.Rook('white',
                                                            p.position,
                                                            image,
                                                            image_box)
                    if which_piece == 3:
                        image = pygame.image.load('white_bishop.png')
                        image = pygame.transform.scale(image, (PIECE_WIDTH,
                                                       PIECE_HEIGHT))
                        image_box = image.get_rect()
                        pieces[pieces.index(p)] = Bishop.Bishop('white',
                                                                p.position,
                                                                image,
                                                                image_box)

                if p in black_pawns and \
                        p.position[1] == '1':
                    black_pawns.remove(p)
                    which_piece = pawn_promotion('black',
                                                 squares[p.position].rect.left,
                                                 squares[p.position].rect.top)
                    if which_piece == 0:
                        image = pygame.image.load('black_queen.png')
                        image = pygame.transform.scale(image, (PIECE_WIDTH,
                                                       PIECE_HEIGHT))
                        image_box = image.get_rect()
                        pieces[pieces.index(p)] = Queen.Queen('black',
                                                              p.position,
                                                              image,
                                                              image_box)
                    if which_piece == 1:
                        image = pygame.image.load('black_knight.png')
                        image = pygame.transform.scale(image, (PIECE_WIDTH,
                                                       PIECE_HEIGHT))
                        image_box = image.get_rect()
                        pieces[pieces.index(p)] = Knight.Knight('black',
                                                                p.position,
                                                                image,
                                                                image_box)
                    if which_piece == 2:
                        image = pygame.image.load('black_rook.png')
                        image = pygame.transform.scale(image, (PIECE_WIDTH,
                                                       PIECE_HEIGHT))
                        image_box = image.get_rect()
                        pieces[pieces.index(p)] = Rook.Rook('black',
                                                            p.position,
                                                            image,
                                                            image_box)
                    if which_piece == 3:
                        image = pygame.image.load('black_bishop.png')
                        image = pygame.transform.scale(image, (PIECE_WIDTH,
                                                       PIECE_HEIGHT))
                        image_box = image.get_rect()
                        pieces[pieces.index(p)] = Bishop.Bishop('black',
                                                                p.position,
                                                                image,
                                                                image_box)

            # Creating a dict of piece positions
            Piece.piece_pos = {}
            for p in pieces:
                Piece.piece_pos[p.position] = p

            Piece.w_control = []
            Piece.b_control = []

            for p in pieces:
                p.get_movement()

            for p in pieces:
                p.get_legal_moves()

            for p in pieces:
                p.get_captures()

            # List of positions
            list_of_positions.append(Piece.piece_pos)

            # Checks
            if white_king.position in Piece.b_control:
                white_king.in_check = True
                squares[white_king.position].color = RED
            else:
                white_king.in_check = False
                squares[white_king.position].color \
                    = squares[white_king.position].original_color

            if black_king.position in Piece.w_control:
                black_king.in_check = True
                squares[black_king.position].color = RED
            else:
                black_king.in_check = False
                squares[black_king.position].color \
                    = squares[black_king.position].original_color

            if white_king.in_check and colors[(turns - 1) % 2] == 'black':
                Piece.piece_pos = list_of_positions[turns - 1]
                list_of_positions.pop()
                pieces = []
                for pos, p in Piece.piece_pos.items():
                    p.position = pos
                    pieces.append(p)
                turns -= 1

                for s in squares.values():
                    s.get_unselected()

                squares[white_king.position].color = RED
                white_king.in_check = True
                squares[black_king.position].color \
                    = squares[black_king.position].original_color
                black_king.in_check = False

            if black_king.in_check and colors[(turns - 1) % 2] == 'white':
                Piece.piece_pos = list_of_positions[turns - 1]
                list_of_positions.pop()
                pieces = []
                for pos, p in Piece.piece_pos.items():
                    p.position = pos
                    pieces.append(p)
                turns -= 1

                for s in squares.values():
                    s.get_unselected()

                squares[black_king.position].color = RED
                black_king.in_check = True
                squares[white_king.position].color \
                    = squares[white_king.position].original_color
                white_king.in_check = False

            white_checkmated = False

            # Mate conditions
            if white_king.in_check and colors[(turns - 1) % 2] == 'white':

                white_mated = True
                game_state = Piece.piece_pos

                for p in game_state.values():

                    # Simulating all moves for white
                    if p.color == 'white':

                        pieces_copy = pieces

                        Piece.w_control = []
                        Piece.b_control = []

                        for p1 in pieces_copy:
                            p1.get_movement()

                        for move in p.legal_moves:
                            if move not in game_state:
                                p.position = move

                        for move in p.captures:
                            if move in game_state and \
                                    game_state[move].color != p.color:
                                pieces_copy.remove(game_state[move])
                                p.position = move

                        Piece.w_control = []
                        Piece.b_control = []

                        for p1 in pieces_copy:
                            p1.get_movement()

                        if white_king.position not in Piece.b_control:
                            white_mated = False
                            break

                if white_mated:
                    print('White checkmated!')
                    white_checkmated = True

                pieces = []
                for pos, p in Piece.piece_pos.items():
                    p.position = pos
                    pieces.append(p)

                Piece.w_control = []
                Piece.b_control = []

                for p in pieces:
                    p.get_movement()

                for p in pieces:
                    p.get_legal_moves()

                for p in pieces:
                    p.get_captures()

            black_checkmated = False

            if black_king.in_check and colors[(turns - 1) % 2] == 'black':

                black_mated = True
                game_state = Piece.piece_pos

                for p in game_state.values():

                    # Simulating all moves for black
                    if p.color == 'black':

                        pieces_copy = pieces

                        Piece.w_control = []
                        Piece.b_control = []

                        for p1 in pieces_copy:
                            p1.get_movement()

                        for move in p.legal_moves:
                            if move not in game_state:
                                p.position = move

                        for move in p.captures:
                            if move in game_state and \
                                    game_state[move].color != p.color and \
                                    game_state[move] in pieces_copy:
                                pieces_copy.remove(game_state[move])
                                p.position = move

                        Piece.w_control = []
                        Piece.b_control = []

                        for p1 in pieces_copy:
                            p1.get_movement()

                        if black_king.position not in Piece.w_control:
                            black_mated = False
                            break

                if black_mated:
                    print('Black checkmated!')
                    black_checkmated = True

                pieces = []
                for pos, p in Piece.piece_pos.items():
                    p.position = pos
                    pieces.append(p)

                Piece.w_control = []
                Piece.b_control = []

                for p in pieces:
                    p.get_movement()

                for p in pieces:
                    p.get_legal_moves()

                for p in pieces:
                    p.get_captures()

            # Stalemate conditions

            stalemate_real = False

            if colors[(turns - 1) % 2] == 'white':
                stalemate = True
                for p in pieces:
                    if p.color == 'white':
                        if len(p.legal_moves) > 0:
                            stalemate = False
                            break

                if stalemate:
                    print('Stalemate!')

            if colors[(turns - 1) % 2] == 'black':
                stalemate = True
                for p in pieces:
                    if p.color == 'black':
                        if len(p.legal_moves) > 0:
                            stalemate = False
                            break

                if stalemate:
                    print('Stalemate!')
                    stalemate_real = True

        new_position = False

        # Drawing everything
        for s in squares.values():
            pygame.draw.rect(screen, s.color, s.rect)

        for p in pieces:
            p.rect.center = squares[p.position].rect.center
            screen.blit(p.image, p.rect)

        if black_checkmated:
            end_screen("White wins!")

        if white_checkmated:
            end_screen("Black wins!")

        if stalemate_real:
            end_screen("Draw!")

        pygame.display.flip()


if __name__ == "__main__":
    main()
