#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class Decision
{
public:
	Mat bgImg;//±³¾°Í¼Æ¬

public:
	Decision(Mat frame0);
	~Decision();
	Mat toBgrImg();  //Éú³É±³¾°Í¼Æ¬   return ±³¾°Í¼Æ¬
	int decision();//ÅÐ¶¨Ëã·¨  return »ð»¨Ö¡µãÊý
	void setFrame(Mat img);
	void set2img(Mat img1, Mat img2);
private:
	Mat img1;
	Mat img2;
	Mat frame;
	int cbMean;

};