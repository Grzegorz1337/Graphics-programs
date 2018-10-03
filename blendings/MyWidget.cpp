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
    cpy=new QImage(900,600,QImage::Format_RGB32);
    Draw1();
    img=new QImage();
    img1 =new QImage();
    img2=new QImage();
    std::cout<<dir.absolutePath().toStdString()<<std::endl;
    img1->load("img2.jpg");
    img2->load("img3.jpg");
    if(img->load("bg.jpg"))
    {
        std::cout<<"OK";
    }
    else
    {
        std::cout<<"NIE OK";
    }
    this->setFixedHeight(cpy->height());
    this->setFixedWidth(cpy->width());
    this->r = new QSlider(Qt::Horizontal,this);
    this->b = new QSlider(Qt::Horizontal,this);
    this->g = new QSlider(Qt::Horizontal,this);
    /*this->h= new QSlider(Qt::Horizontal,this);
    this->s = new QSlider(Qt::Horizontal,this);
    this->v = new QSlider(Qt::Horizontal,this);
    this->alpha = new QSlider(Qt::Horizontal,this);
    this->tx = 0;
    this->ty = 0;
    this->sx = 1;
    this->sy = 1;
    this->px = 0;
    this->py = 0;
    this->a = 0;*/
    r->move(750,30);
    b->move(750,60);
    g->move(750,90);
    /*h->move(750,150);
    s->move(750,210);
    v->move(750,240);
    alpha->move(750,300);*/
    r->setRange(-255,0);
    b->setRange(-255,0);
    g->setRange(-255,0);
    /*h->setRange(0,200);
    s->setRange(0,255);
    v->setRange(0,255);
    alpha->setRange(0,360);*/
    r->show();
    b->show();
    g->show();/*
    h->show();
    s->show();
    v->show();
    alpha->show();*/
    connect(r,SIGNAL(valueChanged(int)),this,SLOT(show1(int a)));
    connect(b,SIGNAL(valueChanged(int)),this,SLOT(show2(int a)));
    connect(g,SIGNAL(valueChanged(int)),this,SLOT(show3(int a)));
    /*connect(h,SIGNAL(valueChanged(int)),this,SLOT(scSetY(int)));
    connect(s,SIGNAL(valueChanged(int)),this,SLOT(pochSetX(int)));
    connect(v,SIGNAL(valueChanged(int)),this,SLOT(pochSetY(int)));
    connect(alpha,SIGNAL(valueChanged(int)),this,SLOT(setAlpha(int)));
    this->rl = new QLabel(this);
    this->bl = new QLabel(this);
    this->gl = new QLabel(this);
    this->hl = new QLabel(this);
    rl->setText("Paski odpowiadajace za translacje x, i y");
    bl->setText("Paski odpowiadajace za skalowanie x, i y");
    gl->setText("Paski odpowiadajace za pohyleie x, i y");
    hl->setText("Pasek odpowiadajacy za obrócenie o kat alfa");
    rl->move(750,10);
    bl->move(750,100);
    gl->move(750,190);
    hl->move(750,280);
    rl->show();*/
}

void MyWidget::trSetX(int a)
{
    this->tx =a;
}
void MyWidget::trSetY(int a)
{
    this->ty = a;

}
void MyWidget::scSetX(int a)
{
    this->sx = a;

}
void MyWidget::scSetY(int a)
{
    this->sy = a;
}
void MyWidget::pochSetX(int a)
{
    this->px = a;
}
void MyWidget::pochSetY(int a)
{
    this->py = a;
}
void MyWidget::setAlpha(int a)
{
    this->a = a;
}

void MyWidget::translacja(int a,int b)
{
    int x,y;
    for(y=0;y<img->height();y++)
    {
        for(x=0;x<img->width();x++)
        {
            img->setPixel(x+a,y+b,img->pixel(x,y));
        }
    }
}

void MyWidget::skalowanie(int a,int b)
{
    int x,y;
    for(y=0;y<img->height();y++)
    {
        for(x=0;x<img->width();x++)
        {
            img->setPixel(x*a,y*b,img->pixel(x,y));
        }
    }
}

void MyWidget::pochylenie(int a,int b)
{
    int x,y;
    for(y=0;y<img->height();y++)
    {
        for(x=0;x<img->width();x++)
        {
            img->setPixel(x+(y*a),y+(x*b),img->pixel(x,y));
        }
    }
}

void MyWidget::rotacja(int alpha)
{
    int x,y;
    double s,c;
    s = sin(alpha);
    c = cos(alpha);
    for(y=0;y<img->height();y++)
    {
        for(x=0;x<img->width();x++)
        {
            img->setPixel((x*c)-(y*s),(x*s)+(y*c),img->pixel(x,y));
        }
    }
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

    for (j=0;j<cpy->height();j++)
    {
        ptr=cpy->scanLine(j);
        for (i=0;i<cpy->width();i++)
        {
               ptr[i*4]=150;
               ptr[i*4+1]=100;
               ptr[i*4+2]=10;
        }
    }
}



void MyWidget::paintEvent(QPaintEvent*)
{

    QPainter p(this);
    p.drawImage(0,0,*cpy);
}

void MyWidget::paintPixel(int x,int y)
{
    int i,j;
    unsigned char *ptr;
    for (j=y-2;j<y+2;j++)
    {
        ptr=img->scanLine(j);
        for (i=0;i<img->width();i++)
        {
            if(i<x+2 && i > x-2)
            {
               ptr[i*4]=0;
               ptr[i*4+1]=0;
               ptr[i*4+2]=0;
            }
        }
    }
}

void MyWidget::show1(int a)
{
    int i,j;
    QColor kolor;
    unsigned char *ptr;
    img->createAlphaMask();
    for (j=0;j<img->height();j++)
    {
        ptr=img->scanLine(j);
        for (i=0;i<img->width();i++)
        {
            img2->setPixelColor(QColor((img->pixel(i,j)),a));
        }
    }
}

void MyWidget::show2(int a)
{
    int i,j;
    QColor kolor;
    unsigned char *ptr;

    for (j=0;j<img1->height();j++)
    {
        ptr=img1->scanLine(j);
        for (i=0;i<img1->width();i++)
        {
               img2->setPixelColor(QColor((img1->pixel(i,j)),a));
        }
    }
}

void MyWidget::show3(int a)
{
    int i,j;
    QColor kolor;
    unsigned char *ptr;

    for (j=0;j<img2->height();j++)
    {
        ptr=img2->scanLine(j);
        for (i=0;i<img2->width();i++)
        {

            img2->setPixelColor(QColor((img2->pixel(i,j)),a));
        }
    }
}


void MyWidget:: mousePressEvent(QMouseEvent* event)
{

}

void MyWidget:: mouseReleaseEvent(QMouseEvent* event)
{

}

void MyWidget::mouseMoveEvent(QMouseEvent* event)
{
    repaint();
}

