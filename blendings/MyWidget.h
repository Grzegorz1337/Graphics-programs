#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <cstdlib>
#include <cmath>
#include <QMouseEvent>
#include <stack>
#include <ctime>
#include <QLabel>
#include <QDir>
#include <QSlider>
#include <QSignalMapper>
struct point{
    int x;
    int y;
};

class MyWidget : public QWidget
{
    Q_OBJECT

    QImage *img;
    QImage *cpy;
    QImage *img1;
    QImage *img2;

    public:
        MyWidget();
        ~MyWidget();
        void Draw1();

    public slots:
        void translacja(int a,int b);
        void skalowanie(int a,int b);
        void rotacja(int alpha);
        void pochylenie(int a,int b);
        void trSetX(int a);
        void trSetY(int a);
        void scSetX(int a);
        void scSetY(int a);
        void pochSetX(int a);
        void pochSetY(int a);
        void setAlpha(int a);
        void show1(int a);
        void show2(int a);
        void show3(int a);

    protected:
        void paintEvent(QPaintEvent*);
        void mouseReleaseEvent(QMouseEvent* event);
        void mousePressEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
        void paintPixel(int x,int y);
        void dylacja();
        void paintMod(int x,int y);
private:
        int tx,ty,sx,sy,px,py,a;
        int dr,db,dg,dh,ds,dv;
        QSlider *r, *b, *g, *h, *s, *v,*alpha;
        QLabel *rl,*bl,*gl,*hl;
        QSignalMapper *kim;
};




#endif // MYWIDGET_H
