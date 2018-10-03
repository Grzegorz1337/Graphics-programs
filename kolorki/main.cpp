#include <QApplication>
#include <QLabel>
#include <stack>
#include "MyWidget.h"


//----------------------------------


int main( int argc, char ** argv )
{
    QApplication a( argc, argv );
    MyWidget m;
    m.show();
    //m.connect(m.r,SIGNAL(valueChanged(int)),m.img,SLOT(koloruj('r')));
    //a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
