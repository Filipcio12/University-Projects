#pragma once

#include "Board.h"
#include "Player.h"
#include "myGraphicsItem.h"

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

#define SCATTER 0
#define CHASE 1

typedef std::pair<double, double> Pos;

class Ghost : public QObject {
	Q_OBJECT

  public:
	QPixmap sprite;
	QPixmap blueGhost;
	Pos nextPos;
	myGraphicsItem body;
	size_t mode;
	size_t direction;
	bool scared;

	Ghost();
	void move(Board* board, const Player& player, double targetX,
			  double targetY);
	void initPos(Board* board);
	virtual void setTarget(Board* board, const Player& player);
	void setSprite(std::string spritePath);

  signals:
	void playerCaught();

  public slots:
	void switchMode();
	void getScared();
	void calmDown();
};
