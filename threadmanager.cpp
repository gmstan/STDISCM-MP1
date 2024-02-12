#include "threadmanager.h"
#include "ball.h"
#include "qtimer.h"

ThreadManager::ThreadManager(QObject *parent)
    : QObject{parent}
{
    currSize = 0;
    maxSize = 4;
    // currThread = new QThread();
    // QVector<Ball*> allBalls;

    // QTimer *ballTimer = new QTimer();
    // connect(ballTimer, &QTimer::timeout, this, &ThreadManager::timerCall);
    // ballTimer->start(20);
}


void ThreadManager::connectBall(Ball *ball){
    qInfo() << "conecctBALL: " << QThread::currentThread();
    allBalls.append(ball);

    // Ball *test = new Ball(ball->startingPosX,ball->startingPosY,ball->speed,ball->angle);
    QThread *thread = new QThread();
    ball->moveToThread(thread);

    thread->start();

    // allNewBalls.append(test);
    // if (!currThread) {
    // QThread *ballThread = new QThread();
    // ball->moveToThread(this->thread());
    // }
    connect(this, &ThreadManager::advanceBalls, ball, &Ball::moveBall);
    connect(ball, &Ball::finish, this, &ThreadManager::updatePos);
    // Start the thread

    ++currSize;
}

void ThreadManager::updatePos(Ball *ball, int x,int y,qreal dx,qreal dy){
    // int j=0;
    // for(int i=0;i<allBalls.size();i++){
    //     allBalls.
    // }
    emit ballPositionChanged(ball, x,y, dx, dy);
    // newBall->setPos(x+dx,y+dy);

}

void ThreadManager::timerCall(){

    // for(int i=0;i<allBalls.size();i++){

    emit advanceBalls(1);
    // }
}

