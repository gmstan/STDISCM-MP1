#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ball.h"
#include "wall.h"
#include "threadmanager.h"
#include "gamescene.h"
#include "sprite.h"


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
    ui->field->setFixedSize(1317, 747);
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
    ui->movementKeys->show();
    connect(ui->left, &QPushButton::clicked, this, &MainWindow::moveSpriteLeft);
    connect(ui->right, &QPushButton::clicked, this, &MainWindow::moveSpriteRight);
    connect(ui->up, &QPushButton::clicked, this, &MainWindow::moveSpriteUp);
    connect(ui->down, &QPushButton::clicked, this, &MainWindow::moveSpriteDown);


    // QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 1234);
    if (!socket.waitForConnected()) {
        qDebug() << "Unable to connect to server.";
    }
    else{
        qDebug() << "Connected to server.";
    }

    // Send data to server
    QString message = "Hello, server!";
    socket.write(message.toUtf8());
    socket.flush();


    // QObject::connect(&socket, &QTcpSocket::readyRead, [&]() {
    //     QByteArray data = socket.readAll();
    //     qDebug() << "Received: " << data;
    // });



    // QTcpSocket *socket = new QTcpSocket(this); // Create a pointer to QTcpSocket
    // socket->connectToHost("127.0.0.1", 1234);
    // if (!socket->waitForConnected()) {
    //     qDebug() << "Unable to connect to server.";
    // }
    // else{
    //     qDebug() << "Connected to server.";
    // }

    // // Send data to server
    // QString message = "Hello, server!";
    // socket->write(message.toUtf8());
    // socket->flush();

    // QObject::connect(socket, &QTcpSocket::readyRead, this, [=]() {
    //     QByteArray data = socket->readAll();
    //     qDebug() << "Received: " << data;
    // });
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


int xStart, xEnd, yStart, yEnd;

void MainWindow::on_startExplore_clicked()
{
    qreal centerX = ui->field->viewport()->width() / 2.0;
    qreal centerY = ui->field->viewport()->height() / 2.0;
    QPointF centerScenePos = ui->field->mapToScene(QPoint(centerX, centerY));

    if (spriteX == -100 && spriteY == -100){
        spriteX = 30;
        spriteY = 20;
    }

    QString message = "newSprite,";
    message.append(QString::number(spriteX));
    message.append(",");
    message.append(QString::number(spriteY));

    qDebug() << message;
    socket.write(message.toUtf8());
    socket.flush();

    if (!socket.waitForReadyRead(3000)) { // Wait for 3 seconds
        qDebug() << "Timeout: No data received from the socket.";
        return; // Return or handle the error accordingly
    }

    QByteArray data = socket.readAll();
    qDebug() << "data: " << data;
    int id = data.toInt();
    qDebug() << "id: " << id;

    Sprite *sprite = new Sprite(id);
    scene->addItem(sprite);

    sprite->setPos(spriteX,spriteY);
    moveViewToCenter(sprite);

    qDebug() << sprite->x();
    qDebug() << sprite->y();

    QTransform transform;
    // Apply your transformation
    transform.scale(17, -15);
    ui->field->setTransform(transform);

    ui->movementKeys->setEnabled(true);
    ui->startExplore->setEnabled(false);
    ui->stopExplore->setEnabled(true);
}

void MainWindow::moveSpriteLeft() {
    if (scene) {
        QList<QGraphicsItem*> items = scene->items();
        for (QGraphicsItem* item : items) {
            Sprite* sprite = dynamic_cast<Sprite*>(item);
            if (sprite) {
                if (sprite->x() - 5 < 0){
                    moveViewToCenter(sprite);
                } else {
                    // Move the sprite left by a certain amount
                    sprite->setX(sprite->x() - 5); // Adjust the value as needed
                    moveViewToCenter(sprite);
                }
                qDebug() << sprite->x();
                spriteX = sprite->x();

                updateSprite(sprite->x(), sprite->y());
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
                if (sprite->x() + 5 > 2550){
                    moveViewToCenter(sprite);
                } else {
                    // Move the sprite right by a certain amount
                    sprite->setX(sprite->x() + 5); // Adjust the value as needed
                    moveViewToCenter(sprite);
                }
                qDebug() << sprite->x();
                spriteX = sprite->x();

                updateSprite(sprite->x(), sprite->y());
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
                if (sprite->y() + 5 > 1430){
                    moveViewToCenter(sprite);
                } else {
                    // Move the sprite up by a certain amount
                    sprite->setY(sprite->y() + 5); // Adjust the value as needed
                    moveViewToCenter(sprite);
                }
                qDebug() << sprite->y();
                spriteY = sprite->y();

                updateSprite(sprite->x(), sprite->y());
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
                if (sprite->y() - 5 < 0){
                    sprite->setY(sprite->y());
                } else {
                    // Move the sprite down by a certain amount
                    sprite->setY(sprite->y() - 5); // Adjust the value as needed
                    moveViewToCenter(sprite);
                }
                qDebug() << sprite->y();
                spriteY = sprite->y();

                updateSprite(sprite->x(), sprite->y());
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
    ui->field->centerOn(spritePos + QPointF(10,6));
}

void MainWindow::updateSprite(int x, int y){
    QString message = "movSprite,";
    message.append(QString::number(x));
    message.append(",");
    message.append(QString::number(y));

    qDebug() << message;
    socket.write(message.toUtf8());
    socket.flush();
}


void MainWindow::on_stopExplore_clicked()
{
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
    ui->movementKeys->setEnabled(false);
    ui->startExplore->setEnabled(true);
    ui->stopExplore->setEnabled(false);

    QString message = "delSprite,";
    qDebug() << message;
    socket.write(message.toUtf8());
    socket.flush();

    // Restore the original transformation
    QTransform transform;
    transform.scale(0.50, -0.50);
    ui->field->setTransform(transform);
}

