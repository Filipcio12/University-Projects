#include "Game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Game game;
    
    // Setting up debug text
    /*QGraphicsTextItem textItem(QString::number(board.matrix[0][27]));
    textItem.setDefaultTextColor(Qt::white);
    textItem.setPos(100, 0);
    board.scene.addItem(&textItem);*/

    return app.exec();
}