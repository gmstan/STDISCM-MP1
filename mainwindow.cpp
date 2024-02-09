#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ball.h"
#include "ball.cpp"
#include "wall.h"
#include "wall.cpp"

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

    //Setup a timer to move the ball
    ballTimer = new QTimer(this);
    connect(ballTimer, SIGNAL(timeout()), scene, SLOT(advance()));
    ballTimer->start(20); // Move the ball every 20 milliseconds

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

// void MainWindow::moveBall()
// {
//     // Get current position of the ball
//     ball->advance();

//     // Check collision with walls
//     QPointF pos = ball->pos();

//     // Check collision with walls
//     if (pos.x() <= 0 || pos.x() >= ui->field->width() - 3) { // 3 is the width of the ball
//         dx = -dx; // Reverse direction in x-axis
//     }
//     if (pos.y() <= 0 || pos.y() >= ui->field->height() - 3) { // 3 is the height of the ball
//         dy = -dy; // Reverse direction in y-axis
//     }

//     // Update ball position
//     ball->setPos(pos);
// }

int numBalls;
qreal speed, angle, startPosX, startPosY;

void MainWindow::on_addBall_clicked()
{
    // variables, starting position X and Y, number of balls, ball speed, ball direction
    startPosX = ui->xInput->text().toInt();
    startPosY = ui->yInput->text().toInt();
    // numBalls = ui->numBalls->text().toInt();
    speed = ui->velocityInput->text().toDouble();
    angle = ui->directionInput->text().toDouble();

    // for (int i = 0; i < numBalls; ++i) {
        Ball *ball = new Ball(startPosX, startPosY, speed, angle);
        scene->addItem(ball);
    // }
    // clearing of input fields

    ui->xInput->setText("");
    ui->yInput->setText("");
    // ui->numBalls->setText("");
    ui->velocityInput->setText("");
    ui->directionInput->setText("");
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

