#include "mywindow.h"
#include "ui_mywindow.h"
#include "cmath"
#include "iostream"
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

    img0 = new QImage(szer, wys, QImage::Format_RGB32);
    img0 -> load(":/img.png");
    ptr0 = img0 -> bits();

    img = new QImage(szer, wys, QImage::Format_RGB32);
    img -> load(":/img.png");
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

void MyWindow::on_reset_clicked()
{
    img = new QImage(szer, wys, QImage::Format_RGB32);
    img -> load(":/img.png");
    ptr = img -> bits();

    AtBtCt_T.clear();
    ABC_T.clear();

    movingPoint = false;

    ui -> przesun -> setEnabled(false);
    ui -> rysuj -> setChecked(true);

    update();
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX, poczY, *img);
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{
    releaseX = event -> x() - poczX;
    releaseY = event -> y() - poczY;

    if (event -> button() == Qt::LeftButton && (releaseX >= 0) && (releaseY >= 0) && (releaseX < szer) && (releaseY < wys))
    {
        if (ui -> rysuj -> isChecked())
        {
            if (AtBtCt_T.size() + ABC_T.size() < 6)
            {
                if (AtBtCt_T.size() < 3)
                {
                    addPoint(releaseX, releaseY, AtBtCt_T);
                }
                else
                {
                    addPoint(releaseX, releaseY, ABC_T);
                }

                if (AtBtCt_T.size() == 3 && ABC_T.size() == 3)
                {
                    texture();
                    ui -> przesun -> setEnabled(true);
                }
            }
        }
        else if (ui -> przesun -> isChecked())
        {
            movingPoint = false;
        }
    }
    update();
}

void MyWindow::addPoint(double x, double y, std::vector<point> &hAlp)
{
    hAlp.push_back(point());
    hAlp[hAlp.size() - 1].x = x;
    hAlp[hAlp.size() - 1].y = y;

    if (hAlp.size() >= 2)
    {
        drawLine(hAlp[hAlp.size() - 2].x, hAlp[hAlp.size() - 2].y, hAlp[hAlp.size() - 1].x, hAlp[hAlp.size() - 1].y, 1);

        if (hAlp.size() == 3)
        {
            drawLine(hAlp[hAlp.size() - 1].x, hAlp[hAlp.size() - 1].y, hAlp[hAlp.size() - 3].x, hAlp[hAlp.size() - 3].y, 1);
        }
    }
    drawPoint(x, y, 1);
}

