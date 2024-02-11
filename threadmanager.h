#pragma once

#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include "ball.h"
#include <QThread>
#include <QVector>
#include <QString>
#include <QObject>
#include <QTimer>

class ThreadManager : public QObject
{
    Q_OBJECT

public:
    explicit ThreadManager(QObject *parent = nullptr);

signals:
    void threadStarted(); // Custom signal for indicating thread start
    void advanceBalls(int step);

private:
    int maxSize;
    int currSize;
    QVector<Ball*> allBalls;
    QThread *currThread;
    QTimer *ballTimer;

public slots:
    void connectBall(Ball *ball);
    void timerCall();


};

#endif // THREADMANAGER_H
