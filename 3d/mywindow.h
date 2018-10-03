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
    unsigned char *ptr;
    struct point {int x; int y; int z;};
    std::vector <point> walls;
    void drawLine(double, double, double, double);
    void addPoint(int, int, int);

private slots:
    void on_quit_clicked();
    void paintEvent(QPaintEvent*);
    void on_reset_clicked();
    void somethingHappened(); 
};

#endif
