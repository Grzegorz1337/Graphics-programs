#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <cstdlib>
#include <cmath>
#include <QMouseEvent>

class MyWidget : public QWidget
{
    Q_OBJECT

    QImage *img;


    public:
        MyWidget();
        ~MyWidget();
        void Draw1();
        void Draw2(int x1,int y1,int x2,int y2);


    protected:


        void paintLine(QPaintEvent*);
        void paintEvent(QPaintEvent*);
        void mouseReleaseEvent(QMouseEvent* event);
        void mousePressEvent(QMouseEvent* event);

private:
        int x1,x2,y1,y2;
};




#endif // MYWIDGET_H
