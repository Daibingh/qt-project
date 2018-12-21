#include "opencv.hpp"

using namespace std;
using namespace cv;

int main()
{
    Mat img;
    string file = "/home/daibingh/qt-pro/test_opencv/test_opencv/0.png";
    /***************************** threshold test *****************************/

    /*Mat img_otsu, img_tri, img_apt_mean, img_apt_gauss;
    double th_otsu, th_tri;
    string file = "/home/daibingh/qt-pro/test_opencv/test_opencv/0.png";
    img = imread(file, IMREAD_GRAYSCALE);
    imshow("origin", img);

    // OTSU THRESHOLD
    th_otsu = threshold(img, img_otsu, 0, 255, THRESH_OTSU);
    // TRUNC THRESHOLD
    th_tri = threshold(img, img_tri, 0, 255, THRESH_TRIANGLE);
    // adaptive threshold mean
    adaptiveThreshold(img, img_apt_mean, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 0);
    //adaptive threshold gaussian
    adaptiveT                                                                                                                                                hreshold(img, img_apt_gauss, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 0);

    imshow("otsu", img_otsu);
    imshow("trunc", img_tri);
    cout<<"th_otsu="<<th_otsu<<"   "<<"th_trunc="<<th_tri<<endl;

    imshow("apt-mean", img_apt_mean);
    imshow("apt_gaussian", img_apt_gauss);*/

    /**************************** smooth test *********************************/

    /*img = imread(file, cv::IMREAD_UNCHANGED);
    Mat img_blur_1, img_blur_2;
    Mat img_median;
    Mat img_gauss, kernel;
    Mat img_bl;
    // mean value filter
    blur(img, img_blur_1, Size(5,5), Point(-1,-1), cv::BORDER_CONSTANT);
    blur(img, img_blur_2, Size(5,5), Point(-1,-1), cv::BORDER_DEFAULT);
    // median value filter
    medianBlur(img, img_median, 5);
    // Gaussian blur
    GaussianBlur(img, img_gauss, Size(5,5), .5, .5);
    kernel = getGaussianKernel(5, .5);
    // bilateral filter
    bilateralFilter(img, img_bl, 5, .5, .5);

    imshow("origin", img);
//    imshow("blur_constant", img_blur_1);
    imshow("blur_default", img_blur_2);
    imshow("median", img_median);
    imshow("Gaussian", img_gauss);
    cout<<kernel<<endl;
    imshow("bilateral", img_bl);*/

    /******************************* image derivative *****************************/
//    Mat img_sobel_x, img_sobel_normal_x, img_sobel_y, img_sobel_normal_y;
//    img = imread(file, cv::IMREAD_GRAYSCALE);
//    // 3*3 sobel deriavtive along x axis
//    Sobel(img, img_sobel_x, CV_32F, 1, 0, 1);
//    // 3*3 sobel deriavtive along y axis
//    Sobel(img, img_sobel_y, CV_32F, 0, 1, 1);
//    normalize(cv::abs(img_sobel_x), img_sobel_normal_x, 0, 255, NORM_MINMAX, CV_8U);
//    normalize(cv::abs(img_sobel_y), img_sobel_normal_y, 0, 255, NORM_MINMAX, CV_8U);
//    imshow("sobel in x axis", img_sobel_normal_x);
//    imshow("sobel in y axis", img_sobel_normal_y);

    // get the sobel kernels
    /*Mat kernel_sobel_x, kernel_sobel_y;
    getDerivKernels(kernel_sobel_x, kernel_sobel_y, 1, 2, 7);
    cout<<"x kernel:"<<endl<<kernel_sobel_x<<endl;
    cout<<"y kernel:"<<endl<<kernel_sobel_y<<endl;*/

    // test laplacian
//    Mat img_lap, img_temp, img_temp2, img_temp3, img_sobel_x, img_sobel_y;
//    img = imread(file, cv::IMREAD_GRAYSCALE);
//    Sobel(img, img_sobel_x, CV_32F, 1, 0, 3);
//    Sobel(img, img_sobel_y, CV_32F, 0, 1, 3);
//    img_temp2 = cv::abs(img_sobel_x) + cv::abs(img_sobel_y);
//    normalize(img_temp2, img_temp3, 0, 255, NORM_MINMAX, CV_8U);
//    Laplacian(img, img_lap, CV_32F, 3);
//    normalize(cv::abs(img_lap), img_temp, 0, 255, NORM_MINMAX, CV_8U);


//    imshow("Laplacian", img_temp);
//    imshow("sobel_x + sobel_y", img_temp3); // compare direct Laplacian and the result of abs(sobel_x)+abs(sobel_y), find the later get clearier edges.

//    Mat img_temp3th;
//    threshold(img_temp3, img_temp3th, 100, 255, THRESH_BINARY);
//    imshow("sum(abs(sobel))", img_temp3th);

//    imwrite("sobel_abs_sum.png", img_temp3);
//    imwrite("laplacian.png", img_temp);

    Mat img_th, img_erode, img_dilate, img_grad, img_grad2;
    img = imread(file, IMREAD_GRAYSCALE);
    threshold(img, img_th, 200, 255, THRESH_BINARY);
//    morphologyEx(img_th, img_dilate, MORPH_DILATE, getStructuringElement(MORPH_RECT, Size(10,10)));
    dilate(img_th, img_dilate, getStructuringElement(MORPH_RECT, Size(10,10)));
//    morphologyEx(img_dilate, img_erode, MORPH_ERODE, getStructuringElement(MORPH_RECT, Size(10,10)));
    erode(img_th, img_erode, getStructuringElement(MORPH_RECT, Size(10,10)));
    morphologyEx(img_th, img_grad2, MORPH_GRADIENT, getStructuringElement(MORPH_RECT, Size(10,10)));
    img_grad = img_dilate - img_erode;

    imshow("grad", img_grad);
    imshow("grad_2", img_grad2);
    imshow("threshold", img_th);
    imshow("dilate", img_dilate);
    imshow("erode", img_erode);

    waitKey(0);
    return 0;
}
