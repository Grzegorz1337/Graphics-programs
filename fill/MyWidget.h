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

struct point{
    int x;
    int y;
};

class MyWidget : public QWidget
{
    Q_OBJECT

    QImage *img;


    public:
        MyWidget();
        ~MyWidget();
        void pixSet(int x,int y);
        bool color(int x,int y);
        void fillColor(point a);
        void Draw1();
        void Draw2(int x1,int y1,int x2,int y2);
        void Draw3(int x1,int y1,int x2,int y2);
        void Draw4(int x1,int y1,int x2,int y2);


    protected:


        void paintLine(QPaintEvent*);
        void paintEvent(QPaintEvent*);
        void mouseReleaseEvent(QMouseEvent* event);
        void mousePressEvent(QMouseEvent* event);
        void Bezier(point a, point b, point c, point d);

private:
        int x1,x2,y1,y2;
        point a,b,c,d;
};




#endif // MYWIDGET_H
