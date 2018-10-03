#include "mywindow.h"
#include "ui_mywindow.h"
#include "iostream"
#include "cmath"
#include "vector"

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow)
{
    ui -> setupUi(this);

    szer = ui -> frame -> width();
    wys = ui -> frame -> height();
    poczX = ui -> frame -> x();
    poczY = ui -> frame -> y();

    img = new QImage(szer, wys, QImage::Format_RGB32);
    img -> fill(QColor(Qt::white).rgb());
    ptr = img -> bits();

    connect(ui -> translacjaX, SIGNAL(valueChanged(int)), this, SLOT(somethingHappened()));
    connect(ui -> translacjaY, SIGNAL(valueChanged(int)), this, SLOT(somethingHappened()));
    connect(ui -> translacjaZ, SIGNAL(valueChanged(int)), this, SLOT(somethingHappened()));
    connect(ui -> skalowanieX, SIGNAL(valueChanged(int)), this, SLOT(somethingHappened()));
    connect(ui -> skalowanieY, SIGNAL(valueChanged(int)), this, SLOT(somethingHappened()));
    connect(ui -> skalowanieZ, SIGNAL(valueChanged(int)), this, SLOT(somethingHappened()));
    connect(ui -> rotacjaX, SIGNAL(valueChanged(int)), this, SLOT(somethingHappened()));
    connect(ui -> rotacjaY, SIGNAL(valueChanged(int)), this, SLOT(somethingHappened()));
    connect(ui -> rotacjaZ, SIGNAL(valueChanged(int)), this, SLOT(somethingHappened()));

    somethingHappened();
}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::on_quit_clicked()
{
    qApp -> quit();
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX, poczY, *img);
}

void MyWindow::on_reset_clicked()
{
    ui -> translacjaX -> setValue(0);
    ui -> translacjaY -> setValue(0);
    ui -> translacjaZ -> setValue(0);
    ui -> skalowanieX -> setValue(10);
    ui -> skalowanieY -> setValue(10);
    ui -> skalowanieZ -> setValue(10);
    ui -> rotacjaX -> setValue(0);
    ui -> rotacjaY -> setValue(0);
    ui -> rotacjaZ -> setValue(0);

    update();
}

