#include "EndScreen.h"

#define VIEW_SIZE 1000
#define BOARD_SIZE 1000 / 2

EndScreen::EndScreen()
{
    scene.setSceneRect(0, 0, VIEW_SIZE, VIEW_SIZE);
    QPixmap sprite("pacman-art/pac-man-logo.png");
    logo.setPixmap(sprite);
    scene.addItem(&logo);
    logo.setCenter(BOARD_SIZE, BOARD_SIZE / 2);
}

void EndScreen::setScores(size_t score, size_t highScore)
{
    QFont font("Emulogic", 12);
    std::string scoreString = std::to_string(score);
    scoreString = (scoreString.size() == 1) ? "0" + scoreString : scoreString;
    scoreText.setPlainText("HIGH SCORE: " + QString::fromStdString(scoreString));
    scoreText.setFont(font);
    scoreText.setDefaultTextColor(Qt::white);
    scene.addItem(&scoreText);
    scoreText.setPos(BOARD_SIZE / 2, BOARD_SIZE);
}