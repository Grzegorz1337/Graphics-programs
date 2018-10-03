/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "widgex.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *a;
    QPushButton *d;
    QPushButton *m;
    widgex *widget;
    QPushButton *fa;
    QPushButton *sc;
    QGroupBox *groupBox;
    QPushButton *erozja;
    QPushButton *dylacja;
    QPushButton *otwarcie;
    QPushButton *zamkniecie;
    QPushButton *zaladuj;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(813, 450);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        a = new QPushButton(centralWidget);
        a->setObjectName(QStringLiteral("a"));
        a->setGeometry(QRect(30, 60, 51, 41));
        QIcon icon;
        icon.addFile(QStringLiteral("../Pobrane/plus(1).png"), QSize(), QIcon::Normal, QIcon::Off);
        a->setIcon(icon);
        d = new QPushButton(centralWidget);
        d->setObjectName(QStringLiteral("d"));
        d->setGeometry(QRect(80, 60, 41, 41));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../Pobrane/clear-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        d->setIcon(icon1);
        m = new QPushButton(centralWidget);
        m->setObjectName(QStringLiteral("m"));
        m->setGeometry(QRect(120, 60, 61, 41));
        QIcon icon2;
        icon2.addFile(QStringLiteral("../Pobrane/move-option.png"), QSize(), QIcon::Normal, QIcon::Off);
        m->setIcon(icon2);
        widget = new widgex(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(190, 30, 571, 341));
        fa = new QPushButton(centralWidget);
        fa->setObjectName(QStringLiteral("fa"));
        fa->setGeometry(QRect(30, 130, 75, 23));
        sc = new QPushButton(centralWidget);
        sc->setObjectName(QStringLiteral("sc"));
        sc->setGeometry(QRect(110, 130, 75, 23));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 220, 120, 151));
        erozja = new QPushButton(groupBox);
        erozja->setObjectName(QStringLiteral("erozja"));
        erozja->setGeometry(QRect(20, 30, 75, 23));
        dylacja = new QPushButton(groupBox);
        dylacja->setObjectName(QStringLiteral("dylacja"));
        dylacja->setGeometry(QRect(20, 60, 75, 23));
        otwarcie = new QPushButton(groupBox);
        otwarcie->setObjectName(QStringLiteral("otwarcie"));
        otwarcie->setGeometry(QRect(20, 90, 75, 23));
        zamkniecie = new QPushButton(groupBox);
        zamkniecie->setObjectName(QStringLiteral("zamkniecie"));
        zamkniecie->setGeometry(QRect(20, 120, 75, 23));
        zaladuj = new QPushButton(centralWidget);
        zaladuj->setObjectName(QStringLiteral("zaladuj"));
        zaladuj->setGeometry(QRect(54, 180, 91, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 813, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        a->setText(QApplication::translate("MainWindow", "dodaj", nullptr));
        d->setText(QApplication::translate("MainWindow", "usun", nullptr));
        m->setText(QApplication::translate("MainWindow", "przesun", nullptr));
        fa->setText(QApplication::translate("MainWindow", "flood", nullptr));
        sc->setText(QApplication::translate("MainWindow", "scanline", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Operacje morfologiczne", nullptr));
        erozja->setText(QApplication::translate("MainWindow", "erozja", nullptr));
        dylacja->setText(QApplication::translate("MainWindow", "dylacja", nullptr));
        otwarcie->setText(QApplication::translate("MainWindow", "otwarcie", nullptr));
        zamkniecie->setText(QApplication::translate("MainWindow", "zamkni\304\231cie", nullptr));
        zaladuj->setText(QApplication::translate("MainWindow", "zaladuj zdjecie", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
