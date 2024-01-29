#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    // Add a ball to the scene
    ball = new QGraphicsEllipseItem(0, 0, 3, 3); // Ball size of 3x3
    ball->setBrush(Qt::red); // Set color
    scene->addItem(ball);

    // Set initial movement direction
    dx = 5;
    dy = 5;

    // Setup a timer to move the ball
    ballTimer = new QTimer(this);
    connect(ballTimer, SIGNAL(timeout()), this, SLOT(moveBall()));
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

void MainWindow::moveBall()
{
    // Get current position of the ball
    QPointF pos = ball->pos();

    // Update position based on direction
    pos.rx() += dx;
    pos.ry() += dy;

    // Check collision with walls
    if (pos.x() <= 0 || pos.x() >= ui->field->width() - 3) { // 3 is the width of the ball
        dx = -dx; // Reverse direction in x-axis
    }
    if (pos.y() <= 0 || pos.y() >= ui->field->height() - 3) { // 3 is the height of the ball
        dy = -dy; // Reverse direction in y-axis
    }

    // Update ball position
    ball->setPos(pos);
}
