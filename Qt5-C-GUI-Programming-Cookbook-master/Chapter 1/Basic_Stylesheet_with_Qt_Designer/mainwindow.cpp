#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->loadStyle(tr("/home/daibingh/qt-pro/Qt5-C-GUI-Programming-Cookbook-master/Chapter 1/Basic_Stylesheet_with_Qt_Designer/Look_and_Feel_Customization-build/style.css"));
    ui->logo->setPixmap(QPixmap(tr(":images/logo.png")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadStyle(const QString &file)
{
    QFile qss(file);
    qss.open(QFile::ReadOnly);
    if(!qss.isOpen())
    {
        qDebug()<<"file not open";
        return;
    }
    qApp->setStyleSheet(qss.readAll());
    qss.close();
}
