#pragma once

#include "opencv.hpp"
#include "string"
#include "vector"
using namespace cv;
using namespace std;

class ArmorDetector
{
public:
	enum COLOR{RED=0, BLUE =1};

	ArmorDetector(int color = RED);
	ArmorDetector::ArmorDetector();
	~ArmorDetector();

	RotatedRect getTarget(Mat frame);
	vector<RotatedRect> findLed(Mat src);
	void drawRect(Mat src, RotatedRect rect, Scalar scalar = Scalar(255, 0, 0));
	RotatedRect adjustRect(RotatedRect rect);
	void findTarget(vector<RotatedRect> rects);
	RotatedRect chooseTarget();
//	float findMaxDmean(Mat src1, Mat src2, Rect r);
	float cacMean(Mat src);
	Rect getSafeRect(Rect rect, Mat img);
	void init(int color);
	void initDetect();

private:
	int m_color = RED;
	Mat m_frame;
	Mat m_blur;
	Mat m_enemy;
	Mat m_subed;
	Mat m_bin;

	vector<RotatedRect> targets;
	vector<float> scores;
	vector<float> temp_scores;
	RotatedRect target;


	int m_gaussRadius = 5;
	int m_binTh = 250;
	int m_contoursTh = 8;
	float m_ledAngleTh = 15.0f;
	float m_ledAspectTh = 1.2f;
	float m_dMeanTh = 1.5f;
	//int m_xEx = 10, m_yEx = 10;
	float m_inAngleTh = 15.0; //¼Ð½Ç
	float m_dAngleTh = 15.0; //Çã½Ç
	float m_hRatioTh = 0.8;
	float m_aspectMaxTh = 5.0;
	float m_aspectMinTh = 1.2;

};

