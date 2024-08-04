#pragma once

#include <QWidget>
#include <QKeyEvent>

#include "Player.h"

class KeyInputHandler : public QObject {
    Q_OBJECT

    public:
        KeyInputHandler(Player* player, QObject* parent = nullptr) 
            : QObject(parent), player(player) {}
    
    protected:
        bool eventFilter(QObject* obj, QEvent* event) override
        {
            if (event->type() == QEvent::KeyPress)
            {
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
            switch (key)
            {
            case Qt::Key_A:
                player->direction = "left";
                break;
            case Qt::Key_D:
                player->direction = "right";
                break;
            case Qt::Key_S:
                player->direction = "down";
                break;
            case Qt::Key_W:
                player->direction = "up";
                break;
            }
        }
};