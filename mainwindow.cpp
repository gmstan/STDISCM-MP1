#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ball.h"
#include "wall.h"
#include "threadmanager.h"

#include <QThreadPool>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create a scene for the graphics view
    scene = new QGraphicsScene(this);
    ui->field->setScene(scene);

    // Create a label to display FPS
    fpsLabel = ui->fpsCounterLabel;
    fpsLabel->setText("FPS: 0");

    // Setup a timer to update FPS
    fpsTimer = new QTimer(this);
    connect(fpsTimer, SIGNAL(timeout()), this, SLOT(updateFPS()));
    fpsTimer->start(500); // Update every half-second

    // Initialize frame count
    frameCount = 0;

    // //Setup a timer to move the ball
    // ballTimer = new QTimer(this);
    // connect(ballTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    // ballTimer->start(20); // Move the ball every 20 milliseconds

    // Lock the size of the graphics view
    ui->field->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->field->setFixedSize(1280, 720); // Set your desired size

    // Set the bottom-left corner of the QGraphicsView to be (0,0)
    ui->field->setRenderHint(QPainter::Antialiasing, true);
    ui->field->setSceneRect(0, 0, ui->field->width(), ui->field->height());

    // Apply a transformation to the view
    QTransform transform;
    transform.translate(0, ui->field->height());
    transform.scale(1, -1);
    ui->field->setTransform(transform);

    // Disable scrollbars
    ui->field->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->field->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // creating walls on the borders
    Wall *bottomwall = new Wall(0, 0, 1280, 0);
    Wall *topwall = new Wall(0, 720, 1280, 720);
    Wall *leftwall = new Wall(0, 0, 0, 720);
    Wall *rightwall = new Wall(1280, 0, 1280, 720);
    scene->addItem(topwall);
    scene->addItem(bottomwall);
    scene->addItem(leftwall);
    scene->addItem(rightwall);


    threadManager = new ThreadManager(this);
    QThread *thread = new QThread(this);
    threadManager->moveToThread(thread);
    connect(thread, &QThread::started, threadManager, &ThreadManager::timerCall);
    thread->start();
    connect(this, &MainWindow::ballCreated, threadManager, &ThreadManager::connectBall);

    QTimer *ballTimer = new QTimer(threadManager); // Pass threadManager as parent
    connect(ballTimer, &QTimer::timeout, threadManager, &ThreadManager::timerCall);
    ballTimer->start(20);


    // QThreadPool threadPool = new QThreadPool(this);
    // threadPool.setMaxThreadCount(20);


    // ballTimer = new QTimer(this);
    // connect(ballTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    // ballTimer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFPS()
{
    // Calculate FPS
    int frames = frameCount;
    frameCount = 0;

    // Update the FPS label
    fpsLabel->setText("FPS: " + QString::number(frames));
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    // Increment frame count
    ++frameCount;
    // Your painting code goes here
}

int numBalls;
qreal speed, angle, startPosX, startPosY, endPosX, endPosY, finalAngle, finalSpeed;

//Adding a Single Ball
void MainWindow::on_addBall_clicked()
{
    // variables, starting position X and Y, number of balls, ball speed, ball direction
    startPosX = ui->xInput->text().toInt();
    startPosY = ui->yInput->text().toInt();
    speed = ui->velocityInput->text().toDouble();
    angle = ui->directionInput->text().toDouble();

    Ball *ball = new Ball(startPosX, startPosY, speed, angle);
    // threadManager->connectBall(ball);
    scene->addItem(ball);
    emit ballCreated(ball);

    // QThread *thread = new QThread();

    // ball->moveToThread(thread);

    // connect(thread, &QThread::started, ball, &Ball::advance);

    // connect(Ball, &Ball::, threadManager, SLOT(connectBall(ball)));
    qInfo() << "main: " << QThread::currentThread();

    // threadManager->connectBall(ball);

    // thread->start();



    // clearing of input fields
    ui->xInput->setText("");
    ui->yInput->setText("");
    ui->velocityInput->setText("");
    ui->directionInput->setText("");
}

