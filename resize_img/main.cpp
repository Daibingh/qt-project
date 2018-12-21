#include <iostream>
#include <string>
#include "opencv.hpp"
using namespace  std;
using namespace cv;

int main()
{
    Mat img = imread("/home/daibingh/qt-pro/darknet/darknet-build/data/dog.jpg", -1);
//    imshow("a", img);
    cout<<img.size<<endl;
    vector<float> rr={.6,.5,.4,.3,.2,.1};
//    Mat img2;
//    resize(img,img2,Size(int(r*img.cols), int(r*img.rows)));
//    imshow("b", img2);
    string s ="/home/daibingh/qt-pro/darknet/darknet-build/data/dog";
    Mat imgt;
    for (int i=0; i<rr.size();i++)
    {
        resize(img,imgt,Size(int(rr[i]*img.cols), int(rr[i]*img.rows)));
        imwrite(s+ "-" + to_string(i) +".jpg", imgt);
    }
    waitKey(0);
    return 0;
}
