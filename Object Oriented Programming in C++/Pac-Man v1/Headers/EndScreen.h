#pragma once

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "myGraphicsItem.h"

class EndScreen {
    public:
        QGraphicsScene scene;
        myGraphicsItem logo;
        QGraphicsTextItem replayText;
        QGraphicsTextItem quitText;
        QGraphicsTextItem scoreText;
        QGraphicsTextItem highScoreText;
    
        EndScreen();
        void setScores(size_t score, size_t highScore);
};