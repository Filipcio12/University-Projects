#pragma once

#include <QTimer>

#include "myGraphicsItem.h"
#include "Board.h"

class Player : public QObject{
  Q_OBJECT

  public:
    QPixmap sprite;
    myGraphicsItem body;
    std::string spritePath;
    std::string direction;
    size_t frame;
    QTimer* timer;

    Player();
    ~Player();
    void move(Board* board);
    void initPos(Board* board);
  
  signals:
    void scareGhosts();
    void victoryReset();

  public slots:
    void animateMovement();
  
  private:
    void eatDot(Board* board, size_t row, size_t column);
    void eatStrawberry(Board* board, size_t row, size_t column);
    void modifyPosition(Board* board, double& x, double& y);
};