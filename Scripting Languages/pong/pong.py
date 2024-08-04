import pygame
import sys
import random
import functions

pygame.init()

# Global variables
black = (0, 0, 0)
white = (255, 255, 255)
scr_width = 720
scr_height = 480
spacing = 1 / 20 * scr_width
scr = pygame.display.set_mode((scr_width, scr_height))
win = scr.get_rect()


def main():
    # pygame.init()
    num_of_players = functions.start_menu()

    # Setting up the paddles
    paddle_left = functions.paddle_setup("left")
    paddle_right = functions.paddle_setup("right")
    step = 2

    # Setting up the ball
    ball = pygame.Rect(0, 0, 10, 10)
    ball.centerx = win.centerx
    ball.centery = random.randint(win.top + ball.h / 2, win.bottom - ball.h / 2)

    # The initial movement of the ball
    ball_direction = 1
    vec = [ball_direction, random.randrange(-1, 3, 2)]

    # The initial score
    score_left = 0
    score_right = 0

    pygame.key.set_repeat(50, 50)
    fps = pygame.time.Clock()

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()

        keys = pygame.key.get_pressed()

        if num_of_players == 2:
            if keys[pygame.K_UP]:
                paddle_right = paddle_right.move(0, -step)
            if keys[pygame.K_DOWN]:
                paddle_right = paddle_right.move(0, step)

        elif num_of_players == 1:
            if ball.centery < paddle_right.centery and \
                    ball.centerx > 3 * scr_width / 4:
                paddle_right = paddle_right.move(0, -step / 2)
            if ball.centery > paddle_right.centery and \
                    ball.centerx > 3 * scr_width / 4:
                paddle_right = paddle_right.move(0, step / 2)

        if keys[pygame.K_w]:
            paddle_left = paddle_left.move(0, -step)
        if keys[pygame.K_s]:
            paddle_left = paddle_left.move(0, step)

        if paddle_left.top < win.top:
            paddle_left.top = win.top
        if paddle_left.bottom > win.bottom:
            paddle_left.bottom = win.bottom
        if paddle_right.top < win.top:
            paddle_right.top = win.top
        if paddle_right.bottom > win.bottom:
            paddle_right.bottom = win.bottom

        ball = ball.move(vec)

        # Scoring system
        if ball.left < win.left:
            score_right += 1
        if ball.right > win.right:
            score_left += 1

        myfont = pygame.font.Font('freesansbold.ttf', scr_height // 10)

        msg_right = myfont.render(str(score_right), True, white)
        msg_left = myfont.render(str(score_left), True, white)

        msg_right_box = msg_right.get_rect()
        msg_left_box = msg_left.get_rect()

        # Try to make the positioning simpler
        msg_right_box.center = win.center
        msg_right_box.centery = win.top
        msg_right_box.centery += msg_right_box.h / 2

        msg_left_box.center = win.center
        msg_left_box.centery = win.top
        msg_left_box.centery += msg_left_box.h / 2

        msg_right_box.centerx += spacing
        msg_right_box.centery += spacing / 2
        msg_left_box.centerx -= spacing
        msg_left_box.centery += spacing / 2

        # Wall collision system
        if ball.left < win.left or ball.right > win.right:
            ball.centerx = win.centerx
            ball.centery = random.randint(int(ball.h/2), win.bottom - ball.h/2)
            ball_direction *= -1
            vec = [ball_direction, random.randrange(-1, 3, 2)]
        if ball.top < win.top or ball.bottom > win.bottom:
            vec[1] = -vec[1]

        # Paddle collision system
        if ball.colliderect(paddle_left) and ball.left < paddle_left.right:
            vec[0] = -vec[0]
        if ball.colliderect(paddle_right) and ball.right > paddle_right.left:
            vec[0] = -vec[0]

        # Game over conditions
        if score_left > 4:
            functions.end_screen(1)
        if score_right > 4:
            functions.end_screen(2)

        # Displaying the screen
        scr.fill(black)
        scr.blit(msg_right, msg_right_box)
        scr.blit(msg_left, msg_left_box)
        functions.draw_middle_line(win.centerx, win.top, win.bottom)
        pygame.draw.rect(scr, white, paddle_left)
        pygame.draw.rect(scr, white, paddle_right)
        pygame.draw.rect(scr, white, ball)
        pygame.display.flip()
        fps.tick(260)


if __name__ == "__main__":
    main()
