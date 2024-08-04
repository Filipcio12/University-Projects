#include "primlib.h"
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#define VERTICES 5
#define ANGLE_STEP 0.04

void drawPolygon(int numSides, int xCenter, int yCenter, int radius,
				 double angle)
{
	double angleStep = 2 * M_PI / numSides;

	for (int i = 0; i < numSides; i++) {
		int x1 = xCenter + radius * cos(angle);
		int y1 = yCenter + radius * sin(angle);
		angle += angleStep;

		int x2 = xCenter + radius * cos(angle);
		int y2 = yCenter + radius * sin(angle);
		gfx_line(x1, y1, x2, y2, YELLOW);
	}
}

int main(int argc, char* argv[])
{
	if (gfx_init()) {
		exit(3);
	}

	const int S_WIDTH = gfx_screenWidth();
	const int S_HEIGHT = gfx_screenHeight();

	double angle = 0.0;
	int xCenter = S_WIDTH / 2;
	int yCenter = S_HEIGHT / 2;
	int radius = 100;
	int radiusStep = 1;

	while (1) {
		gfx_filledRect(0, 0, S_WIDTH - 1, S_HEIGHT - 1, BLACK);
		drawPolygon(VERTICES, xCenter, yCenter, radius, angle);
		gfx_updateScreen();
		SDL_Delay(50);
		
		angle += ANGLE_STEP;
		radius += radiusStep;

		if (angle > 2 * M_PI) {
			angle -= 2 * M_PI;
		}

		if (radius > 200 || radius < 100) {
			radiusStep *= -1;
		}

		if (gfx_isKeyDown(27)) {
			break;
		}
	}
	return 0;
}
