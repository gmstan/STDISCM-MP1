#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "threadmanager.h"
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "gamescene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void ballCreated(Ball *ball);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateBallPosition(Ball *ball, int x, int y, qreal dx, qreal dy);


private slots:
    void displayFPS();
    //void moveBall(); // Added slot for moving the ball
    void on_addBall_clicked();
    void on_addWall_clicked();

    void on_addBall1_clicked();

    void on_addBall2_clicked();

    void on_addBall3_clicked();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    QLabel *fpsLabel;
    QTimer *fpsTimer;
    QTimer *fpsCountTimer;
    QTimer *ballTimer; // Timer for moving the ball
    GameScene *scene;
    QGraphicsEllipseItem *ball;
    int frameCount;
    int dx, dy; // direction of movement for the ball
    ThreadManager *threadManager;
};

#endif // MAINWINDOW_H
