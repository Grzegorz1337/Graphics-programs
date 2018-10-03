#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->a, SIGNAL(clicked()), ui->widget, SLOT(dodajzmienionypunkt()));
    connect(ui->d, SIGNAL(clicked()), ui->widget, SLOT(usunzmienionypunkt()));
    connect(ui->m, SIGNAL(clicked()), ui->widget, SLOT(przesunzmienionypunkt()));
    connect(ui->fa, SIGNAL(clicked()), ui->widget, SLOT(floodmode()));
    connect(ui->sc, SIGNAL(clicked()), ui->widget, SLOT(scanmode()));
    connect(ui->erozja, SIGNAL(clicked()), ui->widget, SLOT(erozjamode()));
    connect(ui->dylacja, SIGNAL(clicked()), ui->widget, SLOT(dylacjamode()));
    connect(ui->otwarcie, SIGNAL(clicked()), ui->widget, SLOT(otwarciemode()));
    connect(ui->zamkniecie, SIGNAL(clicked()), ui->widget, SLOT(zamknieciemode()));
    connect(ui->zaladuj, SIGNAL(clicked()), ui->widget, SLOT(imgmode()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
