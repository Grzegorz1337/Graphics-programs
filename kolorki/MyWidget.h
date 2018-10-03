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


    public:
        MyWidget();
        ~MyWidget();
        void Draw1();

    public slots:
        void kolorujR(int k);
        void kolorujG(int k);
        void kolorujB(int k);
        void kolorujH(int k);
        void kolorujS(int k);
        void kolorujV(int k);

    protected:
        void paintEvent(QPaintEvent*);
        void mouseReleaseEvent(QMouseEvent* event);
        void mousePressEvent(QMouseEvent* event);

private:
        int x1,x2,y1,y2;
        QSlider *r, *b, *g, *h, *s, *v;
        QLabel *rl,*bl,*gl,*hl,*sl,*vl;
        int dr,db,dg,dh,ds,dv;
        QSignalMapper *kim;
        void recolor(int k, char color);
};




#endif // MYWIDGET_H
