#include "stdafx.h"
#include "ArmorDetector.h"

#define PI 3.14159265


ArmorDetector::ArmorDetector(int color)
{
	init(color);
}

ArmorDetector::ArmorDetector()
{

}


ArmorDetector::~ArmorDetector()
{	
	m_frame.release();
	m_bin.release();
	m_enemy.release();
	m_subed.release();
	m_blur.release();
	targets.clear();
	scores.clear();
	temp_scores.clear();
}

void ArmorDetector::init(int color)
{
	this->m_color = color;
	if (color == RED)
	{
		
	}
	else
	{
		
	}
}

void ArmorDetector::initDetect()
{
	this->targets.clear();
	this->scores.clear();
	this->temp_scores.clear();
}

RotatedRect ArmorDetector::getTarget(Mat frame)
{
	initDetect();
	vector<RotatedRect> rrects = this->findLed(frame);
	this->findTarget(rrects);
	RotatedRect target = chooseTarget();
	return target;
}

RotatedRect ArmorDetector::chooseTarget()
{
	RotatedRect target;
	if (targets.size() == 0)
	{
		return RotatedRect();
	}
	else
	{
		float maxScore = 0.0f;
		int maxIndex = 0;
		for (int i = 0; i < scores.size(); i++)
		{
			if (scores[i] > maxScore)
			{
				maxIndex = i;
				maxScore = scores[i];
			}
		}
		target = targets[maxIndex];
	}
	return target;
}

