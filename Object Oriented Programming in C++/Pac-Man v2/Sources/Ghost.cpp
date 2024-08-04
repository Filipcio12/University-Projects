#include "Ghost.h"

#include <QString>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <vector>

#define SCATTER_TIME 7000
#define CHASE_TIME 20000
#define SCARED_TIME 7000
#define GHOST_SCORE 200

#define INIT_ROW 11
#define INIT_COLUMN 14

#define TUNNEL_ROW 14

Ghost::Ghost()
{
	blueGhost.load("pacman-art/ghosts/blue_ghost.png");
	blueGhost =
		blueGhost.scaled(blueGhost.width() * 1.5, blueGhost.height() * 1.5);

	mode = SCATTER;
	QTimer::singleShot(SCATTER_TIME, this, &Ghost::switchMode);

	direction = UP;
	scared = false;
}

void Ghost::setSprite(std::string spritePath)
{
	sprite.load(QString::fromStdString(spritePath));
	sprite = sprite.scaled(sprite.width() * 1.5, sprite.height() * 1.5);
	body.setPixmap(sprite);
}

void Ghost::initPos(Board* board)
{
	double x, y;
	board->getCoordsByTile(INIT_ROW, INIT_COLUMN, x, y);
	body.setCenter(x, y);
	nextPos.first = x;
	nextPos.second = y;
}

void Ghost::switchMode()
{
	mode = (mode + 1) % 2;
	if (mode == SCATTER) {
		QTimer::singleShot(SCATTER_TIME, this, &Ghost::switchMode);
	}
	else if (mode == CHASE) {
		QTimer::singleShot(CHASE_TIME, this, &Ghost::switchMode);
	}
	if (!scared) {
		direction = (direction + 2) % 4;
	}
}

void Ghost::getScared()
{
	scared = true;
	body.setPixmap(blueGhost);
	QTimer::singleShot(SCARED_TIME, this, &Ghost::calmDown);
	direction = (direction + 2) % 4;
}

void Ghost::calmDown()
{
	scared = false;
	body.setPixmap(sprite);
	direction = (direction + 2) % 4;
}

void Ghost::setTarget(Board* board, const Player& player)
{
	double targetX, targetY;
	if (mode == CHASE) {
		size_t row, column;
		board->getTileByCoords(row, column, player.body.getCenterX(),
							   player.body.getCenterY());
		board->getCoordsByTile(row, column, targetX, targetY);
	}
	if (mode == SCATTER) {
		board->getCoordsByTile(1, 25, targetX, targetY);
	}

	move(board, player, targetX, targetY);
}

void Ghost::move(Board* board, const Player& player, double targetX,
				 double targetY)
{
	double ghostX = body.getCenterX();
	double ghostY = body.getCenterY();
	double playerX = player.body.getCenterX();
	double playerY = player.body.getCenterY();

	size_t ghostRow, ghostColumn, playerRow, playerColumn;

	board->getTileByCoords(ghostRow, ghostColumn, ghostX, ghostY);
	board->getTileByCoords(playerRow, playerColumn, playerX, playerY);

    // Handling contact with player
	if (playerRow == ghostRow && playerColumn == ghostColumn) {
		if (scared) {
			board->updateScore(GHOST_SCORE);
			initPos(board);
			return;
		}
		emit this->playerCaught();
		return;
	}

    // Handling Teletunnel (teleportation)
	if (ghostX > board->map.x2() - 1) {
		ghostX = board->map.x() + 1;
		board->getCoordsByTile(TUNNEL_ROW, 0, nextPos.first, nextPos.second);
	}

	if (ghostX < board->map.x() + 1) {
		ghostX = board->map.x2() - 1;
		board->getCoordsByTile(TUNNEL_ROW, MATRIX_COLUMNS - 1, nextPos.first, nextPos.second);
	}

    // Actual movement towards next position
	if ((nextPos.first - ghostX) > 0) {
		body.setCenter(ghostX + 1, ghostY);
		direction = RIGHT;
		return;
	}
	else if ((nextPos.first - ghostX) < 0) {
		body.setCenter(ghostX - 1, ghostY);
		direction = LEFT;
		return;
	}
	else if ((nextPos.second - ghostY) > 0) {
		body.setCenter(ghostX, ghostY + 1);
		direction = DOWN;
		return;
	}
	else if ((nextPos.second - ghostY) < 0) {
		body.setCenter(ghostX, ghostY - 1);
		direction = UP;
		return;
	}

    // Getting all next possible positions
	std::vector<Pos> positions;
	Pos pos;
	pos.first = ghostX;
	pos.second = ghostY;

	Pos up = pos;
	up.second -= TILE_SIZE;
	positions.push_back(up);
	Pos left = pos;
	left.first -= TILE_SIZE;
	positions.push_back(left);
	Pos down = pos;
	down.second += TILE_SIZE;
	positions.push_back(down);
	Pos right = pos;
	right.first += TILE_SIZE;
	positions.push_back(right);

    // Erasing the back position. Ghosts don't move backwards
	positions.erase(positions.begin() + (direction + 2) % 4);

    // Removing positions which have obstacles
	std::vector<Pos> positionsCopy;
	for (size_t i = 0; i < positions.size(); ++i) {
		size_t row, column;
		size_t tile = board->getTileByCoords(row, column, positions[i].first,
											 positions[i].second);
		if (tile != WALL && tile != DOOR && row < MATRIX_ROWS && column < MATRIX_COLUMNS) {
			positionsCopy.push_back(positions[i]);
		}
	}
	positions = positionsCopy;

    // Choosing from the remaining options
    // Scared ghosts pick randomly
	if (scared) {
		srand(time(0));
		size_t randIndex = rand() % positions.size();
		nextPos = positions[randIndex];
		return;
	}
    
    // Otherwise they pick the closest geometrically to target
	size_t minIndex = 0;
	double minD = sqrt(pow(targetX - positions[0].first, 2) +
					   pow(targetY - positions[0].second, 2));
	for (size_t i = 0; i < positions.size(); ++i) {
		double d = sqrt(pow(targetX - positions[i].first, 2) +
						pow(targetY - positions[i].second, 2));
		if (d < minD) {
			minD = d;
			minIndex = i;
		}
	}

	nextPos = positions[minIndex];
}
