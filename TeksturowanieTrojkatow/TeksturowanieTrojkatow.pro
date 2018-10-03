QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeksturowanieTrojkatow
TEMPLATE = app


SOURCES += main.cpp\
        mywindow.cpp

HEADERS  += mywindow.h

FORMS    += mywindow.ui

RESOURCES += \
    zasoby.qrc