vector<RotatedRect> ArmorDetector::findLed(Mat src)
{
	Mat enemy_eq;
	float dmean;
	Mat temp, temp2, temp3, rect_enemy, rect_subed;
	vector<vector<Point> > contours;
	vector<RotatedRect> rrects;
	RotatedRect rrect, rrect1;
	GaussianBlur(src, m_blur, Size(m_gaussRadius, m_gaussRadius), 0, 0);

	Mat src_bgr[3];
	split(m_blur, src_bgr);
	if (m_color == RED)
	{
		m_enemy = src_bgr[2];
		m_subed = src_bgr[1];
	}
	else
	{
		m_enemy = src_bgr[0];
		m_subed = src_bgr[2];
	}
	//imwrite(getTime() + ".png", enemy);
	equalizeHist(m_enemy, enemy_eq);
	//saveImg(enemy_eq, "红色通道均衡");
	threshold(enemy_eq, m_bin, m_binTh, 255, THRESH_BINARY);
	//Mat ele = getStructuringElement(MORPH_RECT, Size(5, 5));
	//morphologyEx(enemy_bin, enemy_bin2, CV_MOP_OPEN, ele);
	m_bin.copyTo(temp2);
	cvtColor(temp2, temp, COLOR_GRAY2BGR);
	temp.copyTo(temp3);
	findContours(m_bin, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	drawContours(temp3, contours, -1, Scalar(0, 0, 255), 1);
	for (int i = 0; i < contours.size(); i++)
	{
		int isize = contours[i].size();
		if (isize > m_contoursTh)
		{
			rrect1 = minAreaRect(contours[i]);
			rrect = adjustRect(rrect1);
			drawRect(temp, rrect, Scalar(0, 255, 0));
			if ((abs(rrect.angle) < m_inAngleTh || 180 - abs(rrect.angle) < m_inAngleTh) && rrect.size.height / rrect.size.width > m_ledAspectTh)
			{
				drawRect(temp, rrect, Scalar(0, 0, 255));
				Rect rect = rrect.boundingRect();

				rect = getSafeRect(rect, src);
				rect_enemy = Mat(m_enemy, rect);
				rect_subed = Mat(m_subed, rect);
				float dmean = cacMean(rect_enemy) - cacMean(rect_subed);

			//	dmean = findMaxDmean(m_enemy, m_green, rect);
				if (dmean > m_dMeanTh)
				{
					rrects.push_back(rrect);
					drawRect(temp, rrect);
					this->temp_scores.push_back(dmean);
					/*cacDmean(enemy, src_bgr[1], zRect);
					saveImg(temp, "检测出的矩形");*/
					/*saveImg(rect_enemy, "红");
					saveImg(rect_g, "绿");
					data.push_back(dmean);*/
				}

			}

		}
	}
	return rrects;
}

void ArmorDetector::drawRect(Mat src, RotatedRect rrect, Scalar scalar)
{
	if (rrect.size.width < 0.1)
	{
		return;
	}
	Point2f pt[4];
	rrect.points(pt);
	for (int i = 0; i < 4; i++)
	{
		line(src, pt[0], pt[1], scalar, 2);
		line(src, pt[1], pt[2], scalar, 2);
		line(src, pt[2], pt[3], scalar, 2);
		line(src, pt[3], pt[0], scalar, 2);
	}
}

void ArmorDetector::findTarget(vector<RotatedRect> rrects)
{
	//vector<RotatedRect> targets;
	float score = 0.0;
	if (rrects.size() >1)
	{

		for (int i = 0; i < rrects.size() - 1; i++)
		{
			for (int j = i + 1; j < rrects.size(); j++)
			{
				float inAngle = abs(rrects[i].angle - rrects[j].angle);
				if (inAngle < m_inAngleTh)
				{
					float dAngle = atan(abs(rrects[i].center.y - rrects[j].center.y) / abs(rrects[i].center.x - rrects[j].center.x)) * 180 / PI;
					if (dAngle < m_dAngleTh)
					{
						if (abs(rrects[i].size.height / rrects[j].size.height - 1) < m_hRatioTh)
						{
							float w = sqrt((rrects[i].center.x - rrects[j].center.x)*(rrects[i].center.x - rrects[j].center.x) + (rrects[i].center.y - rrects[j].center.y)*(rrects[i].center.y - rrects[j].center.y));
							float h = (rrects[i].size.height + rrects[j].size.height) / 2;
							float angle = (rrects[i].angle + rrects[j].angle) / 2;
							if (w / h > m_aspectMinTh && w / h < m_aspectMaxTh)
							{
								float center_x = (rrects[i].center.x + rrects[j].center.x) / 2;
								float center_y = (rrects[i].center.y + rrects[j].center.y) / 2;
								RotatedRect target = RotatedRect(Point2f(center_x, center_y), Size2f(w, h), angle);
								this->targets.push_back(target);
								score = (temp_scores[i] + temp_scores[j]) / 2;
								this->scores.push_back(score);
							}
						}
					}
				}
			}
		}
	}
}

RotatedRect ArmorDetector::adjustRect(RotatedRect rrect)
{
	const Size2f & s = rrect.size;
	if (s.width < s.height)
		return rrect;
	return RotatedRect(rrect.center, Size2f(s.height, s.width), rrect.angle + 90.0);

}

float ArmorDetector::cacMean(Mat src)
{
	float sum = 0.0;
	for (int i = 0; i < src.rows; i++)
	{
		uchar* puchar = src.ptr<uchar>(i);
		for (int j = 0; j < src.cols; j++)
		{
			sum += puchar[j];
		}
	}
	return sum / (src.rows*src.cols);
}

Rect ArmorDetector::getSafeRect(Rect rect, Mat img)
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

//float ArmorDetector::findMaxDmean(Mat src1, Mat src2, Rect r)
//{
//	float d = 0.0, dmax = 0.0;
//	r = getSafeRect(r, src1);
//
//	int w_max = r.width, h_max = r.height, x_max = r.x, y_max = r.y;
//	dmax = cacMean(Mat(src1, r)) - cacMean(Mat(src2, r));
//	if (dmax > 1.0)
//	{
//		for (int i = 0; i < m_xEx; i++)
//		{
//			r.width = r.width + 1;
//			r = getSafeRect(r, src1);
//			d = cacMean(Mat(src1, r)) - cacMean(Mat(src2, r));
//			if (d > dmax)
//			{
//				dmax = d;
//				w_max = r.width;
//			}
//		}
//		r.width = w_max;
//		for (int i = 0; i < m_xEx; i++)
//		{
//			r.x = r.x - 1;
//			r.width = r.width + 1;
//			r = getSafeRect(r, src1);
//			d = cacMean(Mat(src1, r)) - cacMean(Mat(src2, r));
//			if (d > dmax)
//			{
//				dmax = d;
//				x_max = r.x;
//			}
//		}
//		r.x = x_max;
//
//		for (int i = 0; i < m_yEx; i++)
//		{
//			r.height = r.height + 1;
//			r = getSafeRect(r, src1);
//			d = cacMean(Mat(src1, r)) - cacMean(Mat(src2, r));
//			if (d > dmax)
//			{
//				dmax = d;
//				h_max = r.height;
//			}
//		}
//		r.height = h_max;
//
//		for (int i = 0; i < m_yEx; i++)
//		{
//			r.y = r.y - 1;
//			r.height = r.height + 1;
//			r = getSafeRect(r, src1);
//			d = cacMean(Mat(src1, r)) - cacMean(Mat(src2, r));
//			if (d > dmax)
//			{
//				dmax = d;
//				y_max = r.y;
//			}
//		}
//		r.y = y_max;
//	}
//	return dmax;
//}