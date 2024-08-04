#include "primlib.h"
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

#define SCREEN_WIDTH gfx_screenWidth()
#define SCREEN_HEIGHT gfx_screenHeight()
#define GROUND_LEVEL (SCREEN_HEIGHT - 25)
#define NUMBER_OF_PEGS 3
#define NUMBER_OF_DISCS 5
#define PEG_SPACING (SCREEN_WIDTH / (NUMBER_OF_PEGS + 1))
#define PEG_WIDTH (PEG_SPACING / 8)
#define DISC_HEIGHT ((SCREEN_HEIGHT - 50) / NUMBER_OF_DISCS / 3)
#define PEG_HEIGHT (DISC_HEIGHT * (NUMBER_OF_DISCS + 1))
#define FIRST_DISC_WIDTH (PEG_WIDTH * 2)
#define LAST_DISC_WIDTH (PEG_SPACING)
#define DISC_WIDTH_INCREMENT                                                   \
	((LAST_DISC_WIDTH - FIRST_DISC_WIDTH) / NUMBER_OF_DISCS)
#define UPPER_DISC_Y_POSITION (GROUND_LEVEL - PEG_HEIGHT - 2 * DISC_HEIGHT)

#define DISC_SPEED 1
#define DELAY 5
#define TEXT_X_POSITION (SCREEN_WIDTH / 2 - 100)
#define TEXT_Y_POSITION (SCREEN_HEIGHT / 2)
#define TEXT_Y_SHIFT 50

/** STACK IMPLEMENTATION **/

#define STACKSIZE NUMBER_OF_DISCS

struct Stack {
	int top;
	int data[STACKSIZE];
};

void init(struct Stack* stack)
{
	stack->top = 0;
	for (int i = 0; i < STACKSIZE; i++)
		stack->data[i] = 0;
}

void push(struct Stack* stack, int a)
{
	assert(stack->top < STACKSIZE);
	stack->data[stack->top++] = a;
}

int pop(struct Stack* stack)
{
	assert(stack->top > 0);
	int temp = stack->data[--stack->top];
	stack->data[stack->top] = 0;
	return temp;
}

int peek(struct Stack* stack)
{
	assert(stack->top > 0);
	return stack->data[stack->top - 1];
}

int isEmpty(struct Stack* stack)
{
	if (stack->top == 0)
		return 1;
	else
		return 0;
}

int isFull(struct Stack* stack)
{
	if (stack->top == STACKSIZE)
		return 1;
	else
		return 0;
}

void drawPegs()
{
	int y1 = GROUND_LEVEL - PEG_HEIGHT;
	int y2 = GROUND_LEVEL - 1;
	for (int i = 0; i < NUMBER_OF_PEGS; i++) {
		int x1 = PEG_SPACING * (i + 1) - PEG_WIDTH / 2;
		int x2 = PEG_SPACING * (i + 1) + PEG_WIDTH / 2;
		gfx_filledRect(x1, y1, x2, y2, RED);
	}
}

void drawBorders(int x1, int y1, int x2, int y2)
{
	gfx_line(x1, y1, x2, y1, BLUE);
	gfx_line(x2, y1, x2, y2, BLUE);
	gfx_line(x2, y2, x1, y2, BLUE);
	gfx_line(x1, y2, x1, y1, BLUE);
}

void drawDiscs(struct Stack stack[])
{
	for (int i = 0; i < NUMBER_OF_PEGS; i++) {
		for (int j = 0; j < NUMBER_OF_DISCS; j++) {
			if (stack[i].data[j] == 0)
				break;

			int discWidth = FIRST_DISC_WIDTH +
							DISC_WIDTH_INCREMENT * (stack[i].data[j] - 1);

			int x1 = PEG_SPACING * (i + 1) - discWidth / 2;
			int y1 = GROUND_LEVEL - (j + 1) * DISC_HEIGHT;
			int x2 = PEG_SPACING * (i + 1) + discWidth / 2;
			int y2 = y1 + DISC_HEIGHT - 1;

			gfx_filledRect(x1, y1, x2, y2, MAGENTA);
			drawBorders(x1, y1, x2, y2);
		}
	}
}

void drawBackground()
{
	gfx_filledRect(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, BLACK);
	gfx_filledRect(0, GROUND_LEVEL, SCREEN_WIDTH, SCREEN_HEIGHT, YELLOW);
}

void takeUserInput(int* key1, int* key2)
{
	*key1 = gfx_getkey() - '0';
	*key2 = gfx_getkey() - '0';
	if (*key1 == 0)
		*key1 = 9;
	else
		*key1 = *key1 - 1;
	if (*key2 == 0)
		*key2 = 9;
	else
		*key2 = *key2 - 1;
}

