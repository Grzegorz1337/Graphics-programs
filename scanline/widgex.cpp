#include "widgex.h"
#include "mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>
#include <iostream>

widgex::widgex(QWidget *parent) :
    QWidget(parent)
{
    img = new QImage(571, 341, QImage::Format_RGB32);
    img->fill(Qt::black);

}

void widgex::paintEvent(QPaintEvent *)
{
    QPainter p(this);
//    p.fillRect(0,0,width(), height(), Qt::green);
    p.drawImage(0,0,*img);
    update();
}

void widgex::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        p.x = e->x();
        p.y = e->y();
if(mode==1){ punkty.push_back(p); setPoint(); }
if(mode==2){ deletePoint(); }
//if(punkty.size() > 1 && punkty.size() % 3 == 1 && mode == 1){  Bezier(); }
if(mode==4) { floodFill(e->x(),e->y(),0,255); }
if(mode==5) {
  drawLine(punkty[punkty.size()-1].x,punkty[punkty.size()-1].y, punkty[0].x,punkty[0].y);
  scanline(punkty, 255, 255, 255);
  mode = 1;
}
}

     update();
}

void widgex::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        q.x = e -> x();
        q.y = e -> y();
        if(mode==3){


            for(uint i = 0; i < punkty.size(); i++){
                    if(abs(punkty[i].x - p.x) < 6 && abs(punkty[i].y - p.y) < 6){
                        punkty[i].x = q.x;
                                   punkty[i].y = q.y;
                            }
                        }

                              img->fill(0x000000);
                              check = 0;
                           setPoint();

                          // int i = 1;
//                           while(3 * i + 1 <= punkty.size()){
//                               i++;
//                               Bezier();
                                scanline(punkty,255,255,255);
//                           }

        }
    }


    update();
}
void widgex::setPoint()
{
    for(uint k = 0; k < punkty.size(); k++){
        for(int i = -3; i <= 3; i++){
            for(int j = -3; j <= 3; j++){
                setPixel(j + punkty[k].x, i + punkty[k].y, 255, 255, 255);
            }
        }
    }
    update();
}

void widgex::deletePoint()
{

       for(uint a = 0; a < punkty.size(); a++){
            if(abs(punkty[a].x - p.x) < 6 && abs(punkty[a].y - p.y) < 6){

                for(int i = -3; i <= 3; i++){
                    for(int j = -3; j <= 3; j++){
                setPixel(j + punkty[a].x, i + punkty[a].y, 0, 0, 0);
                    }
                }
                punkty.erase(punkty.begin() + a);
            }
       }
       img->fill(0x000000);
       check = 0;

       if(punkty.size()>0){
           setPoint();
           int i = 1;
//           while(3 * i + 1 <= punkty.size()){
//               i++;
//               Bezier();
               scanline(punkty,255,255,255);
//             }
      }



    update();
}


void widgex::Bezier()
{
    int N = 20;
        uint i = check;
        double tmp = punkty[i].x;
        double tmp2 = punkty[i].y;
        for(int k = 0; k <= N; k++){
            double t = (double)k/N;
            p.x = pow((1-t),3)*punkty[i].x + 3*pow((1-t),2)*t*punkty[i+1].x + 3*(1-t)*pow(t,2)*punkty[i+2].x + pow(t,3)*punkty[i+3].x;
            p.y = pow((1-t),3)*punkty[i].y+3*pow((1-t),2)*t*punkty[i+1].y+3*(1-t)*pow(t,2)*punkty[i+2].y+pow(t,3)*punkty[i+3].y;

            drawLine(p.x,p.y,tmp,tmp2);
            tmp = p.x;
            tmp2 = p.y;
        }

    check = i+3;
    update();
}


void widgex::dodajzmienionypunkt(){ mode = 1; }

void widgex::usunzmienionypunkt(){ mode = 2; }

void widgex::przesunzmienionypunkt(){ mode = 3; }

void widgex::floodmode(){ mode = 4; }

void widgex::scanmode(){ mode = 5; cout<<"mode=6n"; }

