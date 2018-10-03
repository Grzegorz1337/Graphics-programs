#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>

namespace Ui
{
    class MyWindow;
}

class MyWindow : public QMainWindow
{   
    Q_OBJECT

public: 
    explicit MyWindow(QWidget *parent = 0);
    ~MyWindow();

private:
    Ui::MyWindow *ui;
    QImage *img;

    int szer, wys, poczX, poczY;
    int pressX, pressY, releaseX, releaseY, actualX, actualY;
    unsigned char *ptr;
    int mode, moveIndex;
    struct point {int x; int y;};
    std::vector<point> T;
    bool movingPoint;

    void clear();
    void setPixelColor(int, int, int, int, int);
    void redrawPoints();
    void removePoint(int);
    void addPoint(int, int);
    void drawPoint(int, int, int);
    void drawLine(int, int);

private slots:
    void on_reset_clicked();
    void on_quit_clicked();
    void on_dodaj_clicked();
    void on_przesun_clicked();
    void on_usun_clicked();
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);
};

#endif