void drawAnimation(struct Stack stack[], int x1, int y1, int x2, int y2)
{
	drawBackground();
	drawPegs(stack);
	drawDiscs(stack);
	gfx_filledRect(x1, y1, x2, y2, MAGENTA);
	drawBorders(x1, y1, x2, y2);
	gfx_updateScreen();
	SDL_Delay(DELAY);
}

void animateDisc(struct Stack stack[], int key1, int key2, int discNumber)
{
	int discWidth = FIRST_DISC_WIDTH + DISC_WIDTH_INCREMENT * (discNumber - 1);
	int x1 = PEG_SPACING * (key1 + 1) - discWidth / 2;
	int y1 = GROUND_LEVEL - (stack[key1].top + 1) * DISC_HEIGHT;
	int x2 = PEG_SPACING * (key1 + 1) + discWidth / 2;
	int y2 = y1 + DISC_HEIGHT - 1;
	int yNew = GROUND_LEVEL - (stack[key2].top + 1) * DISC_HEIGHT;
	while (y1 > UPPER_DISC_Y_POSITION) {
		drawAnimation(stack, x1, y1, x2, y2);
		y1 -= DISC_SPEED;
		y2 -= DISC_SPEED;
	}
	int discCenter = (x1 + x2) / 2;
	if (key1 < key2)
		while (discCenter < PEG_SPACING * (key2 + 1)) {
			drawAnimation(stack, x1, y1, x2, y2);
			x1 += DISC_SPEED;
			x2 += DISC_SPEED;
			discCenter += DISC_SPEED;
		}
	else
		while (discCenter > PEG_SPACING * (key2 + 1)) {
			drawAnimation(stack, x1, y1, x2, y2);
			x1 -= DISC_SPEED;
			x2 -= DISC_SPEED;
			discCenter -= DISC_SPEED;
		}
	while (y1 < yNew) {
		drawAnimation(stack, x1, y1, x2, y2);
		y1 += DISC_SPEED;
		y2 += DISC_SPEED;
	}
}

void moveDisc(struct Stack stack[], int key1, int key2)
{
	if (key1 == key2 || key1 > NUMBER_OF_PEGS - 1 || key1 < 0 ||
		key2 > NUMBER_OF_PEGS - 1 || key2 < 0 || isEmpty(&stack[key1]))
		return;
	if (isEmpty(&stack[key2])) {
		int disc1 = pop(&stack[key1]);
		animateDisc(stack, key1, key2, disc1);
		push(&stack[key2], disc1);
		return;
	}
	int disc1 = peek(&stack[key1]);
	int disc2 = peek(&stack[key2]);
	if (disc1 > disc2)
		return;
	disc1 = pop(&stack[key1]);
	animateDisc(stack, key1, key2, disc1);
	push(&stack[key2], disc1);
}

int makeEndScreen(struct Stack stack[], int condition)
{
	if (!condition)
		return 1;
	gfx_filledRect(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, BLACK);
	gfx_textout(TEXT_X_POSITION, TEXT_Y_POSITION - TEXT_Y_SHIFT,
				"Congratulations!", WHITE);
	gfx_textout(TEXT_X_POSITION, TEXT_Y_POSITION, "Press ENTER to REPLAY",
				WHITE);
	gfx_textout(TEXT_X_POSITION, TEXT_Y_POSITION + TEXT_Y_SHIFT,
				"Press ESC to EXIT", WHITE);
	gfx_updateScreen();
	while (1) {
		int input = gfx_getkey();
		if (input == 27)
			return 0;
		if (input == 13) {
			for (int i = 0; i < NUMBER_OF_PEGS; i++)
				init(&stack[i]);
			for (int i = NUMBER_OF_DISCS; i > 0; i--)
				push(&stack[0], i);
			return 1;
		}
	}
}

int main(int argc, char* argv[])
{
	if (gfx_init()) {
		exit(3);
	}

	int key1, key2;

	struct Stack peg[NUMBER_OF_PEGS];
	for (int i = 0; i < NUMBER_OF_PEGS; i++)
		init(&peg[i]);

	for (int i = NUMBER_OF_DISCS; i > 0; i--)
		push(&peg[0], i);

	do {
		drawBackground();
		drawPegs(peg);
		drawDiscs(peg);
		gfx_updateScreen();
		takeUserInput(&key1, &key2);
		moveDisc(peg, key1, key2);
		printf("%d, %d\n", key1, key2);
	} while (!gfx_isKeyDown(27) &&
			 makeEndScreen(peg, isFull(&peg[NUMBER_OF_PEGS - 1])));
	return 0;
}
