#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "threadmanager.h"
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "gamescene.h"
#include <QThreadPool>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

signals:
    void ballCreated(QVector<Ball*> balls);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateBallPosition(Ball *ball, int x, int y, qreal dx, qreal dy);

private slots:
    void displayFPS();
    void on_addBall_clicked();
    void on_addBall1_clicked();
    void on_addBall2_clicked();
    void on_addBall3_clicked();
    void on_addWall_clicked();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    QLabel *fpsLabel;
    QTimer *fpsTimer;
    QTimer *fpsCountTimer;
    GameScene *scene;
    QGraphicsEllipseItem *ball;
    int frameCount;
    ThreadManager *threadManager;
};

#endif
