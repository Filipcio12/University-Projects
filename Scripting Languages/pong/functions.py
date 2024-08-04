import pygame
import pong
import sys


def draw_middle_line(x1, y1, y2):
    """
    Draws a vertical dashed line from
    coordinates (x1, y1) to (x1, y2)
    """
    box = pygame.Rect(0, 0, 5, 10)
    box.center = (x1, y1)
    for y in range(int(y1 + box.h / 2), int(y2), 2 * box.h):
        box.centery = y
        pygame.draw.rect(pong.scr, pong.white, box)


def start_menu():
    """
    Creates a start menu for the game
    """

    # Title message
    start_font = pygame.font.Font('freesansbold.ttf', pong.scr_height // 10)
    title = start_font.render("PONG Project", True, pong.white)
    title_box = title.get_rect()
    title_box.center = pong.win.center
    title_box.top = pong.win.top + pong.spacing

    # Author message
    start_font = pygame.font.Font('freesansbold.ttf', pong.scr_height // 20)
    author = start_font.render("by Filip Fajfer", True, pong.white)
    author_box = author.get_rect()
    author_box.center = pong.win.center
    author_box.top = title_box.bottom + pong.spacing / 5

    # Game mode messages
    start_font = pygame.font.Font('freesansbold.ttf', pong.scr_height // 15)

    mode1 = start_font.render("1 PLAYER", True, pong.white)
    mode1_box = mode1.get_rect()
    mode1_box.center = pong.win.center
    mode1_box.left -= 5 * pong.spacing
    mode1_box.bottom += pong.spacing

    mode2 = start_font.render("2 PLAYERS", True, pong.white)
    mode2_box = mode2.get_rect()
    mode2_box.center = pong.win.center
    mode2_box.right += 5 * pong.spacing
    mode2_box.bottom += pong.spacing

    # Menu selecting object thing
    menu_selector = start_font.render("*", True, pong.white)
    menu_selector_box = menu_selector.get_rect()
    menu_selector_box.center = mode1_box.center
    menu_selector_box.right = mode1_box.left - pong.spacing / 2

    pygame.key.set_repeat(50, 50)
    fps = pygame.time.Clock()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

        '''mouse_press = pygame.mouse.get_pressed(3)
        mouse_pos = pygame.mouse.get_pos()

        if mouse_press[0] and \
                mode1_box.left <= mouse_pos[0] <= mode1_box.right and \
                mode1_box.top <= mouse_pos[1] <= mode1_box.bottom:
            return 1

        if mouse_press[0] and \
                mode2_box.left <= mouse_pos[0] <= mode2_box.right and \
                mode2_box.top <= mouse_pos[1] <= mode2_box.bottom:
            return 2'''

        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT] and \
                menu_selector_box.right == mode2_box.left - pong.spacing / 2:
            menu_selector_box.right = mode1_box.left - pong.spacing / 2
        if keys[pygame.K_RIGHT] and \
                menu_selector_box.right == mode1_box.left - pong.spacing / 2:
            menu_selector_box.right = mode2_box.left - pong.spacing / 2
        if keys[pygame.K_RETURN] and \
                menu_selector_box.right == mode1_box.left - pong.spacing / 2:
            return 1
        if keys[pygame.K_RETURN] and \
                menu_selector_box.right == mode2_box.left - pong.spacing / 2:
            return 2

        pong.scr.fill(pong.black)
        pong.scr.blit(title, title_box)
        pong.scr.blit(author, author_box)
        y1 = author_box.bottom + pong.spacing
        y2 = pong.win.bottom - pong.spacing
        draw_middle_line(author_box.centerx, y1, y2)
        pong.scr.blit(mode1, mode1_box)
        pong.scr.blit(mode2, mode2_box)
        pong.scr.blit(menu_selector, menu_selector_box)
        pygame.display.flip()
        fps.tick(260)


def end_screen(winner):
    """
    Creates an end screen for the game
    """

    # Game over message
    end_font = pygame.font.Font('freesansbold.ttf', pong.scr_height // 5)
    gameover = end_font.render("Game Over", True, pong.white)
    gameover_box = gameover.get_rect()
    gameover_box.center = pong.win.center
    gameover_box.top = pong.win.top + pong.spacing

    end_font = pygame.font.Font('freesansbold.ttf', pong.scr_height // 10)

    if winner == 1:
        victory = end_font.render("Player 1 wins!", True, pong.white)
    else:
        victory = end_font.render("Player 2 wins!", True, pong.white)

    victory_box = victory.get_rect()
    victory_box.center = pong.win.center
    victory_box.top = gameover_box.bottom + pong.spacing / 5

    end_font = pygame.font.Font('freesansbold.ttf', pong.scr_height // 15)
    quitgame = end_font.render("QUIT GAME", True, pong.white)
    quitgame_box = quitgame.get_rect()
    quitgame_box.center = pong.win.center
    quitgame_box.bottom += 2 * pong.spacing
    quitgame_box.left -= 5 * pong.spacing

    end_font = pygame.font.Font('freesansbold.ttf', pong.scr_height // 15)
    menu = end_font.render("MAIN MENU", True, pong.white)
    menu_box = menu.get_rect()
    menu_box.center = pong.win.center
    menu_box.bottom += 2 * pong.spacing
    menu_box.left += 5 * pong.spacing

    # Menu selecting object thing
    menu_selector = end_font.render("*", True, pong.white)
    menu_selector_box = menu_selector.get_rect()
    menu_selector_box.center = quitgame_box.center
    menu_selector_box.right = quitgame_box.left - pong.spacing / 2

    pygame.key.set_repeat(50, 50)
    fps = pygame.time.Clock()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

        keys = pygame.key.get_pressed()
        if keys[pygame.K_LEFT] and \
                menu_selector_box.right == menu_box.left - pong.spacing / 2:
            menu_selector_box.right = quitgame_box.left - pong.spacing / 2
        if keys[pygame.K_RIGHT] and \
                menu_selector_box.right == quitgame_box.left - pong.spacing / 2:
            menu_selector_box.right = menu_box.left - pong.spacing / 2
        if keys[pygame.K_RETURN] and \
                menu_selector_box.right == quitgame_box.left - pong.spacing / 2:
            sys.exit()
        if keys[pygame.K_RETURN] and \
                menu_selector_box.right == menu_box.left - pong.spacing / 2:
            pong.main()

        pong.scr.fill(pong.black)
        pong.scr.blit(gameover, gameover_box)
        pong.scr.blit(victory, victory_box)
        pong.scr.blit(quitgame, quitgame_box)
        pong.scr.blit(menu, menu_box)
        y1 = victory_box.bottom + pong.spacing
        y2 = pong.win.bottom - pong.spacing
        draw_middle_line(victory_box.centerx, y1, y2)
        pong.scr.blit(menu_selector, menu_selector_box)
        pygame.display.flip()
        fps.tick(260)


def paddle_setup(side):
    """
    Creates a paddle rectangle
    either on the left or on the right
    """
    paddle = pygame.Rect(0, 0, 10, 60)
    if side == "left":
        paddle.center = pong.win.midleft
        paddle.x += pong.spacing
    elif side == "right":
        paddle.center = pong.win.midright
        paddle.x -= pong.spacing
    return paddle
