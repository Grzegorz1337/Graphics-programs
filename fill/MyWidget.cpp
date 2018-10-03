#include "MyWidget.h"
#include <stack>
#include <ctime>
#include<stdlib.h>
#include<time.h>
#include<iostream>
MyWidget::MyWidget()
{
    img=new QImage(800,800,QImage::Format_RGB32);
    Draw1();
    this->setMouseTracking(true);
        this->a.x = 0;
        this->a.y = 0;
        this->b.x = 0;
        this->b.y = 0;
        this->c.x = 0;
        this->c.y = 0;
        this->d.x = 0;
        this->d.y = 0;
}

MyWidget::~MyWidget()
{
    delete img;
    img=NULL;
}

void MyWidget::pixSet(int x,int y)
{
    int i,j;
    unsigned char *ptr;
    ptr=img->scanLine(y);
    ptr[x*4]=255;
    ptr[x*4+1]=0;
    ptr[x*4+2]=0;
}

bool MyWidget::color(int x,int y)
{
    int i,j;
    unsigned char *ptr;

    for (j=y;j<img->height();j++)
    {
        ptr=img->scanLine(j);
        for (i=x;i<img->width();i++)
        {
               if(ptr[i*4]==255 && ptr[i*4+1]==255 && ptr[i*4+2]==255)
               {
                   return true;
               }
               return false;
        }
        return false;
    }
    return false;
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
               ptr[i*4]=255;
               ptr[i*4+1]=255;
               ptr[i*4+2]=255;
        }
    }
}

//y -y1 = ((y2-y1)(x) - (x1)*(y2-y1))/(x2-x1) + y1

void MyWidget::Draw2(int x1,int y1,int x2,int y2)
{
    int i,j;
    int b=0;
    unsigned char *ptr;
    //(x−x1)2+(y−y1)2=R
    double r = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
    for (j=0;j<img->height();j++)
    {
        ptr=img->scanLine(j);
        for (i=0;i<img->width();i++)
        {
            if(pow(i-x1,2) + pow(j-y1,2) <= r*r+2*r && pow(i-x1,2) + pow(j-y1,2) >= r*r-2*r)
            {
                ptr[i*4]=0;
                ptr[i*4+1]=0;
                ptr[i*4+2]=0;
                b++;
            }
        }
    }
    //Draw4(x1,y1,x2,y2);
}

void MyWidget::Draw3(int x1,int y1,int x2,int y2)
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
    if(y1==y2)
    {
        ptr=img->scanLine(y1);
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

void MyWidget::Draw4(int x1,int y1,int x2,int y2)
{
    double r = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
    int xa,ya;
    double aJump = (2*M_PI/6.0);
    double phi = aJump;
    int x = r;
    int y = 0;
    for(int i=0;i<=360/8;i++,phi+=aJump)
    {
        //img->setPixel(r*cos(i)+x1,r*sin(i)+y1,qRgb(255,0,0));
        xa = r*cos(phi);
        ya = r*sin(phi);
        Draw3(x+x1,y1-y,xa+x1,y1-ya);
        x=xa;
        y=ya;
    }
}

/*void MyWidget::Bezier(point a,point b,point c,point d)
{
    // B(t) = (1 − t) 3 P 0 + 3(1 − t) 2 tP 1 + 3(1 − t)t 2 P 2 + t 3 P 3
    for(float t=0;t<=1;t+=0.01)
    {

    }
}*/

void MyWidget::fillColor(point a)
{
    unsigned char *ptr;
    point n[4],d,c;
    n[0].x = 1;
    n[0].y = 0;
    n[1].x = 0;
    n[1].y = -1;
    n[2].x = -1;
    n[2].y = 0;
    n[3].x = 0;
    n[3].y = 1;
    std::stack <point> punkty;
    punkty.push(a);
    img->setPixel(a.x,a.y,qRgb(255,0,0));
    //while(!punkty.empty())
    while(!punkty.empty())
    {
        c = punkty.top();
        punkty.pop();;
        for(int i=0;i<4;i++)
        {
            point d;
            d.x = c.x + n[i].x;
            d.y = c.y + n[i].y;
            if(color(d.x,d.y)){
                pixSet(d.x,d.y);
                repaint();
                punkty.push(d);
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


    /*if(event->buttons() & Qt::LeftButton)
    {
        //Draw2(2,2,100,100);
        //this->x1 = event->x();
        //this->y1 = event->y();
        if(a.x == 0 && a.y==0)
        {
            this->a.x = event->x();
            this->a.y = event->y();
        }
        else
        {
            if(b.x == 0 && b.y==0)
            {
                this->b.x = event->x();
                this->b.y = event->y();
            }
            else
            {
                if(c.x == 0 && c.y==0)
                {
                    this->c.x = event->x();
                    this->c.y = event->y();
                }
                else
                {
                    if(d.x == 0 && d.y==0)
                    {
                        this->d.x = event->x();
                        this->d.y = event->y();
                    }
                    else
                    {
                        //rysuj kurwe
                    }
                }
            }
        }
    }*/
    //else
    if(event->buttons() & Qt::LeftButton)
    {
        this->x1 = event->x();
        this->y1 = event->y();
    }
    else
    {
        point a;
        a.x = event->x();
        a.y = event->y();
        fillColor(a);
    }
    //Draw1();

    //repaint();
}

void MyWidget:: mouseReleaseEvent(QMouseEvent* event)
{


    this->x2 = event->x();
    this->y2 = event->y();


    if(((x2>=0)&&(x2>=0)&&(x2<img->width())&&(y2<img->height())))
        Draw2(this->x1,this->y1,this->x2,this->y2);

    repaint();
}

