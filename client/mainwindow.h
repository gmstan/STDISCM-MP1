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
#include <sprite.h>
#include <QtNetwork>
#include <QTcpSocket>

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

    int spriteX = -100;
    int spriteY = -100;

    QTcpSocket socket;

public slots:
    void updateBallPosition(Ball *ball, int x, int y, qreal dx, qreal dy);

private slots:
    void displayFPS();
    void on_startExplore_clicked();
    void on_stopExplore_clicked();
    void moveSpriteLeft();
    void moveSpriteRight();
    void moveSpriteUp();
    void moveSpriteDown();
    void moveViewToCenter(Sprite *sprite);

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