void MyWindow::texture()
{
    int min_X = ABC_T[0].x, max_X = ABC_T[0].x, min_Y = ABC_T[0].y, max_Y = ABC_T[0].y, interpolation_R, interpolation_G, interpolation_B;
    point A = ABC_T[0], B = ABC_T[1], C = ABC_T[2], At = AtBtCt_T[0], Bt = AtBtCt_T[1], Ct = AtBtCt_T[2];
    double u, v, w, Xt, Yt;

    for (unsigned int i = 0; i < ABC_T.size(); i++)
    {
        if (min_X > ABC_T[i].x)
        {
            min_X = ABC_T[i].x;
        }

        if (max_X < ABC_T[i].x)
        {
            max_X = ABC_T[i].x;
        }

        if (min_Y > ABC_T[i].y)
        {
            min_Y = ABC_T[i].y;
        }

        if (max_Y < ABC_T[i].y)
        {
            max_Y = ABC_T[i].y;
        }
    }

    for (int i = min_Y; i <= max_Y; i++)
    {
        for (int j = min_X; j <= max_X; j++)
        {
            v = (((j - A.x) * (C.y - A.y)) - ((C.x - A.x) * (i - A.y))) / (((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y)));
            w = (((B.x - A.x) * (i - A.y)) - ((j - A.x) * (B.y - A.y))) / (((B.x - A.x) * (C.y - A.y)) - ((C.x - A.x) * (B.y - A.y)));
            u = 1 - v - w;

            if (u > 0 && u < 1 && v > 0 && v < 1 && w > 0 && w < 1)
            {
                Xt = u * At.x + v * Bt.x + w * Ct.x;
                Yt = u * At.y + v * Bt.y + w * Ct.y;

                interpolation_R = (Yt - floor(Yt)) * ((1 - (Xt - floor(Xt))) * getPixelColor(floor(Xt), floor(Yt) + 1, 'r') + (Xt - floor(Xt)) * getPixelColor(floor(Xt) + 1, floor(Yt) + 1, 'r')) + (1 - (Yt - floor(Yt))) * ((1 - (Xt - floor(Xt))) * getPixelColor(floor(Xt), floor(Yt), 'r') + (Xt - floor(Xt)) * getPixelColor(floor(Xt) + 1, floor(Yt), 'r'));
                interpolation_G = (Yt - floor(Yt)) * ((1 - (Xt - floor(Xt))) * getPixelColor(floor(Xt), floor(Yt) + 1, 'g') + (Xt - floor(Xt)) * getPixelColor(floor(Xt) + 1, floor(Yt) + 1, 'g')) + (1 - (Yt - floor(Yt))) * ((1 - (Xt - floor(Xt))) * getPixelColor(floor(Xt), floor(Yt), 'g') + (Xt - floor(Xt)) * getPixelColor(floor(Xt) + 1, floor(Yt), 'g'));
                interpolation_B = (Yt - floor(Yt)) * ((1 - (Xt - floor(Xt))) * getPixelColor(floor(Xt), floor(Yt) + 1, 'b') + (Xt - floor(Xt)) * getPixelColor(floor(Xt) + 1, floor(Yt) + 1, 'b')) + (1 - (Yt - floor(Yt))) * ((1 - (Xt - floor(Xt))) * getPixelColor(floor(Xt), floor(Yt), 'b') + (Xt - floor(Xt)) * getPixelColor(floor(Xt) + 1, floor(Yt), 'b'));

                setPixelColor(j, i, interpolation_R, interpolation_G, interpolation_B);
            }
        }
    }
    redrawTriangle(ABC_T, 1);
}

void MyWindow::drawPoint(int x, int y, int mode)
{
    for (int i = x - 2; i <= x + 2; i++)
    {
        for (int j = y - 2; j <= y + 2; j++)
        {
            if (mode == 1)
            {
                setPixelColor(i, j, 255, 255, 0);
            }
            else
            {
                setPixelColor(i, j, getPixelColor(i, j, 'r'), getPixelColor(i, j, 'g'), getPixelColor(i, j, 'b'));
            }
        }
    }
    update();
}

void MyWindow::mouseMoveEvent(QMouseEvent *event)
{
    actualX = event -> x() - poczX;
    actualY = event -> y() - poczY;

    if (movingPoint && (actualX >= 0) && (actualY >= 0) && (actualX < szer) && (actualY < wys))
    {
        if (movePointFromVector == 0)
        {
            redrawTriangle(AtBtCt_T, 0);

            AtBtCt_T[moveIndex].x = event -> x() - poczX;
            AtBtCt_T[moveIndex].y = event -> y() - poczY;

            redrawTriangle(AtBtCt_T, 1);
        }
        else
        {
            img = new QImage(szer, wys, QImage::Format_RGB32);
            img -> load(":/img.png");
            ptr = img -> bits();

            redrawTriangle(ABC_T, 0);
            redrawTriangle(AtBtCt_T, 1);

            ABC_T[moveIndex].x = event -> x() - poczX;
            ABC_T[moveIndex].y = event -> y() - poczY;

            redrawTriangle(ABC_T, 1);
        }
        texture();
        update();
    }
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    pressX = event -> x() - poczX;
    pressY = event -> y() - poczY;

    if (event -> button() == Qt::LeftButton && ui -> przesun -> isChecked() && (releaseX >= 0) && (releaseY >= 0) && (releaseX < szer) && (releaseY < wys))
    {
        for (int i = 0; i < 3; i++)
        {
            if (pressX >= AtBtCt_T[i].x - 2 && pressX <= AtBtCt_T[i].x + 2 && pressY >= AtBtCt_T[i].y - 2 && pressY <= AtBtCt_T[i].y + 2)
            {
                movePointFromVector = 0;
                moveIndex = i;
                movingPoint = true;
                break;
            }
            else if (pressX >= ABC_T[i].x - 2 && pressX <= ABC_T[i].x + 2 && pressY >= ABC_T[i].y - 2 && pressY <= ABC_T[i].y + 2)
            {
                movePointFromVector = 1;
                moveIndex = i;
                movingPoint = true;
                break;
            }
        }
    }
}

