#include "iostream"
#include "opencv.hpp"
#include "string"

using namespace cv;
using namespace std;

int main()
{
    Mat frame;
//    VideoCapture cap("/home/daibingh/qt-pro/装甲视频/RedCar.avi", 0);
//    int num = 0;
//    if (!cap.isOpened())
//    {
//        cout<<"not open cap!"<<endl;
//        exit(1);
//    }
//    while (cap.read(frame))
//    {
//        imshow("window", frame);
//        uchar key = waitKey(50);
//        if (key == (uchar)27)
//        {
//            cap.release();
//            break;
//        }
//        else if (key == 's')
//        {
//            cout<<"hhhh"<<endl;
//            imwrite("/home/daibingh/qtpro/test_opencv/test_opencv/"+to_string(num)+".png", frame);
//            num ++;
//        }
//    }


    string path = "/home/daibingh/qt-pro/test_opencv/test_opencv";
    string file = path + "/3.png";

    // threshold
    Mat img_th;
    Mat img = imread(file, IMREAD_GRAYSCALE);
    imshow("origin", img);
//    threshold(img, img_th, 200,255,THRESH_BINARY);
    imshow("threshold", img_th);

    waitKey(0);



    // 1 滤波测试
//    string path = "/home/daibingh/qt-pro/test_opencv/test_opencv";
//    string file = path + "/0.png";
//    Mat img, img1, img_blur, img2;
//    img = cv::imread(file, -1);
//    img.copyTo(img2);
//    img1 = img;
//    imshow("origin", img);
//    GaussianBlur(img, img2, Size(3,3), 200, 200);
////    imshow("blur", img_blur);
//    imshow("img1", img1);
//    imshow("img2", img2);
//    waitKey(0);


//    // 2 截取图像
//    const string file = "/home/daibingh/software/opencv331/opencv-3.3.1/samples/data/lena.jpg";
//    Mat img = imread(file, -1);
//    float x_ctr = img.cols/2.0;
//    float y_ctr = img.rows/2.0;
//    float r = 150.0;
//    Mat mask = Mat::zeros(img.rows, img.cols, CV_8UC1);
//    Mat img2;
//    circle(mask, Point(img.cols/2, img.rows/2), 150, Scalar(255),-1);
//    img.copyTo(img2, mask);
//    imshow("aaa", img2);
//    waitKey(0);

    return 0;
}