void widgex::drawLine(float x1, float y1, float x2, float y2)
{
   if(abs(x1 - x2) >= abs(y1 - y2)){
          if(x2 < x1){
              std::swap(x1,x2);
              std::swap(y1,y2);
          }
          for(int x = x1; x <= x2; x++){
              float a = (float)(x - x1)/(x2 - x1);
              float y = (float)y1 + a * (y2 - y1);
              setPixel(x,y,255,255,255);
          }
      }else{
          if(y2 < y1){
              std::swap(x1,x2);
              std::swap(y1,y2);
          }
          for(int y = y1; y <= y2; y++){
              float a = (float)(y - y1)/(y2 - y1);
              float x = (float)x1 + a * (x2 - x1);
              setPixel(x,y,255,255,255);
          }
      }
}

void widgex::setPixel(int x, int y, int r, int g, int b)
{
    if(x >= 0 && y >= 0 && x < img->width() && y < img->height()){
        uchar *pix= img->scanLine(y);
        pix[4*x]=r;
        pix[4*x+1]=g;
        pix[4*x+2]=b;
        }
}

void widgex::floodFill(int x,int y,int oldcolor,int newcolor)
{
    if(oldcolor == newcolor){
        return;
    }
    Qx.push(x);
    Qy.push(y);
    int x1;
    int y1;

    while(!Qx.empty()){
      //  qDebug() << newC.r << newC.g << newC.b;
        x1 = Qx.top();
        y1 = Qy.top();

        Qx.pop();
        Qy.pop();
        if(getpixel(x1,y1) == 3*oldcolor)
            {
            setPixel(x1,y1,255,255,255);
            if(x1-1 >= 0 && y1 >= 0 && x1-1 < img->width() && y1 < img->height()){
            Qx.push(x1-1);
            Qy.push(y1);
            }

            if(x1+1 >= 0 && y1 >= 0 && x1+1 < img->width() && y1 <  img->height()){
            Qx.push(x1+1);
            Qy.push(y1);
            }

            if(x1 >= 0 && y1+1 >= 0 && x1 < img->width() && y1+1 < img->height()){
            Qx.push(x1);
            Qy.push(y1+1);
            }

            if(x1 >= 0 && y1-1 >= 0 && x1 < img->width() && y1-1 < img->height()){
            Qx.push(x1);
            Qy.push(y1-1);
        }
    }
}
}
int widgex::getpixel(int x, int y)
{

        uchar *pixs= img->scanLine(y);
     int pixa = (int) pixs[4*x];
int pixa2 = (int) pixs[4*x+1];
int pixa3 = (int) pixs[4*x+2];
      return  pixa+pixa2+pixa3;

}

void widgex::sort_point(vector<Pkt> &wsk)
{
    for(uint j = 0 ; j < wsk.size()-1; j++){
        for(uint i = 0 ; i < wsk.size()-1; i++){
            if(wsk[i].y > wsk[i+1].y) {
                swap(wsk[i].x, wsk[i+1].x);
                swap(wsk[i].y, wsk[i+1].y);
            }
            if(wsk[i].y == wsk[i+1].y) {
                if(wsk[i].x > wsk[i+1].x){
                    swap(wsk[i].x, wsk[i+1].x);
                    swap(wsk[i].y, wsk[i+1].y);
                 }
            }
        }
    }
}

