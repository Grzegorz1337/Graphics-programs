#include "mywindow.h"
#include "ui_mywindow.h"
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
    movingPoint = false;
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

void MyWindow::on_dodaj_clicked()
{
    mode = 0;
}

void MyWindow::on_przesun_clicked()
{
    mode = 1;
}

void MyWindow::on_usun_clicked()
{
    mode = 2;
}

void MyWindow::on_reset_clicked()
{
    clear();
    update();
}

void MyWindow::clear()
{
    int i, j;
    for (i = 0; i < wys; i++)
    {
        for (j = 0; j < szer; j++)
        {
            setPixelColor(j, i, 255, 255, 255);
        }
    }
    T.clear();
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    pressX = event -> x() - poczX;
    pressY = event -> y() - poczY;

    if (event -> button() == Qt::LeftButton && mode == 1 && (releaseX >= 0) && (releaseY >= 0) && (releaseX < szer) && (releaseY < wys))
    {
        for (unsigned int i = 0; i < T.size(); i++)
        {
            if (pressX >= T[i].x - 2 && pressX <= T[i].x + 2 && pressY >= T[i].y - 2 && pressY <= T[i].y + 2)
            {
                moveIndex = i;
                movingPoint = true;
            }
        }
    }
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    releaseX = event -> x() - poczX;
    releaseY = event -> y() - poczY;

    if (event -> button() == Qt::LeftButton && (releaseX >= 0) && (releaseY >= 0) && (releaseX < szer) && (releaseY < wys))
    {
        if (mode == 0)
        {
            addPoint(releaseX, releaseY);
        }
        else if (mode == 1)
        {
            movingPoint = false;
        }

        else if (mode == 2)
        {
            for (unsigned int i = 0; i < T.size(); i++)
            {
                if (releaseX >= T[i].x - 2 && releaseX <= T[i].x + 2 && releaseY >= T[i].y - 2 && releaseY <= T[i].y + 2)
                {
                    removePoint(i);
                }
            }
        }
    }
    update();
}

void MyWindow::drawLine(int startPos, int mode)
{
    float scoreX, scoreY;
    std::vector<point> k;
    for (float t = 0; t <= 1.000; t += 0.1)
    {
        scoreX = ((1-t)*(1-t)*(1-t))*T[startPos + 0].x + 3*((1-t)*(1-t))*t*T[startPos + 1].x + 3*(1-t)*(t*t)*T[startPos + 2].x + (t*t*t)*T[startPos + 3].x;
        scoreY = ((1-t)*(1-t)*(1-t))*T[startPos + 0].y + 3*((1-t)*(1-t))*t*T[startPos + 1].y + 3*(1-t)*(t*t)*T[startPos + 2].y + (t*t*t)*T[startPos + 3].y;

        if (mode == 1)
        {
            setPixelColor(floor(scoreX), floor(scoreY), 0, 0, 0);
            point c;
            c.x = scoreX;
            c.y = scoreY;
            k.push_back(c);
        }
        else
        {
            setPixelColor(floor(scoreX), floor(scoreY), 255, 255, 255);
        }
    }
    for(unsigned int i=0;i<k.size()-1;i++)
    {
        drawLine2(k[i].x,k[i].y,k[i+1].x,k[i+1].y);
    }
    update();
}

void MyWindow::drawLine2(int x1,int y1,int x2,int y2)
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

void MyWindow::addPoint(int x, int y)
{
    T.push_back(point());
    T[T.size() - 1].x = x;
    T[T.size() - 1].y = y;

    drawPoint(x, y, 1);

    if (((T.size() - 4) % 3 == 0) && T.size() >= 4)
    {
        drawLine(T.size() - 4, 1);
    }
}

void MyWindow::removePoint(int index)
{
    unsigned int i = 0;
    drawPoint(T[index].x, T[index].y, 0);

    while (i + 3 < T.size())
    {
        drawLine(i, 0);
        i += 3;
    }

    T.erase(T.begin() + index);
    i = 0;

    while (i + 3 < T.size())
    {
        drawLine(i, 1);
        i += 3;
    }
    redrawPoints();
    update();
}

void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    actualX = event->x() - poczX;
    actualY = event->y() - poczY;

    if (movingPoint && (actualX >= 0) && (actualY >= 0) && (actualX < szer) && (actualY < wys))
    {
        unsigned int i = 0;
        drawPoint(T[moveIndex].x, T[moveIndex].y, 0);

        while (i + 3 < T.size())
        {
            drawLine(i, 0);
            i += 3;
        }
        T[moveIndex].x = event->x() - poczX;
        T[moveIndex].y = event->y() - poczY;

        drawPoint(T[moveIndex].x, T[moveIndex].y, 1);

        i = 0;

        while (i + 3 < T.size())
        {
            drawLine(i, 1);
            i += 3;
        }
        redrawPoints();
        update();
    }
}

void MyWindow::drawPoint(int x, int y, int mode)
{
    for (int iX = x - 2; iX <= x + 2; iX++)
    {
        for (int iY = y - 2; iY <= y + 2; iY++)
        {
            if (mode == 1)
            {
                setPixelColor(iX, iY, 255, 0, 0);
            }
            else
            {
                setPixelColor(iX, iY, 255, 255, 255);
            }
        }
    }
    update();
}

void MyWindow::redrawPoints()
{
    for (unsigned int i = 0; i < T.size(); i++)
    {
        drawPoint(T[i].x, T[i].y, 1);
    }
}


void MyWindow::setPixelColor(int x, int y, int r, int g, int b)
{
    if ((x >= 0) && (y >= 0) && (x < szer) && (y < wys))
    {
        ptr[szer*4*y + 4*x + 2] = r;
        ptr[szer*4*y + 4*x + 1] = g;
        ptr[szer*4*y + 4*x] = b;
    }
}


