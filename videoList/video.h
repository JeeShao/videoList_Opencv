#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

class Video
{
public:				   //��Ա����
	Mat frame;
	VideoCapture cap;
public:
	Video();
	~Video();
public:				  //��Ա����
	Mat getYCrCbFrame();
	//vector<Mat>	images;

private:
	Mat readCap();
	void releaseCap();
};


