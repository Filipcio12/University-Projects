#include "Player.h"

#include <vector>

#define INIT_ROW 23
#define INIT_COLUMN 13
#define TUNNEL_ROW 14

#define DOT_SCORE 10
#define STRAWBERRY_SCORE 50

#define ANIM_RATE 200

Player::Player()
{
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(animateMovement()));
	timer->start(ANIM_RATE);

	frame = 1;
	direction = "right";
	dir = RIGHT;
	spritePath = "pacman-art/pacman-";
	sprite.load("pacman-art/pacman-right/1.png");
	sprite = sprite.scaled(sprite.width() * 1.5, sprite.height() * 1.5);

	body.setPixmap(sprite);
}

void Player::initPos(Board* board)
{
	double x, y;
	board->getCoordsByTile(INIT_ROW, INIT_COLUMN, x, y);
	body.setCenter(x, y);
	nextPos.first = x;
	nextPos.second = y;
}

Player::~Player()
{
	delete timer;
}

void Player::eatDot(Board* board, size_t row, size_t column)
{
	Point coords;
	coords.first = row;
	coords.second = column;
	delete board->dots[coords];
	board->dots.erase(coords);
	board->matrix[row][column] = EMPTY_DOT;
	board->updateScore(DOT_SCORE);

	if (board->dots.empty() && board->strawberries.empty()) {
		emit this->victoryReset();
		return;
	}
}

void Player::eatStrawberry(Board* board, size_t row, size_t column)
{
	Point coords;
	coords.first = row;
	coords.second = column;
	delete board->strawberries[coords];
	board->strawberries.erase(coords);
	board->matrix[row][column] = EMPTY_STRAWBERRY;
	emit this->scareGhosts();
	board->updateScore(STRAWBERRY_SCORE);

	if (board->dots.empty() && board->strawberries.empty()) {
		emit this->victoryReset();
		return;
	}
}

void Player::modifyPosition(Board* board, double& x, double& y)
{
	if (direction == "right") {
		x += 1;
	}
	else if (direction == "left") {
		x -= 1;
	}
	else if (direction == "down") {
		y += 1;
	}
	else if (direction == "up") {
		y -= 1;
	}

	// Handle teleportation
	if (x > board->map.x2() - 1) {
		x = board->map.x() + 1;
	}

	if (x < board->map.x() + 1) {
		x = board->map.x2() - 1;
	}
}

void Player::move(Board* board)
{
	/*double x = body.getCenterX();
	double y = body.getCenterY();

	modifyPosition(board, x, y);

	size_t row, column;
	size_t tile = board->getTileByCoords(row, column, x, y);
	
	if (tile == WALL || tile == DOOR) {
		return;
	}
	if (tile == DOT) {
		eatDot(board, row, column);
	}
	if (tile == STRAWBERRY) {
		eatStrawberry(board, row, column);
	}

	body.setCenter(x, y);*/
	
	double x = body.getCenterX();
	double y = body.getCenterY();
	
	size_t row, column;
	size_t tile = board->getTileByCoords(row, column, x, y);
	
	if (tile == DOT) {
		eatDot(board, row, column);
	}
	if (tile == STRAWBERRY) {
		eatStrawberry(board, row, column);
	}
	
	if (x > board->map.x2() - 1) {
		x = board->map.x() + 1;
		board->getCoordsByTile(TUNNEL_ROW, 0, nextPos.first, nextPos.second);
	}

	if (x < board->map.x() + 1) {
		x = board->map.x2() - 1;
		board->getCoordsByTile(TUNNEL_ROW, MATRIX_COLUMNS - 1, nextPos.first, nextPos.second);
	}
	
	if ((nextPos.first - x) > 0) {
		body.setCenter(x + 1, y);
		direction = "right";
		return;
	}
	else if ((nextPos.first - x) < 0) {
		body.setCenter(x - 1, y);
		direction = "left";
		return;
	}
	else if ((nextPos.second - y) > 0) {
		body.setCenter(x, y + 1);
		direction = "down";
		return;
	}
	else if ((nextPos.second - y) < 0) {
		body.setCenter(x, y - 1);
		direction = "up";
		return;
	}
	
	Pos pos;
	pos.first = x;
	pos.second = y;
	
	Pos up = pos;
	up.second -= TILE_SIZE;
	size_t upTile = board->getTileByCoords(row, column, up.first, up.second);
	Pos left = pos;
	left.first -= TILE_SIZE;
	size_t leftTile = board->getTileByCoords(row, column, left.first, left.second);
	Pos down = pos;
	down.second += TILE_SIZE;
	size_t downTile = board->getTileByCoords(row, column, down.first, down.second);
	Pos right = pos;
	right.first += TILE_SIZE;
	size_t rightTile = board->getTileByCoords(row, column, right.first, right.second);
	
	if (dir == UP && upTile != WALL && upTile != DOOR) {
		nextPos = up;
		return;
	}
	else if (dir == LEFT && leftTile != WALL && leftTile != DOOR) {
		nextPos = left;
		return;
	}
	else if (dir == DOWN && downTile != WALL && downTile != DOOR) {
		nextPos = down;
		return;
	}
	else if (dir == RIGHT && rightTile != WALL && rightTile != DOOR) {
		nextPos = right;
		return;
	}
	else {
		if (direction == "right" && rightTile != WALL && rightTile != DOOR) {
			nextPos = right;
		}
		if (direction == "left" && leftTile != WALL && leftTile != DOOR) {
			nextPos = left;
		}
		if (direction == "down" && downTile != WALL && downTile != DOOR) {
			nextPos = down;
		}
		if (direction == "up" && upTile != WALL && upTile != DOOR) {
			nextPos = up;
		}
	}
}

void Player::animateMovement()
{
	spritePath =
		"pacman-art/pacman-" + direction + "/" + std::to_string(frame) + ".png";
	sprite.load(QString::fromStdString(spritePath));
	sprite = sprite.scaled(sprite.width() * 1.5, sprite.height() * 1.5);
	body.setPixmap(sprite);
	frame = frame % 3 + 1;
}
