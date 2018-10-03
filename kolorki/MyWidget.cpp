#include "MyWidget.h"
#include <stack>
#include <ctime>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<cmath>
MyWidget::MyWidget()
{
    QDir dir(".");
    img=new QImage();
    std::cout<<dir.absolutePath().toStdString()<<std::endl;
    if(img->load("bg.jpg"))
    {
        std::cout<<"OK";
    }
    else
    {
        std::cout<<"NIE OK";
    }
    this->setFixedHeight(img->height());
    this->setFixedWidth(img->width()+300);
    this->r = new QSlider(Qt::Horizontal,this);
    this->b = new QSlider(Qt::Horizontal,this);
    this->g = new QSlider(Qt::Horizontal,this);
    this->h= new QSlider(Qt::Horizontal,this);
    this->s = new QSlider(Qt::Horizontal,this);
    this->v = new QSlider(Qt::Horizontal,this);
    r->move(650,10);
    b->move(650,40);
    g->move(650,70);
    h->move(650,100);
    s->move(650,130);
    v->move(650,160);
    r->setRange(0,255);
    b->setRange(0,255);
    g->setRange(0,255);
    h->setRange(0,255);
    s->setRange(0,255);
    v->setRange(0,255);
    r->show();
    b->show();
    g->show();
    h->show();
    s->show();
    v->show();
    connect(r,SIGNAL(valueChanged(int)),this,SLOT(kolorujR(int)));
    connect(b,SIGNAL(valueChanged(int)),this,SLOT(kolorujG(int)));
    connect(g,SIGNAL(valueChanged(int)),this,SLOT(kolorujB(int)));
    connect(h,SIGNAL(valueChanged(int)),this,SLOT(kolorujH(int)));
    connect(s,SIGNAL(valueChanged(int)),this,SLOT(kolorujS(int)));
    connect(v,SIGNAL(valueChanged(int)),this,SLOT(kolorujV(int)));
    kim = new QSignalMapper(this);
}

MyWidget::~MyWidget()
{
    delete img;
    img=NULL;
}

void MyWidget::kolorujR(int k)
{
    recolor(k,'r');
}
void MyWidget::kolorujG(int k)
{
    recolor(k,'g');
}
void MyWidget::kolorujB(int k)
{
    recolor(k,'b');
}
void MyWidget::kolorujH(int k)
{
    recolor(k,'h');
}
void MyWidget::kolorujS(int k)
{
    recolor(k,'s');
}
void MyWidget::kolorujV(int k)
{
    recolor(k,'v');
}

void MyWidget::recolor(int k, char color)
{
    int i,j;
    QColor kolor;
    unsigned char *ptr;
    cpy = new QImage();
    cpy = img;
    for (j=0;j<cpy->height();j++)
    {
        ptr=cpy->scanLine(j);
        for (i=0;i<cpy->width();i++)
        {
            switch(color)
            {
                case 'r':
                    ptr[i*4]= (ptr[i*4] + k)%255;
                    break;
                case 'b':
                    ptr[i*4+1]= (ptr[i*4] + k)%255;
                    break;
                case'g':
                    ptr[i*4+2]= (ptr[i*4] + k)%255;
                    break;
                case 'h':
                    kolor = cpy->pixel(i,j);
                    kolor.toHsv();
                    kolor.setHsv(k,0,0,255);
                    kolor.toRgb();
                    ptr[i*4]=(ptr[i*4]+kolor.red())%255;
                    ptr[i*4]=(ptr[i*4]+kolor.green())%255;
                    ptr[i*4]=(ptr[i*4]+kolor.blue())%255;
                    break;
                case 's':
                    kolor = cpy->pixel(i,j);;
                    kolor.toHsv();
                    kolor.setHsv(0,k,0,255);
                    kolor.toRgb();
                    ptr[i*4]=(ptr[i*4]+kolor.red())%255;
                    ptr[i*4]=(ptr[i*4]+kolor.green())%255;
                    ptr[i*4]=(ptr[i*4]+kolor.blue())%255;
                    break;
                case 'v':
                    kolor = cpy->pixel(i,j);
                    kolor.toHsv();
                    kolor.setHsv(0,0,k,255);
                    kolor.toRgb();
                    ptr[i*4]=(ptr[i*4]+kolor.red())%255;
                    ptr[i*4]=(ptr[i*4]+kolor.green())%255;
                    ptr[i*4]=(ptr[i*4]+kolor.blue())%255;;
                    break;
            }
        }
    }
    img = cpy;
    repaint();
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



void MyWidget::paintEvent(QPaintEvent*)
{

    QPainter p(this);
    p.drawImage(0,0,*img);
}

void MyWidget:: mousePressEvent(QMouseEvent* event)
{


    if(event->buttons() & Qt::LeftButton)
    {
        this->x1 = event->x();
        this->y1 = event->y();
        repaint();
    }
}

void MyWidget:: mouseReleaseEvent(QMouseEvent* event)
{


    this->x2 = event->x();
    this->y2 = event->y();

    repaint();
}

