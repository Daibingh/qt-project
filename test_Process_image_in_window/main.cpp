#include "iostream"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "QApplication"
#include "imageprocess.h"

using namespace cv;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    ImageProcess w;
    w.show();

    return app.exec();

}
