#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class Video
{
public:				   //成员变量
	Mat frame;
	VideoCapture cap;
public:
	Video();
	~Video();
public:				  //成员函数
	Mat getYCrCbFrame();
	//vector<Mat>	images;

private:
	Mat readCap();
	void releaseCap();
};