//Adding Multiple Balls within a certain range of X and Y
void MainWindow::on_addBall1_clicked()
{
    speed = ui->velocityInput1->text().toDouble();
    angle = ui->directionInput1->text().toDouble();
    startPosX = ui->startXInput->text().toInt();
    endPosX = ui->endXInput->text().toInt();
    startPosY = ui->startYInput->text().toInt();
    endPosY = ui->endYInput->text().toInt();
    numBalls = ui->numBallsInput1->text().toInt();

    qreal deltaX = (endPosX - startPosX) / (numBalls + 1);
    qreal deltaY = (endPosY - startPosY) / (numBalls + 1);

    for (int i=0; i<numBalls;++i) {
        qreal currPosX = startPosX + i * deltaX;
        qreal currPosY = startPosY + i * deltaY;

        Ball *ball = new Ball(currPosX, currPosY, speed, angle);
        scene->addItem(ball);
    }

    ui->velocityInput1->setText("");
    ui->directionInput1->setText("");
    ui->startXInput->setText("");
    ui->endXInput->setText("");
    ui->startYInput->setText("");
    ui->endYInput->setText("");
    ui->numBallsInput1->setText("");
}

void MainWindow::on_addBall2_clicked()
{
    startPosX = ui->xInput2->text().toInt();
    startPosY = ui->yInput2->text().toInt();
    speed = ui->velocityInput2->text().toDouble();
    angle = ui->initialDirectionInput->text().toDouble();
    finalAngle = ui->finalDirectionInput->text().toDouble();
    numBalls = ui->numBallsInput2->text().toInt();

    qreal deltaAngle = (finalAngle - angle) / (numBalls + 1);

    for (int i = 0; i < numBalls; ++i) {
        qreal newAngle = deltaAngle + i * deltaAngle;
        Ball *ball = new Ball(startPosX, startPosY, speed, newAngle);
        scene->addItem(ball);
    }

    ui->xInput2->setText("");
    ui->yInput2->setText("");
    ui->velocityInput2->setText("");
    ui->initialDirectionInput->setText("");
    ui->finalDirectionInput->setText("");
    ui->numBallsInput2->setText("");
}

void MainWindow::on_addBall3_clicked()
{
    startPosX = ui->xInput3->text().toInt();
    startPosY = ui->yInput3->text().toInt();
    speed = ui->initialVelocityInput->text().toDouble();
    finalSpeed = ui->finalVelocityInput->text().toDouble();
    angle = ui->directionInput3->text().toDouble();
    numBalls = ui->numBallsInput3->text().toInt();

    qreal deltaSpeed = (finalSpeed - speed) / (numBalls + 1);
    for (int i = 0; i < numBalls; ++i) {
        qreal newSpeed = speed + i * deltaSpeed;
        Ball *ball = new Ball(startPosX, startPosY, newSpeed, angle);
        scene->addItem(ball);
    }

    ui->xInput3->setText("");
    ui->yInput3->setText("");
    ui->initialVelocityInput->setText("");
    ui->finalVelocityInput->setText("");
    ui->directionInput3->setText("");
    ui->numBallsInput3->setText("");
}

int xStart, xEnd, yStart, yEnd;

void MainWindow::on_addWall_clicked()
{
    xStart = ui->wallXStart->text().toInt();
    yStart = ui->wallYStart->text().toInt();
    xEnd = ui->wallXEnd->text().toInt();
    yEnd = ui->wallYEnd->text().toInt();

    Wall *wall = new Wall(xStart, yStart, xEnd, yEnd);
    scene->addItem(wall);

    ui->wallXStart->setText("");
    ui->wallYStart->setText("");
    ui->wallXEnd->setText("");
    ui->wallYEnd->setText("");
}






