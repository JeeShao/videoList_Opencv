#pragma once
#include<iostream>
#include<thread>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class Decision
{
public:
	Mat bgImg;//±³¾°Í¼Æ¬



public:
	Decision();
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
	int cbMean1;
	int cbMean2;
	int cbMean3;
	int cbMean4;

	static int rowNumber;
	static int colNumber;

	void blockImg1(int rowNumber, int colNumber);
	void blockImg2(int rowNumber, int colNumber);
	void blockImg3(int rowNumber, int colNumber);
	void blockImg4(int rowNumber, int colNumber);

};