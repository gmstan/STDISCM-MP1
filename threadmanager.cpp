#include "threadmanager.h"
#include "ball.h"
#include "qtimer.h"

ThreadManager::ThreadManager(QObject *parent)
    : QObject{parent}
{
    currSize = 0;
    maxSize = 8;
}


void ThreadManager::connectBall(QVector<Ball*> balls){

    for (int i=0;i<balls.size();i++){

        if(currSize>=maxSize || !currThread){
            qDebug() << "NEW THREAD";

            QThread *thread = new QThread();
            currThread = thread;
            currThread->start();
            currSize=0;
        }

        balls[i]->moveToThread(currThread);
        ++currSize;

        connect(this, &ThreadManager::advanceBalls, balls[i], &Ball::moveBall);
        connect(balls[i], &Ball::finish, this, &ThreadManager::updatePos);
    }
}

void ThreadManager::updatePos(Ball *ball, int x,int y,qreal dx,qreal dy){

    emit ballPositionChanged(ball, x,y, dx, dy);
    ball->setPos(x + dx, y + dy);
}

void ThreadManager::timerCall(){
    // emit advanceBalls(1);
    QMetaObject::invokeMethod(this, "advanceBalls", Qt::QueuedConnection, Q_ARG(int, 1));
}

