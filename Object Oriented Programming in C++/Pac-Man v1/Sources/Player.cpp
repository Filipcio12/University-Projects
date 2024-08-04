#include "Player.h"

#define INIT_ROW 23
#define INIT_COLUMN 13

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
	double x = body.getCenterX();
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

	body.setCenter(x, y);
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
