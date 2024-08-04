#pragma once

#include "Ghost.h"

class Blinky : public Ghost {
  public:
	void setTarget(Board* board, const Player& player)
	{
		double targetX, targetY;

		if (mode == CHASE) {
			size_t row, column;
			board->getTileByCoords(row, column, player.body.getCenterX(),
								   player.body.getCenterY());
			board->getCoordsByTile(row, column, targetX, targetY);
		}
		if (mode == SCATTER) {
			board->getCoordsByTile(0, 25, targetX, targetY);
			targetY -= 16 * 3;
		}

		move(board, player, targetX, targetY);
	}
};
