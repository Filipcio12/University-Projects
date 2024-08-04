#pragma once

#include "Ghost.h"

class Pinky : public Ghost {
    public:
        void setTarget(Board* board, const Player& player)
        {
            double targetX, targetY;

            if (mode == CHASE) {
                size_t row, column;
                double playerX = player.body.getCenterX();
                double playerY = player.body.getCenterY();

                if (player.direction == "up") {
                    playerY -= 16 * 4;
                }
                if (player.direction == "left") {
                    playerX -= 16 * 4;
                }
                if (player.direction == "down") {
                    playerY += 16 * 4;
                }
                if (player.direction == "right") {
                    playerX += 16 * 4;
                }

                board->getTileByCoords(row, column, playerX, playerY);
                board->getCoordsByTile(row, column, targetX, targetY);
            }
            if (mode == SCATTER) {
                board->getCoordsByTile(0, 2, targetX, targetY);
                targetY -= 16 * 3;
            }

            move(board, player, targetX, targetY); 
        }
};