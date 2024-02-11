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

    QTimer *ballTimer = new QTimer();
    connect(ballTimer, &QTimer::timeout, this, &ThreadManager::timerCall);
    ballTimer->start(20);
}


void ThreadManager::connectBall(Ball *ball){
    qInfo() << ball;
    qInfo() << "conecctBALL: " << QThread::currentThread();

    // if (!currThread) {
    QThread *ballThread = new QThread();
    ball->moveToThread(ballThread);
    // }
    connect(this, &ThreadManager::advanceBalls, ball, &Ball::moveBall);
    // Start the thread
    ballThread->start();


    // auto advanceWithArg = [ball]() {
    //     // Call the advance function of the Ball object with the argument
    //     ball->advance(1);
    // };

    // Connect the custom started signal to the lambda function
    // connect(this, &ThreadManager::threadStarted, advanceWithArg);

    // Start the timer and connect its timeout signal to a slot in the ThreadManager
    // ballTimer->start(20);
    // connect(ballTimer, &QTimer::timeout, this, [ball]() {
    //     ball->advance(1);
    // });
    allBalls.append(ball);
    ++currSize;
}

void ThreadManager::timerCall(){

    // for(int i=0;i<allBalls.size();i++){

    emit advanceBalls(1);
    // }
}