void widgex::scanline(vector<Pkt> pkt, int r, int g, int b)
{
//inizlizacja pierwszych pkt
    int miny = pkt[0].y;
    int maxy = pkt[0].y;

    //Petla w której wyszukujemy punkt z minmalna wartoscia y i punkt z maksymalna wartoscia y
    for(uint i = 0 ; i < pkt.size(); i++){
        if(miny > pkt[i].y){
            miny = pkt[i].y;
        }
        if(pkt[i].y > maxy){
            maxy = pkt[i].y;
        }
    }
// punkty przecięcia linii skanującej z krawędziami wielokąta
    vector<Pkt>  punkty_przeciecia;

    //przechodzimy wszystkie linie
    for(int y = miny; y < maxy; y++){

       punkty_przeciecia.clear();
        for(uint i = 0; i < pkt.size(); i++){
            float tmpx = pkt[i].x;
            float tmpy = pkt[i].y;

            float tmpx1 = pkt[(i+1) % pkt.size()].x;
            float tmpy1 = pkt[(i+1) % pkt.size()].y;


            //czy pkt nie jest poza y (ponizej,powyzej)
           if(((tmpy < tmpy1) && ((y < tmpy) || (y >= tmpy1))) || ((tmpy >= tmpy1) && ((y >= tmpy) || (y < tmpy1)))){
                continue;
            }else{
               if((tmpy1 - tmpy) == 0){
                   continue;
                }else{
                   p.x = tmpx + ((y - tmpy) / (tmpy1 - tmpy)) * (tmpx1 - tmpx);
                   p.y = y;
                   punkty_przeciecia.push_back(p);
                }
            }
       }
//sortowanie punktów przecięcia z lini skanującej z krawędziąmi wielokata
   sort_point(punkty_przeciecia);

   for(uint i = 0; i < punkty_przeciecia.size(); i+=2){
       //wypelnianie wielokata poprzez rysowanie lini z uzyskanych pkt
       drawLine(punkty_przeciecia[i].x, punkty_przeciecia[i].y, punkty_przeciecia[(i+1) % punkty_przeciecia.size()].x, punkty_przeciecia[i].y);
    }
  }
}


void widgex::erozjamode(){ erosion(); update(); copy(); }
void widgex::dylacjamode(){ dilatation(); update(); copy(); }
void widgex::otwarciemode(){ erosion(); copy();  dilatation(); update(); }
void widgex::zamknieciemode(){ dilatation(); copy(); erosion(); update(); }

void widgex::imgmode(){
    img = new QImage("img3.jpg");
   // img->fill(Qt::white);
    widtha = 258;
    heighta = 288;
    tempimg = new uchar[widtha*widtha*4];
    tempimg1 = new uchar[widtha*heighta*4];

    tempimg = img->bits();
   memcpy(tempimg1, tempimg, widtha*heighta*4);

}

void widgex::erosion()
{
    int i, j;
    for (i = 0; i < heighta ; ++i) {
        for (j = 0; j < widtha ; ++j) {
            int size = 4*widtha*i + 4*j;
            if(tempimg[size] < 128 || tempimg[size + 1] < 128 || tempimg[size + 2 ] < 128 )
            {

                if(i-1 >= 0 && j-1 >= 0){
                    if(tempimg[4*widtha*(i-1) + 4*(j-1)] == 255)
                    {
                        tempimg1[size] = 255;
                        tempimg1[size + 1] = 255;
                        tempimg1[size + 2] = 255;
                    }
                }

                if(i-1 >= 0){
                    if(tempimg[4*widtha*(i-1) + 4*(j)] == 255)
                    {
                        tempimg1[size] = 255;
                        tempimg1[size + 1] = 255;
                        tempimg1[size + 2] = 255;
                    }
                }

                if(i-1 >= 0 && j+1 < widtha){
                    if(tempimg[4*widtha*(i-1) + 4*(j+1)] == 255)
                    {
                        tempimg1[size] = 255;
                        tempimg1[size + 1] = 255;
                        tempimg1[size + 2] = 255;
                    }
                }

                if(j-1 >= 0){
                    if(tempimg[4*widtha*(i) + 4*(j-1)] == 255)
                    {
                        tempimg1[size] = 255;
                        tempimg1[size + 1] = 255;
                        tempimg1[size + 2] = 255;
                    }
                }

                if(j+1 >= widtha){
                    if(tempimg[4*widtha*(i) + 4*(j+1)] == 255)
                    {
                        tempimg1[size] = 255;
                        tempimg1[size + 1] = 255;
                        tempimg1[size + 2] = 255;
                    }
                }

                if(i+1 <= heighta && j-1 >= 0){
                    if(tempimg[4*widtha*(i+1) + 4*(j-1)] == 255)
                    {
                        tempimg1[size] = 255;
                        tempimg1[size + 1] = 255;
                        tempimg1[size + 2] = 255;
                    }
                }

                if(i+1 >= heighta){
                    if(tempimg[4*widtha*(i+1) + 4*(j)] == 255)
                    {
                        tempimg1[size] = 255;
                        tempimg1[size + 1] = 255;
                        tempimg1[size + 2] = 255;
                    }
                }

                if(i+1 <= heighta && j+1 <= widtha){
                    if(tempimg[4*widtha*(i+1) + 4*(j+1)] == 255)
                    {
                        tempimg1[size] = 255;
                        tempimg1[size + 1] = 255;
                        tempimg1[size + 2] = 255;
                    }
                }

            }
            else{
                tempimg1[size+1] = 255;
                tempimg1[size] = 255;
                tempimg1[size + 2] = 255;
            }


        }
    }

}

