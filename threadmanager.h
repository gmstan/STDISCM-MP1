#pragma once

#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include "ball.h"
#include <QThread>
#include <QVector>
#include <QString>
#include <QObject>
#include <QTimer>
#include <QMutex>
#include <QQueue>

class ThreadManager : public QObject
{
    Q_OBJECT

public:
    explicit ThreadManager(QObject *parent = nullptr);
    void updatePos(Ball *newBall, int startingPosX,int startingPosY,qreal dx,qreal dy);

signals:
    void threadStarted();
    void advanceBalls(int step);
    void ballPositionChanged(Ball *ball, int x, int y, qreal dx, qreal dy);
private:
    int maxSize;
    int currSize;
    QVector<Ball*> allBalls;
    QVector<Ball*> allNewBalls;
    QThread *currThread;
    QTimer *ballTimer;
    QMutex mutex;
    QQueue<QThread*> threadPool;

public slots:
    void connectBall(QVector<Ball*> balls);
    void timerCall();
};

#endif // THREADMANAGER_H
