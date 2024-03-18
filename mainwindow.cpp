#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ball.h"
#include "wall.h"
#include "threadmanager.h"
#include "gamescene.h"
#include "sprite.h"
#include "server.h"


#include <QGraphicsPolygonItem>
#include <QPolygonF>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->movementKeys->hide();

    scene = new GameScene(this);
    ui->field->setScene(scene);

    fpsLabel = ui->fpsCounterLabel;
    fpsLabel->setText("FPS: 0");

    fpsTimer = new QTimer(this);
    connect(fpsTimer, SIGNAL(timeout()), this, SLOT(displayFPS()));
    fpsTimer->start(500);

    ui->field->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // ui->field->setFixedSize(1287, 727);
    ui->field->setFixedSize(1317, 747);
    // ui->field->setFixedSize(1357, 787);
    ui->field->setRenderHint(QPainter::Antialiasing, true);
    ui->field->setSceneRect(-30, -20, ui->field->width()*2, ui->field->height()*2);

    QTransform transform;
    transform.translate(0, ui->field->height());
    transform.scale(0.50, -0.50);
    ui->field->setTransform(transform);

    ui->field->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->field->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Wall *bottomwall = new Wall(0, -20, 2571, -20, 40);
    Wall *topwall = new Wall(0, 1470, 2571, 1470, 40);
    Wall *leftwall = new Wall(-30, 0, -30, 1451, 60);
    Wall *rightwall = new Wall(2600, 0, 2600, 1451, 60);
    scene->addItem(topwall);
    scene->addItem(bottomwall);
    scene->addItem(leftwall);
    scene->addItem(rightwall);

    threadManager = new ThreadManager(this);

    connect(this, &MainWindow::ballCreated, threadManager, &ThreadManager::connectBall);

    fpsCountTimer = new QTimer(this);
    connect(fpsCountTimer, &QTimer::timeout, scene, &GameScene::computeFPS);
    fpsCountTimer->start(20);

    ui->stopExplore->setEnabled(false);
    connect(ui->left, &QPushButton::clicked, this, &MainWindow::moveSpriteLeft);
    connect(ui->right, &QPushButton::clicked, this, &MainWindow::moveSpriteRight);
    connect(ui->up, &QPushButton::clicked, this, &MainWindow::moveSpriteUp);
    connect(ui->down, &QPushButton::clicked, this, &MainWindow::moveSpriteDown);
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


void MainWindow::on_startExplore_clicked()
{
    // Calculate the center position of the transformed view
    qreal centerX = ui->field->viewport()->width() / 2.0;
    qreal centerY = ui->field->viewport()->height() / 2.0;

    // Map the center position from viewport coordinates to scene coordinates
    QPointF centerScenePos = ui->field->mapToScene(QPoint(centerX, centerY));

    // Create and add the sprite at the center position
    Sprite *sprite = new Sprite();
    scene->addItem(sprite);

    if (spriteX == -100 && spriteY == -100){
        sprite->setPos(-5,-20);
        // sprite->setPos(2520,-20);
        // sprite->setPos(2520,-20);

        spriteX = -5;
        spriteY = -20;
    }
    else{
        sprite->setPos(spriteX,spriteY);
    }
    moveViewToCenter(sprite);

    qDebug() << centerScenePos;
    qDebug() << QPointF(sprite->boundingRect().width() / 2.0, sprite->boundingRect().height() / 2.0);
    qDebug() << sprite->x();
    qDebug() << sprite->y();

    QTransform transform;
    // Apply your transformation
    transform.scale(17, -15);
    ui->field->setTransform(transform);

    ui->ballConfig->hide();
    ui->movementKeys->show();
    ui->startExplore->setEnabled(false);
    ui->stopExplore->setEnabled(true);
}

