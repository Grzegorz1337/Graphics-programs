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
    QImage *img, *img0;

    int szer, wys, poczX, poczY;
    int pressX, pressY, releaseX, releaseY, actualX, actualY;
    unsigned char *ptr, *ptr0;
    int mode, moveIndex, movePointFromVector;
    struct point {double x; double y;};
    std::vector<point> AtBtCt_T, ABC_T;
    bool movingPoint;

    // Deklaracje funkcji
    void clear();
    void setPixelColor(int, int, int, int, int);
    void redrawTriangle(std::vector <point> &, int);
    void addPoint(double, double, std::vector <point> &);
    void drawPoint(int, int, int);
    void drawLine(double, double, double, double, int);
    void texture();
    int getPixelColor(int, int, char);

private slots:
    void on_reset_clicked();
    void on_quit_clicked();
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);
};

#endif

