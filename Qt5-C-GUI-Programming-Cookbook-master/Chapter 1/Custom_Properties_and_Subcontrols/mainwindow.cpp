#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadStyle(tr("/home/daibingh/qt-pro/Qt5-C-GUI-Programming-Cookbook-master/Chapter\ 1/Custom_Properties_and_Subcontrols/Custom_Properties_Subcontrols-build/style.css"));
    ui->button1->setProperty("pagematches", true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadStyle(const QString& file)
{
    QFile qss(file);
    qss.open(QFile::ReadOnly);
    if(!qss.isOpen())
    {
        qDebug()<<"file not open!";
        return;
    }
    qApp->setStyleSheet(qss.readAll());
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    // Set all buttons to false
    ui->button1->setProperty("pagematches", false);
    ui->button2->setProperty("pagematches", false);
    ui->button3->setProperty("pagematches", false);

    // Set one of the buttons to true
    if (index == 0)
        ui->button1->setProperty("pagematches", true);
    else if (index == 1)
        ui->button2->setProperty("pagematches", true);
    else
        ui->button3->setProperty("pagematches", true);

    // Update buttons style
    ui->button1->style()->polish(ui->button1);
    ui->button2->style()->polish(ui->button2);
    ui->button3->style()->polish(ui->button3);
}
