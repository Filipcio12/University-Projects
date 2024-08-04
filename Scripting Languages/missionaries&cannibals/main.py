"""
Missionary & Cannibals

Pygame game project which
uses graph-based logic.
"""
import sys
import pygame


def get_mouse(rect):
    """
    The function checks if the
    mouse clicked a given rectangle.
    :param rect: given rectangle
    :return: boolean value
    """
    mouse_press = pygame.mouse.get_pressed(3)
    mouse_pos = pygame.mouse.get_pos()

    if mouse_press[0] and \
            rect.left <= mouse_pos[0] <= rect.right and \
            rect.top <= mouse_pos[1] <= rect.bottom:
        return True

    return False


def enter_boat(rect, orig):
    """
    The function moves the passenger
    over onto the boat rectangle.
    Then adds the actor to the list
    of passengers. It also writes
    down the passenger's orignal y
    coordinate.
    :param rect: passenger rectangle
    :param orig: passenger's original y coordinate
    :return: -
    """
    rect.bottom = boat_rect.top

    if len(passengers) == 0:
        rect.left = boat_rect.left

    elif len(passengers) == 1:
        passengers[0].left = boat_rect.left
        rect.right = boat_rect.right

    passengers.append(rect)
    pos_passengers.append(orig)


def leave_boat(rect, orig):
    """
    Moves the passenger to either the
    left or right bank and back to its
    original y coordinate. Then it removes
    the passenger and original y coordinate
    from both lists.
    :param rect: passenger rectangle
    :param orig: passenger's original y coordinate
    :return: -
    """
    if boat_rect.left == boat_pos_left:
        rect.midleft = (0, orig)

    elif boat_rect.right == boat_pos_right:
        rect.midright = (arena.width, orig)

    passengers.remove(rect)
    pos_passengers.remove(orig)


def success():
    """
    Displays a success message
    to the player.
    :return: -
    """
    myfont = pygame.font.Font('freesansbold.ttf', 48)
    msg = myfont.render("Success", True, (255, 0, 0))
    msg_box = msg.get_rect()
    msg_box.center = arena.center
    window.blit(msg, msg_box)
    pygame.display.flip()
    pygame.time.wait(1000)


def failure():
    """
    Displays a failure message
    to the player.
    :return: -
    """
    myfont = pygame.font.Font('freesansbold.ttf', 48)
    msg = myfont.render("Failure", True, (255, 0, 0))
    msg_box = msg.get_rect()
    msg_box.center = arena.center
    window.blit(msg, msg_box)
    pygame.display.flip()
    pygame.time.wait(1000)


def start_menu():
    """
    Displays a start menu
    to the player.
    :return: -
    """
    # Title
    title_font = pygame.font.Font('freesansbold.ttf', int(arena.height * 0.1))
    title = title_font.render("Missionaries & Cannibals", True, pygame.Color("white"))
    title_box = title.get_rect()
    title_box.center = arena.center
    title_box.top = arena.height * 0.05

    # Game information
    msg_font = pygame.font.Font('freesansbold.ttf', int(arena.height * 0.05))

    msg = []
    msg.append(msg_font.render("Three missionaries and three cannibals are on", True, pygame.Color("white")))
    msg.append(msg_font.render("one side of a river that they wish to cross.", True, pygame.Color("white")))
    msg.append(msg_font.render("A boat is available that can hold at most two", True, pygame.Color("white")))
    msg.append(msg_font.render("people and at least one.", True, pygame.Color("white")))
    msg.append(msg_font.render("You must never leave a group of missionaries", True, pygame.Color("white")))
    msg.append(msg_font.render("outnumbered by cannibals on the same bank.", True, pygame.Color("white")))
    msg.append(msg_font.render("Goal: find an action sequence that brings", True, pygame.Color("white")))
    msg.append(msg_font.render("everyone safely to the opposite bank.", True, pygame.Color("white")))
    msg.append(msg_font.render("Simply click a person to place them in and out", True, pygame.Color("white")))
    msg.append(msg_font.render("of the boat. Click the boat to move it to", True, pygame.Color("white")))
    msg.append(msg_font.render("the other side. Click start to begin. Good luck!", True, pygame.Color("white")))

    msg_box = []
    for i, message in enumerate(msg):
        msg_box.append(message.get_rect())

    msg_box[0].center = arena.center
    msg_box[0].top = arena.height * 0.2
    for i in range(len(msg_box) - 1):
        msg_box[i + 1].top = msg_box[i].bottom
        msg_box[i + 1].left = msg_box[i].left

    # Start button
    start_font = pygame.font.Font('freesansbold.ttf', int(arena.height * 0.1))
    start = start_font.render("Start", True, pygame.Color("white"))
    start_box = start.get_rect()
    start_box.center = arena.center
    start_box.top = arena.height * 0.8

    # Start menu game loop
    fpsClock = pygame.time.Clock()
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

        if get_mouse(start_box):
            break

        window.fill(pygame.Color("black"))
        window.blit(title, title_box)
        for i in range(len(msg)):
            window.blit(msg[i], msg_box[i])
        window.blit(start, start_box)
        pygame.display.flip()
        fpsClock.tick(120)


# Initialization
pygame.init()
window = pygame.display.set_mode((640, 480))
arena = window.get_rect()

# Adding a background
bg = pygame.image.load("background.jpg")
bg = pygame.transform.scale(bg, (arena.width, arena.height))
bg_rect = bg.get_rect()
bg_rect.x = 0
bg_rect.y = 0

