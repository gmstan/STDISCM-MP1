#include "threadmanager.h"
#include "ball.h"
#include "qtimer.h"

ThreadManager::ThreadManager(QObject *parent)
    : QObject{parent}
{
    currSize = 0;
    maxSize = 4;
}


void ThreadManager::connectBall(QVector<Ball*> balls){
    qInfo() << "conecctBALL: " << QThread::currentThread();

    for (int i=0;i<balls.size();i++){
        QThread *thread = new QThread();
        balls[i]->moveToThread(thread);
        thread->start();
        connect(this, &ThreadManager::advanceBalls, balls[i], &Ball::moveBall);
        connect(balls[i], &Ball::finish, this, &ThreadManager::updatePos);
    }


    // connect(this, &ThreadManager::advanceBalls, ball, &Ball::moveBall);
    // connect(ball, &Ball::finish, this, &ThreadManager::updatePos);
    // Start the thread

    ++currSize;
}

void ThreadManager::updatePos(Ball *ball, int x,int y,qreal dx,qreal dy){

    emit ballPositionChanged(ball, x,y, dx, dy);
    ball->setPos(x + dx, y + dy);
}

void ThreadManager::timerCall(){
    emit advanceBalls(1);
}

