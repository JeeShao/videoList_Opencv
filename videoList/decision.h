#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class Decision
{
public:
	Mat bgImg;//����ͼƬ

public:
	Decision(Mat frame0);
	~Decision();
	Mat toBgrImg();  //���ɱ���ͼƬ   return ����ͼƬ
	int decision();//�ж��㷨  return ��֡����
	void setFrame(Mat img);
	void set2img(Mat img1, Mat img2);
private:
	Mat img1;
	Mat img2;
	Mat frame;
	int cbMean;

};