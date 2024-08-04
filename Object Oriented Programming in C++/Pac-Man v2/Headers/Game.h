#pragma once

#include <QGraphicsView>
#include <QMainWindow>
#include <QObject>
#include <QTimer>

#include "Blinky.h"
#include "Board.h"
#include "Clyde.h"
#include "EndScreen.h"
#include "Inky.h"
#include "KeyInputHandler.h"
#include "Pinky.h"
#include "Player.h"

class Game : public QObject {
	Q_OBJECT

  public:
	Game();
	~Game();

  public slots:
	void update();
	void playerCaught();
	void victoryReset();

  private:
	Board board;
	EndScreen endScreen;
	Player player;
	Blinky blinky;
	Pinky pinky;
	Inky inky;
	Clyde clyde;
	KeyInputHandler* keyInputHandler;
	QGraphicsView* view;
	QMainWindow mainWindow;
	QTimer* timer;

    void setTimer();
    void setMainWindow();
    void setView();
    void setPlayer();
    void setGhosts();
    void setSignals();
};
