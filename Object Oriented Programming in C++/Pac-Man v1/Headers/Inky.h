#pragma once

#include "Ghost.h"

class Inky : public Ghost {
    public:   
        void setTarget(Board* board, const Player& player, const Blinky& blinky)
        {
            double targetX, targetY;
            
            if (mode == CHASE) {
                size_t row, column;
                double playerX = player.body.getCenterX();
                double playerY = player.body.getCenterY();

                if (player.direction == "up") {
                    playerY -= 16 * 2;
                }
                if (player.direction == "left") {
                    playerX -= 16 * 2;
                }
                if (player.direction == "down") {
                    playerY += 16 * 2;
                }
                if (player.direction == "right") {
                    playerX += 16 * 2;
                }

                board->getTileByCoords(row, column, playerX, playerY);
                board->getCoordsByTile(row, column, playerX, playerY);

                double blinkyX = blinky.body.getCenterX();
                double blinkyY = blinky.body.getCenterY();

                board->getTileByCoords(row, column, blinkyX, blinkyY);
                board->getCoordsByTile(row, column, blinkyX, blinkyY);

                double vectorX = playerX - blinkyX;
                double vectorY = playerY - blinkyY;

                targetX = playerX + vectorX;
                targetY = playerY + vectorY;
            }
            if (mode == SCATTER) {
                board->getCoordsByTile(30, 27, targetX, targetY);
                targetY += 16 * 2;
            }

            move(board, player, targetX, targetY);
        }
};