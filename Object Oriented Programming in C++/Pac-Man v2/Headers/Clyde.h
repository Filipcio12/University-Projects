#pragma once

#include "Ghost.h"
#include <cmath>

class Clyde : public Ghost {
  public:
	void setTarget(Board* board, const Player& player)
	{
		double targetX, targetY;

		if (mode == CHASE) {
			size_t row, column;
			double playerX = player.body.getCenterX();
			double playerY = player.body.getCenterY();

			board->getTileByCoords(row, column, playerX, playerY);
			board->getCoordsByTile(row, column, playerX, playerY);

			double ghostX = body.getCenterX();
			double ghostY = body.getCenterY();

			board->getTileByCoords(row, column, ghostX, ghostY);
			board->getCoordsByTile(row, column, ghostX, ghostY);

			double d =
				sqrt(pow(playerX - ghostX, 2) + pow(playerY - ghostY, 2));

			if (d > 16 * 8) {
				board->getTileByCoords(row, column, playerX, playerY);
				board->getCoordsByTile(row, column, targetX, targetY);
			}
			else {
				board->getCoordsByTile(30, 0, targetX, targetY);
				targetY += 16 * 2;
			}
		}
		if (mode == SCATTER) {
			board->getCoordsByTile(30, 0, targetX, targetY);
			targetY += 16 * 2;
		}

		move(board, player, targetX, targetY);
	}
};