void MainWindow::moveSpriteLeft() {
    if (scene) {
        QList<QGraphicsItem*> items = scene->items();
        for (QGraphicsItem* item : items) {
            Sprite* sprite = dynamic_cast<Sprite*>(item);
            if (sprite) {
                if (sprite->x() - 5 < -35){
                    moveViewToCenter(sprite);
                } else {
                    // Move the sprite left by a certain amount
                    sprite->setX(sprite->x() - 5); // Adjust the value as needed
                    moveViewToCenter(sprite);
                }
                qDebug() << sprite->x();
                spriteX = sprite->x();
            }
        }
    }
}

void MainWindow::moveSpriteRight() {
    if (scene) {
        QList<QGraphicsItem*> items = scene->items();
        for (QGraphicsItem* item : items) {
            Sprite* sprite = dynamic_cast<Sprite*>(item);
            if (sprite) {
                if (sprite->x() + 5 > 2520){
                    moveViewToCenter(sprite);
                } else {
                    // Move the sprite right by a certain amount
                    sprite->setX(sprite->x() + 5); // Adjust the value as needed
                    moveViewToCenter(sprite);
                }
                qDebug() << sprite->x();
                spriteX = sprite->x();
            }
        }
    }
}

void MainWindow::moveSpriteUp() {
    if (scene) {
        QList<QGraphicsItem*> items = scene->items();
        for (QGraphicsItem* item : items) {
            Sprite* sprite = dynamic_cast<Sprite*>(item);
            if (sprite) {
                if (sprite->y() + 5 > 1390){
                    moveViewToCenter(sprite);
                } else {
                    // Move the sprite up by a certain amount
                    sprite->setY(sprite->y() + 5); // Adjust the value as needed
                    moveViewToCenter(sprite);
                }
                qDebug() << sprite->y();
                spriteY = sprite->y();
            }
        }
    }
}

void MainWindow::moveSpriteDown() {
    if (scene) {
        QList<QGraphicsItem*> items = scene->items();
        for (QGraphicsItem* item : items) {
            Sprite* sprite = dynamic_cast<Sprite*>(item);
            if (sprite) {
                if (sprite->y() - 5 < -35){
                    sprite->setY(sprite->y());
                } else {
                    // Move the sprite down by a certain amount
                    sprite->setY(sprite->y() - 5); // Adjust the value as needed
                    moveViewToCenter(sprite);
                }
                qDebug() << sprite->y();
                spriteY = sprite->y();
            }
        }
    }
}

void MainWindow::moveViewToCenter(Sprite *sprite) {
    if (!sprite || !scene) return;

    // Get the position of the sprite in scene coordinates
    QPointF spritePos = sprite->scenePos();

    // Get the current scale factor of the viewport
    qreal scaleFactorX = ui->field->transform().m11(); // X scale factor
    qreal scaleFactorY = ui->field->transform().m22(); // Y scale factor

    // Calculate the difference between the sprite position and the center of the view, scaled by the current scale factor
    qreal dx = ui->field->viewport()->width() / 2.0;
    qreal dy = ui->field->viewport()->height() / 2.0;

    // Adjust the view's center position based on the calculated difference
    ui->field->centerOn(spritePos + QPointF(dx/16, dy/8));
}

void MainWindow::on_stopExplore_clicked()
{
    // Remove the sprite from the scene
    if (scene) {
        QList<QGraphicsItem*> items = scene->items();
        for (QGraphicsItem* item : items) {
            Sprite* sprite = dynamic_cast<Sprite*>(item);
            if (sprite) {
                scene->removeItem(sprite);
                delete sprite; // Optionally delete the sprite if you're not using it anymore
                break; // Assuming there's only one sprite, so we can exit the loop after removing it
            }
        }
    }
    ui->ballConfig->show();
    ui->movementKeys->hide();
    ui->startExplore->setEnabled(true);
    ui->stopExplore->setEnabled(false);
    // Restore the original transformation
    QTransform transform;
    transform.scale(0.50, -0.50);
    ui->field->setTransform(transform);
}

