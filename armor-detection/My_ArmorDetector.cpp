// My_ArmorDetector.cpp : �������̨Ӧ�ó������ڵ㡣
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

	vector<string> list = getList("�����ͼƬ.txt");
	Mat frame;
#ifdef USEVIDEO
	string red_file = "E:\\VS2013\\Projects\\װ����Ƶ\\RedCar.avi";
	string blue_file = "E:\\VS2013\\Projects\\װ����Ƶ\\BlueCar.avi";
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


			frame = imread("�����ͼƬ\\" + list[k]);
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
			//	saveImg(frame, "©��\\");
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
