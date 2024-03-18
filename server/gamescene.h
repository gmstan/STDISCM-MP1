#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTime>
#include <QDebug>
#include <QTimer>

class GameScene : public QGraphicsScene
{
public:
    GameScene(QObject *parent = nullptr);
    qreal getFPS();

public slots:
    void computeFPS();

private:
    int fps;
    QTime lastTime;
    int frames;
    qreal currFPS;

};

#endif
