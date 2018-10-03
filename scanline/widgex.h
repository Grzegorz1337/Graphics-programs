#ifndef WIDGEX_H
#define WIDGEX_H
using namespace std;
#include <QWidget>
#include <stack>
struct Pkt{
    int x;
    int y;
};
class widgex : public QWidget
{
    Q_OBJECT
public:
    explicit widgex(QWidget *parent = 0);
    vector<Pkt> punkty;
    Pkt p, q;
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
    stack<int> Qx;
    stack<int> Qy;
    vector <Pkt> point;
   // vector<QPoint> ob;
private:
        QImage *img;
         int r,g,b;
         void setPixel(int x, int y, int r, int g, int b);
         void drawLine(float x1, float y1, float x2, float y2);
          void setPoint();
          void deletePoint();
            void Bezier();
          int mode = 0;
           uint check = 0;
           void floodFill(int x,int y,int oldcolor,int newcolor);
           int getpixel(int x, int y);
           void sort_point(vector <Pkt> &wsk);
           void scanline(vector<Pkt> pkt, int r, int g, int b);
           int widtha, heighta;
           void dilatation();
           void erosion();
           unsigned char *tempimg, *tempimg1;
           void copy();
signals:

public slots:
    void dodajzmienionypunkt();
    void usunzmienionypunkt();
    void przesunzmienionypunkt();
        void floodmode();
         void scanmode();
         void erozjamode();
         void dylacjamode();
         void otwarciemode();
         void zamknieciemode();
          void imgmode();
};

#endif // WIDGEX_H
