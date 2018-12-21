#include "opencv.hpp"
#include "ctime"
#include "math.h"
#include "fstream"
#include "iostream"
#include "string"

#define RED 0
#define BLUE 1
#define PI 3.14159265
#define DEBUG

using namespace std;
using namespace cv;

Mat histeq(Mat in);
Mat getBinaryImg1(Mat src, int flags);
Mat getBinaryImg2(Mat src, int flags);
string getTime();
vector<RotatedRect>  findLed(Mat src);
vector<RotatedRect> findLed2(Mat src);
Mat getBinaryImg3(Mat src, int flags);
vector<RotatedRect> getBinary_LED(Mat src, int flags);
void drawRect(Mat src, RotatedRect rect, Scalar scalar = Scalar(255,0,0));
RotatedRect adjustRect(RotatedRect rect);
vector<RotatedRect> findTarget(vector<RotatedRect> rects);
vector<string> getList(const string file);
void getMean(Mat src, vector<float>& mean);
Rect getSafeRect(Rect rect, Mat img);
int saveImg(Mat src, string path = ".\\", string strEx = "");
template <typename T>
int saveText(const string file, vector<T>& data);
template <typename T>
int saveText(const string file, vector<vector<T> >& data);
int cacDmean(Mat src1, Mat src2, Rect r);
float findMaxDmean(Mat src1, Mat src2, Rect r);
int loadsvmparams(const string file, Mat& w, Mat&b);
bool isRed(Mat data, Mat w, Mat b);
RotatedRect chooseTarget(vector<RotatedRect> targets);

//vector<float> data;
vector<vector<float> > multiData;
vector<Mat> pic;
Mat curr_frame;
Mat w, b;

int main()
{
    Mat frame;
    string file = "/home/daibingh/qt-pro/装甲视频/RedCar.avi";
//    string file = "/home/daibingh/qt-pro/装甲视频/BlueCar.avi";
    VideoCapture cap(file);
    if (!cap.isOpened())
    {
        exit(-1);
    }

    while (cap.read(frame))
    {

        vector<RotatedRect> rects;
        rects = getBinary_LED(frame, RED);
        vector<RotatedRect> targets = findTarget(rects);
        RotatedRect target = chooseTarget(targets);
        drawRect(frame, target);
        imshow("result", frame);
        int sec = 0;

        sec = 50;
        char key = waitKey(sec);
        if (key == 27)
        {
            break;
        }

    }
    return 0;
}

//二值化方案1：高斯滤波->通道分离->两通道相减->sobel边缘提取->阈值（二值化）
Mat getBinaryImg1(Mat src, int flags)
{
    Mat src_blur, enemy, enemy_eq, src_g_eq, dst;
    GaussianBlur(src, src_blur, Size(5,5), 0, 0);
    Mat src_bgr[3];
    split(src_blur, src_bgr);
    if (flags == RED)
    {
        enemy = src_bgr[2];
    }
    else
    {
        enemy = src_bgr[0];
    }
    Mat subImg = enemy - src_bgr[1];
    Mat img_sobel_x, img_sobel_y, img_sobel;
    Sobel(subImg, img_sobel_x, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);
    Sobel(subImg, img_sobel_y, CV_8U, 0, 1, 3, 1, 0, BORDER_DEFAULT);
    img_sobel = 0.5*img_sobel_x + 0.5*img_sobel_y;
//	imwrite(getTime()+".png",subImg);
    //convertScaleAbs(img_sobel, img_sobel1);
    threshold(img_sobel, dst, 35, 255, THRESH_BINARY);
    return dst;
}

