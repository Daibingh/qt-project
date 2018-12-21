 #include "imageprocess.h"
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QSize>
#include <QDebug>
#include <QSlider>
#include <QRegExp>
#include <QFile>
#include <QMessageBox>
//#include "opencv.hpp"


ImageProcess::ImageProcess(QWidget *parent) : QMainWindow(parent),
    ui(new Ui_MainWindow)
{
    ui->setupUi(this); 

    ui->label->setText(tr(""));
    ui->label_2->setText(tr(""));
    ui->horizontalSlider->setValue(0);
    ui->lineEdit->setText(QString::number(ui->horizontalSlider->value()));
    this->loadStylesheet(tr(":/qss/black.css"));

    // the button's clicked signal is already connected to the function by "connectSlotsByName(...)" in Ui_Mainwindow.h.
    // if you uncomment the line below, the slot function will act twice!
//    connect(ui->buttonLoadImg, &QPushButton::clicked, this, &ImageProcess::on_buttonLoadImg_clicked);
    connect(ui->horizontalSlider, &QSlider::valueChanged, [this](int value){ui->lineEdit->setText(QString::number(value));});

}

ImageProcess::~ImageProcess()
{
    delete ui;
}

int ImageProcess::loadStylesheet(const QString &file)
{
    QFile qss(file);
    qss.open(QFile::ReadOnly);
    if(!qss.isOpen())
    {
        return -1;
    }
    qApp->setStyleSheet(qss.readAll());
    qss.close();
    qDebug()<<"load successfull";
    return 0;
}

void ImageProcess::on_buttonLoadImg_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open a picture"), tr("."),
                                                  tr("Image Files (*.png *.jpg *.bmp)"));
    qDebug()<<fileName;
//    img->load(fileName);
    ui->label->setPixmap(QPixmap(fileName));
//    ui->label->resize(QSize(img->width(), img->height()));
}

void ImageProcess::on_horizontalSlider_valueChanged(int value)
{
    if (fileName == NULL)
    {
        ui->label_2->setText(tr("Please open an image first!"));
        ui->label->setText(tr("Please open an image first!"));
        return;
    }
    QString tempFileName("./.temp.png");
    img = cv::imread(fileName.toStdString(), cv::IMREAD_GRAYSCALE);
    cv::threshold(img, imgProc, value, 255, cv::THRESH_BINARY);
    cv::imwrite(tempFileName.toStdString(), imgProc);
    ui->label_2->setPixmap(QPixmap(tempFileName));
}

void ImageProcess::on_buttonSaveImg_clicked()
{
    QString saveFileName;
    QRegExp re("(.+)\\.(\\w{3,4})");
    if (re.indexIn(fileName) == -1)
    {
        qDebug()<<"parse file name failed!";
        return;
    }
    qDebug()<<re.cap(1);
    qDebug()<<re.cap(2);
    saveFileName = re.cap(1) + "_threshold_" + ui->lineEdit->text() + "." + re.cap(2);
    qDebug()<<"The processed image is saved in " + saveFileName;
    QMessageBox::information(this, tr("Image saved"), "The processed image is saved in " + saveFileName);
    cv::imwrite(saveFileName.toStdString(), imgProc);
}