# Creating actors
missionary = []
cannibal = []
actors = []

for i in range(3):
    missionary.append({"file": "missionary.jpg"})
    cannibal.append({"file": "cannibal.jpg"})
    actors.append(missionary[i])

for i in range(3):
    actors.append(cannibal[i])

for i, actor in enumerate(actors):
    actor["surf"] = pygame.image.load(actor["file"])
    actor["surf"] = pygame.transform.scale(actor["surf"], (arena.width / 10, arena.height / 10))
    actor["rect"] = actor["surf"].get_rect()
    actor["rect"].midleft = (0, (i + 1) * arena.height / 7)
    actor["orig"] = (i + 1) * arena.height / 7  # The original position of the actor

# Creating a boat
boat_surf = pygame.image.load("boat.jpg")
boat_surf = pygame.transform.scale(boat_surf, (arena.width / 5, arena.height / 10))
boat_rect = boat_surf.get_rect()
boat_rect.center = arena.center
boat_pos_left = arena.width * 0.15
boat_pos_right = arena.width * 0.85
boat_rect.left = boat_pos_left
passengers = []
pos_passengers = []

# Creating the game graph
gamegraph = {
    # gamestate
    "cccmmmb-": {"c": "ccmmm-cb", "cc": "cmmm-ccb", "m": "cccmm-mb", "mm": "cccm-mmb", "cm": "ccmm-cmb"},
    "ccmmm-cb": {"c": "cccmmmb-"},
    "cmmm-ccb": {"c": "ccmmmb-c", "cc": "cccmmmb-"},
    "ccmm-cmb": {"c": "cccmm-mb", "m": "ccmmmb-c", "cm": "cccmmmb-"},
    "ccmmmb-c": {"c": "cmmm-ccb", "cc": "mmm-cccb", "m": "ccmm-cmb", "mm": "ccm-cmmb", "cm": "cmm-ccmb"},
    "mmm-cccb": {"c": "cmmmb-cc", "cc": "ccmmmb-c"},
    "cmmmb-cc": {"c": "mmm-cccb", "m": "cmm-ccmb", "mm": "cm-ccmmb", "cm": "mm-cccmb"},
    "cm-ccmmb": {"c": "ccmb-cmm", "cc": "cccmb-mm", "m": "cmmb-ccm", "mm": "cmmmb-cc", "cm": "ccmmb-cm"},
    "ccmmb-cm": {"c": "cmm-ccmb", "cc": "mm-cccmb", "m": "ccm-cmmb", "mm": "cc-cmmmb", "cm": "cm-ccmmb"},
    "cc-cmmmb": {"c": "cccb-mmm", "m": "ccmb-cmm", "mm": "ccmmb-cm", "cm": "cccmb-mm"},
    "cccb-mmm": {"c": "cc-cmmmb", "cc": "c-ccmmmb"},
    "c-ccmmmb": {"c": "ccb-cmmm", "cc": "cccb-mmm", "m": "cmb-ccmm", "mm": "cmmb-ccm", "cm": "ccmb-cmm"},
    "cmb-ccmm": {"c": "m-cccmmb", "m": "c-ccmmmb", "cm": "-cccmmmb"},
    "ccb-cmmm": {"c": "c-ccmmmb", "cc": "-cccmmmb"},
    # failures
    "cccmm-mb": "failure",
    "cccm-mmb": "failure",
    "cccmmb-m": "failure",
    "ccm-cmmb": "failure",
    "cmm-ccmb": "failure",
    "mm-cccmb": "failure",
    "ccmb-cmm": "failure",
    "cccmb-mm": "failure",
    "cmmb-ccm": "failure",
    # success
    "-cccmmmb": "success"}

gamestate = "cccmmmb-"

# Start menu
start_menu()

# Main loop
fpsClock = pygame.time.Clock()
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

    # Entering the boat
    for i, actor in enumerate(actors):
        if get_mouse(actor["rect"]) and len(passengers) < 2 and \
                (actor["rect"].left == 0 and boat_rect.left == boat_pos_left or
                 actor["rect"].right == arena.width and boat_rect.right == boat_pos_right):
            enter_boat(actor["rect"], actor["orig"])

    # Leaving the boat
    for i, passenger in enumerate(passengers):
        if get_mouse(passenger):
            leave_boat(passenger, pos_passengers[i])

    # Moving the boat
    if get_mouse(boat_rect) and len(passengers) > 0:
        if boat_rect.left == boat_pos_left:
            boat_rect.right = boat_pos_right

        elif boat_rect.right == boat_pos_right:
            boat_rect.left = boat_pos_left

        passengers[0].left = boat_rect.left
        if len(passengers) == 2:
            passengers[1].right = boat_rect.right

        # Affecting the game state
        gamemove = ""
        for i, passenger in enumerate(passengers):
            if pos_passengers[i] > arena.height * 0.5:
                gamemove += 'c'
            elif pos_passengers[i] < arena.height * 0.5:
                gamemove += 'm'
        gamemove = ''.join(sorted(gamemove))
        gamestate = gamegraph[gamestate][gamemove]

    # Drawing everything
    window.blit(bg, bg_rect)
    for actor in actors:
        window.blit(actor["surf"], actor["rect"])
    window.blit(boat_surf, boat_rect)

    # Checking end conditions
    if gamegraph[gamestate] == "failure":
        failure()

    if gamegraph[gamestate] == "success":
        success()

    pygame.display.flip()
    fpsClock.tick(120)
