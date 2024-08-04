#pragma once

#include <QKeyEvent>
#include <QWidget>

#include "Player.h"

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

class KeyInputHandler : public QObject {
	Q_OBJECT

  public:
	KeyInputHandler(Player* player, QObject* parent = nullptr)
		: QObject(parent), player(player)
	{
	}

  protected:
	bool eventFilter(QObject* obj, QEvent* event) override
	{
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			handleKeyPress(keyEvent);
			return true;
		}
		return QObject::eventFilter(obj, event);
	}

  private:
	Player* player;

	void handleKeyPress(QKeyEvent* keyEvent)
	{
		int key = keyEvent->key();
		switch (key) {
		case Qt::Key_A:
			player->dir = LEFT;
			break;
		case Qt::Key_D:
			player->dir = RIGHT;
			break;
		case Qt::Key_S:
			player->dir = DOWN;
			break;
		case Qt::Key_W:
			player->dir = UP;
			break;
		}
	}
};
