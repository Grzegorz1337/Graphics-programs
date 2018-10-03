#include "MyWidget.h"


MyWidget::MyWidget()
{
    img=new QImage(800,600,QImage::Format_RGB32);
    Draw1();
    this->setMouseTracking(true);
}

MyWidget::~MyWidget()
{
    delete img;
    img=NULL;
}

void MyWidget::Draw1()
{
    int i,j;
    unsigned char *ptr;

    for (j=0;j<img->height();j++)
    {
        ptr=img->scanLine(j);
        for (i=0;i<img->width();i++)
        {
               ptr[i*4]=150;
               ptr[i*4+1]=100;
               ptr[i*4+2]=10;
        }
    }
}

//y -y1 = ((y2-y1)(x) - (x1)*(y2-y1))/(x2-x1) + y1

void MyWidget::Draw2(int x1,int y1,int x2,int y2)
{
    int i,j,inx,iny;
    unsigned char *ptr;
    double a,b;
    a = ((y1-y2)*1.0)/((x1-x2)*1.0);
    b = (y1-((((y1-y2)*1.0)/((x1-x2)*1.0))*x1));
    inx = (x1<x2)?1:-1;
    iny = (y1<y2)?1:-1;
    for (j=y1;j!=y2;j+=iny)
    {
        ptr=img->scanLine(j);
        for (i=x1;i!=x2;i+=inx)
        {
            if(((a*i+b>=j-abs(a)) && (a*i+b<=j+abs(a))) || (((a*i+b>=j-1) && (a*i+b<=j+1))))
            {
               ptr[i*4]=0;
               ptr[i*4+1]=0;
               ptr[i*4+2]=0;
            }
        }
    }
}

void MyWidget::paintEvent(QPaintEvent*)
{

    QPainter p(this);
    p.drawImage(0,0,*img);
}

void MyWidget:: mousePressEvent(QMouseEvent* event)
{


    if(event->buttons() & Qt::LeftButton)
    {
        //Draw2(2,2,100,100);
        this->x1 = event->x();
        this->y1 = event->y();
    }
    else
    Draw1();

    repaint();
}

void MyWidget:: mouseReleaseEvent(QMouseEvent* event)
{

    this->x2 = event->x();
    this->y2 = event->y();


    if(((x2>=0)&&(x2>=0)&&(x2<img->width())&&(y2<img->height())))
        Draw2(this->x1,this->y1,this->x2,this->y2);

    repaint();
}

