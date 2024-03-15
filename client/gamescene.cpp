#include "gamescene.h"

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
        currFPS = fps;
    }
}

qreal GameScene::getFPS()
{
    return currFPS;
}