//二值化方案2：高斯滤波->亮度调整->通道分离->两通道相减->阈值化（二值化）效果较好
Mat getBinaryImg2(Mat src, int flags)
{
    Mat src_blur, src_eq, enemy, dst;
    GaussianBlur(src, src_blur, Size(5,5),0,0);
    Mat src_blur_an = src_blur - Scalar(120,120,120);
    Mat src_bgr[3];
    split(src_blur_an, src_bgr);
    if (flags == RED)
    {
        enemy = src_bgr[2];
    }
    else
    {
        enemy = src_bgr[0];
    }
    Mat subImg = enemy - src_bgr[1];
    //imwrite(getTime() + ".png", subImg);
    threshold(subImg, dst, 15, 255, THRESH_BINARY);
    return dst;
}

//二值化方案3：高斯滤波->通道分离->两通道相减->laplacian边缘提取->阈值（二值化）
Mat getBinaryImg3(Mat src, int flags)
{

    Mat src_blur, enemy, enemy_eq, src_g_eq, dst;
    GaussianBlur(src, src_blur, Size(5, 5), 0, 0);
    Mat src_bgr[3];
    split(src_blur, src_bgr);
    if (flags == RED)
    {
        enemy = src_bgr[2];
    }
    else
    {
        enemy = src_bgr[0];
    }
    Mat subImg = enemy - src_bgr[1];
    Mat img_lap, img_lap1;
    Laplacian(subImg, img_lap, CV_16S, 3);
    convertScaleAbs(img_lap, img_lap1);
    //	imwrite(getTime()+".png",subImg);
    //convertScaleAbs(img_sobel, img_sobel1);
    threshold(img_lap1, dst, 20, 255, THRESH_BINARY);
    return dst;
}

