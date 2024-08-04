#include "Game.h"

#include <QApplication>
#include <QDesktopWidget>

void Game::setTimer()
{
    timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(16); // 60 FPS
}

void Game::setMainWindow()
{
    QDesktopWidget* desktop = QApplication::desktop();
	int x = (desktop->width() - VIEW_SIZE) / 2;
	int y = (desktop->height() - VIEW_SIZE) / 2;
	mainWindow.setGeometry(x, y, VIEW_SIZE, VIEW_SIZE);
	mainWindow.setWindowTitle("Pac-Man");
}

void Game::setView()
{
    view = new QGraphicsView(/*&mainWindow*/);
	view->setScene(&board.scene);
	view->setWindowTitle("Pac-Man");
	view->resize(VIEW_SIZE, VIEW_SIZE);
	QBrush backgroundColor(Qt::black);
	view->setBackgroundBrush(backgroundColor);
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Game::setPlayer()
{
    board.scene.addItem(&player.body);
	player.initPos(&board);
	keyInputHandler = new KeyInputHandler(&player);
	mainWindow.installEventFilter(keyInputHandler);
	view->installEventFilter(keyInputHandler);
	// mainWindow.show();
	view->show();
}

void Game::setGhosts()
{
    blinky.setSprite("pacman-art/ghosts/blinky.png");
	pinky.setSprite("pacman-art/ghosts/pinky.png");
	inky.setSprite("pacman-art/ghosts/inky.png");
	clyde.setSprite("pacman-art/ghosts/clyde.png");

	board.scene.addItem(&blinky.body);
	blinky.initPos(&board);
	board.scene.addItem(&pinky.body);
	pinky.initPos(&board);
	board.scene.addItem(&inky.body);
	inky.initPos(&board);
	board.scene.addItem(&clyde.body);
	clyde.initPos(&board);
}

void Game::setSignals()
{
    QObject::connect(&player, SIGNAL(scareGhosts()), &blinky, SLOT(getScared()));
	QObject::connect(&player, SIGNAL(scareGhosts()), &pinky, SLOT(getScared()));
	QObject::connect(&player, SIGNAL(scareGhosts()), &inky, SLOT(getScared()));
	QObject::connect(&player, SIGNAL(scareGhosts()), &clyde, SLOT(getScared()));

	QObject::connect(&blinky, SIGNAL(playerCaught()), this,
					 SLOT(playerCaught()));
	QObject::connect(&pinky, SIGNAL(playerCaught()), this,
					 SLOT(playerCaught()));
	QObject::connect(&inky, SIGNAL(playerCaught()), this, SLOT(playerCaught()));
	QObject::connect(&clyde, SIGNAL(playerCaught()), this,
					 SLOT(playerCaught()));

	QObject::connect(&player, SIGNAL(victoryReset()), this,
					 SLOT(victoryReset()));
}

Game::Game()
{
    setTimer();
    setMainWindow();
    setView();
	setPlayer();
	setGhosts();
	setSignals();
}

Game::~Game()
{
	delete view;
	delete keyInputHandler;
	delete timer;
}

void Game::update()
{
	player.move(&board);
	blinky.setTarget(&board, player);
	pinky.setTarget(&board, player);
	inky.setTarget(&board, player, blinky);
	clyde.setTarget(&board, player);
	view->viewport()->update();
}

void Game::playerCaught()
{
	board.lives--;
	if (board.lives > 0) {
		player.initPos(&board);
		blinky.initPos(&board);
		pinky.initPos(&board);
		inky.initPos(&board);
		clyde.initPos(&board);
	}
	else {
		// Move to end screen
		timer->stop();
		view->setScene(&endScreen.scene);
		endScreen.setScores(board.score, 0);
	}
}

void Game::victoryReset()
{
	player.initPos(&board);
	blinky.initPos(&board);
	pinky.initPos(&board);
	inky.initPos(&board);
	clyde.initPos(&board);
	board.placeDots();
}