void MyWindow::redrawTriangle(std::vector<point> &hAlp, int mode)
{
    for (unsigned int i = 0; i < hAlp.size(); i++)
    {
        if (mode == 1)
        {
            drawPoint(hAlp[i].x, hAlp[i].y, 1);
        }
        else
        {
            drawPoint(hAlp[i].x, hAlp[i].y, 0);
        }
    }

    for (int i = 0; i <= 2; i++)
    {
        if (i < 2)
        {
            if (mode == 1)
            {
                drawLine(hAlp[i].x, hAlp[i].y, hAlp[i + 1].x, hAlp[i + 1].y, 1);
            }
            else
            {
                drawLine(hAlp[i].x, hAlp[i].y, hAlp[i + 1].x, hAlp[i + 1].y, 0);
            }
        }
        else
        {
            if (mode == 1)
            {
                drawLine(hAlp[i].x, hAlp[i].y, hAlp[i - 2].x, hAlp[i - 2].y, 1);
            }
            else
            {
                drawLine(hAlp[i].x, hAlp[i].y, hAlp[i - 2].x, hAlp[i - 2].y, 0);
            }
        }
    }
}

void MyWindow::drawLine(double startX, double startY, double endX, double endY, int mode)
{
    double a, b, hAlp;
    int x, y;

    if (abs(startX - endX) >= abs(startY - endY))
    {
        if (startX > endX)
        {
            hAlp = startX;
            startX = endX;
            endX = hAlp;
            hAlp = startY;
            startY = endY;
            endY = hAlp;
        }
        a = (endY - startY) / (endX - startX);
        b = endY - (a * endX);

        for (int i = startX; i <= endX; i++)
        {
            y = round((a * i) + b);

            if (mode == 1)
            {
                setPixelColor(i, y, 255, 255, 0);
            }
            else
            {
                setPixelColor(i, y, getPixelColor(i, y, 'r'), getPixelColor(i, y, 'g'), getPixelColor(i, y, 'b'));
            }
        }
    }
    else
    {
        if (startY > endY)
        {
            hAlp = startX;
            startX = endX;
            endX = hAlp;
            hAlp = startY;
            startY = endY;
            endY = hAlp;
        }
        a = (endX - startX) / (endY - startY);
        b = endX - (a * endY);

        for (int i = startY; i <= endY; i++)
        {
            x = round((a * i) + b);

            if (mode == 1)
            {
                setPixelColor(x, i, 255, 255, 0);
            }
            else
            {
                setPixelColor(x, i, getPixelColor(x, i, 'r'), getPixelColor(x, i, 'g'), getPixelColor(x, i, 'b'));
            }
        }
    }
    update();
}

int MyWindow::getPixelColor(int x, int y, char part)
{
    if ((x >= 0) && (y >= 0) && (x < szer) && (y < wys))
    {
        switch (part)
        {
            case 'r':
                return ptr0[szer*4*y + 4*x + 2];
                break;
            case 'g':
                return ptr0[szer*4*y + 4*x + 1];
                break;
            case 'b':
                return ptr0[szer*4*y + 4*x];
                break;
        }
    }
    return 0;
}

void MyWindow::setPixelColor(int x, int y, int r, int g, int b)
{
    if ((x >= 0) && (y >= 0) && (x < szer) && (y < szer))
    {
        ptr[szer*4*y + 4*x + 2] = r;
        ptr[szer*4*y + 4*x + 1] = g;
        ptr[szer*4*y + 4*x] = b;
    }
}