void MyWindow::somethingHappened()
{
    int translationX, translationY, translationZ,  halfImgX = szer / 2, halfImgY = wys / 2, hAlp_X, hAlp_Y, hAlp_Z, edgeLength;
    edgeLength = 150;
    double scaleX,scaleY,scaleZ, rotateOX, rotateOY, rotateOZ;

    translationX = ui -> translacjaX -> value();
    translationY = ui -> translacjaY -> value();
    translationZ = ui -> translacjaZ -> value();
    scaleX = ((double)(ui -> skalowanieX -> value()))/10.0;
    scaleY = ((double)(ui -> skalowanieY -> value()))/10.0;
    scaleZ = ((double)(ui -> skalowanieZ -> value()))/10.0;
    rotateOX = ((double)(ui -> rotacjaX -> value()))/100.0;
    rotateOY = ((double)(ui -> rotacjaY -> value()))/100.0;
    rotateOZ = ((double)(ui -> rotacjaZ -> value()))/100.0;

    img -> fill(QColor(Qt::white).rgb());

    //front
    addPoint(halfImgX - (edgeLength / 2), halfImgY - (edgeLength / 2), 0); // l-t
    addPoint(halfImgX + (edgeLength / 2), halfImgY - (edgeLength / 2), 0); // r-t
    addPoint(halfImgX + (edgeLength / 2), halfImgY + (edgeLength / 2), 0); // r-b
    addPoint(halfImgX - (edgeLength / 2), halfImgY + (edgeLength / 2), 0); // l-b

    //tył
    addPoint(halfImgX - (edgeLength / 2), halfImgY - (edgeLength / 2), 0.7 * edgeLength); // l-t
    addPoint(halfImgX + (edgeLength / 2), halfImgY - (edgeLength / 2), 0.7 * edgeLength); // r-t
    addPoint(halfImgX + (edgeLength / 2), halfImgY + (edgeLength / 2), 0.7 * edgeLength); // r-b
    addPoint(halfImgX - (edgeLength / 2), halfImgY + (edgeLength / 2), 0.7 * edgeLength); // l-b

    for (unsigned int i = 0; i <= walls.size() - 1; i++)
    {
        walls[i].x = walls[i].x - halfImgX;
        walls[i].y = walls[i].y - halfImgY;

        if (rotateOX != 0)
        {
            hAlp_Y = ((walls[i].y * cos(rotateOX)) - (walls[i].z * sin(rotateOX)));
            hAlp_Z = ((walls[i].y * sin(rotateOX)) + (walls[i].z * cos(rotateOX)));
            walls[i].y = hAlp_Y;
            walls[i].z = hAlp_Z;
        }

        if (rotateOY != 0)
        {
            hAlp_X = ((walls[i].x * cos(rotateOY)) + (walls[i].z * sin(rotateOY)));
            hAlp_Z = (((-1 * walls[i].x) * sin(rotateOY)) + (walls[i].z * cos(rotateOY)));
            walls[i].x = hAlp_X;
            walls[i].z = hAlp_Z;
        }

        if (rotateOZ != 0)
        {
            hAlp_X = ((walls[i].x * cos(rotateOZ)) - (walls[i].y * sin(rotateOZ)));
            hAlp_Y = ((walls[i].x * sin(rotateOZ)) + (walls[i].y * cos(rotateOZ)));
            walls[i].x = hAlp_X;
            walls[i].y = hAlp_Y;
        }

        walls[i].x = (walls[i].x * scaleX) + halfImgX + translationX;
        walls[i].y = (walls[i].y * scaleY) + halfImgY + translationY;
        walls[i].z = (walls[i].z * scaleZ) + translationZ;

        //3D -> 2D
        walls[i].x = (walls[i].x / ((walls[i].z / 1000.0) + 1.0));
        walls[i].y = (walls[i].y / ((walls[i].z / 1000.0) + 1.0));
    }

    //dolna ściana
    drawLine(walls[2].x, walls[2].y, walls[3].x, walls[3].y);
    drawLine(walls[2].x, walls[2].y, walls[6].x, walls[6].y);
    drawLine(walls[3].x, walls[3].y, walls[7].x, walls[7].y);
    drawLine(walls[6].x, walls[6].y, walls[7].x, walls[7].y);

    //górna ściana
    drawLine(walls[0].x, walls[0].y, walls[1].x, walls[1].y);
    drawLine(walls[0].x, walls[0].y, walls[4].x, walls[4].y);
    drawLine(walls[4].x, walls[4].y, walls[5].x, walls[5].y);
    drawLine(walls[5].x, walls[5].y, walls[1].x, walls[1].y);

    //ściany boczne
    drawLine(walls[0].x, walls[0].y, walls[3].x, walls[3].y);
    drawLine(walls[1].x, walls[1].y, walls[2].x, walls[2].y);
    drawLine(walls[4].x, walls[4].y, walls[7].x, walls[7].y);
    drawLine(walls[5].x, walls[5].y, walls[6].x, walls[6].y);

    walls.clear();
    update();
}

void MyWindow::addPoint(int x, int y, int z)
{
    walls.push_back(point());
    walls[walls.size() - 1].x = x;
    walls[walls.size() - 1].y = y;
    walls[walls.size() - 1].z = z;
}


void MyWindow::drawLine(double x1,double y1,double x2,double y2)
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
               ptr[i*4+1]=255;
               ptr[i*4+2]=0;
            }
        }
        if(x1==x2)
        {
            ptr[(int)x1*4]=0;
            ptr[(int)x1*4+1]=255;
            ptr[(int)x1*4+2]=0;
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
               ptr[i*4+1]=255;
               ptr[i*4+2]=0;
            }
        }
    }
}
