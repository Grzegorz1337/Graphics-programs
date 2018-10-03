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
#include <QPushButton>
#include <QGenericMatrix>


class MyWidget : public QWidget
{
    Q_OBJECT

    QImage *img;
    QImage *cpy;


    public:
        MyWidget();
        ~MyWidget();
        void Draw1();

    public slots:
        void translacja(int a,int b);
        void skalowanie(double a,double b);
        void rotacja(double alpha);
        void pochylenie(double a,double b);
        void handleButton();

    protected:
        void paintEvent(QPaintEvent*);
        void paintPixel(int x,int y);
        void interpolacja(int x,int y,double sx,double sy,int ix,int iy);
        void paintMod(int x,int y);
private:
        int tx,ty,sx,sy,px,py,a;
        int dr,db,dg,dh,ds,dv;
        QSlider *r, *b, *g, *h, *s, *v,*alpha;
        QLabel *rl,*bl,*gl,*hl;
        QSignalMapper *kim;
        QPushButton *wykonaj;
        typedef QMatrix3x3 trans, rot, poch, skal;
};




#endif // MYWIDGET_H
