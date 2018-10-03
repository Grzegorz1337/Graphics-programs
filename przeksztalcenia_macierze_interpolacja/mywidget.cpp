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
    cpy = new QImage(img->width(),img->height(),QImage::Format_RGB32);
    this->setFixedHeight(img->height()+200);
    this->setFixedWidth(img->width()+400);
    this->r = new QSlider(Qt::Horizontal,this);
    this->b = new QSlider(Qt::Horizontal,this);
    this->g = new QSlider(Qt::Horizontal,this);
    this->h= new QSlider(Qt::Horizontal,this);
    this->s = new QSlider(Qt::Horizontal,this);
    this->v = new QSlider(Qt::Horizontal,this);
    this->alpha = new QSlider(Qt::Horizontal,this);
    this->tx = 0;
    this->ty = 0;
    this->sx = 1;
    this->sy = 1;
    this->px = 0;
    this->py = 0;
    this->a = 0;
    wykonaj = new QPushButton("Wykonaj",this);
    wykonaj->move(730,330);
    connect(wykonaj, SIGNAL (released()),this, SLOT (handleButton()));
    wykonaj->show();
    r->move(730,30);
    b->move(730,60);
    g->move(730,120);
    h->move(730,150);
    s->move(730,210);
    v->move(730,240);
    alpha->move(730,300);
    r->setRange(-100,100); //Translacja x
    b->setRange(-100,100); //Translacja y
    g->setRange(0,200); //skalowanie x
    h->setRange(0,200); //skalowanie y
    s->setRange(0,100); //pochylenie x
    v->setRange(0,100); //pochylenie y
    alpha->setRange(0,360); //obrót o alpha
    g->setValue(100);
    h->setValue(100);
    r->show();
    b->show();
    g->show();
    h->show();
    s->show();
    v->show();
    alpha->show();
    this->rl = new QLabel(this);
    this->bl = new QLabel(this);
    this->gl = new QLabel(this);
    this->hl = new QLabel(this);
    rl->setText("Paski odpowiadajace za translacje x, i y");
    bl->setText("Paski odpowiadajace za skalowanie x, i y");
    gl->setText("Paski odpowiadajace za pohylenie x, i y");
    hl->setText("Pasek odpowiadajacy za obrócenie o kat alfa");
    rl->move(730,10);
    bl->move(730,100);
    gl->move(730,190);
    hl->move(730,280);
    rl->show();
}

void MyWidget::handleButton()
{
    //translacja(r->value(),b->value());
    //skalowanie(((double)g->value()) / 100.0,((double)h->value()) / 100.0);
    //rotacja((double)(alpha->value()) * M_PI / 180.0);
    pochylenie((double)(s->value())/100.0,(double)(v->value()/100.0));
}


void MyWidget::translacja(int a,int b)
{
    int x,y;
    int point[3];
    point[2] = 1;
    for(y=0;y+b<img->height();y++)
    {
        point[1] = y;
        for(x=0;x+a<img->width();x++)
        {
            point[0] = x;
            QGenericMatrix<1,3,int> punkt(point);
            cpy->setPixel(x+a,y+b,img->pixel(x,y));
        }
    }
    *img = *cpy;
    delete cpy;
    cpy = new QImage(img->width(),img->height(),QImage::Format_RGB32);
    *cpy = *img;
    repaint();
}

void MyWidget::skalowanie(double a,double b)
{
    int x,y;
    std::cout<<a<<b;
    for(y=0;y<=img->height();y++)
    {
        for(x=0;x<=img->width();x++)
        {
            interpolacja((int)(x*a),(int)(y*b),a,b,x,y);
        }
    }
    *img = *cpy;
    delete cpy;
    cpy = new QImage(img->width(),img->height(),QImage::Format_RGB32);
    *cpy = *img;
    repaint();
}

void MyWidget::pochylenie(double a,double b)
{
    int x,y;
    for(y=0;y<img->height();y++)
    {
        for(x=0;x<img->width();x++)
        {
            cpy->setPixel(x+(y*a),y+(x*b),img->pixel(x,y));
        }
    }
    *img = *cpy;
    delete cpy;
    cpy = new QImage(img->width(),img->height(),QImage::Format_RGB32);
    *cpy = *img;
    repaint();

    /*
                     [ 1   shy 0 ]
         [x,y,1] *   | shx 1   0 | = [x+y*shx,x*shy + y,1]
                     [ 0   0   1 ]
    */
}

void MyWidget::rotacja(double alpha)
{
    std::cout<<(cos(alpha)-sin(alpha)+((img->width()/2)*(1-cos(alpha))+(img->height()/2)*sin(alpha)))<<"   "<<(sin(alpha)+cos(alpha)+((-1*img->width()/2)*sin(alpha)+(img->height()/2)*(1-cos(alpha))))<<endl;
    std::cout<<cos(alpha)-sin(alpha)<<" "<<sin(alpha)+cos(alpha);
    for(int y=0;y<img->height();y++)
    {
        for(int x=0;x<img->width();x++)
        {
            interpolacja(x*cos(alpha)- y*sin(alpha) + ((img->width()/2)*(1-cos(alpha))+(img->height()/2)*sin(alpha)),x*sin(alpha)+ y*cos(alpha)+ (-1*(img->width()/2)*sin(alpha)+(img->height()/2)*(1-cos(alpha))),2,2,x,y);
            //cpy->setPixel(x*cos(alpha)- y*sin(alpha) + ((img->width()/2)*(1-cos(alpha))+(img->height()/2)*sin(alpha)),x*sin(alpha)+ y*cos(alpha)+ (-1*(img->width()/2)*sin(alpha)+(img->height()/2)*(1-cos(alpha))),img->pixel(x,y));
        }
    }
    *img = *cpy;
    delete cpy;
    cpy = new QImage(img->width(),img->height(),QImage::Format_RGB32);
    *cpy = *img;
    repaint();
    /*
              [ cos (a)                         sin (a)                         0 ]
    [x,y,1] * [ -sin (a)                        cos (a)                         0 ] = [x*cos(a) - x*sin(a) + x*(xP*(1-cos(a)) + yP*sin(a)),y*sin(a) + y*cos(a) + y*(-xP*sin(a) + yP*(1 - cos(a)))
              [ xP*(1 - cos(a)) + yP*sin(a)     -xP*sin(a) + yP*(1 - cos(a))    1 ]
                    { macierz przejscia tr(0,0)*rot(alpha)*tr(n,m) }

     xP - przejscie pixela do poczatku uklady wspolrzednych po x (img->width()/2)
     yP - przejscie pixela do poczatku ukladu wspolrzednych po y (img->height()/2)
    */
}


MyWidget::~MyWidget()
{
    delete img;
    img=NULL;
}

void MyWidget::interpolacja(int x,int y,double sx,double sy,int ix,int iy)
{
    for(int Y=(int)(y-(sy/2.0));Y<=y+(sy/2.0);Y++)
    {
        for(int X=(int)(x-(sx/2.0));X<=x+(sx/2.0);X++)
        {
            cpy->setPixel(X,Y,img->pixel(ix,iy));
        }
    }

}
void MyWidget::paintEvent(QPaintEvent*)
{

    QPainter p(this);
    p.drawImage(0,0,*img);
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