//二值化和检测灯柱一块完成，利用目标颜色通道二值化->提取up-right矩形->利用两个通道在矩形内灰度平均值之差验证红蓝
vector<RotatedRect> getBinary_LED(Mat src, int flags)
{

    Mat src_blur, enemy, enemy_eq, enemy_bin;
    Mat temp, temp2, temp3;
    vector<vector<Point> > contours;
    vector<RotatedRect> rects;
    RotatedRect rect, rect1;
    GaussianBlur(src,src_blur,Size(5,5),0,0);

    curr_frame = src_blur;

    Mat src_bgr[3];
    split(src_blur, src_bgr);
    if (flags == RED)
    {
        enemy = src_bgr[2] - src_bgr[1];
    }
    else
    {
        enemy = src_bgr[0] - src_bgr[1];
    }
    //imwrite(getTime() + ".png", enemy);
//    equalizeHist(enemy, enemy_eq);
    //saveImg(enemy_eq, "红色通道均衡");
    threshold(enemy, enemy_bin, 25, 255, THRESH_BINARY);
#ifdef DEBUG
    imshow("threshold_250", enemy_bin);
#endif
//    Mat ele = getStructuringElement(MORPH_RECT, Size(5, 5));
//    morphologyEx(enemy_bin, enemy_bin2, CV_MOP_OPEN, ele);
    enemy_bin.copyTo(temp2);
    cvtColor(temp2, temp, COLOR_GRAY2BGR);
    temp.copyTo(temp3);
    findContours(enemy_bin, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    drawContours(temp3, contours, -1, Scalar(0, 0, 255), 1);
    for (int i = 0; i < contours.size(); i++)
    {
        int isize = contours[i].size();
        if (isize > 8)
        {
            rect1 = minAreaRect(contours[i]);
            rect = adjustRect(rect1);
            drawRect(temp, rect, Scalar(0, 255, 0));
            if ((abs(rect.angle) < 15 || 180 - abs(rect.angle) < 15) && rect.size.height / rect.size.width > 1.2)
            {
                drawRect(temp, rect, Scalar(0,0,255));
                rects.push_back(rect);
                drawRect(temp, rect);
            }

        }
    }
    return rects;
}

void getMean(Mat src, vector<float>& mean)
{
    vector<float> sum(3,0.0);
        for (int i = 0; i < src.rows; i++)
        {
            Vec3b* p = src.ptr<Vec3b>(i);
            for (int j = 0; j < src.cols; j++)
            {
                for (int k = 0; k < src.channels(); k++)
                {
                    sum[k] += p[j][k];
                }
            }
        }
        sum[0] /= src.rows*src.cols;
        sum[1] /= src.rows*src.cols;
        sum[2] /= src.rows*src.cols;
        mean = sum;
}

//string getTime()
//{
//    struct tm t;   //tm结构变量
//    time_t now;  //声明time_t类型变量
//    time(&now);      //获取系统日期和时间
//    localtime_s(&t, &now);   //获取当地日期和时间

//    char buf[1024];
//    //strftime(buf, sizeof(buf), "%c", &t);
//    sprintf_s(buf,"%d_%d_%d",t.tm_hour,t.tm_min,t.tm_sec);
//    string str = buf;
//    return str;
//}

vector<RotatedRect> findLed(Mat src)
{
    Mat src_closed, src1;
    /*Mat ele_small = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(src, src1, CV_MOP_OPEN, ele_small, Point(-1,-1), 1);*/

    Mat ele = getStructuringElement(MORPH_RECT, Size(3, 7));
    morphologyEx(src, src_closed, CV_MOP_CLOSE, ele,Point(-1,-1), 2);
    /*Mat src_dl, src_er;
    dilate(src, src_dl, ele1);
    erode(src_dl, src_er, ele2);*/
    Mat temp;
    cvtColor(src_closed, temp, COLOR_GRAY2BGR);
    vector<vector<Point> > contours;
    findContours(src_closed, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //drawContours(temp, contours, -1, Scalar(0, 0, 255), 1);
    vector<RotatedRect> ledRect;

    for (int i = 0; i < contours.size(); i++)
    {
        if (contours[i].size() > 15)
        {
            RotatedRect rect;
            RotatedRect rect1 = minAreaRect(contours[i]);
            rect = adjustRect(rect1);
            drawRect(temp, rect,Scalar(0,0,255));
            if ((abs(rect.angle) < 15 || 180 - abs(rect.angle) < 15) && rect.size.height / rect.size.width > 1.2 )
            {
                ledRect.push_back(rect);
                drawRect(temp, rect);
            }
        }

    }
    return ledRect;
}

vector<RotatedRect> findLed2(Mat src)
{
    Mat src_closed, src1;
    /*Mat ele_small = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(src, src1, CV_MOP_OPEN, ele_small, Point(-1,-1), 1);*/

    Mat ele = getStructuringElement(MORPH_RECT, Size(1, 7));
    morphologyEx(src, src_closed, CV_MOP_CLOSE, ele, Point(-1, -1), 2);
    /*Mat src_dl, src_er;
    dilate(src, src_dl, ele1);
    erode(src_dl, src_er, ele2);*/
    Mat temp;
    cvtColor(src_closed, temp, COLOR_GRAY2BGR);
    vector<vector<Point> > contours;
    findContours(src_closed, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    //drawContours(temp, contours, -1, Scalar(0, 0, 255), 1);
    vector<RotatedRect> ledRect;

    for (int i = 0; i < contours.size(); i++)
    {
        if (contours[i].size() > 15)
        {
            RotatedRect rect;
            RotatedRect rect1 = minAreaRect(contours[i]);
            rect = adjustRect(rect1);
            drawRect(temp, rect, Scalar(0, 0, 255));
            if ((abs(rect.angle) < 15 || 180 - abs(rect.angle) < 15) && rect.size.height / rect.size.width > 1.2)
            {
                ledRect.push_back(rect);
                drawRect(temp, rect);
            }
        }

    }
    return ledRect;
}



void drawRect(Mat src, RotatedRect rect, Scalar scalar)
{
    if (rect.size.width < 0.1)
    {
        return;
    }
    Point2f pt[4];
    rect.points(pt);
    for (int i = 0; i < 4; i++)
    {
        line(src, pt[0], pt[1], scalar, 2);
        line(src, pt[1], pt[2], scalar, 2);
        line(src, pt[2], pt[3], scalar, 2);
        line(src, pt[3], pt[0], scalar, 2);
    }
}

RotatedRect adjustRect(RotatedRect rect)
{
    const Size2f & s = rect.size;
    if (s.width < s.height)
        return rect;
    return RotatedRect(rect.center, Size2f(s.height, s.width), rect.angle + 90.0);

}

vector<RotatedRect> findTarget(vector<RotatedRect> rects)
{
    vector<RotatedRect> targets;
    if (rects.size() >1 )
    {

    for (int i = 0; i < rects.size()-1; i++)
    {
        for (int j = i+1; j < rects.size(); j++)
        {
            float dAngle = abs(rects[i].angle - rects[j].angle);
            if (dAngle < 15)
            {
                float angle1 = atan(abs(rects[i].center.y - rects[j].center.y) / abs(rects[i].center.x - rects[j].center.x)) * 180 / PI;
                if (angle1 < 15)
                {
                    if (abs(rects[i].size.height / rects[j].size.height - 1) < 0.8)
                    {
                        float w = sqrt((rects[i].center.x - rects[j].center.x)*(rects[i].center.x - rects[j].center.x) + (rects[i].center.y - rects[j].center.y)*(rects[i].center.y - rects[j].center.y));
                        float h = (rects[i].size.height + rects[j].size.height) / 2;
                        float angle = (rects[i].angle + rects[j].angle) / 2;
                        if (w / h > 1.2 && w / h < 5)
                        {
                            float center_x = (rects[i].center.x + rects[j].center.x) / 2;
                            float center_y = (rects[i].center.y + rects[j].center.y) / 2;
                            RotatedRect target = RotatedRect(Point2f(center_x, center_y), Size2f(w, h), angle);
                            targets.push_back(target);
                        }
                    }
                }
            }
        }
    }
    }
    return targets;
}

vector<string> getList(char* file)
{
    vector<string> list;
    ifstream ifs(file);
    if (!ifs.is_open())
    {
        cerr << "read error" << endl;
    }
    string name;
    while (ifs.good())
    {
        getline(ifs, name);
        list.push_back(name);
    }
    return list;
}

Rect getSafeRect(Rect rect, Mat img)
{
    int img_width = img.cols;
    int img_height = img.rows;
    int w, h;
    if (rect.x < 0)
    {
        rect.x = 0;
    }
    if (rect.y < 0)
    {
        rect.y = 0;
    }
    if (w = img_width - rect.x < rect.width)
    {
        rect.width = w;
    }
    if (h = img_height - rect.y < rect.height)
    {
        rect.height = h;
    }
    return rect;
}

//int saveImg(Mat src, string path, string strEx)
//{
//    static int num = 0;
//    string name = path + getTime() + "_" + to_string(num) + strEx + ".png";
//    imwrite(name, src);
//    return ++ num;
//}

template <typename T>
int saveText(const string file, vector<T>& data)
{
    ofstream ofs(file, ios_base::out);
    if (!ofs.is_open())
    {
        cerr << "file is not opened!" << endl;
        exit(-1);
    }
    for (int i = 0; i < data.size()-1; i++)
    {
        ofs << data[i];
        ofs << "\n";
    }
    ofs << data[data.size() - 1];
    ofs.close();
    return 0;
}

template <typename T>
int saveText(const string file, vector<vector<T> >& data)
{
    if (data.size() == 0)
    {
        return -1;
    }
    int rows = data.size();
    int cols = data[0].size();
    ofstream ofs(file, ios_base::out);
    if (!ofs.is_open())
    {
        cerr << "file is not opened!" << endl;
        exit(-1);
    }
    for (int i = 0; i < rows - 1; i++)
    {
        for (int j = 0; j < cols-1; j++)
        {
            ofs << data[i][j] << "\t";
        }
        ofs << data[i][cols - 1] << "\n";
    }
    for (int j = 0; j < cols - 1; j++)
    {
        ofs << data[rows-1][j] << "\t";
    }
    ofs << data[rows - 1][cols-1];
    ofs.close();
    return 0;
}

int loadsvmparams(const string file, Mat& w, Mat& b)
{
    FileStorage fs(file, FileStorage::READ);
    if (!fs.isOpened())
    {
        cerr << "load svm params error" << endl;
        return -1;
    }
    fs["w"] >> w;
    fs["b"] >> b;
    fs.release();
    return 0;
}

bool isRed(Mat data, Mat w, Mat b)
{
    Mat mf;
    double f;
    mf = w*data.t() + b;
    f = mf.at<double>(0,0);
    return (f > 0);

}

RotatedRect chooseTarget(vector<RotatedRect> targets)
{
    if (targets.size() < 1)
    {
        return RotatedRect();
    }
    return targets[0];
}

//int cacDmean(Mat src1, Mat src2, Rect r)
//{
//	static int count = 0;
//	vector<float> dmean;
//	float d = 0.0;
//	for (int i = 0; i < 50; i++)
//	{
//		r = getSafeRect(r, src1);
//		d = getMean(Mat(src1, r)) - getMean(Mat(src2, r));
//		dmean.push_back(d);
//		r.x = r.x - 1;
//		r.y = r.y - 1;
//		r.width = r.width + 1;
//		r.height = r.height + 1;
//	}
//	string file = "dmeanChange_" + to_string(count) + ".txt";
//	saveText(file, dmean);
//	return ++ count;
//}

//float findMaxDmean(Mat src1, Mat src2, Rect r)
//{
//	Mat temp, temp1;
//	int x_max_expand = 6;
//	int y_max_expand = 8;
//	float d = 0.0, dmax = 0.0;
//	r = getSafeRect(r, src1);
//
//	Rect r1 = r;
//	temp1 = Mat(curr_frame, r);
//
//	int w_max = r.width, h_max = r.height, x_max = r.x, y_max = r.y;
//	dmax = getMean(Mat(src1, r)) - getMean(Mat(src2, r));
//	if (dmax > 1.0)
//	{
//		for (int i = 0; i < x_max_expand; i++)
//		{
//			r.width = r.width + 1;
//			r = getSafeRect(r, src1);
//			d = getMean(Mat(src1, r)) - getMean(Mat(src2, r));
//			if (d > dmax)
//			{
//				dmax = d;
//				w_max = r.width;
//			}
//		}
//		r.width = w_max;
//		for (int i = 0; i < x_max_expand; i++)
//		{
//			r.x = r.x - 1;
//			r.width = r.width + 1;
//			r = getSafeRect(r, src1);
//			d = getMean(Mat(src1, r)) - getMean(Mat(src2, r));
//			if (d > dmax)
//			{
//				dmax = d;
//				x_max = r.x;
//			}
//		}
//		r.x = x_max;
//
//		for (int i = 0; i < y_max_expand; i++)
//		{
//			r.height = r.height + 1;
//			r = getSafeRect(r, src1);
//			d = getMean(Mat(src1, r)) - getMean(Mat(src2, r));
//			if (d > dmax)
//			{
//				dmax = d;
//				h_max = r.height;
//			}
//		}
//		r.height = h_max;
//
//		for (int i = 0; i < y_max_expand; i++)
//		{
//			r.y = r.y - 1;
//			r.height = r.height + 1;
//			r = getSafeRect(r, src1);
//			d = getMean(Mat(src1, r)) - getMean(Mat(src2, r));
//			if (d > dmax)
//			{
//				dmax = d;
//				y_max = r.y;
//			}
//		}
//		r.y = y_max;
//		temp = Mat(curr_frame, r);
//#ifdef  SAVEDATA
//		saveImg(temp, "矩形区域\\");
//		data.push_back(dmax);
//#endif
//
//	}
//
//	return dmax;
//}
