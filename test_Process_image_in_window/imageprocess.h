#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <QImage>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

class ImageProcess : public QMainWindow
{
    Q_OBJECT
public:
    explicit ImageProcess(QWidget *parent = 0);
    Ui_MainWindow* ui;
    ~ImageProcess();
    int loadStylesheet(const QString& file);

signals:

public slots:
    void on_buttonLoadImg_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_buttonSaveImg_clicked();

private:
    cv::Mat img, imgProc;
    QString fileName = NULL;
};

#endif // IMAGEPROCESS_H