void widgex::dilatation()
{

    int i, j;
    for (i = 0; i < heighta ; ++i) {
        for (j = 0; j < widtha ; ++j) {
            int size = 4*widtha*i + 4*j;
            if(tempimg[size] < 256 || tempimg[size + 1] < 256 || tempimg[size + 2 ] < 256 )
            {

                if(i-1 >= 0 && j-1 >= 0){
                    if(tempimg[4*widtha*(i-1) + 4*(j-1)] == 0)
                    {
                        tempimg1[size] = 0;
                        tempimg1[size + 1] = 0;
                        tempimg1[size + 2] = 0;
                    }
                }

                if(i-1 >= 0){
                    if(tempimg[4*widtha*(i-1) + 4*(j)] == 0)
                    {
                        tempimg1[size] = 0;
                        tempimg1[size + 1] = 0;
                        tempimg1[size + 2] = 0;
                    }
                }

                if(i-1 >= 0 && j+1 < widtha){
                    if(tempimg[4*widtha*(i-1) + 4*(j+1)] == 0)
                    {
                        tempimg1[size] = 0;
                        tempimg1[size + 1] = 0;
                        tempimg1[size + 2] = 0;
                    }
                }

                if(j-1 >= 0){
                    if(tempimg[4*widtha*(i) + 4*(j-1)] == 0)
                    {
                        tempimg1[size] = 0;
                        tempimg1[size + 1] = 0;
                        tempimg1[size + 2] = 0;
                    }
                }

                if(j+1 >= widtha){
                    if(tempimg[4*widtha*(i) + 4*(j+1)] == 0)
                    {
                        tempimg1[size] = 0;
                        tempimg1[size + 1] = 0;
                        tempimg1[size + 2] = 0;
                    }
                }

                if(i+1 <= heighta && j-1 >= 0){
                    if(tempimg[4*widtha*(i+1) + 4*(j-1)] == 0)
                    {
                        tempimg1[size] = 0;
                        tempimg1[size + 1] = 0;
                        tempimg1[size + 2] = 0;
                    }
                }

                if(i+1 >= heighta){
                    if(tempimg[4*widtha*(i+1) + 4*(j)] == 0)
                    {
                        tempimg1[size] = 0;
                        tempimg1[size + 1] = 0;
                        tempimg1[size + 2] = 0;
                    }
                }

                if(i+1 <= heighta && j+1 <= widtha){
                    if(tempimg[4*widtha*(i+1) + 4*(j+1)] == 0)
                    {
                        tempimg1[size] = 0;
                        tempimg1[size + 1] = 0;
                        tempimg1[size + 2] = 0;
                    }
                }

            }
            else{
                tempimg1[size+1] = 255;
                tempimg1[size] = 255;
                tempimg1[size + 2] = 255;
            }


        }
    }

}
void widgex::copy()
{
    for (int i = 1; i < heighta-1; ++i) {
        for (int j = 1; j < widtha-1; ++j) {
            tempimg[widtha*4*i + 4*j + 2] = tempimg1[widtha*4*i + 4*j + 2];
            tempimg[widtha*4*i + 4*j] = tempimg1[widtha*4*i + 4*j];
            tempimg[widtha*4*i + 4*j + 1] = tempimg1[widtha*4*i + 4*j + 1];
        }
    }
   // tempimg1 = img.bits();
  // memcpy(tempimg, tempimg1, widtha*heighta*4);
}
