#include "gamescene.h"
#include <QDebug>
#include <QTime>
#include <QTimer>

GameScene::GameScene(QObject *parent)
{
    lastTime = QTime::currentTime();
    frames = 0;
}


void GameScene::computeFPS()
{
    QTime currentTime = QTime::currentTime();
    int elapsedTime = lastTime.msecsTo(currentTime);
    lastTime = currentTime;

    if (elapsedTime > 0) {
        double fps = 2400.0 / elapsedTime;
        // frames++;
        currFPS = fps;
        qDebug() << "FPS:" << QString::number(fps, 'f', 2);
    }
}

qreal GameScene::getFPS()
{
    return currFPS;
}

