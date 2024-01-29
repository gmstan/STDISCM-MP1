#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateFPS();
    void moveBall(); // Added slot for moving the ball

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    QLabel *fpsLabel;
    QTimer *fpsTimer;
    QTimer *ballTimer; // Timer for moving the ball
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ball;
    int frameCount;
    int dx, dy; // direction of movement for the ball
};

#endif // MAINWINDOW_H
