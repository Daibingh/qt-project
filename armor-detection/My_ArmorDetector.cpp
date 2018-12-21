// My_ArmorDetector.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "ArmorDetector.h"
#include "iostream"
#include "fstream"
#include "string"

#define USEVIDEO

vector<string> getList(const string file)
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

int main()
{
	ArmorDetector detector(ArmorDetector::RED);

	vector<string> list = getList("红典型图片.txt");
	Mat frame;
#ifdef USEVIDEO
	string red_file = "E:\\VS2013\\Projects\\装甲视频\\RedCar.avi";
	string blue_file = "E:\\VS2013\\Projects\\装甲视频\\BlueCar.avi";
	VideoCapture cap(red_file);
	
	if (!cap.isOpened())
	{
		exit(-1);
	}
#endif

#ifdef USEVIDEO
	while (cap.read(frame))
	{
#endif

#ifndef USEVIDEO
		int k = 0;
		while (k < list.size())
		{


			frame = imread("红典型图片\\" + list[k]);
			k++;
#endif
			RotatedRect rrect;

			rrect = detector.getTarget(frame);
			detector.drawRect(frame, rrect);
			imshow("a", frame);
			int sec = 0;
#ifdef USEVIDEO
			sec = 50;
#endif
			char key = waitKey(sec);
			if (key == 27)
			{
				break;
			}
			else if (key == 32)
			{
			//	saveImg(frame, "漏检\\");
			}
#ifndef USEVIDEO
		}
#endif

#ifdef USEVIDEO
	}
#endif
#ifdef  SAVEDATA
	saveText("dmean.txt", data);
#endif
	return 0;
}
