#include "threadmanager.h"
#include "ball.h"
#include "qtimer.h"

ThreadManager::ThreadManager(QObject *parent)
    : QObject{parent}
{
    currSize = 0;
    maxSize = 16;
    ballTimer = new QTimer();
    ballTimer->start(20);

    for (int i = 0; i < 100; ++i) {
        QThread *thread = new QThread(this);
        threadPool.enqueue(thread);
        thread->start();
    }
}

void ThreadManager::connectBall(QVector<Ball*> balls){

    for (int i=0;i<balls.size();i++){
        if (threadPool.isEmpty()) {
            for (int i = 0; i < 10; ++i) {
                QThread *thread = new QThread(this);
                threadPool.enqueue(thread);
                thread->start();
            }
        }

        if(currSize>=maxSize || !currThread){
            QThread *thread = threadPool.dequeue();
            currThread = thread;
            currThread->start();
            currSize=0;
        }

        balls[i]->moveToThread(currThread);
        ++currSize;

        connect(ballTimer, &QTimer::timeout, balls[i], [=](){
            QMutexLocker locker(&mutex);
            balls[i]->moveBall(1);
        });
        connect(balls[i], &Ball::finish, this, &ThreadManager::updatePos);
    }
}

void ThreadManager::updatePos(Ball *ball, int x,int y,qreal dx,qreal dy){
    emit ballPositionChanged(ball, x,y, dx, dy);

    QMutexLocker locker(&mutex);
    ball->setPos(x + dx, y + dy);
}

void ThreadManager::timerCall(){
    QMetaObject::invokeMethod(this, "advanceBalls", Qt::QueuedConnection, Q_ARG(int, 1));
}

