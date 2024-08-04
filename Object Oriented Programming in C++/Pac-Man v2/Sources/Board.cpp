#include "Board.h"

Board::Board()
{
	scene.setSceneRect(0, 0, VIEW_SIZE, VIEW_SIZE);
	QPixmap sprite("pacman-art/map.png");
	sprite = sprite.scaled(sprite.width() * 2, sprite.height() * 2);
	map.setPixmap(sprite);
	scene.addItem(&map);
	map.setCenter(BOARD_SIZE, BOARD_SIZE);
	placeDots();
	placeTexts();
	lives = 3;
}

void Board::placeItem(ItemMap& items, const QPixmap& sprite, size_t row,
					  size_t column)
{
	myGraphicsItem* item = new myGraphicsItem();
	item->setPixmap(sprite);
	scene.addItem(item);
	double x, y;
	getCoordsByTile(row, column, x, y);
	item->setCenter(x, y);
	Point coords;
	coords.first = row;
	coords.second = column;
	items[coords] = item;
}

void Board::placeDots()
{
	QPixmap dotSprite("pacman-art/other/dot.png");
	dotSprite = dotSprite.scaled(dotSprite.width() * 2, dotSprite.height() * 2);
	QPixmap strawberrySprite("pacman-art/other/strawberry.png");
	strawberrySprite = strawberrySprite.scaled(strawberrySprite.width() * 2,
											   strawberrySprite.height() * 2);

	for (size_t column = 0; column < MATRIX_COLUMNS; ++column) {
		for (size_t row = 0; row < MATRIX_ROWS; ++row) {
			if (matrix[row][column] == DOT) {
				placeItem(dots, dotSprite, row, column);
			}
			if (matrix[row][column] == STRAWBERRY) {
				placeItem(strawberries, strawberrySprite, row, column);
			}
			if (matrix[row][column] == EMPTY_DOT) {
				placeItem(dots, dotSprite, row, column);
				matrix[row][column] = DOT;
			}
			if (matrix[row][column] == EMPTY_STRAWBERRY) {
				placeItem(strawberries, strawberrySprite, row, column);
				matrix[row][column] = STRAWBERRY;
			}
		}
	}
}

void Board::placeTexts()
{
	QFont font("Emulogic", 12);
	highScoreText.setPlainText("HIGH SCORE");
	// highScoreText.setFont(QFont("Arial", 12));
	highScoreText.setFont(font);
	highScoreText.setDefaultTextColor(Qt::white);
	scene.addItem(&highScoreText);
	double highScoreTextX, highScoreTextY;
	getCoordsByTile(0, 8, highScoreTextX, highScoreTextY);
	highScoreTextY -= TILE_SIZE * 5;
	highScoreText.setPos(highScoreTextX, highScoreTextY);

	score = 0;
	std::string scoreString = std::to_string(score);
	scoreString = "00";
	scoreText.setPlainText(QString::fromStdString(scoreString));
	scoreText.setFont(font);
	scoreText.setDefaultTextColor(Qt::white);
	scene.addItem(&scoreText);
	double scoreTextX, scoreTextY;
	getCoordsByTile(0, 4, scoreTextX, scoreTextY);
	scoreTextY -= TILE_SIZE * 3;
	scoreText.setPos(scoreTextX, scoreTextY);
}

Board::~Board()
{
	ItemMap::iterator it;
	for (it = dots.begin(); it != dots.end(); it++) {
		delete it->second;
	}
	for (it = strawberries.begin(); it != strawberries.end(); it++) {
		delete it->second;
	}
}

void Board::updateScore(size_t points)
{
	score += points;
	std::string scoreString = std::to_string(score);
	scoreString = (scoreString.size() == 1) ? "0" + scoreString : scoreString;
	scoreText.setPlainText(QString::fromStdString(scoreString));
	lives = (score % 10000 == 0) ? lives + 1 : lives;
}

void Board::getCoordsByTile(size_t row, size_t column, double& x, double& y)
{
	double x1 = map.x(), y1 = map.y();
	double x2 = map.x2(), y2 = map.y2();
	double tileWidth = (x2 - x1) / MATRIX_COLUMNS;
	double tileHeight = (y2 - y1) / MATRIX_ROWS;

	x = x1 + column * tileWidth + tileWidth / 2;
	y = y1 + row * tileHeight + tileHeight / 2;
}

size_t Board::getTileByCoords(size_t& row, size_t& column, double x, double y)
{
	double x1 = map.x(), y1 = map.y();
	double x2 = map.x2(), y2 = map.y2();
	double tileWidth = (x2 - x1) / MATRIX_COLUMNS;
	double tileHeight = (y2 - y1) / MATRIX_ROWS;

	int i = int((y - y1) / tileHeight); // row
	int j = int((x - x1) / tileWidth);	// column

	if (i < 0 || i > MATRIX_ROWS - 1 || j < 0 || j > MATRIX_COLUMNS - 1) {
		return 0;
	}

	row = (size_t)i;
	column = (size_t)j;

	return matrix[row][column];
}

size_t Board::getTileByIndices(size_t row, size_t column)
{
	return matrix[row][column];
}
