#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ball.h"
#include "wall.h"
#include "threadmanager.h"
#include "gamescene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new GameScene(this);
    ui->field->setScene(scene);

    fpsLabel = ui->fpsCounterLabel;
    fpsLabel->setText("FPS: 0");

    fpsTimer = new QTimer(this);
    connect(fpsTimer, SIGNAL(timeout()), this, SLOT(displayFPS()));
    fpsTimer->start(500);

    ui->field->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->field->setFixedSize(1287, 727);
    ui->field->setRenderHint(QPainter::Antialiasing, true);
    ui->field->setSceneRect(0, 0, ui->field->width()*2, ui->field->height()*2);

    QTransform transform;
    transform.translate(0, ui->field->height());
    transform.scale(0.50, -0.50);
    ui->field->setTransform(transform);

    ui->field->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->field->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Wall *bottomwall = new Wall(0, -1, 2571, -1);
    Wall *topwall = new Wall(0, 1451, 2571, 1451);
    Wall *leftwall = new Wall(-1, 0, -1, 1451);
    Wall *rightwall = new Wall(2571, 0, 2571, 1451);
    scene->addItem(topwall);
    scene->addItem(bottomwall);
    scene->addItem(leftwall);
    scene->addItem(rightwall);

    threadManager = new ThreadManager(this);

    connect(this, &MainWindow::ballCreated, threadManager, &ThreadManager::connectBall);

    fpsCountTimer = new QTimer(this);
    connect(fpsCountTimer, &QTimer::timeout, scene, &GameScene::computeFPS);
    fpsCountTimer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayFPS()
{
    double fps = scene->getFPS();
    fpsLabel->setText(QString("FPS: ") + QString::number(fps, 'f', 1));
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    ++frameCount;
}

void MainWindow::updateBallPosition(Ball *ball, int x, int y, qreal dx, qreal dy)
{
    ball->setPos(x + dx, y + dy);
}


int numBalls;
qreal speed, angle, startPosX, startPosY, endPosX, endPosY, finalAngle, finalSpeed;

//Adding a Single Ball
void MainWindow::on_addBall_clicked()
{
    startPosX = ui->xInput->text().toInt();
    startPosY = ui->yInput->text().toInt();
    speed = ui->velocityInput->text().toDouble();
    angle = ui->directionInput->text().toDouble();

    Ball *ball = new Ball(startPosX, startPosY, speed, angle);
    scene->addItem(ball);
    connect(threadManager, &ThreadManager::ballPositionChanged, this, &MainWindow::updateBallPosition);

    QVector<Ball*> balls;
    balls.append(ball);
    emit ballCreated(balls);

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

    QVector<Ball*> balls;

    for (int i=0; i<numBalls;++i) {
        qreal currPosX = startPosX + i * deltaX;
        qreal currPosY = startPosY + i * deltaY;

        Ball *ball = new Ball(currPosX, currPosY, speed, angle);
        scene->addItem(ball);
        balls.append(ball);
    }
    emit ballCreated(balls);

    ui->velocityInput1->setText("");
    ui->directionInput1->setText("");
    ui->startXInput->setText("");
    ui->endXInput->setText("");
    ui->startYInput->setText("");
    ui->endYInput->setText("");
    ui->numBallsInput1->setText("");
}

//Adding Multiple Balls with a range of directions
void MainWindow::on_addBall2_clicked()
{
    startPosX = ui->xInput2->text().toInt();
    startPosY = ui->yInput2->text().toInt();
    speed = ui->velocityInput2->text().toDouble();
    angle = ui->initialDirectionInput->text().toDouble();
    finalAngle = ui->finalDirectionInput->text().toDouble();
    numBalls = ui->numBallsInput2->text().toInt();

    qreal deltaAngle = (finalAngle - angle) / (numBalls - 1);

    QVector<Ball*> balls;
    for (int i = 0; i < numBalls; ++i) {
        qreal newAngle = angle + i * deltaAngle;
        Ball *ball = new Ball(startPosX, startPosY, speed, newAngle);
        scene->addItem(ball);
        balls.append(ball);
    }
    emit ballCreated(balls);

    ui->xInput2->setText("");
    ui->yInput2->setText("");
    ui->velocityInput2->setText("");
    ui->initialDirectionInput->setText("");
    ui->finalDirectionInput->setText("");
    ui->numBallsInput2->setText("");
}

//Adding Multiple Balls with a range of velocities
void MainWindow::on_addBall3_clicked()
{
    startPosX = ui->xInput3->text().toInt();
    startPosY = ui->yInput3->text().toInt();
    speed = ui->initialVelocityInput->text().toDouble();
    finalSpeed = ui->finalVelocityInput->text().toDouble();
    angle = ui->directionInput3->text().toDouble();
    numBalls = ui->numBallsInput3->text().toInt();

    qreal deltaSpeed = (finalSpeed - speed) / (numBalls + 1);
    QVector<Ball*> balls;
    for (int i = 0; i < numBalls; ++i) {
        qreal newSpeed = speed + i * deltaSpeed;
        Ball *ball = new Ball(startPosX, startPosY, newSpeed, angle);
        scene->addItem(ball);
        balls.append(ball);
    }
    emit ballCreated(balls);

    ui->xInput3->setText("");
    ui->yInput3->setText("");
    ui->initialVelocityInput->setText("");
    ui->finalVelocityInput->setText("");
    ui->directionInput3->setText("");
    ui->numBallsInput3->setText("");
}

int xStart, xEnd, yStart, yEnd;

//Adding a wall in the scene
void MainWindow::on_addWall_clicked()
{
    xStart = ui->wallXStart->text().toInt();
    yStart = ui->wallYStart->text().toInt();
    xEnd = ui->wallXEnd->text().toInt();
    yEnd = ui->wallYEnd->text().toInt();

    Wall *wall = new Wall(xStart*2, yStart*2, xEnd*2, yEnd*2);
    scene->addItem(wall);

    ui->wallXStart->setText("");
    ui->wallYStart->setText("");
    ui->wallXEnd->setText("");
    ui->wallYEnd->setText("");
}
